#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define md5_ROL(x,c) (((x) << (c)) | ((x) >> (32 - (c))))
#define md5_ROR(x,c) (((x) >> (c)) | ((x) << (32 - (c))))

struct Md5
{
	uint32_t digest[4];
	uint32_t a,b,c,d,e,f,g;
};




uint32_t md5_get_pad_bit(uint32_t len){

	if(len % 64 == 56){
		len++;
	}
	while((len % 64) != 56){
		len++;
	}
	return len * 8;
}



void cal_k(uint32_t *k){
	
	for(int i = 0; i < 64; i++){
		k[i] = floor(fabs(sin(i+1)) * (pow(2,32)));
	}
	
}

void get_md5(struct Md5 *md5,char *initial_msg, uint32_t length) {
	//uint32_t length = strlen(initial_msg);
		
	unsigned char *buffer = NULL;
	uint32_t k[64];
	uint32_t bits;
	uint32_t lb = length * 8;
	
	uint32_t r[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22, 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};

	md5->digest[0] = 0x67452301;
	md5->digest[1] = 0xEFCDAB89;
	md5->digest[2] = 0x98BADCFE;
	md5->digest[3] = 0x10325476;

	cal_k(k);

	//print_array(k);

	bits = md5_get_pad_bit(length);



	buffer = (unsigned char *)malloc((bits/8) + 64);
	
	memcpy(buffer, initial_msg, length);
	
	buffer[length] = 0x80;

	memcpy(buffer + (bits/8), &lb, 4);






	int idx;
    for(idx=0; idx < ((bits)/8); idx += 64) {
		uint32_t *w = (uint32_t *)(buffer + idx);

		md5->a = md5->digest[0];
		md5->b = md5->digest[1];
		md5->c = md5->digest[2];
		md5->d = md5->digest[3];
 

		for(uint32_t i = 0; i < 64; i++){
			//uint32_t f, g;
			if(i < 16){
				md5->f = (md5->b & md5->c) | ((~md5->b) &md5->d);
				md5->g = i;
			}else if(i < 32){
				md5->f = (md5->d & md5->b) | ((~md5->d) & md5->c);
				md5->g = (5 * i + 1) %16;
			}else if(i < 48){
				md5->f = md5->b ^ md5->c ^ md5->d;
				md5->g = (3 * i + 5) % 16;
			}else{
				md5->f = md5->c ^ (md5->b | (~md5->d));
				md5->g = (7 * i) % 16;
			}

			uint32_t temp;
			temp = md5->d;
			md5->d = md5->c;
			md5->c = md5->b;
			md5->b = md5->b + md5_ROL((md5->a + md5->f + k[i] + w[md5->g]), r[i]);
			md5->a = temp;
		
		}
		
		md5->digest[0] += md5->a;
		md5->digest[1] += md5->b;
		md5->digest[2] += md5->c;
		md5->digest[3] += md5->d;

		
	}
	
	free(buffer);


}

/*
int main(int argc, char **argv){

	if (argc < 2) {
        printf("usage: %s 'string'\n", argv[0]);
        return 1;
    }


	char *msg = argv[1];

	size_t len = strlen(msg);
	struct Md5 *md5;
	md5 = (struct Md5*)malloc(sizeof(struct Md5));
	get_md5(md5,msg);

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

 
 
 
    return 0;


}

*/
