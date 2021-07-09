#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sha.h"
#include "sha256.h"
#include "sha512.h"
#include "md5.h"


void help(){

	printf("===========================================================\n");
	printf("HASH FUNCTION LIBRARY\n");
	printf("INPUT METHOD\n\n");
	printf("[HASH NAME]\t[INPUT]\t[TYPE]\n");
	printf("HASH NAME OPTION: sha1, sha256, sha512, md6\n");
	printf("TYPE OPTIOM: s : STRING, h : HEX\n");
	
	printf("===========================================================\n");


}



void change_hex(char *hex, char *msg ,int size){
	
	
	char *new_msg = NULL;
	new_msg = (char *) malloc(2);
	
	for(int i = 0; i < size; i++){
		strncpy(new_msg, msg + (i * 2), 2);
		*(hex + i) = (char )strtol(new_msg, &new_msg, 16);
	}


	
}

void print_md5(struct Md5 *md5){
	uint8_t *p;


    p=(uint8_t *)&md5->digest[0];
    printf("%2.2X%2.2X%2.2X%2.2X ", p[0], p[1], p[2], p[3], md5->digest[0]);

    p=(uint8_t *)&md5->digest[0];
    printf("%2.2X%2.2X%2.2x%2.2X ", p[0], p[1], p[2], p[3], md5->digest[1]);

    p=(uint8_t *)&md5->digest[0];
    printf("%2.2X%2.2X%2.2x%2.2X ", p[0], p[1], p[2], p[3], md5->digest[2]);

    p=(uint8_t *)&md5->digest[0];
    printf("%2.2X%2.2X%2.2x%2.2X\n", p[0], p[1], p[2], p[3], md5->digest[3]);
    puts("");
}


int main(int argc, char **argv){

	if(argc < 2){
		printf("usage: %s 'mode' 'string' 'type", argv[0]);
		return 1;
	}
	
	char *msg;
	int length;
	if(argv[0]){
		if(!strncmp(argv[1], "-h", strlen(argv[1]))){
			help();
			}
		else if(!strncmp(argv[1], "sha1", strlen(argv[1]))){
			if(argv[2]){
				if(!strncmp(argv[3], "s", strlen(argv[3]))){
					msg = argv[2];
					struct Sha *sha1;
					sha1 = (struct Sha*) malloc(sizeof(struct Sha));
					length = strlen(msg);
					get_sha1(sha1, msg, length);
					for(int i = 0; i < 5; i++)
						printf("%X ", sha1->digest[i]);

				}else if(!strncmp(argv[3], "h", strlen(argv[3]))){
					struct Sha *sha1;
					sha1 = (struct Sha *) malloc(sizeof(struct Sha));
					length = strlen(argv[2])/2;
					msg = (char *)malloc(length);
	
					change_hex(msg,argv[2], length);	
					get_sha1(sha1, msg, length);	
					for(int i = 0; i < 5; i++)
						printf("%X ", sha1->digest[i]);
				}				

			}else{
				printf("choose 's' or 'h']\n");
				return 1;
				
			}

		}else if(!strncmp(argv[1], "sha256", strlen(argv[1]))){
			if(argv[2]){
				if(!strncmp(argv[3], "s", strlen(argv[3]))){
					msg = argv[2];
					struct Sha256 *sha256;
					sha256 = (struct Sha256*) malloc(sizeof(struct Sha256));
					length = strlen(msg);
					get_sha256(sha256, msg, length);
					for(int i = 0; i < 5; i++)
						printf("%X ", sha256->digest[i]);

				}else if(!strncmp(argv[3], "h", strlen(argv[3]))){
					struct Sha256 *sha256;
					sha256 = (struct Sha256 *) malloc(sizeof(struct Sha256));
					length = strlen(argv[2])/2;
					msg = (char *)malloc(length);

					change_hex(msg,argv[2], length);
					get_sha256(sha256, msg, length);
					for(int i = 0; i < 5; i++)
						printf("%X ", sha256->digest[i]);
				}
			}else{
				printf("choose 's' or 'h']\n");
				return 1;

				}
			

			}else if(!strncmp(argv[1], "sha512", strlen(argv[1]))){
				if(argv[2]){
				if(!strncmp(argv[3], "s", strlen(argv[3]))){
					msg = argv[2];
					struct Sha512 *sha512;
					sha512 = (struct Sha512*) malloc(sizeof(struct Sha512));
					length = strlen(msg);
					get_sha512(sha512, msg, length);
					for(int i = 0; i < 5; i++)
						printf("%llX ", sha512->digest[i]);

				}else if(!strncmp(argv[3], "h", strlen(argv[3]))){
					struct Sha512 *sha512;
					sha512 = (struct Sha512 *) malloc(sizeof(struct Sha512));
					length = strlen(argv[2])/2;
					msg = (char *)malloc(length);

					change_hex(msg,argv[2], length);
					get_sha512(sha512, msg, length);
					for(int i = 0; i < 5; i++)
						printf("%llX ", sha512->digest[i]);
				}

			}else{
				printf("choose 's' or 'h']\n");
				return 1;

				}

			}else if(!strncmp(argv[1], "md5", strlen(argv[1]))){
				if(argv[2]){
				if(!strncmp(argv[3], "s", strlen(argv[3]))){
					msg = argv[2];
					struct Md5 *md5;
					md5 = (struct Md5*) malloc(sizeof(struct Md5));
					length = strlen(msg);
					get_md5(md5, msg, length);
					print_md5(md5);
				}else if(!strncmp(argv[3], "h", strlen(argv[3]))){
					struct Md5 *md5;
					md5 = (struct Md5 *) malloc(sizeof(struct Md5));
					length = strlen(argv[2])/2;
					msg = (char *)malloc(length);

					change_hex(msg,argv[2], length);
					get_md5(md5, msg, length);
					print_md5(md5);
				}

			}else{
				printf("choose 's' or 'h']\n");
				return 1;

				}
	
			}

	}


}


