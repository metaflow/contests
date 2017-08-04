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
if not host.endswith('kattis.com'):
    exit(1)
name = url.path.rstrip('/').split('/')[-1] # /problems/skiresort
with open(path, 'r') as myfile:
    info = json.loads(myfile.read().replace('\n', ''))
soup = BeautifulSoup(info['content'], 'lxml')

tables = soup.find_all('table', class_='sample')
cases = []
for t in tables:
    row = t.find_all('tr')[1]
    if not row:
        continue
    td = row.find('td')
    test_case = []
    test_case.append(td.find('pre').string)
    td = row.find_all('td')[1]
    test_case.append(td.find('pre').string)
    cases.append(test_case)

if utils.save_cases(name, cases):
    utils.open_problem(name)
