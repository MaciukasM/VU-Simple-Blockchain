# VU-Simple-Blockchain
This is a repository for the second assignment of VU Blockchain Technologies course (simple blockchain).

## Getting started

First, you need to compile the files:
```shell
g++ -o program main.cpp funkcijos.cpp Hashas/hash.cpp -O2
```
Alternatively, you can use a makefile command:
```shell
mingw32-make all
```
After that, you can simply run your program:
```shell
.\program.exe 
```

## Program output

After running the program, the program will output the mining process of blocks:
```shell
Pradedamas mininimas...

Mininimas baigtas.

Mininimas uztruko: 0.0114432 s.
Difficulty: 2-0
Hashas: 00a1af27f05e7bb6b6d3c41e62a23423a07f9a24194ba8804062738c2221e5bb
Timestamp: 1634238279 (2021-10-14 22:04:39)
Nonce: 989687
Merkle: ef3b4120afa5c61e4366fd3ce7a761bb33da2b77c29d6d01452b03f18751a8af

------------------------------------------------------
```
This is one example of a mined block. 

Here you can see:
* The time it took to mine the block;
* The difficulty (the first number shows how many zeroes should the hash have to have; in this example - 2);
* The hash of the block;
* The timestamp (when the block was mined);
* The nonce;
* The merkle tree of all transactions of the block.

