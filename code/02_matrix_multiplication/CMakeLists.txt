project (strassen)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS_RELEASE "-O4")

add_executable (strassen_test main.c matrix.c strassen.c homework.c)

