project(synthetic_balls)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
ADD_DEFINITIONS(
    -std=c++11
    #-fsanitize=undefined
    #-g

    -march=core-avx2
    -O3
    #-fopenmp
    -ffat-lto-objects
    #-fopenmp-simd
    #-Wopenmp-simd
    #-ftree-vectorizer-verbose=3

    -DDEBUG
)
link_directories(/usr/lib64)
target_link_libraries(synthetic_balls gsl gslcblas QtCore SDL2 pthread gomp)
#boost -> bessel
