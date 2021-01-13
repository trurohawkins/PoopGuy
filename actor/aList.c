void addToList(linkedList_t *head, void *item) {
	while(head->data != 0) {
		if (head->next == 0) {
			head->next =(linkedList_t*)malloc(sizeof(struct linkedList)); 
		}
		head = head->next;
	}
	head->data = item;
}

void freeList(linkedList_t **ll) {
	linkedList_t *cur = *ll;
	linkedList_t *next;
	while (cur != NULL) {
		next = cur->next;
		free(cur);
		cur = next;
	}	
}
