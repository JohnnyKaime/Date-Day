/*******************************************************************************
*File - error.c
*
*This file contains all the function used for error
*handling, such at notification from invalid input
*and searching for non existing datas from nodes.
*Error message is printed to standard error
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
