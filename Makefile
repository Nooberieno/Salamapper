CC = g++

install: TreeNode.hpp parse.hpp rooter.hpp rooter.cpp parse.cpp salamapper.cpp
	sudo mkdir -p /usr/include/salamapper
	sudo mv TreeNode.hpp /usr/include/salamapper/TreeNode.hpp
	sudo mv parse.hpp /usr/include/salamapper/parse.hpp
	sudo mv rooter.hpp /usr/include/salamapper/rooter.hpp
	sudo mv print.hpp /usr/include/salamapper/print.hpp
	$(CC) -fPIC -c rooter.cpp
	$(CC) -fPIC -c parse.cpp
	$(CC) -shared rooter.o parse.o -o libsalamapper.so
	rm parse.o 
	rm rooter.o 
	sudo mv libsalamapper.so /usr/lib64/libsalamapper.so
	$(CC) salamapper.cpp -o salamapper -l salamapper
	sudo mv salamapper /usr/bin/salamapper
	rm -r rooter.cpp parse.cpp salamapper.cpp

develop: TreeNode.hpp parse.hpp rooter.hpp rooter.cpp parse.cpp salamapper.cpp
	sudo mkdir -p /usr/include/salamapper
	sudo cp TreeNode.hpp /usr/include/salamapper/TreeNode.hpp
	sudo cp parse.hpp /usr/include/salamapper/parse.hpp
	sudo cp rooter.hpp /usr/include/salamapper/rooter.hpp
	sudo cp print.hpp /usr/include/salamapper/print.hpp
	$(CC) -fPIC -c rooter.cpp
	$(CC) -fPIC -c parse.cpp
	$(CC) -shared rooter.o parse.o -o libsalamapper.so
	sudo cp libsalamapper.so /usr/lib64/libsalamapper.so
	$(CC) -g -Og salamapper.cpp -o salamapper -l salamapper
	rm parse.o 
	rm rooter.o
	rm libsalamapper.so
	./salamapper "1:2,3,5;2:3;3:4;4:;5:6,7;6:7;7:;" 1
