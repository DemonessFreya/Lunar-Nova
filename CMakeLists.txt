cmake_minimum_required(VERSION 3.15)
project(the-worst-game)

set(OGRE_DIR "C:/OGRE/cmake")  # Adjust path to your OGRE install folder

find_package(OGRE REQUIRED COMPONENTS Bites)

add_executable(the-worst-game main.cpp)

target_link_libraries(the-worst-game PRIVATE OgreBites)
