#!/bin/bash

queues=("FIFO" "LB")


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
