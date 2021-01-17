linkedList *makeList() {
	linkedList *nl = (linkedList*) calloc(1, sizeof(linkedList));
	nl->data = 0;
	nl->next = 0;
//	nl->prev = 0;
	return nl;
}

void addToList(linkedList *head, void *item) {
	while(head->data != 0) {
		if (head->next == 0) {
			head->next = makeList();
	//	       head->->prev = head;	
		}
		head = head->next;
	}
	head->data = item;
}

void *removeFromList(linkedList **head, void *item) {
/*
	linkedList *pre = 0;
	linkedList *cur = *head;
	while (cur != 0) {
		if (cur->data == item) {
			linkedList *tmp = cur;
			if (pre != 0) {
				pre->next = cur->next;
			} else {
				head = cur->next;
			}
			deleteAction(tmp->data);
			free(tmp);
		}
		if (cur->next != 0) {
			pre = cur;
			cur = cur->next;
		} else {
			cur = 0;
		}
	}
*/
	void *data = 0;
	if ((*head)->data == item) {
		linkedList *oh = *head;
		(*head) = (*head)->next;
		data = oh->data;
		free(oh);
	}
	linkedList *tmp = (*head)->next;
	linkedList *pre = *head;
	while (tmp != 0) {
		if (tmp->data == item) {
			pre->next = tmp->next;
			data = tmp->data;
			free(tmp);
			tmp = pre->next;
		} else {
			tmp = tmp->next;
		}
		pre = pre->next;
	}
	return data;
}

void freeList(linkedList **ll) {
	linkedList *cur = *ll;
	linkedList *next;
	while (cur != NULL) {
		next = cur->next;
		free(cur);
		cur = next;
	}	
}
