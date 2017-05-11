project(OpenGL_start)

set(SOURCES
        main.cpp
        OpenGLWindow.cpp
        OpenGLWindow.hpp
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")


add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} glfw glad glm)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY}  glfw glad glm)
target_include_directories(${PROJECT_NAME} PUBLIC ../glad/include/)

install(DIRECTORY glsl DESTINATION "bin/glsl")
install(TARGETS ${PROJECT_NAME} DESTINATION "bin")