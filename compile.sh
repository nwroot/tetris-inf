#!/bin/sh

gcc main.c util.c tetris.c render.c random.c -Iinclude -lSDL2 -lSDL2_image -lSDL2_mixer -g -o tetris
