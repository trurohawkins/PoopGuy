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

bool cmpList(linkedList **head, void *item, bool (*cmp)(void*, void*)) {
	linkedList *cur = *head;
	while (cur != NULL) {
		if (cur->data != NULL) {
			if (cmp(cur->data,item) == true) {
				return true;
			}
		}
		cur = cur->next;
	}
	return false;
}

void *checkList(linkedList **head, bool (*chk)(void*)) {
	linkedList *cur = *head;
	while (cur != NULL) {
		if (cur->data != NULL) {
			if (chk(cur->data) == true) {
				return cur->data;
			}
		}
		cur = cur->next;
	}
	return false;
}

void *printList(linkedList **head, char *listName, void (*print)(void*)) {
	linkedList *cur = *head;
	printf("printing list %s\n", listName);
	int num = 0;
	while (cur != NULL) {
		printf("[%i] ", num);
		if (cur->data != NULL) {
			print(cur->data);
		}
		cur = cur->next;
		num++;
	}
	printf("printing done\n");
}

void *removeFromList(linkedList **head, void *item) {
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

void *removeFromListCheck(linkedList **head, bool (*chk)(void*)) {
	void *data = 0;
	if ((head) != NULL) {
	if ((*head)->data != NULL) {
		if (chk((*head)->data)) {
			linkedList *oh = *head;
			(*head) = (*head)->next;
			data = oh->data;
			free(oh);
		} else {
			linkedList *tmp = (*head)->next;
			linkedList *pre = *head;
			while (tmp != 0) {
				if (chk(tmp->data)) {
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
	}
	}
	return data;
}

void freeList(linkedList **ll) {
	linkedList *cur = *ll;
	linkedList *next = 0;
	while (cur != NULL) {
		next = cur->next;
		if (cur->data != NULL) {
			free(cur->data);
		}
		free(cur);
		cur = next;
	}	
}

void freeListSaveObj(linkedList **ll) {
	linkedList *cur = *ll;
	linkedList *next = 0;
	while (cur != NULL) {
		next = cur->next;
		free(cur);
		cur = next;
	}	
}

void deleteList(linkedList **ll, void (*deleteFunc)(void*)) {
	linkedList *cur = *ll;
	linkedList *next = 0;
	while (cur != NULL) {
		next = cur->next;
		if (cur->data) {
			deleteFunc(cur->data);
		}
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
