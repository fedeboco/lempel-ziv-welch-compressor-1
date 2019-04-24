CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)

all: tp0.exe

tp0.exe: main.cc cmdline.cc diccionario.cc arreglo.cc secuencia.cc compresion.cc compresion.h  diccionario.h arreglo.h secuencia.h cmdline.h 
	$(CXX) $(CXXFLAGS) -o tp0.exe cmdline.cc main.cc diccionario.cc arreglo.cc secuencia.cc compresion.cc 

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err

valgrind: 
	for numero in 0 1 2 3 4 5 6 7 8 9; do \
	echo \ ;\
	echo TEST NÚMERO $$numero ----------------------;\
	valgrind ./tp0.exe -p compress -i "./tests/entrada$${numero}.txt" -o "./tests/salida$${numero}.txt" ;\
	valgrind ./tp0.exe -p decompress -i "./tests/salida$${numero}.txt" -o "./tests/vuelta$${numero}.txt" ;\
	echo \ ;\
	done
	
test:
	for numero in 1 2 3 4 5 6 7 8 9; do \
	echo \ ;\
	echo TEST NÚMERO $$numero ----------------------;\
	./tp0.exe -p compress -i "./tests/entrada$${numero}.txt" -o "./tests/salida$${numero}.txt" ;\
	./tp0.exe -p decompress -i "./tests/salida$${numero}.txt" -o "./tests/vuelta$${numero}.txt" ;\
	diff -q -s "./tests/vuelta$${numero}.txt" "./tests/entrada$${numero}.txt" ;\
	echo \ ;\
	done

test_big:
	echo TEST DE ARCHIVO GRANDE ;\
	./tp0.exe -p compress -i "./tests/entrada_big.txt" -o "./tests/salida_big.txt" ;\
	./tp0.exe -p decompress -i "./tests/salida_big.txt" -o "./tests/vuelta_big.txt" ;\
	diff -q -s "./tests/entrada_big.txt" "./tests/vuelta_big.txt" ;\
	echo \ ;\