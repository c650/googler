CC= g++
CFLAGS= --std=c++11

LDLIBS= -lcurl
LDFLAGS= -L/usr/lib/x86_64-linux-gnu

SRC = *.cpp
OUT = googler.out

build: ${SRC}
	${CC} ${CFLAGS} -o ${OUT} ${SRC} ${LDFLAGS} ${LDLIBS}

.PHONY: clean

clean:
	rm ./*.out
