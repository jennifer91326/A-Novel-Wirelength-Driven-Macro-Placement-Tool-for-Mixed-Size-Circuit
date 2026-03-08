#include "parser3.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include "count_pin_num.h"
using namespace std;

void PinConnectType()
{
    float sizex, sizey, rectx, recty;
    int macroLeftPin=0, macroRightPin=0, macroTopPin=0, macroBotPin=0;

    for (const auto& i : MacroWireMap) {
    for (const auto& k : i.second.macro_InWireMap) {
        //for (auto& i : MacroWireMap)
        {
            auto findOutPin = i.second.macro_OutWireMap.find(k.second.NetName);
            if ( findOutPin != i.second.macro_OutWireMap.end() ) {

                macroLeftPin=0; macroRightPin=0; macroTopPin=0, macroBotPin=0;
                auto findMlist = MacroMlistMap.find(i.second.InstanceName);
                auto iter_Lef = MacroLefMap.find(i.second.CellName);
                sizex = iter_Lef->second.sizex;
                sizey = iter_Lef->second.sizey;
                for (int j=0; j<findMlist->second.vec_pin.size(); j++) {
                    if (findMlist->second.vec_pin[j].pinname == findOutPin->second.PinName) {
                        findMlist->second.vec_pin[j].connectType == 1;

                        rectx = findMlist->second.vec_pin[j].rect_x1;
                        recty = findMlist->second.vec_pin[j].rect_y1;
                        if(rectx < sizex/2) macroLeftPin+=1;
                        else macroRightPin+=1;
                        if(recty < sizey/2) macroBotPin+=1;
                        else macroTopPin+=1;
                    }
                }
                MacroMlistMap[i.second.InstanceName].macroLeftPin += macroLeftPin;
                MacroMlistMap[i.second.InstanceName].macroRightPin += macroRightPin;
                MacroMlistMap[i.second.InstanceName].macroBotPin += macroBotPin;
                MacroMlistMap[i.second.InstanceName].macroTopPin += macroTopPin;
            }
        }
        //for (auto& i : MacroWireMap)
        {
            auto findInPin = i.second.macro_InWireMap.find(k.second.NetName);
            if ( findInPin != i.second.macro_InWireMap.end() ) {

                macroLeftPin=0, macroRightPin=0, macroTopPin=0, macroBotPin=0;
                auto findMlist = MacroMlistMap.find(i.second.InstanceName);
                auto iter_Lef = MacroLefMap.find(i.second.CellName);
                sizex = iter_Lef->second.sizex;
                sizey = iter_Lef->second.sizey;
                for (int j=0; j<findMlist->second.vec_pin.size(); j++) {
                    if (findMlist->second.vec_pin[j].pinname == findInPin->second.PinName) {
                        findMlist->second.vec_pin[j].connectType == 1;

                        rectx = findMlist->second.vec_pin[j].rect_x1;
                        recty = findMlist->second.vec_pin[j].rect_y1;
                        if(rectx < sizex/2) macroLeftPin+=1;
                        else macroRightPin+=1;
                        if(recty < sizey/2) macroBotPin+=1;
                        else macroTopPin+=1;
                    }
                }
                MacroMlistMap[i.second.InstanceName].macroLeftPin += macroLeftPin;
                MacroMlistMap[i.second.InstanceName].macroRightPin += macroRightPin;
                MacroMlistMap[i.second.InstanceName].macroBotPin += macroBotPin;
                MacroMlistMap[i.second.InstanceName].macroTopPin += macroTopPin;
            }
        }
    }
    }
}

