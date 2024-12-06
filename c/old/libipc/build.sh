#!/bin/sh

nontapmsg() {
	echo $*
}

if [ $# -eq 0 ] ; then
	SRC="*.c"
else
	SRC="$*"
fi

for i in $SRC
do
    BIN=$(echo ${i} | sed "s/.c$/.bin/")
    if [ ! -f ${BIN} ] || [ $(stat -c "%X" ${BIN}) -lt  $(stat -c "%X" ${i}) ]
    then
		nontapmsg "compiling ${BIN}"
		# gcc $BIN.c ./lib/*.o -o $BIN -I../src -I ./lib/ -L../ -L./lib/ -lipc -Wall -g -Wextra
		# gcc -Wall -g -Wextra "${i}" -o "${BIN}" -I../src -L../ ../src/ipc.h -lipc
		gcc -Wall -g -Wextra "${i}" -o "${BIN}" -lipc
		touch "${BIN}"
	fi
done
