cmake_minimum_required(VERSION 3.16.3)
project(prog)
set(SOURCES

    #core
    src/core/checkcrossing.cpp
    src/core/core.cpp
    src/core/rand.cpp


    #loging
    src/loging/loging.cpp

    #types
    src/types/alien.cpp
    src/types/alienabc.cpp
    src/types/alienfleetonestorage.cpp
    src/types/alienlazer.cpp
    src/types/arrstorageabc.cpp
    src/types/baselazer.cpp
    src/types/borderclass.cpp
    src/types/complexobject.cpp
    src/types/diescoreobject.cpp
    src/types/diescorescomplex.cpp
    src/types/elementaryobject.cpp
    src/types/fleets.cpp
    src/types/gameclass.cpp  
    src/types/herolazer.cpp
    src/types/herolazerstorage.cpp 
    src/types/gameInfoClass.cpp
    src/types/mainmenu.cpp 
    src/types/nhero.cpp
    src/types/objectsstore.cpp
    src/types/partone.cpp
    src/types/sdlclass.cpp
    src/types/sdltypes.cpp
    src/types/skyclass.cpp
    src/types/texturescollection_load.cpp
    src/types/texturescollection.cpp

    #av7
    src/main.cpp)


#SET(CMAKE_C_COMPILER /usr/bin/clang)
SET(CMAKE_C_COMPILER /usr/bin/g++)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SDL2
    SDL2_image
    SDL2_ttf)

target_compile_options(${PROJECT_NAME} PRIVATE
$<$<NOT:$<C_COMPILER_ID:MSVC>>:-O3  -Wall -Wextra -Wpedantic>)
