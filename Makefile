all: ccalc

ccalc: ccalc.c
	gcc -o $@ $^
	
clean:
	rm -f ccalc

