#!/usr/bin/python
import sys
import os
import re
import subprocess
if len(sys.argv) < 3:
    print("provide problem name and number of nodes")
    exit(1)
problemName = sys.argv[1]
nodeCount = sys.argv[2]

for file in os.listdir('.'):
    if not re.match(problemName + '.+\.h$', file):
        # print(file, "X")
        continue
    name = file.replace('.h', '')
    print(name)
    subprocess.run(["cp", file, problemName + ".h"], stdout=subprocess.PIPE)
    command = ["C:\\Program Files\\Git\\bin\\bash.exe", '-c',
                          ' '.join(['/c/Users/mgoncharov/etc/contests/scripts/dcj/dcj.sh',
                                    'test',
                                    '--source', problemName + '.cpp',
                                    '--nodes', nodeCount,
                                    '--output all'])]
    # print(command)
    out = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if (out.returncode != 0):
        print("FAILED")
        print(out.stdout.decode('utf-8'))
        print(out.stderr.decode('utf-8'))
        continue
    with open(name + ".output", 'wb') as actual:
        actual.write(out.stdout)
    diff = subprocess.run(["diff", name + ".out", name + '.output'], stdout=subprocess.PIPE)
    if (diff.returncode == 0):
        print("PASSED\n{}".format(out.stderr.decode('utf-8')))
        continue
    print(diff.stdout.decode('utf-8'))
    print(out.stderr.decode('utf-8'))
