CC=nvcc

all : naive_matrix_multiply tiled_matrix_multiply

naive_matrix_multiply : naive_matrix_multiply.cu
	${CC} -g -G $^ -o $@

tiled_matrix_multiply : tiled_matrix_multiply.cu
	${CC} -g -G $^ -o $@


clean :
	rm -f naive_matrix_multiply tiled_matrix_multiply
