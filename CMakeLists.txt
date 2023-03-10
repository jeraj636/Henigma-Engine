cmake_minimum_required(VERSION 3.20)

project(a)

add_executable(${PROJECT_NAME}
        test.cpp
        Render/render.cpp
        Objekt/objekt.cpp 
        Objekt/scena.cpp 
        Komponente/upodabljalnik.cpp
        Ostalo/ostalo.cpp   
        glad/src/glad.c
        Komponente/transformacija.cpp
        
)

include_directories(${PROJECT_NAME}
        glad/include/

)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        GL 
        fmt 
)
