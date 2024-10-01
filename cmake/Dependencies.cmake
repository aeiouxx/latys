include(FetchContent)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master)
FetchContent_MakeAvailable(yaml-cpp)
if (WIN32)
  message(STATUS "Building for Windows, including wintun.")
  set(WINTUN_BIN_DIR ${CMAKE_SOURCE_DIR}/ext/wintun/bin)
  string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} WINTUN_ARCH)
  set(WINTUN_DLL_PATH "${WINTUN_BIN_DIR}/${WINTUN_ARCH}/wintun.dll")
  message(STATUS "Wintun DLL path: ${WINTUN_DLL_PATH}")
  # Copy the wintun.dll to output directory (if standalone i guess).
  if (MODE_STANDALONE)
    message(STATUS "Copying wintun.dll to output directory.")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${WINTUN_DLL_PATH}
      $<TARGET_FILE_DIR:${PROJECT_NAME}>)
  endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp)
