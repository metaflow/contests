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

userId = '235842'

parser = argparse.ArgumentParser(description='Ladder')
parser.add_argument('--random', action='store_true')
parser.add_argument('-s','--solved', help='# of user solved')
parser.add_argument('-r','--range', help='range - absolute or %', default='5%')

args = parser.parse_args()

def call(method, values):
  url = 'http://uhunt.felix-halim.net/api/' + method + '/' + '/'.join(values)
  req = urllib2.Request(url)
  response = urllib2.urlopen(req)
  return response.read()

def tried(problem_id):
  submissions = json.loads(call('subs-pids', [userId, str(problem_id)]))
  return len(submissions[userId]['subs']) > 0

def printProblem(problem):
  print '#%d "%s"' % (problem['id'], problem['title'])
  print 'uAC %d AC %d%% WA %d%% TL %d%%' % (
    problem['dacu'],
    100 * problem['ac'] / problem['total'],
    100 * problem['wa'] / problem['total'],
    100 * problem['tl'] / problem['total'])

def problemUrl(problem_id):
  return 'https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=%s' % (problem_id)

def openProblem(problem):
  url = problemUrl(problem['id'])
  webbrowser.open(url)
  subprocess.call(["problem", str(problem['number'])])
  return

# --- main ---
solved = int(args.solved)
d = args.range
if '%' in str(d):
  d = d[:d.find('%')]
  d = int(d) * solved / 100
else:
  d = int(d)
print 'searching for problem with %d +- %d solutions' % (solved, d)

problems_json = json.loads(call('p', []))
problems = []
for problem_json in problems_json:
  total_sumbmissions = 0
  dacu = problem_json[3]
  if dacu < solved - d or dacu > solved + d:
    continue
  for i in range(10, 19):
    total_sumbmissions += int(problem_json[i])
  problem = {'id': problem_json[0],
             'number': problem_json[1],
             'title': problem_json[2],
             'dacu': problem_json[3],
             'total': total_sumbmissions,
             'ac': int(problem_json[18]),
             'tl': int(problem_json[14]),
             'wa': int(problem_json[16]),}
  problems.append(problem)

if not problems:
  print 'no problems in range'
  exit(0)

selected_problem = -1
while problems:
  i = random.randint(0, len(problems) - 1)
  # print 'checking #', i
  if tried(problems[i]['id']):
    # print 'already tried'
    problems.pop(i)
    continue
  selected_problem = i
  break

if selected_problem == -1:
  print 'no new problems in range'
  exit(0)

printProblem(problems[selected_problem])
openProblem(problems[selected_problem])


