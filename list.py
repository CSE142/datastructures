import sys
import random
import moneta_tags as moneta

assert len(sys.argv) == 2, "One integer argument for array size required"
size = int(sys.argv[1])
print("Initilizing random list of size {}".format(size))

#moneta.START_TRACE()

moneta.DUMP_START_ALL("init", True)
rand_list = [random.random() for i in range(size)]
moneta.DUMP_STOP("init")
moneta.DUMP_START_ALL("sort", True)
rand_list.sort()
moneta.DUMP_STOP("sort")

moneta.DUMP_START_ALL("sum", True)
sm = sum(rand_list)
moneta.DUMP_STOP("sum")

print("Sum of list: {}".format(sm))
