.POSIX:

NAME = rirc
VERSION = 0.0

SIC_CFLAGS = ${CFLAGS}
SIC_LDFLAGS = ${LDFLAGS}
SIC_CPPFLAGS = ${LDFLAGS} -DVERSION=\"${VERSION}\" -D_GNU_SOURCE

BIN = rirc
SRC = ${BIN:=.c}
OBJ = ${SRC:.c=.o}

ALL = ${BIN}

${BIN}: ${@:=.o}

.o:
	${CC} -o $@ $< ${SIC_LDFLAGS}

.c.o:
	${CC} -c ${SIC_CFLAGS} ${SIC_CPPFLAGS} -o $@ -c $<

clean:
	rm -f ${BIN} ${OBJ}
