import platform
import os

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
       os.path.exists(name + '.out') or \
       os.path.exists(name + '.cpp'):
        print('{0}.in, {0}.out or {0}.cpp exists override?'.format(name))
        input_char = getch()
        if input_char.upper() != b'Y':
            return False
    for i, c in enumerate(cases):
        with open('{}.in{}'.format(name, i + 1 if i > 0 else ''), 'w') as f:
            f.write(c[0])
        with open('{}.out{}'.format(name, i + 1 if i > 0 else ''), 'w') as f:
            f.write(c[1])
    return True
