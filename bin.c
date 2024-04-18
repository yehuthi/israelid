#include "israelid.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <ID>\n", argv[0]);
		return 1;
	}

	const char *input = argv[1];
	if (strlen(input) != 9) {
		printf("invalid (too short)\n");
		return 0;
	}

	const israelid_checksum_t checksum = israelid_checksum_ascii(input);
	printf("%s (checksum %d)\n", (checksum % 10) == 0 ? "valid" : "invalid", checksum);
	return 0;
}
