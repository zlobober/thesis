project(TwoShortestDisjointPaths)

add_executable(main main.cpp common.cpp bruteforce.cpp dp.cpp generators.cpp algebra.cpp algebra.h)

target_link_libraries(main -static)
