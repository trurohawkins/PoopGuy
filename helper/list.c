linkedList *makeList() {
	linkedList *nl = (linkedList*) calloc(1, sizeof(linkedList));
	nl->data = 0;
	nl->next = 0;
//	nl->prev = 0;
	return nl;
}

void addToList(linkedList **head, void *item) {
	//printf("adding to list");
	if ((*head) == 0) {
		//printf("adding and making new list\n");
		(*head) = makeList();
		(*head)->data = item;
	} else {
		linkedList *tmp = *head;
		while(tmp->data != 0) {
		//	printf("searching through list to add\n");
			if (tmp->next == 0) {
				tmp->next = makeList();
			}
			tmp = tmp->next;
		}
	tmp->data = item;
	}
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
	} else {
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
	}
	return data;
}

void freeList(linkedList **ll) {
	linkedList *cur = *ll;
	linkedList *next = 0;
	while (cur != NULL) {
		next = cur->next;
		free(cur->data);
		free(cur);
		cur = next;
	}	
}

void *removeFromListInt(linkedList **head, int item) {
	void *data = 0;
	if (*head == 0 || (*head)->data == 0) {
		return data;
	}
	if (*(int*)((*head)->data) == item) {
		linkedList *oh = *head;
		(*head) = (*head)->next;
		data = oh->data;
		free(oh);
	} else {
		linkedList *tmp = (*head)->next;
		linkedList *pre = *head;
		while (tmp != 0) {
			if (*((int*)(tmp->data)) == item) {
				pre->next = tmp->next;
				data = tmp->data;
				free(tmp);
				tmp = pre->next;
			} else {
				tmp = tmp->next;
			}
			pre = pre->next;
		}
	}
	return data;
}
