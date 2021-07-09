#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROL(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))


struct Sha
{
    uint32_t digest[5];
    uint32_t w[80];
    uint32_t a,b,c,d,e,f;
};



uint32_t padded_length_in_bits(uint32_t len)
{
    if(len%64 == 56)
    {
        len++;
    }
    while((len%64)!=56)
    {
        len++;
    }
    return len*8;
}


void get_sha1(struct Sha *sha1, char *initial_msg, uint32_t length){
	//uint32_t length = strlen(initial_msg);

    unsigned char *buffer;
    uint32_t bits;
    uint32_t temp, k;
    uint32_t lb = length*8;
	
    bits = padded_length_in_bits(length);
    buffer = (unsigned char *) malloc((bits/8)+8);

	
    memcpy(buffer, initial_msg, length);


    *(buffer + length) = 0x80;

    for(int i = length+1; i<(bits/8); i++){
        *(buffer+i) = 0x00;
    }

    *(buffer +(bits/8)+4+0) = (lb>>24) & 0xFF;
    *(buffer +(bits/8)+4+1) = (lb>>16) & 0xFF;
    *(buffer +(bits/8)+4+2) = (lb>>8) & 0xFF;
    *(buffer +(bits/8)+4+3) = (lb>>0) & 0xFF;
   

/*
	for(int i = 0; i < (bits/8)+12; i++){
		printf("%X ",*(buffer + i));

	}

	printf("\n\n");
	printf("length: %d\n", lb);
	
	for(int i = 0; i < 8; i++){
		printf("%x ", *(buffer +(bits/8)+4+i));
	}
	printf("\n\n");
*/

	sha1->digest[0] = 0x67452301;
    sha1->digest[1] = 0xEFCDAB89;
    sha1->digest[2] = 0x98BADCFE;
    sha1->digest[3] = 0x10325476;
    sha1->digest[4] = 0xC3D2E1F0;

    for(int i = 0; i < ((bits + 64)/512); i++){
        for(int j = 0; j < 80; j++)
            sha1->w[j] = 0x00;

        for(int j = 0; j < 16; j++){
            sha1->w[j] =buffer[j*4+0];
            sha1->w[j] = sha1->w[j]<<8;
            sha1->w[j] |= buffer[j*4+1];
            sha1->w[j] = sha1->w[j]<<8;
            sha1->w[j] |= buffer[j*4+2];
            sha1->w[j] = sha1->w[j]<<8;
            sha1->w[j] |= buffer[j*4+3];
        }

        for(int j = 16; j < 80; j++)
            sha1->w[j] = ROL(sha1->w[j-3] ^ sha1->w[j-8] ^ sha1->w[j-14] ^ sha1->w[j-16],1);


        sha1->a = sha1->digest[0];
        sha1->b = sha1->digest[1];
        sha1->c = sha1->digest[2];
        sha1->d = sha1->digest[3];
        sha1->e = sha1->digest[4];


        for(int j = 0; j < 80; j++){
            if((j>=0) && (j<20))
            {
                sha1->f = ((sha1->b)&(sha1->c)) | ((~(sha1->b))&(sha1->d));
                k = 0x5A827999;

            }
            else if((j>=20) && (j<40))
            {
                sha1->f = (sha1->b)^(sha1->c)^(sha1->d);
                k = 0x6ED9EBA1;
            }
            else if((j>=40) && (j<60))
            {
                sha1->f = ((sha1->b)&(sha1->c)) | ((sha1->b)&(sha1->d)) | ((sha1->c)&(sha1->d));
                k = 0x8F1BBCDC;
            }
            else if((j>=60) && (j<80))
            {
                sha1->f = (sha1->b)^(sha1->c)^(sha1->d);
                k = 0xCA62C1D6;
            }

            temp = ROL(sha1->a,5) + (sha1->f) + (sha1->e) + k + sha1->w[j];
            sha1->e = (sha1->d);
            sha1->d = (sha1->c);
            sha1->c = ROL((sha1->b),30);
            sha1->b = (sha1->a);
            sha1->a = temp;
            temp = 0x00;

        }
        sha1->digest[0] += sha1->a;
        sha1->digest[1] += sha1->b;
        sha1->digest[2] += sha1->c;
        sha1->digest[3] += sha1->d;
        sha1->digest[4] += sha1->e;
        buffer = buffer+64;

    }


}



/*
int main(int argc, char **argv){

    if(argc < 2){
        printf("usage: %s 'string'\n", argv[0]);
        return 1;
    }


    char *msg = argv[1];



    size_t len = strlen(msg);
    get_sha1(sha1,msg);

   for(int i=0; i<5; i++)
    {
        printf("%X ",sha1->digest[i]);
    }


    free(sha1);
    return 0;



}
*/

