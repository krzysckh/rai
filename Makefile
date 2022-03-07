CFLAGS=-Wall -Wextra -std=c89 -ggdb
LDFLAGS=-lm
PREFIX=/usr

%.gz: %
	gzip -k $<
all: rai rai.1.gz
clean:
	rm -f rai *.gz
install: all
	install -Dm755 -s rai -t $(PREFIX)/bin/
	install -Dm644 rai.1.gz -t $(PREFIX)/share/man/man1/
uninstall:
	rm -rf $(PREFIX)/bin/rai
	rm -rf $(PREFIX)/share/man/man1/rai.1.gz
