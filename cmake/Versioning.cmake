find_package(Git QUIET)
SET(PROJECT_VERSION_MAJOR 0)
SET(PROJECT_VERSION_MINOR 0)
SET(PROJECT_VERSION_PATCH 1)
if (GIT_FOUND)
  execute_process(
      COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE GIT_COMMIT_HASH
      OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  message(STATUS "Git commit hash: ${GIT_COMMIT_HASH}")
else()
  message(WARNING "Git not found, commit hash will be unknown")
  set(GIT_COMMIT_HASH "unknown")
endif()
set(REVISION_FILE "${CMAKE_SOURCE_DIR}/revision.h")
if (EXISTS ${REVISION_FILE})
  file(READ ${REVISION_FILE} REVISION_FILE_CONTENTS)
  string(STRIP ${REVISION_FILE_CONTENTS} REVISION_NUMBER)
else()
  message(WARNING "Revision file not found, revision number will be set to 0")
  set(REVISION_NUMBER 0)
endif()
set(PROJECT_REVISION "${REVISION_NUMBER}")
set(PROJECT_COMMIT_HASH "${GIT_COMMIT_HASH}")
set(BUILD_REVISION "${PROJECT_REVISION} ${PROJECT_COMMIT_HASH}")

message(STATUS "Project version: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} (${BUILD_REVISION})})")
configure_file("${CMAKE_SOURCE_DIR}/src/version.h.in" 
               "${CMAKE_BINARY_DIR}/version.h"
               @ONLY)

