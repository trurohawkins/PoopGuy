Value *makeValue(char *k, float val) {
	Value *v = (Value*)calloc(1, sizeof(Value));
	//printf("%i\n", strlen(k));
	v->key = (char*)calloc(strlen(k)+1, sizeof(char));
	strcpy(v->key, k);
	v->value = val;
	return v;
}

void freeValue(void *v) {
	Value *val = (Value*)v;
	free(val->key);
	free(val);
}

void addStat(Form *f, char *k, float val) {
	Value *v = makeValue(k, val);
	addToList((linkedList**)(&f->stats), v);
}

float *getStat(Form *f, char *stat) {
	linkedList *cur = (linkedList*)(f->stats);
	while(cur != NULL) {
		if (cur->data != NULL) {
			Value *v = (Value*)cur->data;
			if (strcmp(v->key, stat) == 0) {
				return &(v->value);
			}
		}
		cur = cur->next;
	}
	return NULL;
}

void setStat(Form *f, char *stat, float val) {
	linkedList *cur = (linkedList*)(f->stats);
	while(cur != NULL) {
		if (cur->data != NULL) {
			Value *v = (Value*)cur->data;
			if (strcmp(v->key, stat) == 0) {
				v->value = val;
				return;
			}
		}
		cur = cur->next;
	}
}
