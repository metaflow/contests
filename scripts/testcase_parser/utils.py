import os
import platform
import subprocess
from os.path import expanduser

isWin = platform.system() == "Windows"

def save_cases(name, cases):
    for i, c in enumerate(cases):
        suffix = '' if i == 0 else str(i + 1)
        in_file = '{}.in{}'.format(name, suffix)
        out_file = '{}.out{}'.format(name, suffix)
        if os.path.exists(in_file) or os.path.exists(out_file):
            print('{} or {} already exists, skipping'.format(in_file, out_file))
            continue
        with open(in_file, 'w') as f:
            f.write(c[0])
        with open(out_file, 'w') as f:
            f.write(c[1])
    return True


def open_problem(name):
    if isWin:
        subprocess.run(["C:\\Program Files\\Git\\bin\\bash.exe", '-c',
                        '/c/Users/mgoncharov/etc/contests/problem.sh {}'.format(name)])
    else:
        subprocess.run([expanduser('~/etc/contests/problem.sh'), name])
