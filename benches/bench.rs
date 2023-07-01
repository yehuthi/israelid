use criterion::{black_box, criterion_group, criterion_main, Criterion};

fn bench(c: &mut Criterion) {
	c.bench_function("valid", |b| {
		b.iter(|| {
			israelid::valid_ascii(black_box(*b"123456782"));
		});
	});
}

criterion_group!(benches, bench);
criterion_main!(benches);
