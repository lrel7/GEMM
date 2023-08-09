CC = g++
CXXFLAGS = -O3 -march=native -mtune=native -flto -fuse-linker-plugin --std=c++2a -fopenmp -g
LDFLAGS = -lm -isystem ../benchmark/include -L../benchmark/build/src -lbenchmark -lpthread
TARGET = matmul
SOURCES = matmul_${VERSION}.c main.cpp test.cpp

ifeq (${VERSION},)
    $(error VERSION is not specified. Please provide a valid VERSION value.)
endif

benchmark:
	${CC} ${SOURCES} ${CXXFLAGS} ${LDFLAGS} -o ${TARGET}

run: benchmark
	./matmul > ../output/output_${VERSION}.txt
	cat ../output/output_${VERSION}.txt

clean:
	rm -f *.o ${TARGET}
