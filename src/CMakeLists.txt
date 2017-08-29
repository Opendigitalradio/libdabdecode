set(LIBRARY_NAME ${${PROJECT_NAME}_LOWER})

add_library(${LIBRARY_NAME}
  ensemble/ensemble.cpp
  ensemble/service.cpp
  ensemble/service_component.cpp
  ensemble/subchannel.cpp
  frame/cif.cpp
  frame/fib.cpp
  frame/frame.cpp
  parser/fic_parser.cpp
  parser/fic_parser_fig_0.cpp
  parser/fic_parser_fig_1.cpp
  viterbi/calc_metric.cpp
  viterbi/core_algorithms.cpp
  viterbi/fsm.cpp
  )

target_link_libraries(${LIBRARY_NAME}
  ${LIBRARY_NAME}_iface
  )

if(NOT ${${PROJECT_NAME}_UPPER}_HAS_PARENT)
  install(TARGETS ${LIBRARY_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    )
endif()
