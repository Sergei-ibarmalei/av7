cmake_minimum_required(VERSION 3.16.3)
project(prog)
set(SOURCES
    src/types/sdlclass.cpp
    src/types/sdltypes.cpp
    src/loging/loging.cpp
    src/types/texturescollection.cpp
    src/types/texturescollection_load.cpp
    src/types/mainmenu.cpp 
    src/types/gameclass.cpp   
    src/types/borderclass.cpp
    src/types/skyclass.cpp
    src/types/partone.cpp
    src/types/gameInfoClass.cpp
    src/types/longlazer.cpp
    src/types/n_ob.cpp
    src/types/n_oblist.cpp
    src/types/elist.cpp
    src/types/aliens.cpp
    src/types/fleets.cpp
    src/types/movingfleets.cpp
    src/core/core.cpp
    src/core/rand.cpp
    src/core/checking.cpp
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
$<$<NOT:$<C_COMPILER_ID:MSVC>>:  -Wall -Wextra -Wpedantic>)
