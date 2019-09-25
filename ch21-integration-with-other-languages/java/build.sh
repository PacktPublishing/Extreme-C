set -x

mkdir -p build/headers
mkdir -p build/classes

javac -cp src -h build/headers -d build/classes src/com/packt/extreme_c/ch21/ex1/Main.java
