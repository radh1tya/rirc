.POSIX:

NAME = rirc
VERSION = 0.0

RIRC_CFLAGS = ${CFLAGS}
RIRC_LDFLAGS = ${LDFLAGS}
RIRC_CPPFLAGS = ${LDFLAGS} -DVERSION=\"${VERSION}\" -D_GNU_SOURCE

BIN = rirc
SRC = ${BIN:=.c}
OBJ = ${SRC:.c=.o}

ALL = ${BIN}

${BIN}: ${@:=.o}

.o:
	${CC} -o $@ $< ${RIRC_LDFLAGS}

.c.o:
	${CC} -c ${RIRC_CFLAGS} ${RIRC_CPPFLAGS} -o $@ -c $<

clean:
	rm -f ${BIN} ${OBJ}
