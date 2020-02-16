.phony all:
all: diskinfo disklist

diskinfo: diskinfo.c
	gcc diskinfo.c

disklist: disklist.c
	gcc disklist.c


.PHONY clean:
clean:
	-rm -rf *.o *.exe

