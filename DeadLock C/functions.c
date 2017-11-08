#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "node.h"

typedef struct node node;

void Clear(struct node * processlist[], int resourcelist[]){
	int i;
	for(i = 0; i <= 25; i++){
		resourcelist[i] = 0;
		if(processlist[i] != NULL){
			processlist[i] -> next = NULL;
			processlist[i] -> data = ' ';
		}else{
			processlist[i] = NULL;
		}
	}
}

int Requests(struct node ** processlist, char process, int resourcelist){
	node *newNode = (node*) malloc(sizeof(node));
	newNode -> data = process;
	newNode -> next = NULL;

	if(resourcelist == 0){
		*processlist = newNode;
		return 1;
	}else{
		node *current = *processlist;
		node *prevNode = *processlist;
		while(current -> next != NULL && current -> data != process){
			prevNode = current;
			current = current -> next;
		}
		if(current -> data == process){
			return 0;
		}else{
			current -> next = newNode;
			return 1;
		}
		//snipplets
		/*node *current = (*processlist);
		node *pre = (*processlist);
		while(current -> next != NULL){
			if(current -> data == process){
				return 0;
			}else{
				pre = current;
				current = current -> next;
			}
		}
		if(current -> data == process){
			return 0;
		}else{
			current -> next = newNode;
			return 1;
		}*/
	}
}

int Removes(struct node ** processlist, char process){
	char headData = (*processlist) -> data;
	if(headData == process){
		node *temp = (node*) malloc(sizeof(node));
		temp = *processlist;
		*processlist = (*processlist) -> next;
		return 1;
	}else{
		node *current = *processlist;
		node *pre = *processlist;
		while(current -> next != NULL && current -> data != process){
			pre = current;
			current = current -> next;
		}
		if(current -> next != NULL && current -> data == process){
			pre -> next = current -> next;
			return 1;
		}
	}
	return 0;
}


void Kill(struct node * processlist[], char process, int resourcelist[]){
	int flag = 1;
	int i;
	for(i = 0; i <= 25; i++){
		if(resourcelist[i] != 0){
			if(Removes(&processlist[i], process)){
				resourcelist[i]--;
				flag = 0;
			}
		}
	}
	if(flag == 1){
		InvalidInput();
	}
}

int Releases(struct node ** processlist, char process){
	char headData = (*processlist) -> data;
	if(headData == process){
		node *temp = (node*) malloc(sizeof(node));
		temp = *processlist;
		*processlist = (*processlist) -> next;
		return 1;
	}else{
		InvalidInput();
		return 0;
	}
}


void PrintList(node ** head, int length){
	if(length == 0){
		printf("-\n");
	}else{
		printf("%s\n", "asdf");
		node *current = *head;
		while(current != NULL){
			printf("%c", current->data);
			if(current -> next != NULL){
				printf("-");
			}
			current = current -> next;
		}	
	}
	printf("\n");
}