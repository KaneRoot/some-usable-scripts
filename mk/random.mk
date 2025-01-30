APP ?= my-app
strace-pid:
	@# strace an already running application
	sudo strace -p $$(pidof $(APP))

strace:
	@# --decode-fds = get file names
	sudo strace --decode-fds -e desc,network $(APP)
