CFLAGS=-Wall -Wextra -std=c89
PREFIX=/usr

.SUFFIXES: .1 .1.gz

.1.1.gz: rai.1
	gzip -k $<

all: rai rai.1.gz

clean:
	rm -f rai *.gz
install: all
	cp rai $(PREFIX)/bin/
	cp rai.1.gz $(PREFIX)/share/man/man1/
uninstall:
	rm -rf $(PREFIX)/bin/rai
	rm -rf $(PREFIX)/share/man/man1/rai.1.gz
