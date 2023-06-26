all:

DOMAIN ?= karchnu.fr
get-certificate-info:
	openssl s_client -connect $(DOMAIN):443
verify-web-certificate-dates:
	echo | openssl s_client -connect $(DOMAIN):443 2>/dev/null | openssl x509 -noout -dates

show-connected-ipv4:
	@# Don't forget the double $$ since we are in a Makefile.
	@netstat -n -p tcp | drop-until tcp | awk '{print $$5}' | cut -d. -f 1-4 | sort | uniq

detect-volume:
	ffmpeg -i $(SRC) -af "volumedetect" -vn -sn -dn -f null /dev/null

PORT ?=
which-bin-uses-this-port:
	fstat | grep ':$(PORT)'

MAIL_DOMAIN ?= mail.karchnu.fr
verify-mail-certificate:
	echo | openssl s_client -starttls smtp -showcerts -connect $(MAIL_DOMAIN):587 -servername $(MAIL_DOMAIN) | openssl x509 -noout -dates

verify-mail-imap-certificate:
	echo | openssl s_client -showcerts -connect $(MAIL_DOMAIN):993 -servername $(MAIL_DOMAIN) | openssl x509 -noout -dates
