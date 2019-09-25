set -x

clang++ -c -g -fPIC -I$PWD/../.. -I$JAVA_HOME/include \
  -I$JAVA_HOME/include/darwin NativeStack.cpp -o NativeStack.o

clang++ -dynamiclib -L$PWD/../.. NativeStack.o -lcstack -o libNativeStack.dylib
