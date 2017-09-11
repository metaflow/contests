#!/usr/bin/env python

from bs4 import BeautifulSoup
from urllib.parse import urlsplit
import json
import msvcrt
import os
import platform
import subprocess
import sys
import utils

url = sys.argv[1]
path = sys.argv[2]

url = urlsplit(url)
host = url.netloc
if host != 'csacademy.com':
    exit(1)
name = url.path.rstrip('/').split('/')[-1] # /contest/round-40/task/move-the-bishop/
with open(path, 'r') as myfile:
    info = json.loads(myfile.read().replace('\n', ''))
soup = BeautifulSoup(info['content'], 'lxml')

rows = soup.find('table', class_='table-65') \
           .find_all('tr')
cases = []
for row in rows:
    td = row.find('td')
    if not td:
        continue
    test_case = []
    test_case.append(td.find('pre').string)
    td = td.next_sibling
    test_case.append(td.find('pre').string)
    cases.append(test_case)

if utils.save_cases(name, cases):
    utils.open_problem(name)
