set(LIB_SOURCES viterbi/calc_metric.cpp
                viterbi/core_algorithms.cpp
                viterbi/fsm.cpp

                frame/frame.cpp
                frame/cif.cpp
                frame/fib.cpp

                ensemble/ensemble.cpp
                ensemble/service.cpp
                ensemble/service_component.cpp
                ensemble/subchannel.cpp

                parser/fic_parser.cpp
                parser/fic_parser_fig_0.cpp
                parser/fic_parser_fig_1.cpp)


add_library(${PROJECT_NAME}_static STATIC ${LIB_SOURCES} ${DABCOMMON_SOURCES})
add_library(${PROJECT_NAME}        SHARED ${LIB_SOURCES} ${DABCOMMON_SOURCES})
