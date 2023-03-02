#!/bin/bash
g++ Objekt/objekt.cpp Objekt/scena.cpp test.cpp Render/render.cpp Komponente/upodabljalnik.cpp Ostalo/ostalo.cpp   glad/src/glad.c   -lGL -lglfw -lfmt -Iglad/include/