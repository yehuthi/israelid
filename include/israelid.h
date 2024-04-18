#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint8_t israelid_checksum_t;

israelid_checksum_t israelid_checksum_ascii(const char *id);

#ifdef __cplusplus
}
#endif
