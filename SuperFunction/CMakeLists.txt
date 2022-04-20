cmake_minimum_required(VERSION 3.13)
project(SuperFunction VERSION 1.0.0)

set(PROJECT_NAME SuperFunction)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra --coverage -g -Wno-unused-variable")



################################################################################
# Source groups
################################################################################
set(main
    "superFunction.cpp"
)

source_group("." FILES ${main})

set(ALL_FILES
    ${main}
)

add_executable(${PROJECT_NAME} ${ALL_FILES})
