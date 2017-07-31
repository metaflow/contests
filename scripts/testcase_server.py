#!/usr/bin/env python

from http.server import BaseHTTPRequestHandler, HTTPServer
import urllib
import urllib.request
import os
import subprocess

parsers = [
    ['python', './testcase_parsers/codeforces.py', '%url%', '%html%']
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
        post_data = self.rfile.read()
        with open("./testcase.html", "w") as f:
            f.write(str(post_data).replace('\\n', '\n'))
        for p in parsers:
            print(p)
            copy = p
            for id, s in enumerate(copy):
                copy[id] = s.replace('%url%', 'http://localhost') \
                            .replace('%html%', os.path.abspath("./testcase.html"))
            print(copy)
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
