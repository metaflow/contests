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

h3 = soup.find_all('h3')
cases = []
input = ""
for h in h3:
    if h.string == 'Example Input':
        input = h.next_sibling.string
    if h.string == 'Example Output':
        cases.append([input, h.next_sibling.string])
if utils.save_cases(name, cases):
    utils.open_problem(name)
