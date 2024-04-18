#include <benchmark/benchmark.h>
#include "israelid.h"

static void BM_checksum_ascii(benchmark::State& state) {
	for (auto _ : state) {
		israelid_checksum_ascii("12345689");
	}
}

BENCHMARK(BM_checksum_ascii);
BENCHMARK_MAIN();

