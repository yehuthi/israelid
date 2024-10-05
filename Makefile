.PHONY: clean bench benchmark

benchmark: ./build/bench
bench: benchmark
	./build/bench

./build/bench:
	cmake -DCMAKE_BUILD_TYPE=Release -DISRAELID_BENCH=ON -Bbuild
	cmake --build build

clean:
	rm -rf ./build
