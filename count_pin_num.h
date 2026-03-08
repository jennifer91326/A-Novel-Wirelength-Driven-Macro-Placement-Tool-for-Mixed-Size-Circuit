#ifndef COUNT_PIN_NUM_H_INCLUDED
#define COUNT_PIN_NUM_H_INCLUDED
#include <bits/stdc++.h>
using namespace std;

void PinConnectType();
int count_pin_num(string macroCellName, string MacroInstanceName, int x_macro, int y_macro);
//int get_flip_case(int x_macro, int y_macro, int most_pin);
//void choose_flip(int flip_case, int i);
void flip(string intance, string orientation);
void flip_SA(string intance, string orientation);
void general_flip();
void general_flip_SA();

extern vector<shiftstruct> firstQBST;
extern vector<shiftstruct> secondQBST;
extern vector<shiftstruct> thirdQBST;
extern vector<shiftstruct> fourthQBST;
extern vector<shiftstruct> minHeap;
bool lessSort(shiftstruct a,shiftstruct b);
void divideQuadrant();
void findInfluencer();


#endif // COUNT_PIN_NUM_H_INCLUDED
