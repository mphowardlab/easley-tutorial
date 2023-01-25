
#ifdef PARALLELISM_MPI
#include <mpi.h>
#endif

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
    {
    int rank = 0;
    int size = 1;
    #ifdef PARALLELISM_MPI
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    if (provided <  MPI_THREAD_FUNNELED)
        {
        std::cerr << "Threaded MPI support not available" << std::endl;
        return 1;
        }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    #endif

    if (argc != 2)
        {
        std::cerr << "Usage: parallelism N" << std::endl;
        return 1;
        }
    const uint64_t N = std::stoll(argv[1]);

    int sum = 0;
    uint64_t start, end;
    if (size > 1)
        {
        uint64_t N_per_rank = (N+1) / size;
        start = rank*N_per_rank;
        end = (rank == size-1) ? (N+1) : start+N_per_rank;
        }
    else
        {
        start = 0;
        end = N+1;
        }
    #ifdef PARALLELISM_OPENMP
    #pragma omp parallel for schedule(static) default(none) shared(start,end) reduction(+:sum)
    #endif
    for (uint64_t i=start; i < end; ++i)
        {
        sum += 1-2*(i % 2);
        }
    #ifdef PARALLELISM_MPI
    MPI_Allreduce(MPI_IN_PLACE, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    #endif

    if (rank == 0)
        {
        std::cout << "sum of (-1)^i from i=0 to i=" << N << " = " << sum << std::endl;
        }

    #ifdef PARALLELISM_MPI
    MPI_Finalize();
    #endif
    return 0;
    }
