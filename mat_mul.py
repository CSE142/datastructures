import moneta_tags as moneta
import sys
import time
import random

assert len(sys.argv) == 3, "Two argument required: Matrix size and opt / unopt"
size = int(sys.argv[1])
optim = True if sys.argv[2] == 'opt' else False
print("Initilizing random matrices of size {}".format(size))

moneta.DUMP_START_ALL("init", True)

a = [[random.random() for i in range(size)] for j in range(size)]
b = [[random.random() for i in range(size)] for j in range(size)]

c = [[0.0 for i in range(size)] for j in range(size)]

moneta.DUMP_STOP('init')

start_time = time.time()

moneta.DUMP_START_ALL("matmul", True)

if not optim:
    for i in range(size):
        for j in range(size):
            for k in range(size):
                c[i][k] += a[i][j] * b[j][k]

else:
    for i in range(size):
        for j in range(size):
            tmp_sum = 0.0
            for k in range(size):
                tmp_sum += a[i][k] * b[k][j]
            c[i][j] = tmp_sum

moneta.DUMP_STOP("matmul")

time_elapsed = time.time() - start_time
print('Total time for matrix multiplication of matrices of size {} is: {} s'.format(size, time_elapsed))
