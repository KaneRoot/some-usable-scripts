First of all, these scripts helped me to record my first video.
Here is my [youtube channel][beautemusculation] to see the result.

# Scripts to record videos

Both `record-audio.sh` and `record-video.sh` do exactly what their name is saying.
These are simple ffmpeg calls.
Their unique parameter is the output filename.

Since I use them on OpenBSD the audio driver is sndio and not Alsa or OSS or PulseAudio or whatever.

# Recording the camera

I don't record my face from my camera in a separate video stream.
I just display my camera feed in a window thanks to `camera.sh` and my whole screen is recorded with `record-video.sh.`.

There are two optional parameters: brightness and saturation.

Don't hesitate to tweak a bit this script: there are a few hardcoded ffmpeg parameters, such as a very low quality video size.

# Synchronize audio and video

The script `sync.sh` is to include in your environment.
It adds a few shell functions, using ffmpeg and mpv to help mixing and synchronizing audio and video.

- stereo2mono: my first error was to record a mono input in stereo, so I had audio only on the left side.
  This fixes the issue by removing the superflous empty track.
  Side note: since then, `record-audio.sh` was corrected (see `-ac 1` option).
- please_read: I'm like super lazy.
  This launches mpv with both video and audio without having to specify both files and the mpv option.
  Just read the source, the function is obvious.
- avsync: this is the core function to synchronize audio and video.
  Usage: `avsync video audio delay output`.
- avs: did I mention I'm lazy?
  This function is just me not wanting to type all `4` parameters for avsync.
  Again, read the source code, it's obvious.

# Forget about record-audio-and-video.sh

This script _probably_ does work if your computer is powerful enough.
That's not the case for mine.

# Software

I used `ffmpeg` a lot in these scripts.
That's one of the most versatile program you can find, anywhere.

I recommand `kdenlive` for both video editing (transitions, effects, inserts...) and for a few audio editing too.
It does help removing audio artifacts.
Learn how to use `keyframes` and you'll be ready for crazy productivity in no time.

I also use `audacity` to remove background noise, which allows to increase the volume smoothly.

Finally, for creating a thumbnail for my videos, I use `krita`.

# Hardware

About any low-end camera will do the job.
Don't get too crazy, 50 euros is enough.
Cheap cameras allow you to stream with low video quality, which is great for recording directly on your computer.
Since you probably don't need to have your face in fullscreen, the low quality is not a problem.

If you want a good video quality, either record with your phone or with the camera but without streaming it on your computer (quality isn't the same).
I watched probably dozen of hours of people talking and showing the quality of their cheap cameras, and finally I only use a ridiculously low quality... which is perfectly fine for the job!

Also, if you really want to improve the quality of the image, be sure to have enough light.
Low-end cameras aren't great with low lights setups (as I use, but fuck it I don't even care at this point).

Don't forget to have fun!

[beautemusculation]: https://www.youtube.com/channel/UC7nYol-RiCxMV7Tzg_jOV4w/featured
