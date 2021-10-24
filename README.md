# VU-Simple-Blockchain
This is a repository for the second assignment of VU Blockchain Technologies course (simple blockchain).

Contents:
* [Changelog](#changelog)
* [Getting started](#getting-started)
* [Program output](#program-output)
  * [Option #1](#option-1)
  * [Option #2](#option-2)

## Changelog

* [v0.1](https://github.com/MantasM2001/VU-Simple-Blockchain/releases/tag/v0.1): Initial version of the blockchain. (NOTE! Does not work correctly, see [v0.1.1](https://github.com/MantasM2001/VU-Simple-Blockchain/releases/tag/v0.1.1) for a working first version.)
* [v0.1.1](https://github.com/MantasM2001/VU-Simple-Blockchain/releases/tag/v0.1.1): Bug fixes, added transaction verification.
* [v0.2](https://github.com/MantasM2001/VU-Simple-Blockchain/releases/tag/v0.2): Adding support for 5 miners (done sequentially), fixing some bugs.
* [v0.2.0.1](https://github.com/MantasM2001/VU-Simple-Blockchain/releases/tag/v0.2.0.1): Small changes to the pushing of the blocks on the blockchain.
* [v0.2.1](https://github.com/MantasM2001/VU-Simple-Blockchain/tree/v0.2.1) (UNRELEASED, not working properly): Trying to initialize mining (the blocks) in parallel.

## Getting started

First, you need to compile the files:
```shell
g++ -o program main.cpp funkcijos.cpp Hashas/hash.cpp -O2
```
After that, you can simply run your program:
```shell
.\program.exe 
```

## Program output

As of [v0.2](https://github.com/MantasM2001/VU-Simple-Blockchain/releases/tag/v0.2), the program (after running it) will let the user choose between two options:
```shell
1 - Blockchain'as su 1 miner'iu (v0.1)
2 - Blockchain'as su 5 miner'iais (v0.2)

Iveskite savo pasirinkima: 1
```
### Option 1

If the user chooses option 1, the program will output the mining process of blocks:
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
This is one example of a mined block which was added to the blockchain.

Here you can see:
* The time it took to mine the block;
* The difficulty (the first number shows how many zeroes should the hash have to have; in this example - 2);
* The hash of the block;
* The timestamp (when the block was mined);
* The nonce;
* The merkle tree of all transactions of the block.

The program mines blocks until it runs out of transactions (~10000).

### Option 2

If the user chooses option 2, the program, similarly to option 1, will output the mining process of blocks, with the addition of which miner mined out the block:
```shell
Pradedamas mininimas...

Isminino 1 mineris!

Bloko mininimas baigtas.

Mininimas uztruko: 0.406569 s.
Difficulty: 3-0
Hashas: 00074032e241b64dc885dc790790ec5e19983b57727b55d232603fe6567c0406
Timestamp: 1634921455 (2021-10-22 19:50:55)
Nonce: 2350378
Merkle: 724d8b139760f86f2adb03b06f34ab68fc9af874b790bc89b364f4c7d9e35747
```
Also, that miner will be awarded with some currency (for example, 5).
