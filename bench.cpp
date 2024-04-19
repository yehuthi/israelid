#include <benchmark/benchmark.h>
#include "israelid.h"

static void BM_checksum_ascii(benchmark::State& state) {
	for (auto _ : state) israelid_checksum_ascii("12345689", 9);
}
static void BM_israelid_checksum_ascii_9_sse(benchmark::State& state) {
	alignas(128) const char input[] = "12345689";
	for (auto _ : state) israelid_checksum_ascii_9_sse(input);
}

BENCHMARK(BM_checksum_ascii);
BENCHMARK(BM_israelid_checksum_ascii_9_sse);
BENCHMARK_MAIN();

