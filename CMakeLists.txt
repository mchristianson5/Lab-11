cmake_minimum_required(VERSION 3.5)

project(lab11 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(lab11
        main.c
        type.h
        util.c
        util.h
        cd_ls_pwd.h
        cd_ls_pwd.c
        globals.h
        globals.c
        )
set_target_properties(lab11 PROPERTIES COMPILE_OPTIONS "-m32" LINK_FLAGS "-m32")
target_compile_options(lab11 PRIVATE -Wall -W -pedantic -pipe -Wno-unused-parameter -ggdb)
