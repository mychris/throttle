include config.mk

SRC := throttle.c

all: throttle throttle.1.gz README.txt

throttle: ${SRC} config.mk
	${CC} ${CFLAGS} ${LDFLAGS} ${SRC} -o $@

throttle.1.gz: throttle.1 config.mk
	sed 's/VERSION/${VERSION}/g' throttle.1 | gzip -c - >| $@

README.txt: throttle.1.gz
	gzip -d -c throttle.1.gz | groff -k -Tutf8 -m man | col -b -x >| $@

dist: config.mk clean
	mkdir -p throttle-${VERSION}
	cp config.mk Makefile \
		throttle.1 README.txt \
		${SRC} \
		throttle-${VERSION}
	tar -c -f throttle-${VERSION}.tar throttle-${VERSION}
	gzip -9 throttle-${VERSION}.tar
	rm -r -f throttle-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f throttle ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/throttle
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -f throttle.1.gz ${DESTDIR}${MANPREFIX}/man1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/throttle.1.gz

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/throttle ${DESTDIR}${MANPREFIX}/man1/throttle.1.gz

clean:
	rm -f throttle throttle.1.* throttle-*.tar*

.PHONY: all clean install uninstall dist
