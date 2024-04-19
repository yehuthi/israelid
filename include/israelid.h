#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

enum {
	ISRAELID_ID_LEN = 9
};

typedef uint8_t israelid_checksum_t;

israelid_checksum_t israelid_checksum_ascii(const char *id, uint8_t len);
bool israelid_checksum_valid(israelid_checksum_t checksum);

bool israelid_valid_ascii(const char *id, uint8_t len);

// internal (for testing and benchmarking):
#ifdef __SSE4_1__
israelid_checksum_t _israelid_checksum_ascii_9_sse(const char *id);
#endif
israelid_checksum_t _israelid_checksum_ascii_scalar(const char *id, uint8_t len);

#ifdef __cplusplus
}
#endif
