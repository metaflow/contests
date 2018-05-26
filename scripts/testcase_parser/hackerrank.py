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
if not host.endswith('hackerrank.com'):
    exit(1)
name = url.path.rstrip('/').split('/')[-1] # /challenges/day-of-the-programmer
with open(path, 'r') as myfile:
    info = json.loads(myfile.read().replace('\n', ''))
soup = BeautifulSoup(info['content'], 'lxml')

inputs = soup.find_all('div', attrs={'class': 'challenge_sample_input'})
outputs = soup.find_all('div', attrs={'class': 'challenge_sample_output'})
samples = zip(inputs, outputs)
cases = []
for s in samples:
    input_lines = []
    output_lines = []
    for i in s[0].find('pre').strings:
        input_lines.append(str(i).strip())
    for i in s[1].find('pre').strings:
        output_lines.append(str(i).strip())
    cases.append(('\n'.join(filter(bool, input_lines)) + '\n',
                  '\n'.join(filter(bool, output_lines)) + '\n'))

if utils.save_cases(name, cases):
    utils.open_problem(name)
