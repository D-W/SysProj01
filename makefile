make:
	gcc parse.c redirect.c executor.c shell.c -o shell

run: shell
	./shell

clean:
	rm shell
