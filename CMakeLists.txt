cmake_minimum_required(VERSION 3.16)

project(SOCKET VERSION 1.0.0)

add_executable(${PROJECT_NAME}  main.cpp)

add_subdirectory(src)

configure_file(config.h.in config.h)

find_package(Git)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(SUB_MODULES "sub modules for git" ON)
endif()


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} sockets)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_SOURCE_DIR}/build/config.h" DESTINATION include)
