#!/bin/bash

make
./menu /dev/input/event0 `cat rootdev`
SEL=$?
cat rootdev | tail -n+$SEL | head -n+1 | cut -d= -f2
make clean
