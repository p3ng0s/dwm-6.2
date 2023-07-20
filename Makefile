# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}
OBJ_LIGHT = ${SRC:.c=.o-light}
OBJ_LIVE = ${SRC:.c=.o-live}

all: options dwm dwm-light dwm-live

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<
	${CC} ${LFLAGS} -c ${CFLAGS} $< -o $@-light
	${CC} ${LIVEFLAGS} -c ${CFLAGS} $< -o $@-live

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

dwm-light: ${OBJ_LIGHT}
	${CC} ${LFLAGS} -o $@ ${OBJ_LIGHT} ${LDFLAGS}

dwm-live: ${OBJ_LIVE}
	${CC} ${LIVEFLAGS} -o $@ ${OBJ_LIVE} ${LDFLAGS}

clean:
	rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz
	rm -f dwm-light ${OBJ_LIGHT}
	rm -f dwm-live ${OBJ_LIVE}

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	cp -f dwm-light ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm-light
	cp -f dwm-live ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm-live
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${MANPREFIX}/man1/dwm.1\
		${DESTDIR}${PREFIX}/bin/dwm-light\
		${DESTDIR}${PREFIX}/bin/dwm-live

.PHONY: all options clean dist install uninstall
