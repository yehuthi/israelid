#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "israelid.h"

#ifdef __SSE4_1__
israelid_checksum_t _israelid_checksum_ascii_9_sse(const char *restrict id);
#endif
israelid_checksum_t _israelid_checksum_ascii_scalar(const char *restrict id, uint8_t len);

#ifdef __cplusplus
}
#endif
