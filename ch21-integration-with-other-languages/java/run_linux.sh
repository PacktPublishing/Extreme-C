set -x

LD_LIBRARY_PATH=$PWD/.. java -Djava.library.path=$PWD/native -cp build/classes com.packt.extreme_c.ch21.ex1.Main
