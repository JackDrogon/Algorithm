#include <stdio.h>
#include <stdlib.h>

// TODO add generic type
// TODO 使用弹性块, 这样就可以直接使用cap[10], 不过这样没办法检查边界溢出了
typedef struct {
	size_t size;
	size_t cur;
	int *cap;
} vector;

void init(vector *vec, size_t size)
{
	vec->size = size;
	vec->cur = 0;
	vec->cap = (int *) malloc(size * sizeof(int));
}

int put(vector *vec, size_t place, int value)
{
	if (place < vec->size) {
		vec->cap[place] = value;
		return 1;
	} else {
		return 0;
	}
}

void push(vector *vec, int value)
{
	if (vec->cur >= vec->size) {
		// TODO Err check
		vec->cap = (int *) realloc(vec->cap, vec->size*2*sizeof(int));
		vec->size *= 2;
	}
	vec->cap[vec->cur++] = value;
}

// TODO add deal with place > size
int get(vector *vec, size_t place)
{
	if (place < vec->size) {
		return vec->cap[place];
	} else {
		return 0;
	}
}

void destory(vector *vec)
{
	vec->cur = vec->size = 0;
	free(vec->cap);
}

// TODO add clear function

int main()
{
	vector vec;
	init(&vec, 10);
	int i;
	for (i = 0; i < 25; ++i) {
		push(&vec, 2*i);
	}
	for (i = 0; i < 25; ++i) {
		printf("%d -> %d\n", i, get(&vec, i));
	}
	destory(&vec);

	return 0;
}
