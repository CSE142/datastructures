# This is master makefile for this lab.  You should not edit this file, since
# changes you make will be ignored by the autograder.
#
# You can edit config.env to configure the build process.
#
# Here are the variables you can set in config.env:
#
# CMD_LINE_ARGS=<args>    :  This is passed to fp_sum.exe 
# GPROF=yes               :  Will enable gprof
# DEBUG=yes               :  Will enable debugging, which will hurt performance.
# OPTIMIZE=<gcc options>  :  Optimization flags for gcc.
# COMPILER=gcc-9          :  Choose the compiler you want.

default: tourDeCache.csv IPC.s MCMPS.s MBMPS.s all_around.s

CLEANUP=*inst_mix.csv *l1.csv tourDeCache.csv *.exe *.s

COMPILER=gcc-8

TOUR_DE_CACHE_OPTIMIZE=-O2 -fno-unroll-loops -fno-inline
IPC_OPTIMIZE=$(TOUR_DE_CACHE_OPTIMIZE)
MCMPS_OPTIMIZE=$(TOUR_DE_CACHE_OPTIMIZE)
MBMPS_OPTIMIZE=$(TOUR_DE_CACHE_OPTIMIZE)
ALL_AROUND_OPTIMIZE=$(TOUR_DE_CACHE_OPTIMIZE)

include $(ARCHLAB_ROOT)/cse141.make

TAGS=--tag GPROF=$(GPROF) --tag OPTIMIZE=$(OPTIMIZE) --tag DEVEL_MODE=$(DEVEL_MODE)

MEMOPS?=50000000

ifeq ($(DEVEL_MODE),yes)
INST_MIX_CMD_LINE_ARGS=--stat runtime=ARCHLAB_WALL_TIME $(TAGS) --tag STATS=INST_MIX 
L1_CACHE_CMD_LINE_ARGS=--stat runtime=ARCHLAB_WALL_TIME $(TAGS) --tag STATS=L1CACHE 
L2_CACHE_CMD_LINE_ARGS=--stat runtime=ARCHLAB_WALL_TIME $(TAGS) --tag STATS=L2CACHE 
TOUR_DE_CACHE_CMD_LINE_ARGS = --stat runtime=ARCHLAB_WALL_TIME 
else
INST_MIX_CMD_LINE_ARGS=--stat-set inst_mix.cfg $(TAGS) --tag STATS=INST_MIX 
L1_CACHE_CMD_LINE_ARGS=--stat-set L1.cfg $(TAGS) --tag STATS=L1CACHE 
L2_CACHE_CMD_LINE_ARGS=--stat-set L2.cfg $(TAGS) --tag STATS=L2CACHE 
TOUR_DE_CACHE_CMD_LINE_ARGS=--run-canary --MHz 1900 --engine papi --stat branches=PAPI_BR_INS --stat mispredicts=PAPI_BR_MSP --stat runtime=ARCHLAB_WALL_TIME --calc MBMPS=mispredicts/runtime/1e6 --stat IC=PAPI_TOT_INS --stat cycles=PAPI_TOT_CYC --calc IPC=IC/cycles --stat L1CM=PAPI_L1_DCM --calc MCMPS=L1CM/runtime/1e6 --calc all_around=MBMPS*IPC*MCMPS --calc GHz=cycles/runtime/1e9 $(TAGS)
endif

$(BUILD)IPC.o: C_OPTS=$(IPC_OPTIMIZE)
$(BUILD)MCMPS.o: C_OPTS=$(MCMPS_OPTIMIZE)
$(BUILD)MBMPS.o: C_OPTS=$(MBMPS_OPTIMIZE)
$(BUILD)all_around.o: C_OPTS=$(ALL_AROUND_OPTIMIZE)

IPC.s: C_OPTS=$(IPC_OPTIMIZE)
MCMPS.s: C_OPTS=$(MCMPS_OPTIMIZE)
MBMPS.s: C_OPTS=$(MBMPS_OPTIMIZE)
all_around.s: C_OPTS=$(ALL_AROUND_OPTIMIZE)

tourDeCache.exe: $(BUILD)MBMPS.o $(BUILD)IPC.o $(BUILD)MCMPS.o $(BUILD)all_around.o 

.PHONY: exe
exe: tourDeCache.exe fp_sum.exe

tourDeCache.csv: tourDeCache.exe
	./tourDeCache.exe tour --stats-file $@ $(TOUR_DE_CACHE_CMD_LINE_ARGS)
	pretty-csv $@

ARCHLAB_CACHE_CORE=archlab_run --engine papi --calc IPS=inst_count/runtime
ARCHLAB_L1=$(ARCHLAB_CACHE_CORE) --stat-set L1.cfg
ARCHLAB_L2=$(ARCHLAB_CACHE_CORE) --stat-set L2.cfg
ARCHLAB_L3=$(ARCHLAB_CACHE_CORE) --stat-set L3.cfg
ARCHLAB_INST_MIX=archlab_run --engine papi --stat-set inst_mix.cfg

CC1_CMD=/usr/lib/gcc/x86_64-linux-gnu/9/cc1plus -fpreprocessed sample.i -quiet -dumpbase sample.i -mtune=generic -march=x86-64 -auxbase-strip /tmp/main.o -g -O3 -Werror -std=gnu++11 -version -fasynchronous-unwind-tables -fstack-protector-strong -Wformat-security -o /tmp/cse141ccjTD2Yk.s

