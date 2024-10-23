CC = g++

install: TreeNode.hpp parse.hpp rooter.hpp rooter.cpp parse.cpp salamapper.cpp
	sudo mkdir -p /usr/include/salamapper
	sudo mv TreeNode.hpp /usr/include/salamapper/TreeNode.hpp
	sudo mv parse.hpp /usr/include/salamapper/parse.hpp
	sudo mv rooter.hpp /usr/include/salamapper/rooter.hpp
	sudo mv print.hpp /usr/include/salamapper/print.hpp
	$(CC) -fPIC -c rooter.cpp -D_POSIX_C_SOURCE=200809L
	$(CC) -fPIC -c parse.cpp -D_POSIX_C_SOURCE=200809L
	$(CC) -fPIC -c salamapper.cpp -D_POSIX_C_SOURCE=200809L
	$(CC) -shared rooter.o parse.o salamapper.o -o libsalamapper.so
	rm parse.o 
	rm rooter.o
	rm salamapper.o 
	sudo mv libsalamapper.so /usr/lib64/libsalamapper.so

develop: TreeNode.hpp parse.hpp rooter.hpp rooter.cpp parse.cpp salamapper.cpp
	sudo mkdir -p /usr/include/salamapper
	sudo cp TreeNode.hpp /usr/include/salamapper/TreeNode.hpp
	sudo cp parse.hpp /usr/include/salamapper/parse.hpp
	sudo cp rooter.hpp /usr/include/salamapper/rooter.hpp
	sudo cp print.hpp /usr/include/salamapper/print.hpp
	sudo cp salamapper.h /usr/include/salamapper/salamapper.h
	$(CC) -fPIC -c rooter.cpp -D_POSIX_C_SOURCE=200809L
	$(CC) -fPIC -c parse.cpp -D_POSIX_C_SOURCE=200809L
	$(CC) -fPIC -c salamapper.cpp -D_POSIX_C_SOURCE=200809L
	$(CC) -fPIC -c c_api.cpp -D_POSIX_C_SOURCE=200809L
	$(CC) -shared rooter.o parse.o salamapper.o c_api.o -o libsalamapper.so
	sudo cp libsalamapper.so /usr/lib/libsalamapper.so
	sudo cp libsalamapper.so /usr/lib64/libsalamapper.so
	rm parse.o 
	rm rooter.o
	rm salamapper.o
	rm c_api.o
	rm libsalamapper.so
