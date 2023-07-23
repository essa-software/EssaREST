cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(EssaREST)

add_executable(
    EssaREST
    main.cpp
    src/server/BasicServer.cpp
    src/server/HttpServer.cpp

    src/rest/HttpClientRequest.cpp
    
)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

include(FetchContent)
set(ESSA_UTIL_ONLY ON)
FetchContent_Declare(Essa
    GIT_REPOSITORY https://github.com/essa-software/EssaGUI.git
    GIT_TAG e9cfe93830c596aa17e89b36e9ae4cefc3460bfe
    OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(Essa)

target_link_libraries(EssaREST Essa::Util)
essautil_setup_target(EssaREST)