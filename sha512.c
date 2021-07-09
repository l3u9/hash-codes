#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define sha512_ROL(value, bits) (((value) << (bits)) | ((value) >> (64 - (bits))))
#define sha512_ROR(value, bits) (((value) >> (bits)) | ((value) << (64 - (bits))))
#define sha512_S(x,n) (((x)&0xFFFFFFFFFFFFFFFF)>>(n))
#define sha512_o0(msg) ((sha512_ROR(msg,1)) ^ (sha512_ROR(msg, 8)) ^ (sha512_S(msg, 7)))
#define sha512_o1(msg) ((sha512_ROR(msg,19)) ^ (sha512_ROR(msg, 61)) ^ (sha512_S(msg,6)))
#define sha512_t0(msg) ((sha512_ROR(msg,28)) ^ (sha512_ROR(msg, 34)) ^ (sha512_ROR(msg,39)))
#define sha512_t1(msg) ((sha512_ROR(msg,14)) ^ (sha512_ROR(msg, 18)) ^ (sha512_ROR(msg,41)))
#define funcF(x,y,z) (z ^ (x & (y ^ z)))
#define funcG(x,y,z) (((x | y) & z) | (x & y))


uint64_t sha512_k[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538, 
              0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe, 
              0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 
              0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 
              0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab, 
              0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725, 
              0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 
              0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b, 
              0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218, 
              0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 
              0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 
              0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec, 
              0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c, 
              0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 
              0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 
              0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};


struct Sha512
{
	uint64_t digest[8];
	uint64_t w[80];
	uint64_t a,b,c,d,e,f,g,h;
};


	



uint64_t sha512_get_pad_bit(uint64_t len)
{
	if(len % 128 == 112){
		len++;
	}
	while((len%128)!=112)
	{
		len++;
	}


	return len * 8;


}


void get_sha512(struct Sha512 *sha512, char *initial_msg, uint64_t length){
	//uint64_t length = strlen(initial_msg);
	
	unsigned char *buffer = NULL;
	uint64_t bits= 0;
	uint64_t temp, temp2;
	uint64_t lb = length * 8;


	bits = sha512_get_pad_bit(length);
	printf("bits: %llu\n",bits);
	buffer = (unsigned char *) malloc((bits/8)+16);

	memcpy(buffer, initial_msg, length);

	*(buffer + length) = (uint8_t)0x80;

	for(int i = length+1; i < (bits/8) ; i++){
		*(buffer + i) = 0x00;
	}

	*(buffer + (bits/8) + 8 + 0) = (lb>>56) &0xff;
	*(buffer + (bits/8) + 8 + 1) = (lb>>48) &0xff;
	*(buffer + (bits/8) + 8 + 2) = (lb>>40) &0xff;
	*(buffer + (bits/8) + 8 + 3) = (lb>>32) &0xff;
	*(buffer + (bits/8) + 8 + 4) = (lb>>24) &0xff;
	*(buffer + (bits/8) + 8 + 5) = (lb>>16) &0xff;
	*(buffer + (bits/8) + 8 + 6) = (lb>>8) &0xff;
	*(buffer + (bits/8) + 8 + 7) = (lb>>0) &0xff;



	sha512->digest[0] = 0x6a09e667f3bcc908;
    sha512->digest[1] = 0xbb67ae8584caa73b;
    sha512->digest[2] = 0x3c6ef372fe94f82b;
    sha512->digest[3] = 0xa54ff53a5f1d36f1;
    sha512->digest[4] = 0x510e527fade682d1;
    sha512->digest[5] = 0x9b05688c2b3e6c1f;
    sha512->digest[6] = 0x1f83d9abfb41bd6b;
    sha512->digest[7] = 0x5be0cd19137e2179;


	for(int i = 0; i < ((bits + 128)/1024); i++){
		for(int j = 0; j < 80; j++)
			sha512->w[j] = 0x00;
		

		for(int j=0; j<16; j++ ){
			sha512->w[j] = buffer[j * 8];
			sha512->w[j] = sha512->w[j] << 8;
			sha512->w[j] |= buffer[j * 8 + 1];
			sha512->w[j] = sha512->w[j] << 8;
			sha512->w[j] |= buffer[j*8+2];
			sha512->w[j] = sha512->w[j] << 8;
			sha512->w[j] |= buffer[j*8+3];
			sha512->w[j] = sha512->w[j] << 8;
			sha512->w[j] |= buffer[j*8+4];
			sha512->w[j] = sha512->w[j] << 8;
			sha512->w[j] |= buffer[j*8+5];
			sha512->w[j] = sha512->w[j] << 8;
			sha512->w[j] |= buffer[j*8+6];
			sha512->w[j] = sha512->w[j] << 8;
			sha512->w[j] |= buffer[j*8+7];
		}



				


		for(int j = 16; j < 80; j++)
			sha512->w[j] = sha512->w[j-16] + sha512_o0(sha512->w[j-15]) + sha512->w[j-7] + sha512_o1(sha512->w[j-2]);
	
		sha512->a = sha512->digest[0];
		sha512->b = sha512->digest[1];
		sha512->c = sha512->digest[2];
		sha512->d = sha512->digest[3];
		sha512->e = sha512->digest[4];
		sha512->f = sha512->digest[5];
		sha512->g = sha512->digest[6];
		sha512->h = sha512->digest[7];

		for(int j = 0; j < 80; j++){
			temp = sha512->h + sha512_t1(sha512->e) + funcF(sha512->e,sha512->f,sha512->g) + sha512_k[j] + sha512->w[j];
			temp2 = sha512_t0(sha512->a) + funcG(sha512->a,sha512->b,sha512->c);
			sha512->h = sha512->g;
			sha512->g = sha512->f;
			sha512->f = sha512->e;
			sha512->e = sha512->d + temp;
			sha512->d = sha512->c;
			sha512->c = sha512->b;
			sha512->b = sha512->a;
			sha512->a = temp + temp2;
		 

		}

		sha512->digest[0] += sha512->a;
		sha512->digest[1] += sha512->b;
		sha512->digest[2] += sha512->c;
		sha512->digest[3] += sha512->d;
		sha512->digest[4] += sha512->e;
		sha512->digest[5] += sha512->f;
		sha512->digest[6] += sha512->g;
		sha512->digest[7] += sha512->h;
		
		buffer += 128;		
	}


}

/*
int main(int argc, char **argv){

	if(argc < 2){
		printf("usage: %s 'string'\n", argv[0]);
		return 1;
	}

	char *msg = argv[1];
	
	struct sha512_Sha512 *sha512;
	sha512 = (struct sha512_Sha512 *)malloc(sizeof(struct sha512_Sha512));

	get_sha512(sha512, msg);

	for(int i = 0; i < 8; i++)
		printf("%llX ", sha512->digest[i]);

	free(sha512);
	


}

*/