TRUE_CMD=/bin/true
GUNZIP_CMD=gzip --decompress --force --keep example.tar.gz
HTTP_CMD=pyperformance run --fast --benchmarks tornado_http
FRACTAL_CMD=pyperformance run --fast --benchmarks chaos

.PRECIOUS: %.l1.csv %.l2.csv %.l3.csv %.inst_mix.csv
.PHONY: %.perfcount

%.perfcount: %.l1.csv  #%.inst_mix.csv  # %.l2.csv %.l3.csv 
	@true

%.l1.csv: 
	$(ARCHLAB_L1) --stats-file $@ --tag app=$* -- $(CMD)
	pretty-csv $@

%.l2.csv: 
	$(ARCHLAB_L2) --stats-file $@ --tag app=$* -- $(CMD)
	pretty-csv $@

%.l3.csv: 
	$(ARCHLAB_L3) --stats-file $@ --tag app=$* -- $(CMD)
	pretty-csv $@

%.inst_mix.csv: 
	$(ARCHLAB_INST_MIX) --stats-file $@ --tag app=$* -- $(CMD)
	pretty-csv $@

.PHONY: %.all
%.all: %.perfcount %.mtrace
	merge-csv $**.csv | pretty-csv -


gcc.perfcount: CMD=$(CC1_CMD)
gunzip.perfcount: CMD=$(GUNZIP_CMD)
http.perfcount: CMD=$(HTTP_CMD)
fractal.perfcount: CMD=$(FRACTAL_CMD)
true.perfcount: CMD=$(TRUE_CMD)


fp_sum.exe: MAIN=fp_sum

FP_SUM_LIST_CMD=./fp_sum.exe --datastructure list --size 4096
fp_sum_list.perfcount: fp_sum.exe
fp_sum_list.perfcount: CMD=$(FP_SUM_LIST_CMD)
fp_sum_list.mtrace: fp_sum.exe
fp_sum_list.mtrace: CMD=$(FP_SUM_LIST_CMD)

#fp_sum_list.l1.csv: fp_sum.exe
#	./fp_sum.exe --datastructure list --size 10000000 --stats-file $@  --stat-set L1.cfg --tag app=fp_sum_list --engine papi
#fp_sum_list.inst_mix.csv: fp_sum.exe
#	./fp_sum.exe --datastructure list --size 10000000 --stats-file $@ --stat-set inst_mix.cfg --tag app=fp_sum_list --engine papi

FP_SUM_VECTOR_CMD=./fp_sum.exe --datastructure vector --size 4096
fp_sum_vector.perfcount: fp_sum.exe
fp_sum_vector.perfcount: CMD=$(FP_SUM_VECTOR_CMD)

fp_sum_vector.mtrace: fp_sum.exe
fp_sum_vector.mtrace: CMD=$(FP_SUM_VECTOR_CMD)

FP_SUM_SET_CMD=./fp_sum.exe --datastructure set --size 4096
fp_sum_set.perfcount: fp_sum.exe
fp_sum_set.perfcount: CMD=$(FP_SUM_SET_CMD)
fp_sum_set.mtrace: fp_sum.exe
fp_sum_set.mtrace: CMD=$(FP_SUM_SET_CMD)

FP_SUM_UNORDERED_SET_CMD=./fp_sum.exe --datastructure unordered_set --size 4096
fp_sum_unordered_set.perfcount: fp_sum.exe
fp_sum_unordered_set.perfcount: CMD=$(FP_SUM_UNORDERED_SET_CMD)
fp_sum_unordered_set.mtrace: fp_sum.exe
fp_sum_unordered_set.mtrace: CMD=$(FP_SUM_UNORDERED_SET_CMD)

PYTHON_LIST_CMD=python list.py 1000
python_list.perfcount: CMD=$(PYTHON_LIST_CMD)
python_list.mtrace: CMD=$(PYTHON_LIST_CMD)

PYTHON_MATMUL_CMD=python mat_mul.py 300 unopt
python_matmul.mtrace: CMD=$(PYTHON_MATMUL_CMD)
python_matmul.perfcount: CMD=$(PYTHON_MATMUL_CMD)

PYTHON_MATMUL_NUMPY_CMD=python mat_mul_numpy.py 300
python_numpy.mtrace: CMD=$(PYTHON_MATMUL_NUMPY_CMD)
python_numpy.perfcount: CMD=$(PYTHON_MATMUL_NUMPY_CMD)

PYTHON_HASH_CMD=python hash.py 1000
python_hash.mtrace: CMD=$(PYTHON_HASH_CMD)
python_hash.perfcount: CMD=$(PYTHON_HASH_CMD)


.PHONY: python
python:  python_list.perfcount python_matmul.perfcount python_numpy.perfcount

gcc.trace: CMD=$(GCC_CMD)
true.mtrace: CMD=$(TRUE_CMD)
gunzip.mtrace: CMD=$(GUNZIP_CMD)

.PHONY: %.mtrace
%.mtrace: 
	mtrace --trace $* --memops $(MEMOPS) --file-count 10 -- $(CMD)
	merge-csv $**.stats.csv | pretty-csv -

-include solution/solution.make
