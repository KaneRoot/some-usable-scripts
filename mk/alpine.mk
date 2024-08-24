CHROOT    ?= /tmp/root
ARCH      ?= x86_64
VERSION   ?= v3.20
MIRROR    ?= http://uk.alpinelinux.org/alpine/
URL_REPOS ?= $(MIRROR)$(VERSION)

enter:
	chroot $(CHROOT) /bin/sh

install:
	@echo "creating a new alpine $(VERSION) chroot"
	mkdir -p $(CHROOT)
	apk --arch $(ARCH) -X $(URL_REPOS)/main/ -U --allow-untrusted --root $(CHROOT) --initdb add alpine-base
	cp /etc/resolv.conf $(CHROOT)/etc/
	echo "$(URL_REPOS)/main"       > $(CHROOT)/etc/apk/repositories
	echo "$(URL_REPOS)/community" >> $(CHROOT)/etc/apk/repositories

mount:
	for a in proc sys dev; do mount -o bind /$$a $(CHROOT)/$$a; done

unmount:
	-umount $(CHROOT)/proc
	-umount $(CHROOT)/sys
	-umount $(CHROOT)/dev

delete: unmount
	rm -r $(CHROOT)

new: install mount enter
