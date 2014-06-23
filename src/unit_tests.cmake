
################################################################################

# SAMPLEOBJ is used by lit.cfg to create a template build rule. 
# When we LIT builds a negative compilation test it uses the flags for SAMPLEOBJ
add_executable(SAMPLEOBJ sample_test.pass.cpp)
target_include_directories(SAMPLEOBJ PUBLIC ${ELIB_ROOT_PATH}/packages/rapid-cxx-test/)
target_link_libraries(SAMPLEOBJ elib ${CMAKE_THREAD_LIBS_INIT} )
set_target_properties(SAMPLEOBJ PROPERTIES EXCLUDE_FROM_ALL ON EXCLUDE_FROM_DEFAULT_BUILD ON)

# We actually need to give sample_test a target that matches the naming convention
# for tests. 
add_test_target(sample_test sample_test.pass.cpp)


if (PYTHONINTERP_FOUND)
    
  get_directory_property(ELIB_AVAILABLE_FEATURES DIRECTORY . COMPILE_DEFINITIONS)

  set(LIT_EXECUTABLE "${ELIB_ROOT_PATH}/packages/lit/lit.py" CACHE FILEPATH "Path to LLVM's lit.py.")
  set(LIT_ARGS_DEFAULT "-sv" CACHE STRING "Default lit args")
  set(LIT_ARGS "${LIT_ARGS_DEFAULT}")
  separate_arguments(LIT_ARGS)

  set(SAMPLE_OBJECT "SAMPLEOBJ")

  set(AUTO_GEN_COMMENT "## Autogenerated by elib configuration.\n# Do not edit!")
  
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.in
    ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
    @ONLY)

  add_custom_target(check-lit
    COMMAND ${ELIB_PYTHON_EXECUTABLE}
            ${LIT_EXECUTABLE}
            ${LIT_ARGS}
            ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS elib elib_python_executable
    COMMENT "Running elib tests")

else()
  message(WARNING "Could not find Python, no check target will be available!")
endif()