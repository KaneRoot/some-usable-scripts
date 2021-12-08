#!/bin/sh

ffmpeg -y -loglevel error -f x11grab -framerate 30 -video_size 1920x1080 -i :0.0 $@
