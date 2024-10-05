/** \file */
#pragma once
#ifdef __cplusplus
extern "C" {

#if defined(__GNUC__)
#define restrict __restrict__
#elif defined (_MSC_VER)
#define restrict __declspec(restrict)
#else
#define restrict
#endif

#endif

#include <stdbool.h>
#include <stdint.h>

enum {
	/// The length of Israeli ID numbers (including the control digit).
	ISRAELID_ID_LEN = 9
};

/// The integer type for checksums.
typedef uint8_t israelid_checksum_t;

/// Computes the checksum for the given Israeli ID number.
///
/// The input length to this function doesn't have to be ::ISRAELID_ID_LEN.
israelid_checksum_t israelid_checksum_ascii(const char *restrict id, uint8_t len);

/// Checks whether the given checksum is valid.
///
/// Note that the length of the ID is not manifested in the checksum, therefore, a checksum may be valid but the ID number invalid if the length is not ::ISRAELID_ID_LEN.
/// See ::israelid_valid_ascii, which checks both the length and the checksum.
bool israelid_checksum_valid(israelid_checksum_t checksum);

/// Checks whether the given Israeli ID number is valid.
bool israelid_valid_ascii(const char *restrict id, uint8_t len);

/// Computes a digit that ensures the control digit would be valid, if added to the end of the ID.
///
/// That is: the ::israelid_checksum_ascii of the string `"<id><israelid_id_checksum(id)>"` should always be a ::israelid_checksum_valid. See also ::israelid_control_ascii.
uint8_t israelid_control_complement(const char *restrict id, uint8_t len);

/// The same as ::israelid_control_complement but returns the digit as an ASCII character.
char israelid_control_complement_ascii(const char *restrict id, uint8_t len);

#ifdef __cplusplus
}
#endif
