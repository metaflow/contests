#!/usr/bin/env python

import sys
from urllib.parse import urlsplit
import json
import os
import msvcrt
from bs4 import BeautifulSoup
import platform
import subprocess

if platform.system() == "Windows":
	import msvcrt
	def getch():
		return msvcrt.getch()
else:
	import tty, termios, sys
	def getch():
		fd = sys.stdin.fileno()
		old_settings = termios.tcgetattr(fd)
		try:
			tty.setraw(sys.stdin.fileno())
			ch = sys.stdin.read(1)
		finally:
			termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
		return ch

print(sys.argv)
url = sys.argv[1]
path = sys.argv[2]

url = urlsplit(url)
host = url.netloc
if host != 'codeforces.com' and host != 'codoforces.ru':
    exit(1)
name = url.path[-1:]
if os.path.exists(name + '.in') or \
   os.path.exists(name + '.out') or \
   os.path.exists(name + '.cpp'):
    print('{0}.in, {0}.out or {0}.cpp exists override?'.format(name))
    input_char = getch()
    if input_char.upper() != b'Y':
        exit(0)

with open(path, 'r') as myfile:
    info = json.loads(myfile.read().replace('\n', ''))
soup = BeautifulSoup(info['content'], 'lxml')
inputs = soup.find_all('div', attrs={'class': 'input'})
outputs = soup.find_all('div', attrs={'class': 'output'})
samples = zip(inputs, outputs)
cases = []
for s in samples:
    # print('in')
    input_lines = []
    output_lines = []
    for i in s[0].find('pre').strings:
        # print(str(i).strip())
        input_lines.append(str(i).strip())
    for i in s[1].find('pre').strings:
        # print(str(i).strip())
        output_lines.append(str(i).strip())
    cases.append(('\n'.join(input_lines) + '\n', '\n'.join(output_lines) + '\n'))

for i, c in enumerate(cases):
    with open('{}.in{}'.format(name, i + 1 if i > 0 else ''), 'w') as f:
        f.write(c[0])
    with open('{}.out{}'.format(name, i + 1 if i > 0 else ''), 'w') as f:
        f.write(c[1])

subprocess.call(["C:\\Program Files\\Git\\bin\\bash.exe", '-c', '/c/Users/mgoncharov/etc/contests/problem.sh {}'.format(name)])
