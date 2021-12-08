#!/bin/sh

# This doesn't work as intended on my very limited computer.
# Too CPU intensive.
ffmpeg -y -loglevel error -f x11grab -framerate 30 -video_size 1920x1080 -i :0.0 -f sndio -i snd/0 $@
