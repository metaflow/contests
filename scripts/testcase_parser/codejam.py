#!/usr/bin/env python

import sys
from urllib.parse import urlsplit
import json
import os
import msvcrt
from bs4 import BeautifulSoup
import platform
import subprocess
import utils
import re

url = sys.argv[1]
path = sys.argv[2]

url = urlsplit(url)
host = url.netloc
if host != 'code.google.com':
    exit(1)

# name = url.path[-1:] # /codeforces/538/problem/A
with open(path, 'r') as myfile:
    info = json.loads(myfile.read().replace('\n', ''))
soup = BeautifulSoup(info['content'], 'lxml')
name = soup.find(id='dsb-problem-title-div').getText()
name = re.sub(r'^Problem ', '', name)
name = name.replace('. ', '_').replace(' ', '_').lower()
active = soup.find('div', attrs={'class': 'dsb-content-pages'}, style=re.compile(r'display: *block'))
divs = active.find_all('pre', attrs={'class': 'io-content'})
input = divs[0].text
output = divs[1].text
cases = [(input, output)]
if utils.save_cases(name, cases):
    utils.open_problem(name)
