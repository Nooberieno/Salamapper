CC = g++

move: TreeNode.h parse.h rooter.h
	sudo mkdir /usr/include/salamapper
	sudo mv TreeNode.h /usr/include/salamapper/TreeNode.h
	sudo mv parse.h /usr/include/salamapper/parse.h
	sudo mv rooter.h /usr/include/salamapper/rooter.h

compile: rooter.cpp parse.cpp
	$(CC) -fPIC -c rooter.cpp
	$(CC) -fPIC -c parse.cpp
	$(CC) -shared rooter.o parse.o -o libsalamapper.so

install: libsalamapper.so
	sudo mv libsalamapper.so /usr/lib/libsalamapper.so
	$(CC) -g -Og salamapper.cpp -o salamapper -l salamapper
	sudo mv salamapper /usr/bin/salamapper