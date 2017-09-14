/*
*Theory of Computation
*Practical 1
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char * input =  argv[1];
	int index;
	int state = 0;
	for (index = 0; index < strlen(input); index++){
		if(input[index] == '0'){
			if(state == 0){
				//Stay same level
			}else if(state == 1){
				state = 2;
			}else if(state == 2){
				state = 1;
			}
		}else if(input[index] == '1'){
			state = 1; 
		}
	}

	if(state == 1){
		printf("%s\n", "accept");
	}else{
		printf("%s\n", "reject");
	}

	return 0;
}
