# Builds all examples

DIRS=$(wildcard c/*) $(wildcard cpp/*)

all:
	@for DIR in $(DIRS); do\
		echo --- $$DIR ---; \
		(cd $$DIR; make) \
	done

clean:
	@for DIR in $(DIRS); do\
		echo --- $$DIR ---; \
		(cd $$DIR; make clean) \
	done

.PHONY: clean all

