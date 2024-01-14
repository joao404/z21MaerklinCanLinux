cmake_minimum_required(VERSION 3.20)

project(z21maerklincan)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Helper)
include_directories(${PROJECT_SOURCE_DIR}/include/trainBoxMaerklin)
include_directories(${PROJECT_SOURCE_DIR}/include/z21)

add_executable(z21maerklincan)

target_sources(z21maerklincan PRIVATE
        src/main.cpp
        src/z60.cpp
        src/Can2Lan.cpp
        src/Cs2DataParser.cpp
        src/WebService.cpp
        src/trainBoxMaerklin/CanInterfaceLinux.cpp
        src/trainBoxMaerklin/MaerklinCanInterface.cpp
        src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp
        src/trainBoxMaerklin/MaerklinConfigDataStream.cpp
        src/trainBoxMaerklin/MaerklinLocoManagment.cpp
        src/z21/UdpInterfaceLinux.cpp
        src/z21/z21Interface.cpp
        src/z21/z21InterfaceObserver.cpp
        )


