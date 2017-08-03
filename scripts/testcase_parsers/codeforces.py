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

print(sys.argv)
url = sys.argv[1]
path = sys.argv[2]

url = urlsplit(url)
host = url.netloc
if host != 'codeforces.com' and host != 'codoforces.ru':
    exit(1)

name = url.path[-1:] # /codeforces/538/problem/A
with open(path, 'r') as myfile:
    info = json.loads(myfile.read().replace('\n', ''))
soup = BeautifulSoup(info['content'], 'lxml')
inputs = soup.find_all('div', attrs={'class': 'input'})
outputs = soup.find_all('div', attrs={'class': 'output'})
samples = zip(inputs, outputs)
cases = []
for s in samples:
    input_lines = []
    output_lines = []
    for i in s[0].find('pre').strings:
        input_lines.append(str(i).strip())
    for i in s[1].find('pre').strings:
        output_lines.append(str(i).strip())
    cases.append(('\n'.join(input_lines) + '\n', '\n'.join(output_lines) + '\n'))

if utils.save_cases(name, cases):
    subprocess.call(["C:\\Program Files\\Git\\bin\\bash.exe", '-c', '/c/Users/mgoncharov/etc/contests/problem.sh {}'.format(name)])
