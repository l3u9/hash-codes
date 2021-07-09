#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROL(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))
#define ROR(value, bits) (((value) >> (bits)) | ((value) << (32 - (bits))))
#define S(x,n) (((x)&0xFFFFFFFFUL)>>(n))
#define o0(msg) ((ROR(msg,7)) ^ (ROR(msg, 18)) ^ (S(msg, 3)))
#define o1(msg) ((ROR(msg,17)) ^ (ROR(msg, 19)) ^ (S(msg,10)))
#define t0(msg) ((ROR(msg,2)) ^ (ROR(msg, 13)) ^ (ROR(msg,22)))
#define t1(msg) ((ROR(msg,6)) ^ (ROR(msg, 11)) ^ (ROR(msg,25)))
#define funcF(x,y,z) (z ^ (x & (y ^ z)))
#define funcG(x,y,z) (((x | y) & z) | (x & y))


uint32_t k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};


struct Sha256
{
	uint32_t digest[8];
	uint32_t w[64];
	uint32_t a,b,c,d,e,f,g,h;
};



uint32_t get_pad_bit(uint32_t len)
{
	if(len % 64 == 56){
		len++;
	}
	while((len%64)!=56)
	{
		len++;
	}

	return len * 8;


}


void get_sha256(struct Sha256 *sha256, char *initial_msg, uint32_t length){
	
	unsigned char *buffer;
	uint32_t bits;
	uint32_t temp, temp2;
	uint32_t lb = length * 8;




	bits = get_pad_bit(length);
	buffer = (unsigned char *) malloc((bits/8)+8);

	printf("bits: %d\n",bits);
	memcpy(buffer, initial_msg, length);

	*(buffer + length) = 0x80;

	for(int i = length+1; i < (bits/8); i++){
		*(buffer + i) = 0x00;
	}

	*(buffer + (bits/8) + 4 + 0) = (lb>>24) &0xff;
	*(buffer + (bits/8) + 4 + 1) = (lb>>16) &0xff;
	*(buffer + (bits/8) + 4 + 2) = (lb>>8) &0xff;
	*(buffer + (bits/8) + 4 + 3) = (lb>>0) &0xff;

	

	sha256->digest[0] = 0x6a09e667;	
	sha256->digest[1] = 0xbb67ae85;
	sha256->digest[2] = 0x3c6ef372;
	sha256->digest[3] = 0xa54ff53a;
	sha256->digest[4] = 0x510e527f;
	sha256->digest[5] = 0x9b05688c;
	sha256->digest[6] = 0x1f83d9ab;
	sha256->digest[7] = 0x5be0cd19;



	for(int i = 0; i < ((bits + 64)/512); i++){
		for(int j = 0; j < 64; j++)
			sha256->w[j] = 0x00;
		
		for(int j = 0; j < 16; j++){
			sha256->w[j] = buffer[j * 4];
			sha256->w[j] = sha256->w[j] << 8;
			sha256->w[j] |= buffer[j * 4 + 1];
			sha256->w[j] = sha256->w[j] << 8;
			sha256->w[j] |= buffer[j*4+2];
			sha256->w[j] = sha256->w[j] << 8;
			sha256->w[j] |= buffer[j*4+3];
		}
		


		

/*
		for(int j = 0; j < 16; j++){
			LOAD32H( sha256->w[i], buffer + (j*4) );
		}
*/


		for(int j = 16; j < 64; j++)
			sha256->w[j] = sha256->w[j-16] + o0(sha256->w[j-15]) + sha256->w[j-7] + o1(sha256->w[j-2]);
	
		sha256->a = sha256->digest[0];
		sha256->b = sha256->digest[1];
		sha256->c = sha256->digest[2];
		sha256->d = sha256->digest[3];
		sha256->e = sha256->digest[4];
		sha256->f = sha256->digest[5];
		sha256->g = sha256->digest[6];
		sha256->h = sha256->digest[7];

		for(int j = 0; j < 64; j++){
			temp = sha256->h + t1(sha256->e) + funcF(sha256->e,sha256->f,sha256->g) + k[j] + sha256->w[j];
			temp2 = t0(sha256->a) + funcG(sha256->a,sha256->b,sha256->c);
			sha256->h = sha256->g;
			sha256->g = sha256->f;
			sha256->f = sha256->e;
			sha256->e = sha256->d + temp;
			sha256->d = sha256->c;
			sha256->c = sha256->b;
			sha256->b = sha256->a;
			sha256->a = temp + temp2;
		 

		}

		sha256->digest[0] += sha256->a;
		sha256->digest[1] += sha256->b;
		sha256->digest[2] += sha256->c;
		sha256->digest[3] += sha256->d;
		sha256->digest[4] += sha256->e;
		sha256->digest[5] += sha256->f;
		sha256->digest[6] += sha256->g;
		sha256->digest[7] += sha256->h;
		buffer += 64;
		
	}


}

/*
int main(int argc, char **argv){

	if(argc < 2){
		printf("usage: %s 'string'\n", argv[0]);
		return 1;
	}

	char *msg = argv[1];
	
	struct Sha256 *sha256;
	sha256 = (struct Sha256 *)malloc(sizeof(struct Sha256));

	get_sha256(sha256, msg);

	for(int i = 0; i < 8; i++)
		printf("%X ", sha256->digest[i]);

	free(sha256);
	


}

*/
