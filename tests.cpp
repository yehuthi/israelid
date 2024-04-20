#include <gtest/gtest.h>
#include "israelid.h"

TEST(israelid, checksum_ascii_scalar) {
	EXPECT_EQ(
		_israelid_checksum_ascii_scalar("123456789", 9),
		// 123456789
		// 121212121
		// 1 4 3 8 5 12 7 16 9
		// 1 4 3 8 5 3 7 7 9
		// 47
		47
	);
}

TEST(israelid, checksum_ascii_sse) {
#define CASE(LITERAL) \
	{ \
		alignas(128) const char input[] = LITERAL; \
		assert(sizeof(input) == 9 + /* NUL */ 1); \
		EXPECT_EQ( \
			_israelid_checksum_ascii_9_sse(input), \
			_israelid_checksum_ascii_scalar(input, 9) \
		) << "for input " << input << " (line " << __LINE__ << ")"; \
	}
	// bad
	CASE("123456789");
	CASE("654223991");
	CASE("999999999");
	CASE("555555550");
	// good
	CASE("123456782");
	CASE("654223999");
	CASE("000000000");
	CASE("111111118");
	CASE("222222226");
	CASE("333333334");
	CASE("444444442");
#undef CASE
}

TEST(israelid, valid_scalar) {
	ASSERT_FALSE(israelid_valid_ascii("123456789", 9));
	ASSERT_TRUE(israelid_valid_ascii("123456782", 9));
	ASSERT_FALSE(israelid_valid_ascii("", 0));
	ASSERT_FALSE(israelid_valid_ascii("a1b2", 4));
}

TEST(israelid, compute_checksum_len_9) {
	ASSERT_EQ(israelid_id_checksum("123456782", 9), 0) << "already valid";
	ASSERT_EQ(israelid_id_checksum("12345678", 8), 2) << "even delta, standard position";
	ASSERT_EQ(israelid_id_checksum("111", 3), 3) << "even delta, doubled position";
	ASSERT_EQ(israelid_id_checksum("11111", 5), 6) << "odd delta, doubled position";
	ASSERT_EQ(israelid_id_checksum("10", 2), 9) << "odd delta, standard position";
	// ascii
	ASSERT_EQ(israelid_id_checksum_ascii("12345678", 8), '2');
}
