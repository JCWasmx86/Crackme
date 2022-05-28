#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include "data.h"

unsigned char swap_halves_of_byte(unsigned char);
unsigned char ror(unsigned char, int);
unsigned char rol(unsigned char, int);
char buf[8192] = {0};
char* loc = (char*)0x7f134032a2bcef;
uint64_t rdtsc(void);
typedef void (*func)(void (*)(void), void (*)(void), size_t);

__attribute__((constructor))
void set_location() {
	uint64_t start = rdtsc();
	uint64_t remainder = start % 8185;
	loc = &buf[remainder];
}
__attribute__((constructor))
void decrypt_data() {
	mprotect(data, sizeof(data), PROT_WRITE | PROT_READ | PROT_EXEC);
	uint32_t key = 0x7fff74f1;
	uint32_t* ptr = (uint32_t*)&data[0];
	for(uint32_t i = 0; i < sizeof(data) / 4; i++) {
		ptr[i] ^= key;
		key <<= 5;
		key += 5381;
		key |= 432;
	}
	for(int i = 0; i < sizeof(data); i++) {
		if(i % 5 == i % 3 && i % 5 == 0) {
			// data[i] = swap_halves_of_byte(data[i]);
		} else if(i % 5 == 0) {
			// data[i] = ror(data[i], i % 8);
		} else if(i % 3 == 0) {
			// data[i] = rol(data[i], i % 8);
		}
	}
}
typedef struct {
	uint64_t u;
	uint64_t u1;
} bytes_16;
void my_memset(void* p, int v, int size) {
	if(size % 16 == 0) {
		bytes_16* ptr = p;
		for(int i = 0; i < size / 16; i++) {
			ptr[i].u = v;
			ptr[i].u1 = v;
		}
	} else if(size % 8 == 0) {
		uint64_t* ptr = p;
		for(int i = 0; i < size / 8; i++) {
			ptr[i] = v;
		}
	} else if(size % 4 == 0) {
		uint32_t* ptr = p;
		for(int i = 0; i < size / 4; i++) {
			ptr[i] = v;
		}
	} else {
		for(int i = 0; i < size; i++) {
			((unsigned char*)p)[i] = v;
		}
	}
}
void fail(void) {
	fputs("Wrong password!\n", stderr);
}
void success(void) {
	printf("You found the password: \"%s\"\n", (char*)data);
}
int main(void) {
	char input[256] = {0x33};
	my_memset(input, 0, sizeof(input));
	puts("Enter password:");
	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = 0;
	memcpy(data, input, strlen(input));
	void* ptr = &data[256];
	func f = (func)(void**)ptr;
	f(fail, success, strlen(input));
	return 0;
}
