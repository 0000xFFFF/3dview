#!/bin/bash
g++ -D GLM_ENABLE_EXPERIMENTAL src/*.cpp src/*.c -Wfatal-errors -lglfw -lGL -lGLEW -lSDL2 -o 3dtest
