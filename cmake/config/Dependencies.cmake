include("ExternalDependency")

set(${${PROJECT_NAME}_UPPER}_DEPS)

if(EXTERNAL_DEPS_VIA STREQUAL "conan")
  if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS)
    include("ConanPackages")
    install_conan_packages(SYSTEM_HEADERS
      PKGOPTS ${CONAN_OPTIONS}
      )
    list(APPEND ${${PROJECT_NAME}_UPPER}_DEPS
      CONAN_PKG::libdabcommon
      )
  endif()
elseif(EXTERNAL_DEPS_VIA STREQUAL "git")
  external_dependency(CMAKE
    NAME    "dabcommon"
    REPO    "https://github.com/fmorgner/libdabcommon"
    )
else()
  message(FATAL_ERROR "Unknown dependency resolution mechanism 'EXTERNAL_DEPS_VIA}'")
endif()
