#!/usr/bin/env python

import sys
from bs4 import BeautifulSoup

print(sys.argv)
print("url", sys.argv[1])
path = sys.argv[2]
print("path", path)

with open(path, 'r') as myfile:
    html = myfile.read().replace('\n', '')
soup = BeautifulSoup(html, 'lxml')
inputs = soup.find_all('div', attrs={'class': 'input'})
outputs = soup.find_all('div', attrs={'class': 'output'})
samples = zip(inputs, outputs)
for s in samples:
    print('in')
    for i in s[0].find('pre').strings:
        print(str(i).strip())
    print('out')
    for i in s[1].find('pre').strings:
        print(str(i).strip())
