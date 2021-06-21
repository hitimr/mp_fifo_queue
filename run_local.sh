#!/bin/bash

queues=("FIFO" "LB")
num_objects=("10000" "100000")
thread_cnt=("1" "2" "4" "6" "8" "10" "14" "16" "20" "24")
objectsize="10"
repeats="10"


for queue in "${queues[@]}"
do
    for objects in "${num_objects[@]}"
    do
        for objects in "${num_objects[@]}"
        do
            for threads in "${thread_cnt[@]}"
            do
                ./out/build/benchmark $queue $objects $objectsize $threads $repeats
            done # end thread_cnt
        done
    done # end num_objects
done    # end queue