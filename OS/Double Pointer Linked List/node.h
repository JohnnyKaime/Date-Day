/*******************************************************************************
*File - node.h
*
*Header file that links this node data structure to the driver
*in main.c, serves as a "interface" to call each functions
*or struct node defined below
*******************************************************************************/
/*If this file is defined else where terminate / end it*/
#ifndef NODE_H_
/*Defines the header file*/
#define NODE_H_
/*
*Description:
*Creates node structure used in the list
*	data - type char, stores the data or input from the file
*	node - type node, stores the next linked node
*
*Input:
*Nothing
*
*Output:
*Nothing
*
*Caveats:
*Only accepts char as data inputs
*/
struct node{
	char data;
	struct node * next;
};
/*Terminate / end file*/
#endif
