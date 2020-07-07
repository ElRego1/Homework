build:
	gcc -std=c99 -Wall -Wextra histograma.c -o hist -lm
	gcc -std=c99 -Wall -Wextra statistici.c -o stats -lm

run: build
	./hist
	./stats

clean:
	rm -f hist
	rm -f stats
