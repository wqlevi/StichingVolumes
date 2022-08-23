#!/bin/bash

# 1. run with single core CPU compilation(~1.4sec)
gcc -Wall -o acc_CPU assemble_accCPU_3d.c && time ./acc_CPU

# 2. run with multicore CPU compilation(Failed)
nvc -fast -ta=multicore -Minfo=accel -o acc_CPU assemble_accCPU_3d.c && time ./acc_CPU

# 3. run with GPU compilation(~2.2sec)
nvc -fast -ta=tesla,managed -Minfo=accel -o acc_GPU assemble_accGPU_3d.c && time ./acc_GPU
