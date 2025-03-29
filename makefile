.POSIX:

NAME = rirc
VERSION = 0.0

RIRC_CFLAGS = -std=c89 -Os -DVERSION=\"${VERSION}\" -D_GNU_SOURCE
RIRC_LDFLAGS = -lssl -lcrypto

CC = cc

BIN = rirc
SRC = ${BIN:=.c}
OBJ = ${SRC:.c=.o}

ALL = ${BIN}

${BIN}: ${OBJ}
	${CC} -o $@ ${OBJ} ${RIRC_LDFLAGS}

${OBJ}: ${SRC}
	${CC} -c ${RIRC_CFLAGS} -o $@ $<

clean:
	rm -f ${BIN} ${OBJ}
