#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print(uint32_t *hex, int size){
	char *buffer;
	buffer = (char *) malloc(300);

	//memcpy(buffer , hex, 100);
	
	printf("%x\n", *hex);

}

uint32_t *change_hex(char *msg ,int size){

	uint32_t *hex;

	hex = (uint32_t *)malloc(300);	
	
	char *new_msg = NULL;
	new_msg = (char *) malloc(2);
	hex = (uint32_t *)malloc(size);

	for(int i = 0; i < size; i++){
		strncpy(new_msg, msg + (i * 2), 2);
		*(hex + i) = strtol(new_msg, &new_msg, 16);
	}

	return hex;




}

int main(int argc, char **argv){


	uint32_t *hex;
	uint32_t length;
	length = strlen(argv[1])/2;	

	hex = change_hex(argv[1], length);
	printf("text\n");

	print(hex, length);

}





