#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"

int main(int argc, char * argv[]){
	/*PrintList();
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
	Tail();*/
	
	char const * const fileName = argv[1];
	FILE * file = fopen(fileName,"r");
	char line[256];
	while(fgets(line,sizeof(line),file)){
		line[strcspn(line,"\r\n")] = 0;
		char * command = strtok(line," ");
		//printf("%s\n",command);
		if(command != NULL){
			if(strcmp(command, "InsertAfter") == 0){
				char * dataA = strtok(NULL, " ");
				char * dataB = strtok(NULL, " ");
				InsertAfter(Find(&HEAD,(*dataB)),(*dataA));
			}else if(strcmp(command, "InsertBefore") == 0){
				char * dataA = strtok(NULL, " ");
				char * dataB = strtok(NULL, " ");
				InsertBefore(Find(&HEAD,(*dataB)),(*dataA));
			}else if(strcmp(command, "Push") == 0){
				char * data = strtok(NULL, " ");
				Push(&HEAD,(*data));
			}else if(strcmp(command, "Append") == 0){
				char * data = strtok(NULL, " ");
				Append(&HEAD,(*data));
			}else if(strcmp(command, "Remove") == 0){
				char * data = strtok(NULL, " ");
				Remove(&HEAD,(*data));
			}else if(strcmp(command, "Head") == 0){
				Head();
			}else if(strcmp(command, "Tail") == 0){
				Tail();
			}else if(strcmp(command, "Length") == 0){
				Length();
			}else if(strcmp(command, "PrintList") == 0){
				PrintList();
			}else{
				InvalidInput();
			}
		}else{
			InvalidInput();
		}
	}
	fclose(file);
}