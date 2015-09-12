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
import subprocess
from bs4 import BeautifulSoup

ApiKey = '714a0baaad6b2ea7d18e46363e9ba8583ec26e12'
ApiSecret = '837468f7d6dd95fb25821e344c5c99a11074146d'

parser = argparse.ArgumentParser(description='Ladder')
parser.add_argument('-s','--solved', help='# of user solved', required=True)
parser.add_argument('-r','--range', help='', required=False, default=50)
args = parser.parse_args()

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

def call(method, values):
  values['apiKey'] = ApiKey
  values['time'] = int(time.time())
  url = 'http://codeforces.com/api/' + method
  rand = '123456'
  hash = rand + '/' + method + params(values) + '#' + ApiSecret
  hash = hashlib.sha512(hash).hexdigest()
  while len(hash) < 128:
    hash = '0' + hash
  values['apiSig'] = rand + hash
  url += params(values)
  req = urllib2.Request(url)
  response = urllib2.urlopen(req)
  return response.read()

def problemUrl(contestId, index):
  return 'http://codeforces.com/contest/%s/problem/%s' % \
         (contestId, index)

def openProblem(contestId, index):
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
      print samples
      for s in samples:
        for i in s[0].find('pre').strings:
          in_file.write(i)
          in_file.write('\n')
        for i in s[1].find('pre').strings:
          out_file.write(i)
          out_file.write('\n')
  subprocess.call(["problem", index])
  return

problemset = json.loads(call('problemset.problems', {}))
problems = problemset['result']['problems']
stats = problemset['result']['problemStatistics']
problems = zip(problems, stats)

matched = []
for p in problems:
  if (int(p[1]['solvedCount']) > int(args.solved) + int(args.range)) or \
     (int(p[1]['solvedCount']) < int(args.solved) - int(args.range)):
     continue
  matched.append(p)

if len(matched) == 0:
  print 'nothing'
  exit(1)

selected = matched[random.randint(0, len(matched) - 1)]
print 'from %d: %d %d' % (
      len(matched), selected[1]['solvedCount'], selected[0]['points'])

openProblem(str(selected[0]['contestId']), str(selected[0]['index']))
