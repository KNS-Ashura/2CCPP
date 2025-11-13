cmake_minimum_required(VERSION 3.30)
project(TDP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TDP main.cpp
        SRC/Game.cpp
        Header/Game.h
        SRC/Player.cpp
        Header/Player.h
        SRC/Board.cpp
        Header/Board.h
        SRC/Tile.cpp
        Header/Tile.h)
