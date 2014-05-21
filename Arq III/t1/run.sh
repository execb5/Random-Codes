#!/bin/bash

echo "Compiling... "
gcc -ggdb Graph.c LinkedList.c -o main -I.
echo "DONE!"

echo "Simulating different cache sizes..."

echo "16kB CACHE - tam_bloco 32"
valgrind --tool=cachegrind --cache-sim=yes --D1=16384,8,32 ./main
echo "16kB CACHE - tam_bloco 64"
valgrind --tool=cachegrind --cache-sim=yes --D1=16384,8,64 ./main
echo "16kB CACHE - tam_bloco 128"
valgrind --tool=cachegrind --cache-sim=yes --D1=16384,8,128 ./main
echo "16kB CACHE - tam_bloco 256"
valgrind --tool=cachegrind --cache-sim=yes --D1=16384,8,256 ./main

echo "32kB CACHE - tam_bloco 32"
valgrind --tool=cachegrind --cache-sim=yes --D1=32768,8,32 ./main
echo "32kB CACHE - tam_bloco 64"
valgrind --tool=cachegrind --cache-sim=yes --D1=32768,8,64 ./main
echo "32kB CACHE - tam_bloco 128"
valgrind --tool=cachegrind --cache-sim=yes --D1=32768,8,128 ./main
echo "32kB CACHE - tam_bloco 256"
valgrind --tool=cachegrind --cache-sim=yes --D1=32768,8,256 ./main

echo "64kB CACHE tam_bloco 32"
valgrind --tool=cachegrind --cache-sim=yes --D1=65536,8,32 ./main
echo "64kB CACHE - tam_bloco 64"
valgrind --tool=cachegrind --cache-sim=yes --D1=65536,8,64 ./main
echo "64kB CACHE - tam_bloco 128"
valgrind --tool=cachegrind --cache-sim=yes --D1=65536,8,128 ./main
echo "64kB CACHE - tam_bloco 256"
valgrind --tool=cachegrind --cache-sim=yes --D1=65536,8,256 ./main

echo "128kB CACHE - tam_bloco 32"
valgrind --tool=cachegrind --cache-sim=yes --D1=131072,8,32 ./main
echo "128kB CACHE - tam_bloco 64"
valgrind --tool=cachegrind --cache-sim=yes --D1=131072,8,64 ./main
echo "128kB CACHE - tam_bloco 128"
valgrind --tool=cachegrind --cache-sim=yes --D1=131072,8,128 ./main
echo "128kB CACHE - tam_bloco 256"
valgrind --tool=cachegrind --cache-sim=yes --D1=131072,8,256 ./main

echo "1mB CACHE - tam_bloco 32"
valgrind --tool=cachegrind --cache-sim=yes --D1=1048576,8,32 ./main
echo "1mB CACHE - tam_bloco 64"
valgrind --tool=cachegrind --cache-sim=yes --D1=1048576,8,64 ./main
echo "1mB CACHE - tam_bloco 128"
valgrind --tool=cachegrind --cache-sim=yes --D1=1048576,8,128 ./main
echo "1mB CACHE - tam_bloco 256"
valgrind --tool=cachegrind --cache-sim=yes --D1=1048576,8,256 ./main

echo "2mB CACHE - tam_bloco 32"
valgrind --tool=cachegrind --cache-sim=yes --D1=2097152,8,32 ./main
echo "2mB CACHE - tam_bloco 64"
valgrind --tool=cachegrind --cache-sim=yes --D1=2097152,8,64 ./main
echo "2mB CACHE - tam_bloco 128"
valgrind --tool=cachegrind --cache-sim=yes --D1=2097152,8,128 ./main
echo "2mB CACHE - tam_bloco 256"
valgrind --tool=cachegrind --cache-sim=yes --D1=2097152,8,256 ./main
