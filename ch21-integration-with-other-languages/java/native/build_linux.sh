set -x

g++ -c -g -fPIC -I$PWD/../.. -I$JAVA_HOME/include \
  -I$JAVA_HOME/include/linux NativeStack.cpp -o NativeStack.o

g++ -shared -L$PWD/../.. NativeStack.o -lcstack -o libNativeStack.so
