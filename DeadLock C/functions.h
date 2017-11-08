#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

int Requests(struct node ** processlist, char process, int resourcelist);
void Clear(struct node * processlist[], int resourcelist[]);
int Printlist(struct node ** head, int length);
int Removes(struct node ** processlist, char process);
int Kill(struct node * processlist[], char process, int resourcelist[]);
int Releases(struct node ** processlist, char process);
int DeadLockDectection(struct node * processlist[], int resourcelist[]);


#endif