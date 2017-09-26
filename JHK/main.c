#include "linkedlist.h"
#include "error.h"

int main(int argc, char * argv[]){
	char const * const fileName = argv[1];
	FILE * file = fopen(fileName,"r");
	char line[256];
	while(fgets(line,sizeof(line),file)){
		line[strcspn(line,"\r\n")] = 0;
		char * command = strtok(line," ");
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
