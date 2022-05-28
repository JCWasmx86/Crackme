#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

void validation_failed(void);
void write_ln(char*);
int count(uint64_t);

uint64_t tmp;
uint64_t tmp2;
char* pwd;

void check(int signal) {
	if(tmp == tmp2) {
		validation_failed();
	}
	if(count(tmp) == count(tmp2)) {
		write_ln("You found the password:\n\t");
		write_ln(pwd);
		write_ln("\n");
		exit(0);
	}
	validation_failed();
}
void write_ln(char* s) {
	write(1, s, strlen(s));
}
int count(uint64_t i) {
	if(i < 16) {
		switch(i) {
			case 0:
				return 0;
			case 1:
				return 1;
			case 2:
				return 1;
			case 3:
				return 2;
			case 4:
				return 1;
			case 5:
				return 2;
			case 6:
				return 2;
			case 7:
				return 3;
			case 8:
				return 1;
			case 9:
				return 2;
			case 10:
				return 2;
			case 11:
				return 3;
			case 12:
				return 2;
			case 13:
				return 3;
			case 14:
				return 3;
			case 15:
				return 4;
		}
	}
	int n = 0;
	for(int j = 0; j < 16; j++) {
		n += count((i >> (4 * j)) & 0xf);
	}
	return n;
}
__attribute__((constructor))
void cxa_finalize(void) {
	signal(SIGFPE, check);
}

void validate(char* input, int len);

int main(int argc, char** argv) {
	char input[65] = {0};
	puts("Input:");
	fgets(input, 65, stdin);
	validate(input, strlen(input));
}
