//! Israeli ID number validation.
//!
//! Israeli ID (Mispar Zehut) is composed of digits for the value (currently eight) and then one digit that is the checksum (Sifrat Biqoret), which makes
//! ID numbers self-validating.
//!
//! You can validate an ID with [`valid_ascii`], and calculate a checksum digit with [`checksum_digit_ascii`].

#![no_std]
#![deny(clippy::missing_inline_in_public_items, missing_docs)]

/// Calculates the checksum for the given ASCII digits.
#[inline]
fn checksum_ascii(id: impl IntoIterator<Item = u8>) -> usize {
	id.into_iter().enumerate().fold(0, |acc, (i, next)| {
		let sum = (next - b'0') as usize * ((i % 2) + 1);
		acc + if sum > 9 { sum - 9 } else { sum }
	})
}

/// Validates the given ASCII ID number.
///
/// # Examples
/// ```
/// # use israelid::valid_ascii;
/// assert!(!valid_ascii(*b"123456789"));
/// assert!( valid_ascii(*b"123456782"));
/// ```
#[inline]
pub fn valid_ascii(id: impl IntoIterator<Item = u8>) -> bool { checksum_ascii(id) % 10 == 0 }

/// Calculates the checksum digit for the given ASCII ID, and returns it as an ASCII character.
///
/// # Examples
/// ```
/// # use israelid::checksum_digit_ascii;
/// // returns the checksum as an ASCII character:
/// assert_eq!(checksum_digit_ascii(*b"12345678"), b'2');
/// // ..not as a number:
/// assert_ne!(checksum_digit_ascii(*b"12345678"), 2);
/// ```
#[inline]
pub fn checksum_digit_ascii(id: impl IntoIterator<Item = u8>) -> u8 {
	let rem = checksum_ascii(id) % 10;
	if rem == 0 {
		b'0'
	} else {
		b'0' + (10 - rem) as u8
	}
}

#[cfg(test)]
mod test {
	use super::*;

	#[test]
	fn validate_bad() {
		assert!(!valid_ascii(*b"123456789"));
		assert!(!valid_ascii(*b"654223991"));
		assert!(!valid_ascii(*b"999999999"));
		assert!(!valid_ascii(*b"555555550"));
	}

	#[test]
	fn validate_good() {
		assert!(valid_ascii(*b"123456782"));
		assert!(valid_ascii(*b"654223999"));
		assert!(valid_ascii(*b"000000000"));
		assert!(valid_ascii(*b"111111118"));
		assert!(valid_ascii(*b"222222226"));
		assert!(valid_ascii(*b"333333334"));
		assert!(valid_ascii(*b"444444442"));
	}

	#[test]
	fn checksum_digit_test() {
		assert_eq!(checksum_digit_ascii(*b"12345678"), b'2');
		assert_eq!(checksum_digit_ascii(*b"65422399"), b'9');
		assert_eq!(checksum_digit_ascii(*b"00000000"), b'0');
		assert_eq!(checksum_digit_ascii(*b"11111111"), b'8');
		assert_eq!(checksum_digit_ascii(*b"22222222"), b'6');
		assert_eq!(checksum_digit_ascii(*b"33333333"), b'4');
		assert_eq!(checksum_digit_ascii(*b"44444444"), b'2');
	}
}
