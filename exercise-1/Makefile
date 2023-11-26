files := \
		 main.c\
		 parse.c\
		 report.c\
		 compute_with_threads.c\
		 compute_with_processes.c

files := $(addprefix src/, $(files))

sum: $(files)
	gcc -o sum $(files)

clean:
	rm -f sum
