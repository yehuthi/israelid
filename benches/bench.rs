use criterion::{black_box, criterion_group, criterion_main, Criterion};

#[no_mangle]
#[inline(never)]
pub fn valid_bench() { israelid::valid_ascii(black_box(*b"123456782")); }

#[no_mangle]
#[inline(never)]
pub fn checksum_bench() { israelid::checksum_digit_ascii(black_box(*b"12345678")); }

fn bench(c: &mut Criterion) {
	c.bench_function("valid", |b| {
		b.iter(valid_bench);
	});
	c.bench_function("checksum", |b| b.iter(checksum_bench));
}

criterion_group!(benches, bench);
criterion_main!(benches);
