#!/bin/sh

ffmpeg -y -loglevel error -f sndio -i snd/0 -ac 1 $@
