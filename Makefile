DEPS=funciones.h planificador.h

programa: main.o funciones.o planificador.o $(DEPS)
	gcc -o programa main.o funciones.o planificador.o

%.o: %.c $(DEPS)
	gcc -c -o $@ $<

.PHONY: clean run
clean:
	rm -f programa *.o

run: programa
	./programa
