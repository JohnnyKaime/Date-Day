#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prac3.h"

int main(int argc, char * argv[]){
	PrintList();
	Length();
	Push(&HEAD,'A');
	Push(&HEAD,'B');
	Push(&HEAD,'C');
	PrintList();
	Length();
	Append(&HEAD,'Z');
	Append(&HEAD,'Y');
	PrintList();
	Length();
	InsertBefore(Find(&HEAD,'C'),'X');
	PrintList();
	Length();
	InsertAfter(Find(&HEAD,'D'),'D');
	PrintList();
	Length();
	Remove(&HEAD,'C');
	PrintList();
	Length();
	Head();
	Tail();
}
