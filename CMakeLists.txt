add_executable(main main.c)
add_subdirectory(cgraph)
target_link_libraries(main cgraph)


add_executable(graph-basic-properties graph-basic-properties-main.c)
target_link_libraries(graph-basic-properties cgraph)