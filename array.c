#include <stdio.h>
#include <stdlib.h>

// TODO add generic type
// TODO 使用弹性块
typedef struct {
	size_t size;
	int *cap;
} array;

void init(array *arr, size_t size)
{
	arr->size = size;
	arr->cap = (int *) malloc(size * sizeof(int));
}

void put(array *arr, size_t place, int value)
{
	if (place < arr->size) {
		arr->cap[place] = value;
	} else {
		// TODO Err check
		arr->cap = (int *) realloc(arr->cap, arr->size*2*sizeof(int));
		arr->size *= 2;
		arr->cap[place] = value;
	}
}

// TODO add deal with place > size
int get(array *arr, size_t place)
{
	if (place < arr->size) {
		return arr->cap[place];
	} else {
		return 0;
	}
}

int main()
{
	array arr;
	init(&arr, 10);
	int i;
	for (i = 0; i < 25; ++i) {
		put(&arr, i, 2*i);
	}
	for (i = 0; i < 25; ++i) {
		printf("%d -> %d\n", i, get(&arr, i));
	}

	return 0;
}
