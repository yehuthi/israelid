#include <gtest/gtest.h>
#include "israelid.h"

TEST(israelid, checksum_ascii) {
	EXPECT_EQ(
		israelid_checksum_ascii("123456789", 9),
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
		israelid_checksum_ascii_9_sse(input),
		israelid_checksum_ascii(input, 9)
	);
}
