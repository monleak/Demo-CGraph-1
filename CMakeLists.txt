add_executable(main main.c)
add_subdirectory(cgraph)
target_link_libraries(main cgraph)