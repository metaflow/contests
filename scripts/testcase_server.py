#!/usr/bin/env python

from http.server import BaseHTTPRequestHandler, HTTPServer
import urllib
import urllib.request
import os
import subprocess
import sys
import json

script_dir = os.path.dirname(os.path.realpath(__file__))
parsers = [
    ['python', '%script_dir%/testcase_parsers/codeforces.py', '%url%', '%info%']
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
        request_path = self.path
        length = int(self.headers['Content-Length'])
        data = self.rfile.read()
        data = data.decode('utf-8').encode('cp850','replace').decode('cp850')
        j = json.loads(data)
        # print("data", )
        with open("./testcase.json", "w") as f:
            f.write(data)
        for p in parsers:
            copy = p
            for id, s in enumerate(copy):
                copy[id] = s.replace('%script_dir%', script_dir) \
                            .replace('%url%', j['url']) \
                            .replace('%info%', os.path.abspath("./testcase.json"))
            subprocess.call(copy)

def run():
    try:
        urllib.request.urlopen("http://localhost:4243/exit").read()
    except:
        pass
    print('starting server...')
    server_address = ('0.0.0.0', 4243)
    httpd = HTTPServer(server_address, testHTTPServer_RequestHandler)
    httpd.serve_forever()

run()
