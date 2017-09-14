/*
*Theory of Computation
*Practical 1
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	char *  input = argv[1];
	int state = 0;
	int rules[8][2] = {{0,1},{2,3},{4,5},{6,7},{0,1},{2,3},{4,5},{6,7}};
	int index;
	for (index = 0; index < strlen(input); index++){
		state = rules[state][input[index]];
	}

	if(state == 4 || state == 5 || state == 6 || state == 7){
		printf("%s\n", "accept");
	}else{
		printf("%s\n", "reject");
	}

	return 0;
}
