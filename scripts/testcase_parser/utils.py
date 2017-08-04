import platform
import os
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


def save_cases(name, cases):
    if os.path.exists(name + '.in') or \
       os.path.exists(name + '.out'):
        print('{0}.in or {0}.out exists override?'.format(name))
        input_char = getch()
        print(input_char.decode('utf-8'))
        if input_char.upper() != b'Y':
            print('cancelled')
            return False
    for i, c in enumerate(cases):
        with open('{}.in{}'.format(name, i + 1 if i > 0 else ''), 'w') as f:
            f.write(c[0])
        with open('{}.out{}'.format(name, i + 1 if i > 0 else ''), 'w') as f:
            f.write(c[1])
    return True


def open_problem(name):
    subprocess.run(["C:\\Program Files\\Git\\bin\\bash.exe", '-c', '/c/Users/mgoncharov/etc/contests/problem.sh {}'.format(name)])
