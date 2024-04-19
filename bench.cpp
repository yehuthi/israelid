#include <benchmark/benchmark.h>
#include "israelid.h"

#ifndef __SSE4_1__
#error "benchmarking without SSE4.1 enabled"
#endif

static void BM_checksum_ascii_scalar(benchmark::State& state) {
	for (auto _ : state) _israelid_checksum_ascii_scalar("12345689", 9);
}
static void BM_israelid_checksum_ascii_9_sse(benchmark::State& state) {
	alignas(128) const char input[] = "12345689";
	for (auto _ : state) _israelid_checksum_ascii_9_sse(input);
}

BENCHMARK(BM_checksum_ascii_scalar);
BENCHMARK(BM_israelid_checksum_ascii_9_sse);
BENCHMARK_MAIN();

