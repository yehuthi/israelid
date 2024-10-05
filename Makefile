.PHONY: wasm clean

SRC:=$(shell find ./src -type f)
WASM_OUT:=./build/israelid.wasm

wasm: ${WASM_OUT}
${WASM_OUT}: ${SRC}
	mkdir -p build
	clang                                                       \
		-DISRAELID_WASM --target=wasm32                         \
		--no-standard-libraries -Wl,--no-entry -Wl,--export-all \
		-O3                                                     \
		-o build/israelid.wasm                                  \
		-I./include ${SRC}

clean:
	rm -rf ./build
