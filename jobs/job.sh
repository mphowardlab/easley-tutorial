#!/bin/bash

export PATH=$HOME/Documents/code/mphowardlab/easley-tutorial/install/bin:${PATH}
N=100000000000

echo "Using serial process"
export OMP_NUM_THREADS=1
time parallelism $N
echo ""

for np in 2 4
do
    echo "Using ${np} OpenMP threads"
    export OMP_NUM_THREADS=${np}
    time parallelism $N
    echo ""
done

for np in 2 4
do
    echo "Using ${np} MPI ranks"
    export OMP_NUM_THREADS=1
    time mpirun -n $np parallelism $N
    echo ""
done

echo "Using 2 MPI ranks, 2 OpenMP threads without mapping"
export OMP_NUM_THREADS=2
time mpirun -n 2 --report-bindings parallelism $N
echo ""

echo "Using 2 MPI ranks, 2 OpenMP threads with mapping"
export OMP_NUM_THREADS=2
time mpirun -n 2 --map-by ppr:2:socket:PE=2 --report-bindings parallelism $N
echo ""

