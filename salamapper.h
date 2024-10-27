#ifndef SALAMAPPER_H
#define SALAMAPPER_H

#ifdef __cplusplus
extern "C"{
#endif

typedef struct TreeHandle TreeHandle;

enum CycleHandling {
	CYCLE_ERROR,
	CYCLE_WARN,
	CYCLE_IGNORE
};

TreeHandle* CreateTree(const char* format_string, const char* root_id, enum CycleHandling cycle_mode);
void ClearTree(TreeHandle* handle);
char* GetTree(TreeHandle* handle);
void FreeString(char* str);
char* TopSortKahnHandle(const TreeHandle* handle);
char* TopSortKahnString(const char* format_string);

#ifdef __cplusplus
}
#endif

#endif