#[=[
    librsa, a way to encrypt simply for beginners.
    Copyright (C) 2023  rom4ster

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
]=]

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


add_executable(testRun testRun.cpp euclid.cpp mpuint.cpp ${RandomFile} rsa.cpp librsa.cpp)
add_executable(testE testEncrypt.cpp euclid.cpp mpuint.cpp ${RandomFile} rsa.cpp librsa.cpp)
add_executable(testD testDecrypt.cpp euclid.cpp mpuint.cpp ${RandomFile} rsa.cpp librsa.cpp)
add_executable(generate generateKeys.cpp euclid.cpp mpuint.cpp ${RandomFile} rsa.cpp librsa.cpp)
