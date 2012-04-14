#!/bin/sh
ffmpeg -f alsa -i plughw:0 -f x11grab -s 1366x768 -r 24 -b 100k -bf 2 -g 300 -i :0.0 -ar 22050  -acodec libvorbis -ab 128k -async 50 -vol 1500 -vcodec huffyuv -aspect 1.6 -sameq screencast.avi
