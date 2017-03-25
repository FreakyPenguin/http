PROG=   http
MAN=    http.1

SRCS=   main.c http.c ftp.c file.c io.c progressmeter.c util.c
SRCS+=  openbsd-compat/imsg.c openbsd-compat/imsg-buffer.c \
	openbsd-compat/basedirname.c

CFLAGS= -Iopenbsd-compat -D_GNU_SOURCE $(EXTRA_CFLAGS)
LDFLAGS= $(EXTRA_LDFLAGS)
LDLIBS=	-lbsd -ltls -lssl -lcrypto -lresolv

all: $(PROG)

$(PROG): $(SRCS:.c=.o)

#	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(SRCS:.c=.o) $(PROG)

.PHONY: all clean
