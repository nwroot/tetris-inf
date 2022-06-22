#!/bin/sh

gcc main.c util.c -Iinclude -lSDL2 -lSDL2_image -o tetris
