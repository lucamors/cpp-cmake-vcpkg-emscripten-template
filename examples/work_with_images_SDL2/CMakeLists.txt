set(EXAMPLE_NAME "work_with_images_SDL2")

add_executable(${EXAMPLE_NAME} main.cc)

# Link Flags --------------------------------------------------------------------------------------
if(EMSCRIPTEN)
    set(EMSDK_FLAGS 
        "--use-port=sdl2"
        "--use-port=sdl2_image:formats=bmp,png,xpm,jpg"
        "--preload-file assets"
        "-s USE_GLFW=3"
        "-s ASSERTIONS=1"
        "-s WASM=1"
        "-s ASYNCIFY"
        "-s GL_ENABLE_GET_PROC_ADDRESS=1"
        "-s FORCE_FILESYSTEM=1"
    )
    string(JOIN " " EMSDK_FLAGS ${EMSDK_FLAGS})
    set_target_properties(${EXAMPLE_NAME} PROPERTIES LINK_FLAGS ${EMSDK_FLAGS})
else()
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_image REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
endif()

# Assets ------------------------------------------------------------------------------------------
set(ASSET_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/assets)
file(COPY ${ASSET_SOURCE_DIR} DESTINATION ${CMAKE_BINARY_DIR})
add_compile_definitions(ASSETS_DIR="/assets")