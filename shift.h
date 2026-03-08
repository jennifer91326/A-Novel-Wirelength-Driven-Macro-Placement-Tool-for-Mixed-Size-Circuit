#ifndef SHIFT_H_INCLUDED
#define SHIFT_H_INCLUDED
#include <bits/stdc++.h>
#include <stdio.h>
#include "parser3.h"
using namespace std;

void findInfluencer(string instanceName,string cellName);
void divideQuadrant();
void shiftAlg();
void FindShiftingRange(string instanceName, string cellName, int quadrant);
void ShiftMacro(string instanceName, string cellName, int quadrant);
extern float xboundary;
extern float yboundary;
#endif // SHIFT_H_INCLUDED
