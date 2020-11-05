#!/bin/bash

dir="../nv"
#dir="."

./client 127.0.0.1 5555 < "${dir}/init_commands.txt"

for ((i=0;i<20;i++))
  do \
    ./client 127.0.0.1 5555 < "${dir}/client_commands.txt" > /tmp/res$i &
  done
wait

./client 127.0.0.1 5555 < "${dir}/finish_commands.txt"

for ((i=0;i<20;i++))
  do \
    for ((j=0;j<i;j++))
      do \
        diff -q /tmp/res$i /tmp/res$j
      done
    grep '^ *Student' /tmp/res$i | wc
  done
