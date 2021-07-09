#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sha.h"
#include "sha256.h"
#include "sha512.h"
#include "md5.h"


#define BLOCK_SIZE 64

void key_xor(unsigned char *buffer, unsigned char *key, int pad){

	for(int i = 0; i < BLOCK_SIZE; i++)
		buffer[i] = key[i] ^ pad;

}


void HMAC(char *initial_key, char *initial_msg){

	int length;
	unsigned char *buffer, *buffer2;
	unsigned char ipad[BLOCK_SIZE];
	unsigned char opad[BLOCK_SIZE];	


	buffer = (unsigned char *) malloc(BLOCK_SIZE);
	buffer2 = (unsigned char *) malloc(BLOCK_SIZE * 2);



	struct Sha *sha1;
	sha1 = (struct Sha*) malloc(sizeof(struct Sha));
	length = strlen(initial_key);
	if(length > BLOCK_SIZE){
		get_sha1(sha1, initial_key, strlen(initial_key));
		memcpy(buffer, sha1->digest, BLOCK_SIZE);
	}
	else{
		memcpy(buffer, initial_key, BLOCK_SIZE);
	}


	

	key_xor(ipad, buffer, 0x36);
	key_xor(opad, buffer, 0x5c);

	memcpy(buffer2, ipad, BLOCK_SIZE);
	memcpy((buffer2 + BLOCK_SIZE), initial_msg, strlen(initial_msg));

	get_sha1(sha1, buffer2, strlen(buffer));
	

	memcpy(buffer2, opad, BLOCK_SIZE);
	memcpy((buffer2 + BLOCK_SIZE), sha1->digest, strlen(sha1->digest));

	get_sha1(sha1, buffer2, strlen(buffer2));

	for(int i = 0; i < 5; i++)
		printf("%X ", sha1->digest[i]);

	

/*
	length = strlen(buffer);
	get_sha1(sha1,buffer, length);
	puts(sha1->digest);
*/

		
		


}


int main(int argc, char **argv){

	HMAC("Jefe", "what do ya want for nothing?");

}






