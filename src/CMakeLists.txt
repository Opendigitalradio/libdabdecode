set(LIB_SOURCES viterbi/fsm.cpp)

add_library(dabdecode_static STATIC ${LIB_SOURCES})
add_library(dabdecode SHARED ${LIB_SOURCES})
