#!/usr/bin/env bash

gcc -O3 main.c -o engine `sdl-config --cflags --libs`