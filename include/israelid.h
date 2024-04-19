#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint8_t israelid_checksum_t;

israelid_checksum_t israelid_checksum_ascii(const char *id, uint8_t len);

israelid_checksum_t israelid_checksum_ascii_9_sse(const char *id);

#ifdef __cplusplus
}
#endif
