#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	char data;
	struct node * next;
};

struct node * HEAD = NULL;
int SIZE = 0;
//Error msg
void InvalidInput(){
	fprintf(stderr,"Input not valid\n");
}

//Add to head
void Push(struct node ** ptpt, char data){
	struct node * newNode = malloc(sizeof(struct node));
	newNode -> data = data;
	newNode -> next = * ptpt;
	*ptpt = newNode;
	SIZE++;
}
//??
void Insert(struct node ** ptpt, char data){
	struct node * newNode = malloc(sizeof(struct node));
	newNode -> next = * ptpt;
	newNode -> data = data;
	*ptpt = newNode;
}
//Add to end
struct node * Append(struct node ** ptpt, char data){
	struct node * current = *ptpt;
	if(current == NULL){
		Push(ptpt, data);
	}else{
		while(current -> next != NULL){
			current = current -> next;
		}
		Push(&(current -> next), data);
	}
	SIZE++;
}
//Print list
void PrintList(){
	struct node * current = HEAD;
	if(HEAD == NULL){
		printf("-\n");
	}else{
		while(current != NULL){
			printf("%c",current->data);
			if(current -> next != NULL){
				printf("-");
			}
			current = current -> next;
		}
		printf("\n");
	}
}
//Get size
void Length(){
	if(HEAD == NULL && SIZE == 0){
		printf("0\n");
	}else{
		printf("%d\n",SIZE);
	}
}

node Find(char data){
	if(HEAD == NULL){
		return NULL;
	}else if(HEAD.data == data){
		return &HEAD;
	}
}
