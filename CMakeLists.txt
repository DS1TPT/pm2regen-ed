cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDRAD_REQUIRED ON)

project(pm2regen-ed LANGUAGES C)

add_executable(pm2regen-ed
    src/main.c
    src/langPack.c
    src/file.c
    src/save.c
    src/ui.c
    src/vt.c
    lib/tinyAES/aes.c
)

target_include_directories(pm2regen-ed PRIVATE
    inc
    lib
)