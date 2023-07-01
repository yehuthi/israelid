use criterion::{black_box, criterion_group, criterion_main, Criterion};

#[no_mangle]
#[inline(never)]
pub fn valid_bench(id: &[u8]) { israelid::valid_ascii(black_box(id.iter().copied())); }

#[no_mangle]
#[inline(never)]
pub fn checksum_bench(id: &[u8]) { israelid::checksum_digit_ascii(black_box(id.iter().copied())); }

fn bench(c: &mut Criterion) {
	c.bench_function("valid", |b| {
		b.iter(|| valid_bench(b"123456782"));
	});
	c.bench_function("checksum", |b| b.iter(|| checksum_bench(b"12345678")));
}

criterion_group!(benches, bench);
criterion_main!(benches);
