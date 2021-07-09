/*
#define ROL(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))
#define sha512_ROL(value, bits) (((value) << (bits)) | ((value) >> (64 - (bits))))
#define sha512_ROR(value, bits) (((value) >> (bits)) | ((value) << (64 - (bits))))
#define sha512_S(x,n) (((x)&0xFFFFFFFFFFFFFFFF)>>(n))
#define sha512_o0(msg) ((sha512_ROR(msg,1)) ^ (sha512_ROR(msg, 8)) ^ (sha512_S(msg, 7)))
#define sha512_o1(msg) ((sha512_ROR(msg,19)) ^ (sha512_ROR(msg, 61)) ^ (sha512_S(msg,6)))
#define sha512_t0(msg) ((sha512_ROR(msg,28)) ^ (sha512_ROR(msg, 34)) ^ (sha512_ROR(msg,39)))
#define sha512_t1(msg) ((sha512_ROR(msg,14)) ^ (sha512_ROR(msg, 18)) ^ (sha512_ROR(msg,41)))
#define funcF(x,y,z) (z ^ (x & (y ^ z)))
#define funcG(x,y,z) (((x | y) & z) | (x & y))
#define S(x,n) (((x)&0xFFFFFFFFUL)>>(n))
#define o0(msg) ((ROR(msg,7)) ^ (ROR(msg, 18)) ^ (S(msg, 3)))
#define o1(msg) ((ROR(msg,17)) ^ (ROR(msg, 19)) ^ (S(msg,10)))
#define t0(msg) ((ROR(msg,2)) ^ (ROR(msg, 13)) ^ (ROR(msg,22)))
#define t1(msg) ((ROR(msg,6)) ^ (ROR(msg, 11)) ^ (ROR(msg,25)))
#define md5_ROL(x,c) (((x) << (c)) | ((x) >> (32 - (c))))
#define md5_ROR(x,c) (((x) >> (c)) | ((x) << (32 - (c))))
*/

/*
struct Sha *sha1;
struct Sha256 *sha256;
struct Sha512 *sha512;
struct Md5 *md5;
*/
//sha1 func
void get_sha1(struct Sha *sha1, char *initial_msg, uint32_t length);


//sha256 func
void get_sha256(struct Sha256 *sha256, char *initial_msg, uint32_t length);

void get_sha512(struct Sha512 *sha512, char *initial_msg, uint64_t length);

void get_md5(struct Md5 *md5,char *initial_msg, uint32_t length);

