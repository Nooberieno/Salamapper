#include <salamapper/salamapper.h>
#include <assert.h>
#include <stdio.h>

void BasicTest(){
	const char* input = "1:2,3,5;2:3;3:4;4:;5:6,7;6:7;7:;";
	const char* root_id = "1";

	TreeHandle* tree = CreateTree(input, root_id, CYCLE_IGNORE);
	assert(tree != NULL && "Tree Creation Failed");

	char* ASCII_Output = GetTree(tree);
	assert(ASCII_Output != NULL && "ASCII_Output Failed");
	printf("Tree visualization: \n%s\n", ASCII_Output);

	FreeString(ASCII_Output);
	ClearTree(tree);
	printf("Basic functionality test passed\n");
}

void ErrorHandlingTest(){
	TreeHandle *tree = CreateTree("invalid format", "1", CYCLE_IGNORE);
	assert(tree == NULL && "Invalid input handling failed");

	tree = CreateTree(NULL, "1", CYCLE_IGNORE);
	assert(tree == NULL && "Null input handling failed");

	char* format = "1:2;2:1";
	tree = CreateTree(format, "1", CYCLE_ERROR);
	assert(tree == NULL && "Cycle Error undetected");

	tree = CreateTree(format, "1", CYCLE_IGNORE);
	assert(tree != NULL && "Cycle Error detected when using ignore");

	format = "1:2;2:3,4;3:1,4;4:";
	tree = CreateTree(format, "1", CYCLE_ERROR);
	assert(tree == NULL && "Cycle Error undetected");
	
	tree = CreateTree(format, "1", CYCLE_IGNORE);
	assert(tree != NULL && "Cycle Error detected when using ignore");

	printf("Error handling test passed\n");
}

int main(){
	printf("Starting salamapper C API test... \n");

	BasicTest();
	ErrorHandlingTest();

	printf("All test completed succesfully\n");
	return 0;
}