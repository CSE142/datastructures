import sys
import random
import moneta_tags as moneta

assert len(sys.argv) == 2, "One integer argument for array size required"
size = int(sys.argv[1])
print("Initilizing random list of size {}".format(size))


moneta.DUMP_START_ALL("build_map", True)
the_map = {random.random():1 for i in range(size)}
moneta.DUMP_STOP("build_map")

moneta.DUMP_START_ALL("get_keys", True)
l = list(the_map.keys())
moneta.DUMP_STOP("get_keys")

moneta.DUMP_START_ALL("sort", True)
l.sort()
moneta.DUMP_STOP("sort")

