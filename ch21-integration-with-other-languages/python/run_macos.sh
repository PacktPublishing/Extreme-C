set -x

export CSTACK_LIB_PATH=..

DYLD_LIBRARY_PATH=$CSTACK_LIB_PATH python stack.py
