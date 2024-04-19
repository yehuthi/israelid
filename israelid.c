#include "israelid.h"
#include <stdint.h>
#include <immintrin.h>

israelid_checksum_t israelid_checksum_ascii(const char *id, uint8_t len) {
	israelid_checksum_t checksum = 0;
	for (int i = 0; i < len; i++) {
		int n = (id[i] - '0') * ((i % 2) + 1);
		checksum += (n > 9) ? (n - 9) : n;
	}
	return checksum;
}

israelid_checksum_t israelid_checksum_ascii_9_sse(const char *id) {
	__m128i id_vec = _mm_load_si128((void*)id);
	id_vec = _mm_sub_epi8(id_vec, _mm_set1_epi8('0'));

	__m128i doubled = _mm_add_epi8(id_vec, id_vec);
	id_vec = _mm_blendv_epi8(
		id_vec,
		doubled,
		_mm_set_epi8(-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1)
	);

	__m128i id_vec_minus_9 = _mm_sub_epi8(id_vec, _mm_set1_epi8(9));
	__m128i larges_mask = _mm_cmpgt_epi8(id_vec, _mm_set1_epi8(9));
	id_vec = _mm_blendv_epi8(id_vec, id_vec_minus_9, larges_mask);

	__m128i sum_vec = _mm_sad_epu8(id_vec, _mm_setzero_si128());
	return _mm_cvtsi128_si32(sum_vec) + (_mm_extract_epi16(id_vec, 4) & 0xFF);
}

