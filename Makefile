CC = g++

install: TreeNode.h parse.h rooter.h rooter.cpp parse.cpp salamapper.cpp
	sudo mkdir /usr/include/salamapper
	sudo mv TreeNode.h /usr/include/salamapper/TreeNode.h
	sudo mv parse.h /usr/include/salamapper/parse.h
	sudo mv rooter.h /usr/include/salamapper/rooter.h
	$(CC) -fPIC -c rooter.cpp
	$(CC) -fPIC -c parse.cpp
	$(CC) -shared rooter.o parse.o -o libsalamapper.so
	rm -r parse.o 
	rm -r rooter.o 
	sudo mv libsalamapper.so /usr/lib64/libsalamapper.so
	$(CC) salamapper.cpp -o salamapper -l salamapper
	sudo mv salamapper /usr/bin/salamapper

develop: TreeNode.h parse.h rooter.h rooter.cpp parse.cpp salamapper.cpp
	sudo mkdir -p /usr/include/salamapper
	sudo cp TreeNode.h /usr/include/salamapper/TreeNode.h
	sudo cp parse.h /usr/include/salamapper/parse.h
	sudo cp rooter.h /usr/include/salamapper/rooter.h
	$(CC) -fPIC -c rooter.cpp
	$(CC) -fPIC -c parse.cpp
	$(CC) -shared rooter.o parse.o -o libsalamapper.so
	sudo cp libsalamapper.so /usr/lib64/libsalamapper.so
	$(CC) -g -Og salamapper.cpp -o salamapper -l salamapper
	rm -r parse.o 
	rm -r rooter.o
	rm -r libsalamapper.so
