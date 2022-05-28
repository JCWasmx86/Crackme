#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

unsigned char swap_halves_of_byte(unsigned char);
unsigned char ror(unsigned char, int);
unsigned char rol(unsigned char, int);

int main(int argc, char** argv) {
	FILE* fp = fopen(argv[1], "rb");
	if(!fp) {
		fprintf(stderr, "%s not found!\n", argv[1]);
		return 1;
	}
	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	assert(size % 4 == 0);
	rewind(fp);
	unsigned char* buf = malloc(size);
	if(!buf) {
		fclose(fp);
		fputs("malloc failed", stderr);
		return 1;
	}
	fread(buf, size, 1, fp);
	uint32_t key = 0x7fff74f1;
	uint32_t* ptr = (uint32_t*)&buf[0];
	for(uint32_t i = 0; i < size / 4; i++) {
		ptr[i] ^= key;
		key <<= 5;
		key += 5381;
		key |= 432;
	}
	// unsigned char* data = buf;
	for(uint32_t i = 0; i < size; i++) {
		if(i % 5 == i % 3 && i % 5 == 0)
			; // data[i] = swap_halves_of_byte(data[i]);
		else if(i % 5 == 0)
			; // data[i] = rol(data[i], (i % 8));
		else if(i % 3 == 0)
			; // data[i] = ror(data[i], (i % 8));
	}
	fclose(fp);
	fp = fopen(argv[2], "wb");
	if(!fp) {
		fprintf(stderr, "%s couldn't open!\n", argv[2]);
		free(buf);
		return 1;
	}
	fwrite(buf, size, 1, fp);
	fclose(fp);
	free(buf);
	return 0;
}
