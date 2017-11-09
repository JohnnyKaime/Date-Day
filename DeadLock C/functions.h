/************************************************************************************************************************************
*Jia-Cong Hou
*3565155
*Prac4 - DeadLock
*File - functions.h
*
*Header file that links to functions.c used in the driver
*main.c, serves as a "interface" to call each functions
*defined below
************************************************************************************************************************************/
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
/*Newly modified functions for prac4*/
int Requests(struct node ** processlist, char process, int resourcelist);
void Clear(struct node * processlist[], int resourcelist[]);
int Printlist(struct node ** process, int resourcelist);
int Removes(struct node ** processlist, char process);
int Kill(struct node * processlist[], char process, int resourcelist[]);
int Releases(struct node ** processlist, char process, int resourcelist);
int EndOfList(int position, int resourcelist[]);
int FindsNext(int position, int resourcelist[]);
int CycleDectection(struct node * processlist[], char process, int position, char current, int resourcelist[], int i, int cycle);
int Finds(struct node ** position, char process);
int DeadLockDetection(struct node * processlist[], int resourcelist[]);
/*Linkedlist functions remained for prac3 still in use*/
void Push(struct node ** ptpt, char data);
void InsertBefore(struct node * ptpt, char data);
void InsertAfter(struct node * ptpt, char data);
struct node * Append(struct node ** ptpt, char data);
struct node * Find(struct node ** ptpt, char data);
void Remove(struct node ** ptpt, char data);
void Head(struct node ** ptpt);
void Tail(struct node ** ptpt);
void Length(struct node ** ptpt);
void checkbit(const char * checkBit);
#endif
