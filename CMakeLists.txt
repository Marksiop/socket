cmake_minimum_required(VERSION 3.16)

project(SOCKET VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} main.cpp)

configure_file(config.h.in config.h)

add_subdirectory(src)

find_package(Git)

if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(SUB_MODULE "sub module" ON)
    #idk why i did this there are no sub-modules but who cares 
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" src)

target_link_libraries(${PROJECT_NAME} PUBLIC sockets)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)