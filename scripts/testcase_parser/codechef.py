#!/usr/bin/env python

from bs4 import BeautifulSoup
from urllib.parse import urlsplit
import json
import sys
import utils

url = sys.argv[1]
path = sys.argv[2]

url = urlsplit(url)
host = url.netloc
if not host.endswith('codechef.com'):
    exit(1)
name = url.path.rstrip('/').split('/')[-1] # /AUG17/problems/RAINBOWA
with open(path, 'r') as myfile:
    info = json.loads(myfile.read().replace('\n', ''))
soup = BeautifulSoup(info['content'], 'lxml')

pre = soup.find('pre')
# print(pre.prettify())
b = pre.find('b')
cases = [[
    str(pre.find('b').next_sibling.string).strip(),
    str(pre.find_all('b')[1].next_sibling.string).strip()
]]
# print(cases)
if utils.save_cases(name, cases):
    utils.open_problem(name)
