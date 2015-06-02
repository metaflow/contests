#!/bin/bash
rsync -uv ./cp*.sublime-snippet $HOME/.config/sublime-text-3/Packages/User/
rsync -uv $HOME/.config/sublime-text-3/Packages/User/cp*.sublime-snippet .
