#!/bin/sh

gcc main.c util.c tetris.c render.c -Iinclude -lSDL2 -lSDL2_image -g -o tetris
