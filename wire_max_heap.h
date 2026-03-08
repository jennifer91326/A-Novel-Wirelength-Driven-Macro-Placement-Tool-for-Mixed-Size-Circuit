#ifndef WIRE_MAX_HEAP_H_INCLUDED
#define WIRE_MAX_HEAP_H_INCLUDED
#include "parser3.h"
#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;
extern bool only_general;
extern long long totalWirelength_big;
extern long long totalWirelength;
extern int bigwire_num;
extern vector <Macro_Connect_WireStructV> thinglist;
//extern Macro_Connect_WireStructV heap[500];
bool compare(Macro_Connect_WireStructV s1, Macro_Connect_WireStructV s2);
long long compute_HPWL();
void create_maxheap();
void insert_max_heap();
void update_HPWL();
void compute_oriTotalHPWL();
Macro_Connect_WireStructV delete_max_heap();
#endif // WIRE_MAX_HEAP_H_INCLUDED




