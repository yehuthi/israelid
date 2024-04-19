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
	alignas(128) const char input[] = "123456789";
	EXPECT_EQ(
		_israelid_checksum_ascii_9_sse(input),
		_israelid_checksum_ascii_scalar(input, 9)
	);
}

TEST(israelid, valid) {
	// 123..
	EXPECT_FALSE(israelid_valid_ascii("123456789", 9));
	EXPECT_TRUE(israelid_valid_ascii("123456782", 9));
	// good
	EXPECT_TRUE(israelid_valid_ascii("654223999", 9));
	EXPECT_TRUE(israelid_valid_ascii("000000000", 9));
	EXPECT_TRUE(israelid_valid_ascii("111111118", 9));
	EXPECT_TRUE(israelid_valid_ascii("222222226", 9));
	EXPECT_TRUE(israelid_valid_ascii("333333334", 9));
	EXPECT_TRUE(israelid_valid_ascii("444444442", 9));
	// bad
	EXPECT_FALSE(israelid_valid_ascii("654223991", 9));
	EXPECT_FALSE(israelid_valid_ascii("999999999", 9));
	EXPECT_FALSE(israelid_valid_ascii("555555550", 9));
	// bad (misc)
	EXPECT_FALSE(israelid_valid_ascii("", 0));
	EXPECT_FALSE(israelid_valid_ascii("1", 1));
	EXPECT_FALSE(israelid_valid_ascii("12", 2));
	EXPECT_FALSE(israelid_valid_ascii("1abc5", 5));

}
