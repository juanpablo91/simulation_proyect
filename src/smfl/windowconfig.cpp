#pragma once 
#include "windowconfig.h"
#include <cstdlib> // for the use of system()

void compileWindow()
{
    system("g++ ./src/smfl/window.cpp -o app -lsfml-graphics -lsfml-window -lsfml-system");
    system("./app");
}

