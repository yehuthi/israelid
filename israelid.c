#include "israelid.h"

israelid_checksum_t israelid_checksum_ascii(const char *id, uint8_t len) {
	israelid_checksum_t checksum = 0;
	for (int i = 0; i < len; i++) {
		int n = (id[i] - '0') * ((i % 2) + 1);
		checksum += (n > 9) ? (n - 9) : n;
	}
	return checksum;
}
