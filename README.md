# easley-tutorial

## Compilation

Load your build environment:
```
module load gcc/8.4.0
module load openmpi/4.0.3
module load cmake/3.19.1
```
Run CMake to configure the build
```
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install
```
Run the build and install the software
```
cmake --build build
cmake --install build
```

## Run jobs

In the ``jobs`` directory, there are different examples for running the program:

- `00-serial`: serial execution on 1 processor
- `01-openmp`: parallel execution on 4 processors using OpenMP (threaded parallelism)
- `02-mpi`: parallel execution on 4 processors using MPI (distributed parallelism)
- `03-mpi+openmp`: parallel execution on 4 processors using MPI+OpenMP (multilevel parallelism)

You can run a job using the ``sbatch`` command to submit it:
```
cd 00-serial
sbatch job.sh
```
and inspect the output in the `slurm-*.out` file that is created. The job file ``job.sh``
configures the parameters of the job.

To check the status of your jobs in the queue, use ``squeue``:
```
squeue -u <username>
```
The ``-u`` option filters only jobs for your ``<username>``. You can omit it to see the whole queue.