int count_pin_num(string macroCellName, string MacroInstanceName, int x_macro, int y_macro)//per one macro
{
    float rectx, recty; //from .lef

    int lpin=0, rpin=0, tpin=0, bpin=0;
    int standardLeftPin,standardRightPin,standardTopPin,standardBotPin;

    auto iter_Mlist = MacroMlistMap.find(MacroInstanceName);

    float sizex = MacroLefMap[macroCellName].sizex;
    float sizey = MacroLefMap[macroCellName].sizey;

    for(int i=0; i<iter_Mlist->second.vec_pin.size(); i++)//one macro
    {
        rectx = iter_Mlist->second.vec_pin[i].rect_x1;
        recty = iter_Mlist->second.vec_pin[i].rect_y1;
        if(rectx < sizex/2) lpin+=1;
        else rpin+=1;
        if(recty < sizey/2) bpin+=1;
        else tpin+=1;
    }
    //MacroLefMap[macroCellName].leftpin = leftpin;
    //MacroLefMap[macroCellName].rightpin = rightpin;
    //MacroLefMap[macroCellName].bottompin = bottompin;
    //MacroLefMap[macroCellName].toppin = toppin;

    int most_pin=0;
    MacroMlistMap[MacroInstanceName].standardLeftPin = lpin-MacroMlistMap[MacroInstanceName].macroLeftPin;
    MacroMlistMap[MacroInstanceName].standardRightPin = rpin-MacroMlistMap[MacroInstanceName].macroRightPin;
    MacroMlistMap[MacroInstanceName].standardBotPin = bpin-MacroMlistMap[MacroInstanceName].macroBotPin;
    MacroMlistMap[MacroInstanceName].standardTopPin = tpin-MacroMlistMap[MacroInstanceName].macroTopPin;
    int leftpin = MacroMlistMap[MacroInstanceName].standardLeftPin;
    int rightpin = MacroMlistMap[MacroInstanceName].standardRightPin;
    int bottompin = MacroMlistMap[MacroInstanceName].standardBotPin;
    int toppin = MacroMlistMap[MacroInstanceName].standardTopPin;


    if(leftpin>rightpin && toppin>bottompin) most_pin = 2;      //left & top
    else if(leftpin>rightpin && toppin<bottompin) most_pin = 3; //left & bottom
    else if(leftpin<rightpin && toppin>bottompin) most_pin = 1; //right & top
    else if(leftpin<rightpin && toppin<bottompin) most_pin = 4; //right & bottom

    //cout<<"MacroInstanceName: "<<MacroInstanceName<<endl;
    //cout<<"   leftpin: "<< MacroMlistMap[MacroInstanceName].standardLeftPin<<"   rightpin: "<< MacroMlistMap[MacroInstanceName].standardRightPin
    //<<"   bottompin: "<< MacroMlistMap[MacroInstanceName].standardBotPin<<"   toppin: "<< MacroMlistMap[MacroInstanceName].standardTopPin << "   most: " << most_pin << endl;
    //cout << "\n y_macro: " << y_macro;
    if((x_macro+sizex*1000 >= x_die/2) && (y_macro+sizey*1000 >= y_die/2) && most_pin == 1) return 1;
    else if((x_macro+sizex*1000 >= x_die/2) && (y_macro+sizey*1000 >= y_die/2) && most_pin == 2) return 2;
    else if((x_macro+sizex*1000 >= x_die/2) && (y_macro+sizey*1000 >= y_die/2) && most_pin == 3) return 3;
    else if((x_macro+sizex*1000 >= x_die/2) && (y_macro+sizey*1000 >= y_die/2) && most_pin == 4) return 4;

    else if((x_macro+sizex*1000 <= x_die/2) && (y_macro+sizey*1000 >= y_die/2) && most_pin == 1) return 5;
    else if((x_macro+sizex*1000 <= x_die/2) && (y_macro+sizey*1000 >= y_die/2) && most_pin == 2) return 6;
    else if((x_macro+sizex*1000 <= x_die/2) && (y_macro+sizey*1000 >= y_die/2) && most_pin == 3) return 7;
    else if((x_macro+sizex*1000 <= x_die/2) && (y_macro+sizey*1000 >= y_die/2) && most_pin == 4) return 8;

    else if((x_macro+sizex*1000 <= x_die/2) && (y_macro+sizey*1000 <= y_die/2) && most_pin == 1) return 9;
    else if((x_macro+sizex*1000 <= x_die/2) && (y_macro+sizey*1000 <= y_die/2) && most_pin == 2) return 10;
    else if((x_macro+sizex*1000 <= x_die/2) && (y_macro+sizey*1000 <= y_die/2) && most_pin == 3) return 11;
    else if((x_macro+sizex*1000 <= x_die/2) && (y_macro+sizey*1000 <= y_die/2) && most_pin == 4) return 12;

    else if((x_macro+sizex*1000 >= x_die/2) && (y_macro+sizey*1000 <= y_die/2) && most_pin == 1) return 13;
    else if((x_macro+sizex*1000 >= x_die/2) && (y_macro+sizey*1000 <= y_die/2) && most_pin == 2) return 14;
    else if((x_macro+sizex*1000 >= x_die/2) && (y_macro+sizey*1000 <= y_die/2) && most_pin == 3) return 15;
    else if((x_macro+sizex*1000 >= x_die/2) && (y_macro+sizey*1000 <= y_die/2) && most_pin == 4) return 16;
    else return 17;
}

void flip(string intance, string orientation)
{
    if (orientation=="S")
    {
        if (MacroMlistMap[intance].orientation == "N")
            MacroMlistMap[intance].orientation = "S"; //xy
        else if (MacroMlistMap[intance].orientation == "FS")
            MacroMlistMap[intance].orientation = "FN";//y
        else if (MacroMlistMap[intance].orientation == "FN")
            MacroMlistMap[intance].orientation = "FS";//x
        else if (MacroMlistMap[intance].orientation == "S")
            MacroMlistMap[intance].orientation = "N";
        return;
    }

    else if (orientation=="FS")
    {
        if (MacroMlistMap[intance].orientation == "N")
            MacroMlistMap[intance].orientation = "FS"; //xy
        else if (MacroMlistMap[intance].orientation == "FS")
            MacroMlistMap[intance].orientation = "N";
        else if (MacroMlistMap[intance].orientation == "FN")
            MacroMlistMap[intance].orientation = "S";
        else if (MacroMlistMap[intance].orientation == "S")
            MacroMlistMap[intance].orientation = "FN";
        return;
    }

    else if (orientation=="FN")
    {
        if (MacroMlistMap[intance].orientation == "N")
            MacroMlistMap[intance].orientation = "FN"; //xy
        else if (MacroMlistMap[intance].orientation == "FS")
            MacroMlistMap[intance].orientation = "S";
        else if (MacroMlistMap[intance].orientation == "FN")
            MacroMlistMap[intance].orientation = "N";
        else if (MacroMlistMap[intance].orientation == "S")
            MacroMlistMap[intance].orientation = "FS";
        return;
    }

    else
    {
        MacroMlistMap[intance].orientation = MacroMlistMap[intance].orientation;
        return;
    }
}

