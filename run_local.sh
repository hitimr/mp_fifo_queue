#!/bin/bash

queues=("FIFO" "LB")
num_objects=("100" "1000" "10000")
thread_cnt=("1" "2" "4" "6" "8" "10" "12" "14" "16" "18" "20" "22" "24" "26" "28" "30" "32" "34" "36" "38" "40" "42" "44" "46" "48" "50" "52" "54" "56" "58" "60" "62" "64")
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
