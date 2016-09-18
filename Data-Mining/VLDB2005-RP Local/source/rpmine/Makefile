flags = -Wall -O3
inputdir = src/

bin/rpmine: bin/fpclosed.o bin/data.o bin/fp_tree.o bin/buffer.o bin/fsout.o bin/fp_node.o
	g++ $(flags) bin/fpclosed.o bin/data.o bin/fp_tree.o bin/buffer.o bin/fsout.o bin/fp_node.o -o bin/rpmine

bin/fpclosed.o: src/fpmax.cpp src/data.h src/fp_tree.h src/common.h src/fsout.h
	g++ $(flags) -DCFI -c src/fpmax.cpp -o bin/fpclosed.o

bin/data.o: src/data.cpp src/data.h
	g++ $(flags) -c src/data.cpp -o bin/data.o

bin/fp_tree.o: src/fp_tree.cpp src/data.h src/fp_tree.h src/common.h src/fsout.h
	g++ $(flags) -c src/fp_tree.cpp -o bin/fp_tree.o

bin/buffer.o: src/buffer.cpp src/data.h src/buffer.h
	g++ $(flags) -c src/buffer.cpp -o bin/buffer.o

bin/fsout.o: src/fsout.cpp src/fsout.h src/common.h
	g++ $(flags) -c src/fsout.cpp -o bin/fsout.o

bin/fp_node.o: src/fp_node.cpp src/fp_node.h src/fsout.h src/common.h
	g++ $(flags) -c src/fp_node.cpp -o bin/fp_node.o

clean:
	rm -f bin/*.o bin/rpmine
