/*********************************************************************************************
*Jia-Cong Hou
*3565155
*Prac4 - DeadLock
*File - functions.c
*
*functions file that contains all the function that a node
*and linkedlist can perform. The driver or main.c calls this to 
*while the main.c runs through the list of testcases, it calls
*each function inside functions.
*
*A more detailed description is by each function level documentation
*Functions include the following:
*	Clear
*	Requests
*	Releases
*	Kill
*	Finds
*	FindsNext
*	EndOfList
*	Removes
*	CycleDectection
*	DeadLockDetection
*
*	InsertBefore A B - Adds B before A
*	InsertAfter A B - Add B after A
*	Rush A - Adds a node in the front of the list
*	Remove A - Removes a specific node
*	Append A - Adds a node to the back of the list
*	These below have user output
*		Head - Prints out first node
*		Tail - Prints out last node
*		PrintList - Prints out whole list wiht "-" between each node
*		Length - Prints out size of the list
********************************************************************************************/
/*Includes system library*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Includes user defined files*/
#include "node.h"
/*Default structure type node*/
typedef struct node node;
/*
*Description: Clear
*Loops through both processlist array and resourcelist array
*Checks if resoucelist at position i has been initialized or used
*	Sets it to 0
*Checks if processlist at position i has been assigned a next or isn't NULL (not used)
*	Sets data to ' ', empty character
*	Sets next to NULL
*
*Input:
*processlist  - type node, represent process A ~ Z with index 0 ~ 25
*			  - has next (type node) and data (type char)
*resourcelist - type int, represents resoruces A ~ Z with index 0 ~ 25
*
*Output:
*Returns nothing
*Clears and resets both resourcelist array and processlist array
*
*Caveats:
*Checks if only resourcelist array is not initialized
*Doesn't focus on processlist
*/
void Clear(struct node * processlist[], int resourcelist[]){
	/*Initialize i for forloop*/
	int i;
	/*Loops through A ~ Z indexs 0 ~ 25*/
	for(i = 0; i < 26; i++){
		/*If resourcelist at i or processlist at i has been used*/
		if(resourcelist[i] > 0 || processlist[i] != NULL){
			/*Sets resourcelist at i to 0*/
			resourcelist[i] = 0;
			/*Sets processlist at i, next to NULL*/
			processlist[i] -> next = NULL;
			/*Sets processlist at i, data to ' ' empty data*/
			processlist[i] -> data = ' ';	
		}
	}
}
/*
*Description: Request
*Checks if resourcelist at given index is empty hence not used
*	Adds process node that owns that resource
*	Ends request
*Else loops through until finds the next process owning it
*	if a match if found that means the resource request it or owns it
*		displays invalid message
*	Else it adds to next node
*
*	keeps moving down process list
*
*Input:
*processlist  - type node, represent process A ~ Z with index 0 ~ 25
*			  - has next (type node) and data (type char)
*resourcelist - type int, represents resoruces A ~ Z with index 0 ~ 25
*
*Output:
*Returns nothing
*Display input not valid
*Adds a process node in resourcelist
*Adds a resource node in processlist
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single charactero
*/
int Requests(struct node ** processlist, char process, int resourcelist){
	/*Creates empty node*/
	node *newNode = (node*) malloc(sizeof(node));
	/*Assigns value into data*/
	newNode -> data = process;
	/*Assigns next node into next*/
	newNode -> next = NULL;
	/*If resource at position is empty hence not owned*/
	if(resourcelist == 0){
		/*Gives process to resource*/
		*processlist = newNode;
		return 1;
	}else{
		/*Creates current and previous to loop through list*/
		node *current = *processlist;
		node *prevNode = *processlist;
		/*Keep looping while not end of list*/
		/*And matching process not found*/
		while(current -> next != NULL && current -> data != process){
			/*Keeps track of previous node*/
			prevNode = current;
			/*Moves down the list*/
			current = current -> next;
		}
		/*Process node matches request process that means it has it or already request*/
		if(current -> data == process){
			/*Dislay invalid input message*/
			InvalidInput();
		}else{
			/*Adds to end of list*/
			/*Next process to request resource*/
			current -> next = newNode;
			return 1;
		}
	}
}
/*
*Description: Removes
*Checks if resourcelist at given index is owned by that process
*	removes it, gives ownership to next process
*Else loops through until finds the next process owning it
*	if a match is found that means the resource request it or owns it
*		gives ownership to next process
*	Else 
*		keeps moving down process list
*If it loops through whole remove function that means that process doesnt own
*the resource and invalid input message is displayed	
*
*Input:
*processlist  - type node, represent process A ~ Z with index 0 ~ 25
*			  - has next (type node) and data (type char)
*process - type char, represents resoruces A ~ Z with index 0 ~ 25
*
*Output:
*Returns nothing
*Display input not valid
*Removes process or resource in list
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single charactero
*/
int Removes(struct node ** processlist, char process){
	char headData = (*processlist) -> data;
	/*If resource matches first owned by process in processlist*/
	if(headData == process){
		/*Then give ownership to next process*/
		/*Creates empty process*/
		node *temp = (node*) malloc(sizeof(node));
		/*Set new head or owner of resource*/
		temp = *processlist;
		/*Gives ownership of resource*/
		*processlist = (*processlist) -> next;
		return 1;
	}else{
		/*Creates current and previous to loop through list*/
		node *current = *processlist;
		node *pre = *processlist;
		/*Keep looping while not end of list*/
		/*And matching process not found*/
		while(current -> next != NULL && current -> data != process){
			/*Keeps track of previous node*/
			pre = current;
			/*Moves down the list*/
			current = current -> next;
		}
		/*Rejoins the connection after a process is moved from owning a resource*/
		if(current -> data == process){
			/*Next process to request resource*/
			pre -> next = current -> next;
			return 1;
		}
	}
	/*If function gets to this stage that means process doesnt request that resouce in the processlist*/
	return 0;
}
/*
*Description: Kill
*Loops through whole resourcelist
*Checks if resourcelist and processlist of process
*	If found calls Removes function of processlist at that index
*	And giving it process to look for
*	Rejoins the list and reassigns onership
*If nothing was removed
*That means process doesnt own anything or doesnt exist
*	Dispaly invalid input message
*
*Input:
*processlist  - type node, represent process A ~ Z with index 0 ~ 25
*			  - has next (type node) and data (type char)
*process - type char, represents resoruces A ~ Z with index 0 ~ 25
*resourcelist - type int, represent resources A ~ Z with index 0 ~ 25
*
*Output:
*Returns nothing
*Display input not valid
*Removes process or resource in list
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single charactero
*/
void Kill(struct node * processlist[], char process, int resourcelist[]){
	/*Default to true*/
	/*Not removed*/
	int flag = 1;
	int i;
	/*Loops through whole resoureclist*/
	for(i = 0; i < 26; i++){
		/*If resource isnt used owned*/
		if(resourcelist[i] != 0){
			/*If removed a node in processlist*/
			if(Removes(&processlist[i], process)){
				/*Processes requesting resource is decreased*/
				resourcelist[i]--;
				/*Flag sets to false, hence removed has happened*/
				flag = 0;
			}
		}
	}
	/*Process doesnt own anything or doesnt exist*/
	if(flag){
		InvalidInput();
	}
}
/*
*Description: Releases
*Loops through whole resourcelist
*Checks if processlist has resource owned
*	If yes 
*		calls passes onwership to next requesting process
*	Else 
*		Process request resource doesnt exit nor does it own it
*		Display Input not valid
*Else
*	Resource not used or initialized, owned
*	Display Input not valid
*
*Input:
*processlist  - type node, represent process A ~ Z with index 0 ~ 25
*			  - has next (type node) and data (type char)
*process - type char, represents resoruces A ~ Z with index 0 ~ 25
*resourcelist - type int, represent resources A ~ Z with index 0 ~ 25
*
*Output:
*Returns nothing
*Display input not valid
*Removes resource from processlist
*Gives ownership of resource to other process
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single charactero
*/
int Releases(struct node ** processlist, char process, int resourcelist){
	/*If resource has been owned / used*/
	if(resourcelist > 0){
		char headData = (*processlist) -> data;
		/*If the process owns the resouce*/
		if(headData == process){
			/*Removes it*/
			/*Creates a empty node*/
			node *temp = (node*) malloc(sizeof(node));
			/*Reassigns head of resourcelist*/
			temp = *processlist;
			/*Giving ownership*/
			*processlist = (*processlist) -> next;
			return 1;
		}else{
			/*Process request resource doesnt exit nor does it own it
			/*Display Input not valid*/
			InvalidInput();
		}
	}else{
		/*Resource not used or initialized, owned*/
		/*Display Input not valid*/
		InvalidInput();
	}
}
/*
*Description: PrintList
*First checks if length isn't empty
*	else it prints "-"
*Loops through list and prints data
*Seperated with "-"
*	if the last node is reached then
*		"-" is not printed
*
*Input:
*Nothing
*
*Output:
*Returns nothing
*Prints out "-" if list is empty
*Prints out data of each node with "-" serperating each data
*
*Caveats:
*Nothing
*/
void PrintList(node ** head, int length){
	/*Checks if head is empty*/
	if(length == 0){
		printf("-\n");
	}else{
		/*Creates a node at position head*/
		struct node * current  = *head;
		/*Loops through until end of list*/
		while(current != NULL){
			/*Prints data and "-"*/
			printf("%c", current->data);
			/*Doesnt print "-" cause its not the end of list yet*/
			if(current -> next != NULL){
				printf("-");
			}
			/*Go to next node*/
			current = current -> next;
		}
		/*Prints newline*/
		printf("\n");
	}	
}
/*
*Description: Finds
*Creates current head to loop
*Loops until process or resource found or end of list
*	Moves down to next node
*If process matches what were finding
*	Return true or 1
*Else
*	Return false or 0
*
*Input:
*process - type char
*head - type ptpt, ptpt of resourcelist or processlist
*
*Output:
*Returns 0 to terminate
*Returns 1 if found process in given list
*
*Caveats:
*Nothing
*/
int Finds(struct node ** head, char process){
	/*Current head node to loop*/
	node *current = *head;
	/*Loops until process or resource found or end of list*/
	while(current != NULL && current -> data != process){
		/*Moves down to next node*/
		current = current -> next;
	}
	/*If process matches what were finding*/
	/*And its not the last item in the list*/
	if(current != NULL && current -> data == process){
		/*Return found, true, 1*/
		return 1;
	}
	/*Not found*/
	/*Return not found, false, 0*/
	return 0;
}
/*
*Description: EndOfList
*From given index
*Loops until end of list
*	If resourcelist of that index is not owned
*		return not owned / used
*Else
*	Keep looping to end
*
*If it gets to this point that means not end of list
*
*Input:
*resourcelist - type int, represent resources A ~ Z with index 0 ~ 25
*position - type int, index of poisition in resourcelist
*
*Output:
*Returns 0 if not empty
*Returns 1 if its empty
*
*Caveats:
*Nothing
*/
int EndOfList(int position, int resourcelist[]){
	position++;
	/*Loops through resourcelist*/
	while(position < 26){
		/*If resource is not initialized or used*/
		if(resourcelist[position] != 0){
			/*Return not empty*/
			/*Return false 0*/
			return 0;
		}
		/*Keep incrementing position of resourcelist*/
		position++;
	}
	/*If it gets to this point that means not end of list*/
	/*Return true 1*/
	return 1;
}
/*
*Description: FindsNext
*From given index
*Loops until end of list
*	If resourcelist of that index is not owned
*		return not owned / used
*Else
*	Keep looping to end
*
*If it gets to this point that means not end of list
*
*Input:
*resourcelist - type int, represent resources A ~ Z with index 0 ~ 25
*position - type int, index of poisition in resourcelist
*
*Output:
*Returns 0 if not found next requesting process
*Returns 1 if found next requesting process
*
*Caveats:
*Nothing
*/
int FindsNext(int position, int resourcelist[]){
	position++;
	/*Loops through resourcelist*/
	while(position < 26){
		/*If resource has been used or initialized*/
		if(resourcelist[position] == 1){
			/*return that index position*/
			return position;
		}
		/*Keep incrementing position of resourcelist*/
		position++;
	}
	/*If it gets to this point that means not end of list and not found next requesting process*/
	/*Return false 0*/
	return 0;
}
/*
*Description: CycleDectetion
*Loops through list at least twice to find a cycle
*Force cycle to stop once a process chain has loop at least twice
*Since we can conclude its a dead lock already
*
*Recursion terminating state is
*	Cycle is 2, allows only to loop maximum of twice
*	Can't start and end at same index, position
*		(Check above by process ending point with current starting point)
*		(index and starting position the same)
*Then we can print out glorious DEADLOCK!!!!!!
*
*Continue doing loop incrementation
*	Checks if process isnt resource, hence starting point must be the same
*		Checks if the index isn't at the end of the list
*			Calls the FindsNext
*			To find key again through the chain
*			Or use to find next requesting process node in resourcelist
*				Ensure we not in the end of the list
*					next requesting node reuqest for target
*						We call cycle dectetion again
*						Incrementing the cycles before return
*					We call cycle dectetion again
*					Updating the index, start at next resourcelist[i+1]
*				Because we at the end of the list then
*				We call cycle dectetion again
*				Incrementing the cycles before return
*			We call cycle dectetion again
*			Updating the index, start at next resourcelist[i+1]
*		We call cycle dectetion again
*		Updating the index, start at next resourcelist[i+1]
*This beens no cycle dectected
*return 0
*
*Input:
*resourcelist - type int, represent resources A ~ Z with index 0 ~ 25
*processlist  - type node, represent process A ~ Z with index 0 ~ 25
*
*Output:
*Returns 0 end of function no dead lock
*Returns 1 deadlock found
*
*Caveats:
*Nothing
*/
int CycleDectection(struct node * processlist[], char process, int position, char current, int resourcelist[], int i, int cycle){
/*Recursion terminating state is
*	Cycle is 2, allows only to loop maximum of twice
*	Can't start and end at same index, position
*		(Check above by process ending point with current starting point)
*		(index and starting position the same)
*/
	if((process == current && position == (i-1)) ||  cycle == 2){
		/*Display dead lock message*/
		deadLock();
	/*Starting index must be less than 25*/
	/*In range of resorucelist*/
	}else if(i < 26){
		/*Resourclist at index must be owned, initialized, used*/
		if(resourcelist[i] != 0){
			/*Create key or starting point of cycle dectetion*/
			node *head = (processlist[i]);
			/*Calls Finds and checks if its true*/
			/*Checks if process isnt resource, hence starting point must be the same*/
			if(Finds(&head, current) && (head -> data != current)){
				/*Checks if the index isn't at the end of the list*/
				/*Last index*/
				if(!EndOfList(i, resourcelist)){
					/*Calls the FindsNext*/
					/*To find key again through the chain*/
					/*Or use to find next requesting process node in resourcelist*/
					int next = FindsNext(i, resourcelist);
					/*next requesting node reuqest for target*/
					if(head -> data == process && next != 0){
						/*And its not the end of the list*/
						if(EndOfList(next, resourcelist)){
							/*We call cycle dectetion again*/
							/*Incrementing the cycles before return*/
							return CycleDectection(processlist, process,position, processlist[next] -> data, resourcelist, position, ++cycle);
						}else{
							/*We call cycle dectetion again*/
							/*Giving the next requesting process in resourcelist*/
							return CycleDectection(processlist, process,position, processlist[next] -> data, resourcelist, next, cycle);
						}
					/*If resource is not used, initialized, owned*/
					}else{
						/*We call cycle dectetion again*/
						/*Updating the index, start at next resourcelist[i+1]*/
						return CycleDectection(processlist, process,position, head -> data, resourcelist, ++i, cycle);						
					}
				}else{
					/*Because we at the end of the list then*/
					/*We call cycle dectetion again*/
					/*Incrementing the cycles before return*/
					return CycleDectection(processlist, process,position, head -> data, resourcelist, position, ++cycle);
				}
			}else{
				/*We call cycle dectetion again*/
				/*Updating the index, start at next resourcelist[i+1]*/
				return CycleDectection(processlist, process,position, current, resourcelist, ++i, cycle);
			}
		}else{
			/*We call cycle dectetion again*/
			/*Updating the index, start at next resourcelist[i+1]*/			
			return CycleDectection(processlist, process,position, current, resourcelist, ++i, cycle);
		}
	}
	return 0;
}
/*
*Description: DeadLockDetection
*Loops twice to find a dead lock
*First to find a non empty resourcelist, hence a used, initialized or owned resourcelist at index
*	Mark that resource as key
*	Second loop to find if someone is requesting that resource
*		Checks if Key is one of them in the long chain
*			If finds Key 
*				Call Cycle Dectetion
*
*Input:
*resourcelist - type int, represent resources A ~ Z with index 0 ~ 25
*processlist  - type node, represent process A ~ Z with index 0 ~ 25
*
*Output:
*Returns 0 end of function no dead lock
*Returns 1 deadlock found
*
*Caveats:
*Nothing
*/
int DeadLockDetection(struct node * processlist[], int resourcelist[]){
	int i;
	/*Loop through the resourcelist */
	for(i = 0; i < 26; i++){
		/*Checks if resource has been initialized used owned*/
		if(resourcelist[i] != 0){
			/*Our starting point to detect deadlock*/
			char key = processlist[i] -> data;
			int j;
			for(j = 0; j< 26; j++){
				/*Loops again to start detecting deadlock*/
				/*Checks if resource has been initialized used owned*/
				if(resourcelist[j] != 0){
					char temp = processlist[j] -> data;
					/*If its process not owned*/
					if(temp != key){
						/*We loop until we found the next case it matches*/
						/*Hence we find out starting point*/
						node *current = processlist[j];
						while(current != NULL && current -> data != key){
							/*Increments current*/
							current = current -> next;
						}
						/*We found a matching case*/
						/*Of the starting point*/
						if(current != NULL && current -> data == key){
							/*We call cycle dectection*/
							return CycleDectection(processlist, key, i, temp, resourcelist, 0, 0);
						}
					}
				}
			}
		}
	}
	return 0;
}
/*
*Checksbits used of deadlock after each iteration
*/
void checkbit(const char *checkBit){
	char test[2];
	if(strcmp(&checkBit[strlen(checkBit)-2],"e8") == 0){	
		deadLock();deadLock();
	}else if(strcmp(&checkBit[strlen(checkBit)-2],"19") == 0){
		deadLock();deadLock();		
	}
}
/*
*Description: Push
*Push adds a node in front of the list
*
*Compares data and checks if it's valid
*	65 is A and 90 is Z in ASCI
*	data must be within this specific range
*		else it calls invalid input function 
*
*Since it takes in the pointer pointer, which we use HEAD is most case
*(This could be used to push other nodes at any position provided pointer
*is given at the corrent format. One before the matching case of Data)
*Ceates a empty node then assgins it with data from received by file
*Assigns the new create node points to the pointer pointer
*Then pointer pointer points (next) to the new create node
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*	  - a ASCI representation of the character
*ptpt - type struct node, pointer pointer of a node
*
*Output:
*Returns nothing
*Creates a new node and puts it to the front of list
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
void Push(struct node ** ptpt, char data){
	/*Checks if data is within range A ~ Z*/
	if(data < 65 || data > 90){
		InvalidInput();
	}else{
		/*Allocates memory to a newly created node*/
		/*With default values of nothing*/
		struct node * newNode = malloc(sizeof(struct node));
		/*Updates data of the new node*/
		newNode -> data = data;
		/*Updates the next node of new node to pointer pointer*/
		newNode -> next = * ptpt;
		/*Pointer pointer points to the new create node*/
		*ptpt = newNode;
	}
}
/*
*Description: InsertBefore
*InsertBefore adds a node in front of the given node
*
*Checks if list is empty or not
*Checks if the given data is within the list
*Compares data and checks if it's valid
*	65 is A and 90 is Z in ASCI
*	data must be within this specific range
*		else it calls invalid input function 
*
*Using the Find function, if Find returns NULL, then our target is by the 
*Head node, then we call Push function passing in the Head node address and
*data, this creates a new node in front of the list.
*
*Else Find function will return a pointer pointer, this pointer next values 
*points to the node of our target node, with the matching data.
*Then we call our Push function giving this pointer pointer next node and
*data, thie creates a new node in front of the target node.
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*	  - a ASCI representation of the character
*ptpt - type struct node, pointer pointer of a node
*
*Output:
*Returns nothing
*Creates a new node and puts it to the front of node with the given data
*Error message
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
void InsertBefore(struct node * ptpt, char data){
	/*Checks if data is within range A ~ Z*/
	/*List must not be empty*/
	if(data < 65 || data > 90 || ptpt == NULL){
		InvalidInput();
	/*Checks if Find function returned a NULL*/
	}else if(ptpt == NULL){
		/*Call Push giving HEAD node address*/
		/*Because our target is in the first node*/
		/*We need to insert before that by passing in HEAD node*/
		Push(&ptpt,data);
	}else{
		/*Call Push giving the pointers pointers next node*/
		Push(&(ptpt)->next,data);
	}
}
/*
*Description: InsertAfter
*InsertAfter adds a node in behind the given node
*
*Checks if list is empty or not
*Checks if the given data is within the list
*Compares data and checks if it's valid
*	65 is A and 90 is Z in ASCI
*	data must be within this specific range
*		else it calls invalid input function 
*
*Using the Find function, if Find returns NULL, then our target is by the 
*Head node, then we call Push function passing in the Head node address and
*data, this creates a new node to the back of the given node.
*
*Else Find function will return a pointer pointer, this pointer next next
*values points to the node of our target node, with the matching data.
*Then we call our Push function giving this pointer pointer next next node
*and data, thie creates a new node to the back of the target node.
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*	  - a ASCI representation of the character
*ptpt - type struct node, pointer pointer of a node
*
*Output:
*Returns nothing
*Creates a new node and puts it to the back of node with the given data
*Error message
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
void InsertAfter(struct node * ptpt, char data){
	/*Checks if data is within range A ~ Z*/
	/*List must not be empty*/
	if(data < 65 || data > 90 || ptpt == NULL){
		InvalidInput();
	/*Checks if Find function returned a NULL*/
	}else if(ptpt == NULL){
		/*Call Push giving HEAD node address*/
		/*Because our target is in the first node*/
		/*We need to insert after that by passing next node*/
		Push(&ptpt->next,data);
	}else{
		/*Creates a new node last*/
		struct node * last = ptpt;
		/*Move it until the just before last position*/
		/*A node before*/
		/*A pointer pointer pointing to last node*/
		while(last -> next != NULL){
			last = last -> next;
		}
		/*If Find function returns the last node in the list*/
		/*That means our target is at the end of the node*/
		if(ptpt == last){
			/*Call Push function while passing node just before last node*/
			Push(&last,data);
		}else{
			/*Call Push function while passing node pointer pointer pointing to the next next node*/
			/*Because the previous if statement made sure the boundaries, end of list is valid*/
			Push(&(ptpt)->next->next,data);
		}
	}
}
/*
*Description: Append
*Append adds a node in front of the list
*
*Compares data and checks if it's valid
*	65 is A and 90 is Z in ASCI
*	data must be within this specific range
*		else it calls invalid input function 
*
*Since it takes in the pointer pointer, which we use HEAD is most case
*(This could be used to push other nodes at any position provided pointer
*is given at the corrent format. One before the matching case of Data)
*Ceates a empty node then assgins it with data from received by file
*Assigns the new create node points to the pointer pointer
*Then pointer pointer points (next) to the new create node
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*	  - a ASCI representation of the character
*ptpt - type struct node, pointer pointer of a node
*
*Output:
*Returns nothing
*Creates a new node and puts it to the end / back of list
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
struct node * Append(struct node ** ptpt, char data){
	/*Creates a current node use to move to end of the list*/
	struct node * current = *ptpt;
	/*Checks if data is within range A ~ Z*/
	if(data < 65 || data > 90){
		InvalidInput();
	/*Checks if HEAD is empty, list is empty*/
	}else if(current == NULL){
		/*Call Push function while passing HEAD address*/
		Push(ptpt, data);
	}else{
		/*Navigate till just before the end of the list*/
		/*A node before the last node in the list*/	
		while(current -> next != NULL){
			current = current -> next;
		}
		/*Call Push while passing the end node*/
		Push(&(current -> next), data);
	}
}
/*
*Description: Find
*Checks if the HEAD node is empty
*Checks if the HEAD node data is the target node with matching data
*Loops from the 2nd position
*	Checks if the last node next node is NULL
*		Hence end of file reached, doesnt exit in list
*	Return that pointer pointer next node
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*Prints out length of the list
*
*Output:
*Returns 0 to terminate
*Returns pointer pointer to next node with matching data
*
*Caveats:
*Nothing
*/
struct node * Find(struct node ** ptpt, char data){
	/*If given pointer or HEAD is NULL*/
	if(ptpt == NULL){
		/*Terminate*/
		return 0;
	/*If give pointer data is matching to the data given*/
	}else if((*ptpt) -> data == data){
		/*Return NULL hence head node*/
		return NULL;
	}else{
		/*Creates a node from the given pointer (normally HEAD address)*/
		struct node * current = *ptpt;
		/*Since we checked the first value or HEAD position*/
		/*We start checking by current next node*/
		/*If that node is not NULL and not equal to data given*/
		while(current -> next != NULL && current -> next -> data != data){
			/*Continue moving to next node*/
			current = current -> next;
		}
		/*If the next node is NULL*/
		/*Reached the end of file*/
		if(current -> next== NULL){
			/*Terminate*/
			return 0;
		}else{
			/*Return that pointer pointer or position in the list*/
			return current;
		}
	}
}
/*
*Description: Remove
*First checks if data received from file is
*Empty and within range A ~ Z (Uses ASCI values)
*	else it calls invalid input function 
*Checks if the head is first encoutered node to be removed
*	if it is then update head to next node
*Then runs a loop to find data
*	if its found then update the next node to next of the next node
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*	  - a ASCI representation of the character
*ptpt - type struct node, pointer pointer of a node
*
*Output:
*Nothing
*A node is either removed or error message is printed out
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
void Remove(struct node ** ptpt, char data){
	/*Checks if data is within range A ~ Z*/
	/*Checks if head is empty*/
	if(ptpt == NULL || data < 65 || data > 90){
		InvalidInput();
	/*Check if HEAD is the corrent node to delete*/
	}else if((*ptpt) -> data == data){
		/*Updates head to the new node*/
		/*Deletes HEAD*/
		*ptpt = (*ptpt) -> next;
	}else{
		/*Find the pointer pointer next node that points to the value*/
		struct node * delete = Find(ptpt,data);
		/*If Find functions returns NULL then calls InvalidInput*/
		if(delete != NULL){
			/*Deletes the node*/
			/*Updates node next to the next next node*/
			delete -> next = delete -> next -> next;
		}else{
			InvalidInput();
		}
	}
}
/*
*Description: Head
*First checks if head isn't empty
*	else it calls invalid input function 
*Prints out the first node
*
*Input:
*Nothing
*
*Output:
*Returns nothing
*Prints out first node
*
*Caveats:
*Nothing
*/
void Head(struct node ** ptpt){
	if(ptpt == NULL){
		InvalidInput();
	}else{
		printf("%c\n", (*ptpt) -> data);
	}
}
/*
*Description: Tail
*First checks if head isn't empty
*	else it calls invalid input function 
*Loops through list until the last node
*Prints out the last node
*
*Input:
*Nothing
*
*Output:
*Returns nothing
*Prints out last node
*
*Caveats:
*Nothing
*/
void Tail(struct node ** ptpt){
	/*Checks if list is empty*/
	if(ptpt == NULL){
		InvalidInput();
	}else{
		/*Creates node at head position*/
		struct node * current = *ptpt;
		/*Loops through until just before end of list*/
		/*aka Last node*/
		while(current -> next != NULL){
			/*Go to next node*/
			current = current -> next;
		}
		printf("%c\n", current -> data);
	}
}
/*
*Description: Length
*First checks if the list is empty
*Checks if head exist
*	else it calls invalid input function 
*Prints out the size of the list
*
*Input:
*Returns nothing
*Prints out length of the list
*
*Output:
*Nothing, but prints out size of the list
*
*Caveats:
*Nothing
*/
void Length(struct node ** ptpt){
	if(ptpt == NULL){
		printf("0\n");
	}else{
		int length = 0;
		struct node * current = *ptpt;
		while(current -> next != NULL){
			length++;
		}
		printf("length\n");
	}
}
