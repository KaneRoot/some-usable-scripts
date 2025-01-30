#		-prf "asendcmd=0.0 afftdn sn start,asendcmd=2 afftdn sn stop,afftdn=nr=10:nf=-40" \

SRC ?= tmp.opus
record-audio:
	record-audio.sh $(SRC)

record-video:
	record-video.sh $(SRC)

OUTPUT ?= tmp.opus
extract-audio:
	ffmpeg -i $(SRC) $(OUTPUT)

normalize:
	@# f: force overriding previous files
	@# koa: keep original audio
	@# pr: progress
	@# -nt {ebu,rms,peak}: normalization type (default is "ebu", which is what we want)
	@# -t TARGET_LEVEL: target db/LUFS level (default is "-23")
	@# (for EBU) -lrt LOUDNESS_RANGE_TARGET: max audio range (default is "7")
	@#
	@# ffmpeg options
	@# -c:a AUDIO_CODEC
	ffmpeg-normalize -f -koa -pr -c:a libopus $(SRC)
