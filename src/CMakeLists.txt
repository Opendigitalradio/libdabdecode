set(LIB_SOURCES viterbi/calc_metric.cpp
                viterbi/core_algorithms.cpp
                viterbi/fsm.cpp

                util/hex_encode.cpp

                mode/modes.cpp

                frame/frame.cpp
                frame/fib.cpp

                ensemble/ensemble.cpp

                parser/fic_parser.cpp
                parser/fic_parser_fig_0.cpp
                parser/fic_parser_fig_1.cpp)


add_library(dabdecode_static STATIC ${LIB_SOURCES})
add_library(dabdecode SHARED ${LIB_SOURCES})

add_executable(demo demo.cpp)
target_link_libraries(demo dabdecode_static)

