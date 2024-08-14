cmake_minimum_required(VERSION 3.10)

project(SFML-TicTacToe)

set(CMAKE_CXX_STANDARD 17)

set(APP_NAME SFMLTicTacToe)

include_directories(vendor/include)
link_directories(vendor/lib)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

add_executable(${APP_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${APP_NAME} flac freetype ogg openal32 sfml-audio-d sfml-graphics-d sfml-network-d sfml-system-d sfml-window-d vorbis vorbisenc vorbisfile)

file(GLOB DLL_FILES "${CMAKE_SOURCE_DIR}/vendor/outputDlls/*.dll")

set(DESTINATION_DIR "${CMAKE_BINARY_DIR}")

add_custom_command(
    TARGET ${APP_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL_FILES}
        ${DESTINATION_DIR}
    COMMENT "Coping output dlls to build directory..."
)