void flip_SA(string intance, string orientation)
{
    if (orientation=="S")
    {
        if (MacroMlistMap_SA[intance].orientation == "N")
            MacroMlistMap_SA[intance].orientation = "S"; //xy
        else if (MacroMlistMap_SA[intance].orientation == "FS")
            MacroMlistMap_SA[intance].orientation = "FN";//y
        else if (MacroMlistMap_SA[intance].orientation == "FN")
            MacroMlistMap_SA[intance].orientation = "FS";//x
        else if (MacroMlistMap_SA[intance].orientation == "S")
            MacroMlistMap_SA[intance].orientation = "N";
        return;
    }

    else if (orientation=="FS")
    {
        if (MacroMlistMap_SA[intance].orientation == "N")
            MacroMlistMap_SA[intance].orientation = "FS"; //xy
        else if (MacroMlistMap_SA[intance].orientation == "FS")
            MacroMlistMap_SA[intance].orientation = "N";
        else if (MacroMlistMap_SA[intance].orientation == "FN")
            MacroMlistMap_SA[intance].orientation = "S";
        else if (MacroMlistMap_SA[intance].orientation == "S")
            MacroMlistMap_SA[intance].orientation = "FN";
        return;
    }

    else if (orientation=="FN")
    {
        if (MacroMlistMap_SA[intance].orientation == "N")
            MacroMlistMap_SA[intance].orientation = "FN"; //xy
        else if (MacroMlistMap_SA[intance].orientation == "FS")
            MacroMlistMap_SA[intance].orientation = "S";
        else if (MacroMlistMap_SA[intance].orientation == "FN")
            MacroMlistMap_SA[intance].orientation = "N";
        else if (MacroMlistMap_SA[intance].orientation == "S")
            MacroMlistMap_SA[intance].orientation = "FS";
        return;
    }

    else
    {
        MacroMlistMap_SA[intance].orientation = MacroMlistMap_SA[intance].orientation;
        return;
    }
}
void general_flip()
{
    string macro_name;
    int x_macro, y_macro;
    int flip_case;

    //int ttest=1;
    PinConnectType();

    for (auto i : MacroMlistMap)
    {
        x_macro = i.second.xLoc;
        y_macro = i.second.yLoc;
        //cout<<ttest++<<": "<< i.second.InstanceName<<endl;
        flip_case = count_pin_num(i.second.CellName, i.second.InstanceName , x_macro, y_macro);
        //<<flip_case<<endl;

        switch (flip_case)
        {
            case 1: case 6: case 11: case 16:
                flip(i.second.InstanceName,"S");
                break;

            case 2: case 5: case 12: case 15:
                flip(i.second.InstanceName,"FS");
                break;

            case 3: case 8: case 9: case 14:
                flip(i.second.InstanceName,"N");
                break;

            case 4: case 7: case 10: case 13:
                //cout << "\ncase: " << flip_case << " " << i.second.InstanceName;
                flip(i.second.InstanceName,"FN");
                break;

            default:
                flip(i.second.InstanceName,"N");
                break;
        }

    }
}
void general_flip_SA()
{
    string macro_name;
    int x_macro, y_macro;
    int flip_case;
    for (auto i : MacroMlistMap_SA)
    {
        x_macro = i.second.xLoc;
        y_macro = i.second.yLoc;
        flip_case = count_pin_num(i.second.CellName, i.second.InstanceName , x_macro, y_macro);
//        cout<< i.second.InstanceName<<endl<<flip_case<<endl;

        switch (flip_case)
        {
            case 1: case 6: case 11: case 16:
                flip_SA(i.second.InstanceName,"S");
                break;

            case 2: case 5: case 12: case 15:
                flip_SA(i.second.InstanceName,"FS");
                break;

            case 3: case 8: case 9: case 14:
                flip_SA(i.second.InstanceName,"N");
                break;

            case 4: case 7: case 10: case 13:
                //cout << "\ncase: " << flip_SA_case << " " << i.second.InstanceName;
                flip_SA(i.second.InstanceName,"FN");
                break;

            default:
                flip_SA(i.second.InstanceName,"N");
                break;
        }

    }
}
