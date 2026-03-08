#ifndef PARSER3_H_INCLUDED
#define PARSER3_H_INCLUDED
#include <bits/stdc++.h>
using namespace std;
extern string input_case;
/////////////////////////////////////////////////////////////////////////////////////////////////.txt
extern int max_distance_constraint;
void parser_txt ();

/////////////////////////////////////////////////////////////////////////////////////////////////.def
int string_to_int();
extern float DieArea;
struct component
{
    string name, type, dir;
    float x,y;
};
struct pin
{
    string name, in_or_out, dir;
    float x,y;
};
//extern vector<component> vec_standard_cell;
//extern vector<pin> vec_pin;
extern map<string,component> map_component;
extern map<string,pin> map_pin;
extern float x_die, y_die;
const std::string split(const std::string &str, const char &delimiter);
void parser_def ();

///////////////////////////////////////////////////////////////////////////////////////////////// wire connection
typedef struct connect_wireVecStructV {
    string macro_cellName;
    string macro_instanceName;
    int bigMacro;
    string macro_PinName; // ex. o1, o2
    float rect_x1, rect_y1, rect_x2, rect_y2; //rect
}Connect_wireVecStructV;

struct weight_wireConnectNumStruct {
    string macro_cellName;
    string macro_instanceName;
    int wireConnectNum;
    int bigMacro;
};

struct weight_macroAreaStruct {
    string macro_cellName;
    string macro_instanceName;
    long int macroArea;
    int bigMacro;
};

typedef struct macro_connect_wireStructV {
    string NetName; // ex. n610963
    int HPWL;
    vector<Connect_wireVecStructV> macro_connectVec;
    vector<weight_wireConnectNumStruct> weight_wireConnectNumVec;
    vector<weight_macroAreaStruct> weight_macroAreaVec;
}Macro_Connect_WireStructV;

extern map<string, Macro_Connect_WireStructV> Macro_Connect_WireMap;

/////////////////////////////////////////////////////////////////////////////////////////////////.v
typedef struct wireStructV {
    string PinName; // ex. o1, o2
    string NetName; // ex. n610963
}WireStructV;

typedef struct macroStructV {
    string InstanceName;
    string CellName;
    map<string, WireStructV> macro_InWireMap;
    map<string, WireStructV> macro_OutWireMap;
}MacroStructV;

extern map<string, MacroStructV> MacroWireMap;

void parser_v();

/////////////////////////////////////////////////////////////////////////////////.lef
struct site
{
    string name;
    float x,y;
};

struct LayerLefStruct
{
    string name,direction;
    float pitch,width;
};

struct PinLefStruct
{
    string pinname,direction,layername;
    float rect_x1,rect_y1,rect_x2,rect_y2;//rect
    bool connectType=0;
};

struct MacroLefStruct
{
    string name,foreign;//,mclass;
    float foreignx,foreigny;
    float sizex,sizey;//size
    long int area;
    int bigMacro;
    string site;
    vector<PinLefStruct> vec_pin;
};

extern site core;
extern map<string,LayerLefStruct> LayerLefMap;//map_layer;
extern map<string,MacroLefStruct> MacroLefMap;//map_macro;
void parser_lef();


/////////////////////////////////////////////////////////////////////////.mlist
struct shiftstruct {
    string CellName,InstanceName;
    float xLoc, yLoc, index;
};
typedef struct componentStructMlist {
    string InstanceName, CellName;
    string placeSet;
    float xLoc, yLoc, shiftBoundaryX, shiftBoundaryY;
    string orientation;
    bool fixed;
    int quadrant;
    float distanceToCenter;
    vector<PinLefStruct> vec_pin;
    vector<shiftstruct> influencerVec;
    int leftpin=0,rightpin=0,toppin=0,bottompin=0;
    int standardLeftPin,standardRightPin,standardTopPin,standardBotPin;
    int macroLeftPin=0,macroRightPin,macroTopPin,macroBotPin;
}ComponentStructMlist;

extern map<string, ComponentStructMlist> MacroMlistMap;
extern map<string, ComponentStructMlist> MacroMlistMap_SA;
extern int ComponentNum;
void parser_mlist();


////////////////////////////////////////////////////////////////////////
void update_bigMacro(float v);
void analysis_density();

///////////////////////////////////////////////////////////////////////// output
void outputDMP();
void output_matlab();
void output_matlab_pins();
void outputPL();

#endif // PARSER3_H_INCLUDED
