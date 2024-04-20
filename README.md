# israelid

A library to validate Israeli ID numbers.

Also available on [JavaScript](https://github.com/yehuthi/israelid.js) and [Rust](https://github.com/yehuthi/israelid.rs).

## Usage

[API reference](https://yehuthi.github.io/israelid/)

Validate an ID with `::israelid_valid_ascii`:
```
bool israelid_valid_ascii(const char *id, uint8_t len);
```
Aligning the `id` to a 128 bit takes a faster code path.

### Checksum

`::israelid_valid_ascii` is a convenience for:
- Checking `len` is the correct length (`::ISRAELID_ID_LEN`, i.e. 9).
- Calculate the checksum with `::israelid_checksum_ascii`.
- Check the `::israelid_checksum_valid` is valid.

### Inverse

You can also compute which digit you need to add to an ID to make it valid with `::israelid_id_checksum_ascii`.
