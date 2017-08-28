#!/usr/bin/env python

from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import os
import subprocess
import sys
import urllib
import urllib.request

script_dir = os.path.dirname(os.path.realpath(__file__))
parsers = [
    ['python', '%script_dir%/codeforces.py', '%url%', '%info%'],
    ['python', '%script_dir%/atcoder.py', '%url%', '%info%'],
    ['python', '%script_dir%/csacademy.py', '%url%', '%info%'],
    ['python', '%script_dir%/codechef.py', '%url%', '%info%'],
    ['python', '%script_dir%/hackerrank.py', '%url%', '%info%'],
    ['python', '%script_dir%/codejam.py', '%url%', '%info%'],
    ['python', '%script_dir%/kattis.py', '%url%', '%info%']
]

class testHTTPServer_RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        url = urllib.parse.urlparse(self.path)
        path = url.path[1:]
        self.send_response(200)
        self.send_header('Content-type','text/plain')
        self.end_headers()
        message = path
        self.wfile.write(bytes(message, "utf8"))
        if path == "exit":
            exit(0)
        return

    def do_POST(self):
        self.send_response(200)
        self.send_header('Content-type','text/plain')
        self.end_headers()
        self.wfile.write(bytes(self.path, "utf8"))
        request_path = self.path
        length = int(self.headers['Content-Length'])
        data = self.rfile.read()
        data = data.decode('utf-8').encode('cp850','replace').decode('cp850')
        j = json.loads(data)
        with open("./testcase.json", "w") as f:
            f.write(data)
        for p in parsers:
            copy = list(p)
            for id, s in enumerate(copy):
                copy[id] = s.replace('%script_dir%', script_dir) \
                            .replace('%url%', j['url']) \
                            .replace('%info%', os.path.abspath("./testcase.json"))
            process = subprocess.run(copy)
            if process.returncode == 0:
                break
        return


def run():
    try:
        # kill another instance
        urllib.request.urlopen("http://localhost:4243/exit").read()
    except:
        pass
    print('starting server...')
    server_address = ('0.0.0.0', 4243)
    httpd = HTTPServer(server_address, testHTTPServer_RequestHandler)
    httpd.serve_forever()

run()
