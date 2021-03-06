#!/usr/bin/env python

from bs4 import BeautifulSoup
from urllib.parse import urlsplit
import json
import sys
import utils

url = sys.argv[1]
path = sys.argv[2]

print(url)
url = urlsplit(url)
host = url.netloc
if not host.endswith('atcoder.jp'):
    exit(1)

if host.endswith('beta.atcoder.jp'):
    exit(1)

name = url.path[-1:] # /tasks/arc079_d -> d
print("name", name)
with open(path, 'r') as myfile:
    info = json.loads(myfile.read().replace('\n', ''))

soup = BeautifulSoup(info['content'], 'lxml')
divs = soup.find(id='task-statement') \
           .find('span', class_='lang-en') \
           .find_all('div', class_='div-sample-copy')
parts = []
for d in divs:
    parts.append(d.find_next_sibling('pre').string)

cases = zip(parts[0:][::2], parts[1:][::2])

if utils.save_cases(name, cases):
    utils.open_problem(name)
