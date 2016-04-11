set(LIB_SOURCES viterbi/fsm.cpp
                viterbi/core_algorithms.cpp
                viterbi/calc_metric.cpp
                frame.cpp
                fib.cpp
                modes/helpers.cpp)

add_library(dabdecode_static STATIC ${LIB_SOURCES})
add_library(dabdecode SHARED ${LIB_SOURCES})

add_executable(demo demo.cpp)
target_link_libraries(demo dabdecode_static)
