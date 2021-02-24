# OPTIMISATION FLAGS :
set(OPT_FLAGS, "-Ofast")
# END OPTIMIZATION FLAGS

# SOURCES :
# Put all your sources here EXCEPT YOUR MAIN.CPP
set(SRC_RAYTRACER
    src/tests.cpp
)

# Directories containing headers must be specified in the include_directories()
include_directories(src)
# END SOURCES

# SETUP
cmake_minimum_required(VERSION 3.12)
project(Raytracer)

# BUILD OPTIONS
set(CMAKE_CXX_STANDARD 17)

# -Wall -Werror -Wextra -pedantic
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OPT_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -fsanitize=address")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_executable(raytracer)
target_sources(raytracer PRIVATE "src/main.cpp" ${SRC_RAYTRACER})
target_link_libraries(raytracer PRIVATE ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${OPENGL_LIBRARIES} ${GLM_LIBRARIES})
