#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct treenode {
	char *word;
	int count;
	struct treenode *left;
	struct treenode *right;
};
typedef struct treenode TREENODE;
typedef TREENODE* TREENODEPtr;

struct listNode {
	char *word;
	int count;
	struct listNode *next;
};
typedef struct listNode LISTNODE;
typedef LISTNODE *LISTNODEPtr;

void to_lower(char*buf);
void insertNode(TREENODEPtr*, char*);
void inOrder(TREENODEPtr);
void insert(LISTNODEPtr *, char*, int);
void print_to_file(LISTNODEPtr, FILE *);

LISTNODEPtr start = NULL;

int main(int argc, char *argv[]) {
	FILE *f, *w;
	TREENODEPtr root = NULL;
	char buf[64], c, ch = 0, *p = buf;
	int count = 0;
	f = fopen(argv[1], "r");
	w = fopen(argv[2], "w");
	
	while(!feof(f)) {
		c = fgetc(f);
		if(isalpha(c)) {
			*p++ = c;
		}
		else if(isalpha(ch)) {
			*p = 0;
			p = buf;
			to_lower(buf);
			insertNode(&root, buf);
			count++;
		}
		ch = c;
	}
	printf("%d", count);
	inOrder(root);
	print_to_file(start, w);
	
	fclose(f);
	fclose(w);
	return 0;
}

void to_lower(char* data){
	while(*data) {
		*data = tolower(*data);
		*data++;
	}
}

void insertNode(TREENODEPtr* root, char* data){
	if(*root == NULL) {
		*root = (TREENODE*)malloc(sizeof(TREENODE));
		if(*root != NULL) {
			(*root)->word = strdup(data);
			(*root)->left = NULL;
			(*root)->right = NULL;
			(*root)->count = 1;
		}
		else
			printf("Not inserted %s", data);
	}
	else {
		if(strcmp(data, (*root)->word) > 0)
			insertNode(&((*root)->right), data);
		else
			if(strcmp(data, (*root)->word) < 0)
				insertNode(&((*root)->left ), data);
			else
				((*root)->count)++;
			
	}
}

void inOrder(TREENODEPtr root) {
	if (root != NULL) {
		inOrder(root->left);
		insert(&start, root->word, root->count);
		inOrder(root->right);
	}
}

void insert(LISTNODEPtr *start, char* data, int coun) {
	LISTNODEPtr newP, prev, curr;
	
	newP = (LISTNODE*) malloc(sizeof(LISTNODE));
	
	if(newP != NULL) {
		newP->word = strdup(data);
		newP->count = coun;
		newP->next = NULL;
		
		prev = NULL;
		curr = *start;
		
		while(curr != NULL && coun < curr->count) {
			prev = curr;
			curr = curr->next;
		}
		
		if (prev == NULL) {
			newP->next = *start;
			*start = newP;
		}
		else {
			prev->next = newP;
			newP->next = curr;
		}
	}
	else
		printf("Not inserted. No memory available.\n");
}

void print_to_file(LISTNODEPtr curr, FILE *w) {
	if (curr == NULL)
		printf("List is empty.\n\n");
	else {
		while(curr != NULL) {
			fprintf(w, "%s---%d\n", curr->word, curr->count);
			curr = curr->next;
		}
	}
}
