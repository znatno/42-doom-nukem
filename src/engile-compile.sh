#!/usr/bin/env bash

gcc main.c -o engine `sdl-config --cflags --libs`