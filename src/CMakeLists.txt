project(OpenGL_start)

set(SOURCES
        main.cpp
        OpenGLWindow.cpp
        OpenGLWindow.hpp
        ShaderNecromanter.cpp
        ShaderNecromanter.hpp
        OpenGLApplication.cpp
        OpenGLApplication.hpp
        models/CubeModel.cpp
        models/CubeModel.hpp
        models/LandModel.cpp
        models/LandModel.hpp
        Stepper.cpp
        Stepper.hpp
        world/Camera.cpp
        world/Camera.hpp
        light/PointLight.cpp
        light/PointLight.hpp
        models/SphereModel.cpp
        models/SphereModel.hpp
        Texture.cpp
        Texture.hpp framebuffers/MSAAFramebuffer.cpp framebuffers/MSAAFramebuffer.hpp models/QuadModel.cpp models/QuadModel.hpp glErrorCheck.hpp GLPrograms/PostProcessingProgram.cpp GLPrograms/PostProcessingProgram.hpp models/SkyBox.cpp models/SkyBox.hpp GLPrograms/ObjectsRenderingProgram.cpp GLPrograms/ObjectsRenderingProgram.hpp GLPrograms/SkyBoxProgram.cpp GLPrograms/SkyBoxProgram.hpp framebuffers/DownSamplingFramebuffer.cpp framebuffers/DownSamplingFramebuffer.hpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")


add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} glfw glad glm)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY}  glfw glad glm)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ../glad/include/ models ../stb/)

install(DIRECTORY glsl DESTINATION "bin/glsl")
install(TARGETS ${PROJECT_NAME} DESTINATION "bin")