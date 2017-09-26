#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "error.h"

struct node * HEAD = NULL;
int SIZE = 0;

//Add to head
void Push(struct node ** ptpt, char data){
	if(data < 65 || data > 90){
		InvalidInput();
	}else{
		struct node * newNode = malloc(sizeof(struct node));
		newNode -> data = data;
		newNode -> next = * ptpt;
		*ptpt = newNode;
		SIZE++;
	}
}
//Bingo
void InsertBefore(struct node * ptpt, char data){
	if(data < 65 || data > 90 || HEAD == NULL){
		InvalidInput();
	}else if(ptpt == NULL){
		Push(&HEAD,data);
	}else{
		Push(&(ptpt)->next,data);
	}
}
//Bingo 
void InsertAfter(struct node * ptpt, char data){
	if(data < 65 || data > 90 || HEAD == NULL){
		InvalidInput();
	}else if(ptpt == NULL){
		Push(&HEAD->next,data);
	}else{
		struct node * last = HEAD;
		while(last -> next != NULL){
			last = last -> next;
		}
		if(ptpt == last){
			Push(&last,data);
		}else{
			Push(&(ptpt)->next->next,data);
		}
	}
}

//Add to end
struct node * Append(struct node ** ptpt, char data){
	struct node * current = *ptpt;
	if(data < 65 || data > 90){
		InvalidInput();
	}else if(current == NULL){
		Push(ptpt, data);
		SIZE++;
	}else{
		while(current -> next != NULL){
			current = current -> next;
		}
		Push(&(current -> next), data);
		SIZE++;
	}
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
//Returns the previous node before the node with the exact match
//If it happens to be the first node or head node then return that rather
struct node * Find(struct node ** ptpt, char data){
	if(ptpt == NULL || HEAD == NULL){
		return 0;
	}else if((*ptpt) -> data == data){
		return NULL;
	}else{
		struct node * current = *ptpt;
		while(current -> next != NULL && current -> next -> data != data){
			current = current -> next;
		}
		if(current -> next== NULL){
			return 0;
		}else{
			return current;
		}
	}
}
//Bingo
void Remove(struct node ** ptpt, char data){
	if(HEAD == NULL || data < 65 || data > 90){
		InvalidInput();
	}else if(HEAD -> data == data){
		HEAD = HEAD -> next;
		SIZE--;
	}else{
		struct node * delete = Find(ptpt,data);
		if(delete != NULL){
			delete -> next = delete -> next -> next;
			SIZE--;
		}else{
			InvalidInput();
		}

	}
}

void Head(){
	if(HEAD == NULL){
		InvalidInput();
	}else{
		printf("%c\n", HEAD -> data);
	}
}

void Tail(){
	if(HEAD == NULL){
		InvalidInput();
	}else{
		struct node * current = HEAD;
		while(current -> next != NULL){
			current = current -> next;
		}
		printf("%c\n", current -> data);
	}
}

