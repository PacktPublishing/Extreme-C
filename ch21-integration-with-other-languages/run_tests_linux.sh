set -x

export CSTACK_LIB_PATH=.

LD_LIBRARY_PATH=$CSTACK_LIB_PATH ./cstack_tests.out
