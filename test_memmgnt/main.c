#include <stdio.h>
#include <stdlib.h>

#include "memmgnt.h"

#define CHUNK_SIZE 1024

struct node {
	struct node* next;
	void* ptr;
};

int total = 0;

void fill_memory(struct node* head) {
	while (head && (head->ptr = memmgnt_malloc(CHUNK_SIZE))) {
		printf("Allocated %d Bytes at 0x%p, total %d\n", CHUNK_SIZE, head->ptr, total += CHUNK_SIZE);
		head = head->next = memmgnt_malloc(sizeof(struct node));
		head->ptr =  0;
		head->next = 0;
		total += sizeof(struct node);
	}
}

void free_memory(struct node* head) {
	struct node* old_head;

	while (head) {
		if (head->ptr) {
			printf("Free %d Bytes at 0x%p, total %d\n", CHUNK_SIZE, head->ptr, total-= CHUNK_SIZE);
			memmgnt_free(head->ptr);
		}

		if (head->next) {
			old_head = head;
			head = head->next;
			memmgnt_free(old_head);
		} else {
		    memmgnt_free(head);
			head = 0;
		}
		total -= sizeof(struct node);
	}
}

int main(void) {
	struct node* head;

	while (1) {
		head = memmgnt_malloc(sizeof(struct node));
		total += sizeof(struct node);

		fill_memory(head);
		free_memory(head);
	}

	return 0;
}
