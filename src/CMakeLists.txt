set(LIB_SOURCES viterbi/calc_metric.cpp
                viterbi/core_algorithms.cpp
                viterbi/fsm.cpp

                util/hex_encode.cpp

                mode/modes.cpp

                frame/frame.cpp
                frame/fib/fib.cpp
                frame/fib/fig/extension.cpp
                frame/fib/fig/fig.cpp
                frame/fib/fig/fig_0/fig_0.cpp
                frame/fib/fig/fig_0/extension_0.cpp
                frame/fib/fig/fig_0/extension_1.cpp
                frame/fib/fig/fig_1/fig_1.cpp
                frame/fib/fig/fig_1/extension_0.cpp
                frame/fib/fig/fig_1/extension_1.cpp
                frame/fib/fig/fig_1/extension_5.cpp
                ensemble/ensemble.cpp)


add_library(dabdecode_static STATIC ${LIB_SOURCES})
add_library(dabdecode SHARED ${LIB_SOURCES})

add_executable(demo demo.cpp)
target_link_libraries(demo dabdecode_static)

