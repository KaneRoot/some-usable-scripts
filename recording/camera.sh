#!/bin/sh

brightness=0.07
saturation=1.8

if [ $# -eq 2 ]; then
	brightness=$1
	saturation=$2
fi

echo "brightness = $brightness"
echo "saturation = $saturation"

ffplay -loglevel error -f v4l2 -input_format mjpeg -vf eq=brightness=$brightness:saturation=$saturation -video_size 640x480 /dev/video1
