/*******************************************************************************
*Jia-Cong Hou
*3565155
*Prac4 - DeadLock
*File - error.c
*
*This file contains all the function used for error
*handling, such at notification from invalid input
*and searching for non existing datas from nodes.
*Error message is printed to standard error
*Dead lock message is printed to standard output
*******************************************************************************/
/*Includes system used library*/
#include <stdio.h>
#include <stdlib.h>
/*Includes user defined files*/
#include "error.h"
/*
*Description:
*Prints out input no valid to standard error "stderr"
*
*Input:
*Nothing
*
*Output:
*Returns nothing
*Displays Input not valid to standard error
*
*Caveats:
*None
*/
void InvalidInput(){
	/*Display error message and a new line*/
	fprintf(stderr,"Input not valid\n");
}
/*
*Description:
*Prints out dead lock to standard output "stdout"
*
*Input:
*Nothing
*
*Output:
*Returns nothing
*Displays deadlock to standard output
*
*Caveats:
*None
*/
void deadLock(){
	fprintf(stdout,"deadlock\n");
}
