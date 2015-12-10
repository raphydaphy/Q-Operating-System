#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "screenUtils.h"

// T: Top, B: Bottom, L: Left, R: Right
// H: Horizontal, V: Vertical, S: Single, D: Double
// X: Cross sign
typedef enum {
    V_S = 0xB3,
    V_L_S = 0xB4,
    V_L_D = 0xB9,
    V_D = 0xBA,
    T_R_D = 0xBB,
    B_R_D = 0xBC,
    T_R_S = 0xBF,
    B_L_S = 0xC0,
    H_T_S = 0xC1,
    H_B_S = 0xC2,
    V_R_S = 0xC3,
    H_S = 0xC4,
    X_S = 0xC5,
    B_L_D = 0xC8,
    T_L_D = 0xC9,
    H_T_D = 0xCA,
    H_B_D = 0xCB,
    V_R_D = 0xCC,
    H_D = 0xCD,
    X_D = 0xCE,
    B_R_S = 0xD9,
    T_L_S = 0xDA
} box_chars;

void paintScreen(int);

void printAt(string, int, uint16, uint16);

void drawFrame(int, uint16, uint16, uint16, uint16);

void drawBorder(int, uint16, uint16, uint16, uint16);

void messageBox(string);

void waitUntilKey(int);

#endif
