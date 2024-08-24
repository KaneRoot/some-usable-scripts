#!/bin/bash

set -x

# WARNING: this codebase is now updated in the "alpine.mk" makefile.
# A makefile is a better option than a plain shell script, it enables
# an automatic selection of the action to perform (by just selecting
# the "rule" to make), without dedicated code.

#APKPKT=apk-tools-static-2.10.1-r0.apk

#mirror=http://uk.alpinelinux.org/alpine/
mirror=http://dl-cdn.alpinelinux.org/alpine
MAIN_DIR=/tmp/root
CHROOT=$MAIN_DIR/chroot
PACKAGES="vim zsh"
#POSTPACKAGES="alpine-sdk git openssh openssl openssl-dev crystal"
POSTPACKAGES=""

chroot_mkdir(){
	mkdir -p $CHROOT || true
}

#chroot_apk_static(){
#	cd ${MAIN_DIR}/
#
#	if [ -f ${APKPKT} ]; then
#		echo "apk already downloaded"
#	else
#		wget ${mirror}/latest-stable/main/`uname -p`/${APKPKT}
#		tar -xzf ${APKPKT}
#	fi
#}

chroot_install(){
	cd ${MAIN_DIR}/

	#${MAIN_DIR}/sbin/apk.static -X ${mirror}/latest-stable/main -U --allow-untrusted --root ${CHROOT} --initdb add alpine-base $PACKAGES
	apk --arch $(arch) -X ${mirror}/latest-stable/main/ -U --allow-untrusted --root ${CHROOT} --initdb add alpine-base
	cp /etc/resolv.conf $CHROOT/etc/
	#cp -r ~/.zsh* ~/.vim* ${CHROOT}/root
	#echo export PS1=\"\(chroot\) \$PS1\"  >> ${CHROOT}/root/.zshrc

	cat << END > $CHROOT/etc/apk/repositories
http://uk.alpinelinux.org/alpine/latest-stable/main
http://uk.alpinelinux.org/alpine/latest-stable/community
END
}

chroot_mount(){
	for a in proc sys dev; do mount -o bind /$a ${CHROOT}/$a; done
}

chroot_env(){
	chroot ${CHROOT} /bin/sh
	#chroot ${CHROOT} /bin/zsh -l
}

chroot_post(){
	#${MAIN_DIR}/sbin/apk.static --root ${CHROOT} add $POSTPACKAGES
	# chroot ${CHROOT} /bin/zsh -l "apk update && apk upgrade && apk add $POSTPACKAGES"
}

ask(){
	echo -en "$1? [YyNn] (n): "
	read V ; echo $V | grep "[Yy]" >/dev/null
	if [ $? -eq 0 ] ; then
		echo -en "doing $1..." ; $1
	else
		echo "not doing $1"
	fi
}

chroot_mkdir
#ask chroot_apk_static
ask chroot_install
ask chroot_mount
ask chroot_post
ask chroot_env
