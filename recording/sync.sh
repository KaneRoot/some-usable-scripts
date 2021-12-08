#!/bin/sh

# This is a list of simple shell functions to handle a few inconveniences
# regarding video and audio synchronization.

# When recording a mono source as a stereo, one of the speaker is muted.
# This removes the second (muted) track from the audio source.
stereo2mono(){
	/usr/bin/ffmpeg -i "$1" -c:v copy -ac 1 "mono-$1"
}

# Side note: I record both audio and video with the same file names, besides the extension.
please_read(){
	/usr/bin/mpv "$1.mkv" -audiofile "$1.opus"
}

# Synchronize the audio and video.
avsync(){

	if [ $# -ne 4 ]; then
		echo "usage: avsync video audio delay output"
		return 1
	fi

	/usr/bin/ffmpeg -i "$1" \
		-itsoffset "$3" \
		-i "$2" \
		-c:a copy -c:v copy -map 0:v:0 -map 1:a:0 \
		"$4"

}

# Video and audio have the same name, except for the extension.
# Example: avs my-video 1.3
avs(){
	if [ $# -ne 2 ]; then
		echo "usage: avs prefix delay"
		return 1
	fi

	avsync "$1".mkv "$1".opus "$2" "$1"-sync.mkv
}
