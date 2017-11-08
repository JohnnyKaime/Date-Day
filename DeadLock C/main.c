#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "node.h"
#include "functions.h"
#include "error.h"

typedef struct node node;

node * processlist[25] = {};
int resourcelist[25] = {};

int main(int argc, char const *argv[])
{
	char const * const fileName = argv[1];
	FILE * file = fopen(argv[1], "r");
    char line[128];

    while (fgets(line, sizeof(line), file)){
    	line[strcspn(line,"\r\n")] = 0;
    	char * part1 = strtok(line," ");

        if(strcmp(part1,"kill") == 0){
            char * part2 = strtok(NULL," ");
            if(*part2 < 65 || *part2 > 90){
                InvalidInput();
            }
            Kill(processlist, *part2, resourcelist);
            //printf("%s %s\n", part1, part2);
        }else if(strcmp(part1,"clear") == 0){
            Clear(processlist, resourcelist);
            //printf("%s\n", part1);
        }else if(*part1 > 64 && *part1 < 91){
            char * part2 = strtok(NULL," ");
            if(strcmp(part2,"requests") == 0){
                char * part3 = strtok(NULL," ");
                if(*part3 > 64 && *part3 < 91){
                    //requests
                    int position = *part3 - 65;
                    if(Requests(&processlist[position], *part1, resourcelist[position])){
                        resourcelist[position]++;
                    }
                    //printf("%s %s %s\n", part1,part2,part3);
                }else{
                  InvalidInput();  
                }
            }else if(strcmp(part2,"releases") == 0){
                char * part3 = strtok(NULL," ");
                if(*part3 > 64 && *part3 < 91){
                    //releases
                    int position = *part3 - 65;
                    if(Releases(&processlist[position], *part1)){
                        resourcelist[position]--;
                    }
                    //printf("%s %s %s\n", part1,part2,part3);
                }else{
                  InvalidInput();  
                }
            }else{
                InvalidInput();
            }
        }else{
            InvalidInput();
        }

        DeadLockDetection(processlist,resourcelist);

        PrintList(processlist,*resourcelist);
	}
    
    fclose(file);
	return 0;
}