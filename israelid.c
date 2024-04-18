#include "israelid.h"

#define ISRAELI_ID_LEN (9)

israelid_checksum_t israelid_checksum_ascii(const char *id) {
	israelid_checksum_t checksum = 0;
	for (int i = 0; i < ISRAELI_ID_LEN; i++) {
		int n = (id[i] - '0') * ((i % 2) + 1);
		checksum += (n > 9) ? (n - 9) : n;
	}
	return checksum;
}
