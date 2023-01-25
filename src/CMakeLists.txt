add_executable(parallelism main.cc)

if(PARALLELISM_MPI)
    target_link_libraries(parallelism PUBLIC MPI::MPI_CXX)
    target_compile_definitions(parallelism PUBLIC PARALLELISM_MPI)
endif()
if(PARALLELISM_OPENMP)
    target_link_libraries(parallelism PUBLIC OpenMP::OpenMP_CXX)
    target_compile_definitions(parallelism PUBLIC PARALLELISM_OPENMP)
endif()
target_compile_features(parallelism PUBLIC cxx_std_14)
# selectively turn on compile options for gcc & clang
target_compile_options(parallelism PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Werror -Wall -Wextra>
     $<$<CXX_COMPILER_ID:GNU>:-fdiagnostics-color=always>
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-fcolor-diagnostics>)

install(TARGETS parallelism RUNTIME)
