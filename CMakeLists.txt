project(untitled)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

IF(WIN32)
    set(RandomFile "random.cpp")
ELSE()
    set(RandomFile "unirandom.cpp")
ENDIF()


add_executable(test test.cpp euclid.cpp mpuint.cpp ${RandomFile} rsa.cpp librsa.cpp)
