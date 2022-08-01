#!/bin/sh

gcc main.c util.c tetris.c render.c random.c scores.c -Iinclude -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -g -o tetris
