#include "israelid.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <ID>\n", argv[0]);
		return 1;
	}

	const char *input = argv[1];
	const size_t input_len = strlen(input);
	const israelid_checksum_t checksum = israelid_checksum_ascii(input, strlen(input));

	const char* status = input_len == 9 ? (checksum % 10 == 0 ? "valid" : "invalid") : "invalid length";
	printf("%s (checksum %d)\n", status, checksum);
	return 0;
}
