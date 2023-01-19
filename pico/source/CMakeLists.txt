# set min ver
cmake_minimum_required(VERSION 3.12)

#inlude build functions from pico sdk
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

#set proj name_
project(DIY_Datalink_Pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#create sdk subdir for libs
pico_sdk_init()

#tell cmake where exec source is
add_executable(${PROJECT_NAME}
    main.c
)

#create map stuff
pico_add_extra_outputs(${PROJECT_NAME})

#LINK TO LIB
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
)

#enable usb output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
