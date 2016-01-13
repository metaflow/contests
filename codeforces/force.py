#!/usr/bin/python
import time
import urllib
import urllib2
import hashlib
import json
import os
import argparse
import random
import webbrowser
import sqlite3
import subprocess
from bs4 import BeautifulSoup
from sets import Set

ApiKey = '714a0baaad6b2ea7d18e46363e9ba8583ec26e12'
ApiSecret = '837468f7d6dd95fb25821e344c5c99a11074146d'

parser = argparse.ArgumentParser(description='Ladder')
parser.add_argument('--random', action='store_true')
parser.add_argument('-s','--solved', help='# of user solved')
parser.add_argument('-r','--range', help='range - absolute or %', default='2%')

parser.add_argument('--open', help='open problem', action='store_true')
parser.add_argument('-c', '--contest', help='id of contest')
parser.add_argument('-p', '--problem', help='index of problem')

parser.add_argument('--experiment', action='store_true')

args = parser.parse_args()
# CREATE TABLE api_cache(url TEXT unique, response TEXT, updated INTEGER);
db = sqlite3.connect('codeforces.db')
db.text_factory = str

def params(values):
  params = values.items()
  params.sort()
  s = ''
  for p in params:
    a = p[0] + '=' + urllib.quote(str(p[1]))
    if s == '':
      s = '?' + a
    else:
      s = s + '&' + a
  return s

def api_call(method, values):
  url = 'http://codeforces.com/api/' + method
  key = url + params(values)
  print key
  cursor = db.cursor()
  cursor.execute('''SELECT response FROM api_cache WHERE url=?''', (key,))
  cached = cursor.fetchone()
  if not cached is None:
    print 'api call cached'
    return cached[0]
    # print 'cached', cached
  rand = '123456'
  values['apiKey'] = ApiKey
  values['time'] = int(time.time())
  hash = rand + '/' + method + params(values) + '#' + ApiSecret
  hash = hashlib.sha512(hash).hexdigest()
  while len(hash) < 128:
    hash = '0' + hash
  values['apiSig'] = rand + hash

  url += params(values)
  req = urllib2.Request(url)
  response = urllib2.urlopen(req)
  s = response.read()
  cursor.execute('''
    INSERT INTO api_cache(url, response, updated) VALUES (?,?,?)
    ''', (key, s, values['time']))
  db.commit()
  return s

def problemUrl(contestId, index):
  return 'http://codeforces.com/contest/%s/problem/%s' % \
         (contestId, index)

def openProblem(contestId, index):
  return
  url = problemUrl(contestId, index)
  webbrowser.open(url)
  if not os.path.exists(contestId):
    os.makedirs(contestId)
  os.chdir(contestId)
  if not os.path.exists(index + '.in') and \
     not os.path.exists(index + '.in.out'):
    with open(index + '.in', 'w') as in_file,\
         open(index + '.in.out', 'w') as out_file:
      html = urllib2.urlopen(url)
      soup = BeautifulSoup(html, 'lxml')
      inputs = soup.find_all('div', attrs = {'class': 'input'})
      outputs = soup.find_all('div', attrs = {'class': 'output'})
      samples = zip(inputs, outputs)
      for s in samples:
        for i in s[0].find('pre').strings:
          in_file.write(unicode(i).encode('utf-8').strip())
          in_file.write('\n')
        for i in s[1].find('pre').strings:
          out_file.write(unicode(i).encode('utf-8').strip())
          out_file.write('\n')
  subprocess.call(["problem", index])
  subprocess.call(["date"])
  return

# ------ main --------
if (args.experiment):
  problemset = json.loads(api_call('problemset.problems', {}))
  problems = problemset['result']['problems']
  stats = problemset['result']['problemStatistics']
  problems = zip(problems, stats)
  print len(problems), 'problems total'
  count = 10
  for p in problems:
    info = p[0]
    stats = p[1]
    if not 'points' in info:
      continue
    print p[0]
    print p[1]
    count -= 1
    if (count < 0):
      break
  exit(0)

if (args.open):
  openProblem(args.contest, args.problem)
  exit(0)

if (args.random):
  solved = int(args.solved)
  range = args.range
  if '%' in str(range):
    range = range[:range.find('%')]
    range = int(range) * solved / 100
  else:
    range = int(range)
  print 'searching for problem with %d +- %d solutions' % (solved, range)
  problemset = json.loads(api_call('problemset.problems', {}))
  problems = problemset['result']['problems']
  stats = problemset['result']['problemStatistics']
  problems = zip(problems, stats)

  matched = []
  alreadySolved = 0
  for p in problems:
    if (int(p[1]['solvedCount']) > int(solved) + int(range)) or \
       (int(p[1]['solvedCount']) < int(solved) - int(range)):
       continue
    if not os.path.exists("%s/%s.cc" % (p[0]['contestId'], p[0]['index'])):
      matched.append(p)
    else:
      alreadySolved += 1

  if len(matched) == 0:
    print 'nothing'
    exit(1)

  selected = matched[random.randint(0, len(matched) - 1)]
  print '%d matched (%d already solved). %s %s solved by %d' % (
    len(matched), alreadySolved,
    selected[0]['contestId'], selected[0]['index'], selected[1]['solvedCount'])

  openProblem(str(selected[0]['contestId']), str(selected[0]['index']))
  exit(0)
