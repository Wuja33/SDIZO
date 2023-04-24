cmake_minimum_required(VERSION 3.25)
project(SDiZO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")
SET_SOURCE_FILES_PROPERTIES(${FILE} PROPERTIES COMPILE_FLAGS -Od)
add_executable(SDiZO Array/ArrayMenu.h Menu.h Menu.cpp Array/Array.cpp Array/ArrayMenu.cpp Tools/FileClass.cpp SDiZO.cpp List/ListElement.cpp List/ListElement.h List/List.cpp List/List.h List/ListMenu.cpp List/ListMenu.h Heap/Heap.cpp Heap/Heap.h Heap/HeapMenu.cpp Heap/HeapMenu.h Tools/Timer.cpp Tools/Timer.h Tools/Generator.cpp Tools/Generator.h RedBlackTree/Node.cpp RedBlackTree/Node.h RedBlackTree/RedBlackTree.cpp RedBlackTree/RedBlackTree.h RedBlackTree/RedBlackTreeMenu.cpp RedBlackTree/RedBlackTreeMenu.h)
