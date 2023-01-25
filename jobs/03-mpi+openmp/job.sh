#!/bin/bash
#SBATCH -N 1
#SBATCH --ntasks-per-node 4
#SBATCH -t 00:05:00
#SBATCH --export=NONE
#SBATCH -p chen_std

# load the software
module load gcc/8.4.0
module load openmpi/4.0.3
export PATH=../../install/bin${PATH:+:${PATH}}

# run the job
export OMP_NUM_THREADS=2
time mpirun -n 2 --map-by ppr:2:socket:PE=2 --report-bindings parallelism 100000000000
