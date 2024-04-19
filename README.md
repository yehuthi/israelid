# israelid

A library to validate Israeli ID numbers.

Also available on [JavaScript](https://github.com/yehuthi/israelid.js) and [Rust](https://github.com/yehuthi/israelid.rs).

## Usage

Validate an ID with:
```
bool israelid_valid_ascii(const char *id, uint8_t len);
```
Aligning the `id` to a 128 bit takes a faster code path.

### Checksum

`israelid_valid_ascii` is a convenience for:
- Checking `len` is the correct length (`ISRAELID_ID_LEN`, i.e. 9).
- Calculate the checksum with `israelid_checksum_ascii`.
- Check the `israelid_checksum_valid` is valid.
