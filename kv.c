#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct kv {
	int capacity;
	struct element **htable;
	int (*hash)(const char *);
	int (*set)(struct kv *, const char *, const char *);
	int (*get)(struct kv *, const char *);
	void (*init)(struct kv *, const int);
	void (*destory)(struct kv *);
};

struct element {
	struct element *next;
	const char *key;
	char *value;
};

int hash(const char *str)
{
	unsigned int hash = 5381;
	size_t len = strlen(str);
	while (len--) hash = ((hash << 5) + hash) + (*str++);

	return hash;
}

int set(struct kv *table, const char *key, const char *value)
{
	int place = hash(key) % table->capacity;
	int key_len = strlen(key);
	char *key_ = (char*) malloc(key_len * sizeof(char));
	strncpy(key_, key, key_len);
	struct element *value_ = (struct element*) malloc(sizeof(struct element));
	value_->key = key_;
	value_->value = value;
	/*
	if (table->value[place] == NULL) {
		// printf("Key: %s, Value: %s\n", key, value);
		value_->next = NULL;
	} else {
		struct element *next = table->value[place];
		// printf("Conflict Key: %s, Value: %s\n", key, value);
		value_->next = next;
	}
	*/
	value_->next = table->htable[place];
	table->htable[place] = value_;

	return 1;
}


char* get(struct kv *table, const char *key)
{
	// TODO assert null / have no value
	int place = hash(key) % table->capacity;
	// TODO Add string compare optimization  first compare with len(use redis sds)
	struct element *value = table->htable[place];
	//printf("Get Key: %s, Value: %s\n", key, value->value);
	while (strcmp(key, value->key)) {
		//printf("%d\n", strcmp(key, value->key));
		value = value->next;
	}

	return value->value;
}

// TODO Add init kv table function
void init(struct kv *table, const int capacity)
{
	table->htable = (struct element **) malloc(capacity * sizeof(struct element *));
	memset(table->htable, 0, sizeof(capacity * sizeof(struct element *)));
	table->capacity = capacity;
}

void destory(struct kv *table)
{
	free(table->htable);
	table->capacity = 0;
}

// TODO rehash function

int main()
{
	int i;
	struct kv table;
	init(&table, 256);
	char key[10];
	char *value;
	for (i = 0; i < 100; ++i) {
		sprintf(key, "%d", i);
		value = (char *)malloc(10*sizeof(char));
		sprintf(value, "%d", i);
		set(&table, key, value);
	}

	for (i = 0; i < 100; ++i) {
		sprintf(key, "%d", i);
		printf("%s => %s\n", key, get(&table, key));
	}

	return 0;
}
