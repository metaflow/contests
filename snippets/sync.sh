#!/bin/bash
rsync -uv ./cp*.sublime-snippet /home/meta/.config/sublime-text-3/Packages/User/
rsync -uv /home/meta/.config/sublime-text-3/Packages/User/cp*.sublime-snippet .
