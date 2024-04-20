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

	const bool valid_len = input_len == ISRAELID_ID_LEN;
	const bool valid_checksum = israelid_checksum_valid(checksum);
	const char *statusi[4] = {
		"invalid",
		"invalid length",
		"invalid",
		"valid",
	};
	const char* status = statusi[(valid_len << 1) | valid_checksum];
	printf("%s (checksum %d", status, checksum);
	if (!valid_checksum)
		printf(", recover digit: %d)\n", israelid_id_checksum(input, input_len));
	else printf(")\n");
	return 0;
}
