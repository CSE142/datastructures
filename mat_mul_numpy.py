import numpy as np
import moneta_tags as moneta
import sys
import time

assert len(sys.argv) == 2, "One integer argument for matrix size required"
size = int(sys.argv[1])
print("Initilizing random matrices of size {}".format(size))

moneta.DUMP_START_ALL("init", True)

a = np.random.rand(size, size)
b = np.random.rand(size, size)

moneta.DUMP_STOP("init")

start_time = time.time()

moneta.DUMP_START_ALL("matmul", True)

c = np.matmul(a, b)

moneta.DUMP_STOP("matmul")

time_elapsed = time.time() - start_time
print('Total time for matrix multiplication of matrices of size {} is: {} s'.format(size, time_elapsed))
