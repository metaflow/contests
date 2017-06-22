import subprocess
import psutil
import sys
import time
import threading
import os

def full_memory(p):
    t = p.memory_full_info().uss
    for c in p.children():
        t += full_memory(c)
    return t

class MyClass(threading.Thread):
    def __init__(self, pid, max_allowed):
        self.pid = pid
        self.max_uss = 0
        self.max_allowed = max_allowed
        threading.Thread.__init__(self)

    def run(self):
        while True:
            try:
                p = psutil.Process(self.pid)
                self.max_uss = max(self.max_uss, full_memory(p))
                if self.max_uss > max_allowed and max_allowed > 0:
                    p.kill(9)
                    break
            except:
                break

print(sys.argv)
cmd = sys.argv[2:]
max_allowed = int(sys.argv[1])
print(cmd)
print(os.environ)
p = psutil.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, env=os.environ)
# peak_uss = 0
myclass = MyClass(p.pid, max_allowed)
myclass.start()
myclass.join()

if myclass.max_uss > myclass.max_allowed and myclass.max_allowed > 0:
    sys.stderr.write(
        "process has used {} > {} allowed\n".format(
            myclass.max_uss, myclass.max_allowed))
    exit(1)
print(myclass.max_uss)

# while p.is_running():
    # try:
        # peak_uss = max(peak_uss, full_memory(p))
    # except:
        # print(sys.exc_info()[0])
        # break
    # time.sleep(0.00001)
# print("completed {} {}".format(p.returncode, peak_uss))
# p = psutil.Popen(["/usr/bin/python", "-c", "print('hello')"], stdout=PIPE)
