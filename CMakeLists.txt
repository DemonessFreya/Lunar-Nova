cmake_minimum_required(VERSION 3.15)
project(OgreApp)

set(OGRE_DIR "C:/OGRE/cmake")  # Adjust path to your OGRE install folder

find_package(OGRE REQUIRED COMPONENTS Bites)

add_executable(OgreApp main.cpp)

target_link_libraries(OgreApp PRIVATE OgreBites)
