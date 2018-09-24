#!/bin/bash

# TODO: good codebase, need parameters and make a more generic tool

APKPKT=apk-tools-static-2.10.1-r0.apk

mirror=http://uk.alpinelinux.org/alpine/
MAINREP=/media/fast/al
CHROOT=$MAINREP/chroot
PACKAGES="vim zsh"
POSTPACKAGES="alpine-sdk git openssh openssl openssl-dev crystal"

chroot_install(){
	mkdir -p $CHROOT
	cd ${MAINREP}/

	if [ -f ${APKPKT} ]; then
		echo "apk already downloaded"
	else
		wget ${mirror}/latest-stable/main/`uname -p`/${APKPKT}
		tar -xzf ${APKPKT}
	fi

	${MAINREP}/sbin/apk.static -X ${mirror}/latest-stable/main -U --allow-untrusted --root ${CHROOT} --initdb add alpine-base $PACKAGES
	cp /etc/resolv.conf $CHROOT/etc/
	cp -r ~/.zsh* ~/.vim* ${CHROOT}/root
	echo export PS1=\"\(chroot\) \$PS1\"  >> ${CHROOT}/root/.zshrc

	cat << END > $CHROOT/etc/apk/repositories
http://uk.alpinelinux.org/alpine/latest-stable/main
http://uk.alpinelinux.org/alpine/latest-stable/community
http://uk.alpinelinux.org/alpine/edge/main
http://uk.alpinelinux.org/alpine/edge/community
END
}

chroot_mount(){
	mount -t proc /proc ${CHROOT}/proc/
	mount -o bind /sys  ${CHROOT}/sys/
	mount -o bind /dev  ${CHROOT}/dev/
}

chroot_env(){
	chroot ${CHROOT} /bin/zsh -l
}

chroot_post(){
	${MAINREP}/sbin/apk.static --root ${CHROOT} add $POSTPACKAGES
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

ask chroot_install
ask chroot_mount
ask chroot_post
ask chroot_env
