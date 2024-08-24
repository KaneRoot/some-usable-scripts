CHROOT    ?= /tmp/root
ARCH      ?= x86_64
VERSION   ?= v3.20
MIRROR    ?= http://uk.alpinelinux.org/alpine/
URL_REPOS ?= $(MIRROR)$(VERSION)

enter-chroot:
	chroot $(CHROOT) /bin/sh

install-chroot:
	@echo "creating a new alpine $(VERSION) chroot"
	mkdir -p $(CHROOT)
	apk --arch $(ARCH) -X $(URL_REPOS)/main/ -U --allow-untrusted --root $(CHROOT) --initdb add alpine-base
	cp /etc/resolv.conf $(CHROOT)/etc/
	echo "$(URL_REPOS)/main"       > $(CHROOT)/etc/apk/repositories
	echo "$(URL_REPOS)/community" >> $(CHROOT)/etc/apk/repositories

mount-chroot:
	for a in proc sys dev; do mount -o bind /$$a $(CHROOT)/$$a; done

umount-chroot:
	-umount $(CHROOT)/proc
	-umount $(CHROOT)/sys
	-umount $(CHROOT)/dev

delete-chroot: umount-chroot
	rm -r $(CHROOT)

new-chroot: install-chroot mount-chroot enter-chroot
