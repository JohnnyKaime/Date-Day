/*******************************************************************************
*Jia-Cong Hou
*3565155
*Prac4 - DeadLock
*File - error.h
*
*Header file that links to error.c used in the driver
*main.c, serves as a "interface" to call each functions
*defined below
*******************************************************************************/
/*If this file is defined else where terminate end it*/
#ifndef ERROR_H_
/*Defines the header file*/
#define ERROR_H_
/*Header functions in error.c to be used*/
void InvalidInput();
void deadLock();
/*Terminate / end file*/
#endif
