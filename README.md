This repo is a fork of Sean Bowe (@ebfull)'s lightning circuit. More background can be found in the original repo https://github.com/ebfull/lightning_circuit.

This fork is experimental change to fix ``./get-libsnark/`` and so on; this fork is for a very special purpose.

This repo implements the following SNARK using [libsnark](https://github.com/scipr-lab/libsnark):

``ZkPoK{ (R1, R2): H1 = sha256(R1) and H2 = sha256(R2) and R1 = R2 ^ X }``

Read: given `H1`, `H2`, and `X`, prove you know `R1` and `R2` such that `R1` is the preimage of `H1`,
`R2` is the preimage of `H2`, and `R1` is `R2 xor X`.

## how to compile

``./get-libsnark && make``

## dependency
``
sudo apt install cmake g++ pkg-config libssl-dev libprocps-dev libboost-all-dev libgmp-dev
``
