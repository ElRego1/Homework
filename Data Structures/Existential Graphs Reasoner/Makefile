CC=gcc
CFLAGS=-fPIC -Wall -Wextra --std=c++11
COMPILE=$(CC) $(CFLAGS)

.PHONY: build clean

build: libaegraph.so

libaegraph.so: aegraph.cpp
	$(COMPILE) -shared -o $@ $<

clean:
	rm -f libaegraph.so
