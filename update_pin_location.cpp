//SAmap
#include "parser3.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include "update_pin_location.h"
using namespace std;

void update_pin_location_SA( string MacroCellName, string MacroInstanceName)
{
        map<string, MacroLefStruct>::iterator iter_macroLef;

        if (MacroMlistMap_SA[MacroInstanceName].orientation == "N")
       {
            for (int i=0; i<MacroMlistMap_SA[MacroInstanceName].vec_pin.size(); i++) {
                // Lef's pin location is orientation 'N'
                float new_RectX1 = MacroLefMap[MacroCellName].vec_pin[i].rect_x1;
                float new_RectX2 = MacroLefMap[MacroCellName].vec_pin[i].rect_x2;
                float new_RectY1 = MacroLefMap[MacroCellName].vec_pin[i].rect_y1;
                float new_RectY2 = MacroLefMap[MacroCellName].vec_pin[i].rect_y2;
                // update to MlistMap
                MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_x1 = new_RectX1;
                MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_x2 = new_RectX2;
                MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_y1 = new_RectY1;
                MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_y2 = new_RectY2;
            }
        }
        else
        {
            iter_macroLef = MacroLefMap.find(MacroCellName);
            if( iter_macroLef != MacroLefMap.end() ) {
                MacroLefStruct tempMacro = iter_macroLef->second;
                float sizex = tempMacro.sizex; float sizey = tempMacro.sizey;

                // case: flip y axis
                if (MacroMlistMap_SA[MacroInstanceName].orientation == "FN" ) {
                    for (int i=0; i<MacroMlistMap_SA[MacroInstanceName].vec_pin.size(); i++) {
                        // Lef's pin location is orientation 'N'
                        float new_RectX1 = sizex - tempMacro.vec_pin[i].rect_x2;
                        float new_RectX2 = sizex - tempMacro.vec_pin[i].rect_x1;
                        float new_RectY1 = tempMacro.vec_pin[i].rect_y1;
                        float new_RectY2 = tempMacro.vec_pin[i].rect_y2;
                        // update to MlistMap
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_x1 = new_RectX1;
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_x2 = new_RectX2;
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_y1 = new_RectY1;
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_y2 = new_RectY2;
                    }
                }
                // case: flip x axis
                if (MacroMlistMap_SA[MacroInstanceName].orientation == "FS" ) {
                    for (int i=0; i<MacroMlistMap_SA[MacroInstanceName].vec_pin.size(); i++) {
                        // Lef's pin location is orientation 'N'
                        float new_RectX1 = tempMacro.vec_pin[i].rect_x1;
                        float new_RectX2 = tempMacro.vec_pin[i].rect_x2;
                        float new_RectY1 = sizey - tempMacro.vec_pin[i].rect_y2 ;
                        float new_RectY2 = sizey - tempMacro.vec_pin[i].rect_y1;
                        // update to MlistMap
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_x1 = new_RectX1;
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_x2 = new_RectX2;
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_y1 = new_RectY1;
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_y2 = new_RectY2;
                    }
                }
                if (MacroMlistMap_SA[MacroInstanceName].orientation == "S") {
                    for (int i=0; i<MacroMlistMap_SA[MacroInstanceName].vec_pin.size(); i++) {
                        // Lef's pin location is orientation 'N'
                        float new_RectX1 = sizex - tempMacro.vec_pin[i].rect_x2;
                        float new_RectX2 = sizex - tempMacro.vec_pin[i].rect_x1;
                        float new_RectY1 = sizey - tempMacro.vec_pin[i].rect_y2 ;
                        float new_RectY2 = sizey - tempMacro.vec_pin[i].rect_y1;
                        // update to MlistMap
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_x1 = new_RectX1;
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_x2 = new_RectX2;
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_y1 = new_RectY1;
                        MacroMlistMap_SA[MacroInstanceName].vec_pin[i].rect_y2 = new_RectY2;
                    }
                }

            }
        }



//     Check
//    if(MacroInstanceName == "A3_B17_C131_D2_E1_F1_o1271927")
//    {
//        cout << "Name: " << MacroInstanceName << "\n";
//        cout << "\tOrientation: " << MacroMlistMap_SA[MacroInstanceName].orientation << endl;
//        for (int j=0; j<MacroMlistMap_SA[MacroInstanceName].vec_pin.size(); j++) {
//            if(MacroMlistMap_SA[MacroInstanceName].vec_pin[j].pinname =="i6")
//            {
//                cout << "\tpin name: " << MacroMlistMap_SA[MacroInstanceName].vec_pin[j].pinname << endl;
//                cout << "\t\tpin location x1: " << MacroMlistMap_SA[MacroInstanceName].vec_pin[j].rect_x1 << "\n";
//                cout << "\t\tpin location x2: " << MacroMlistMap_SA[MacroInstanceName].vec_pin[j].rect_x2 << "\n";
//                cout << "\t\tpin location y1: " << MacroMlistMap_SA[MacroInstanceName].vec_pin[j].rect_y1 << "\n";
//                cout << "\t\tpin location y2: " << MacroMlistMap_SA[MacroInstanceName].vec_pin[j].rect_y2 << "\n";
//            }
//
//        }
//        cout << endl;
//    }



}

void update_pin_location( string MacroCellName, string MacroInstanceName)
{
        map<string, MacroLefStruct>::iterator iter_macroLef;

        if (MacroMlistMap[MacroInstanceName].orientation == "N")
       {
            for (int i=0; i<MacroMlistMap[MacroInstanceName].vec_pin.size(); i++) {
                // Lef's pin location is orientation 'N'
                float new_RectX1 = MacroLefMap[MacroCellName].vec_pin[i].rect_x1;
                float new_RectX2 = MacroLefMap[MacroCellName].vec_pin[i].rect_x2;
                float new_RectY1 = MacroLefMap[MacroCellName].vec_pin[i].rect_y1;
                float new_RectY2 = MacroLefMap[MacroCellName].vec_pin[i].rect_y2;
                // update to MlistMap
                MacroMlistMap[MacroInstanceName].vec_pin[i].rect_x1 = new_RectX1;
                MacroMlistMap[MacroInstanceName].vec_pin[i].rect_x2 = new_RectX2;
                MacroMlistMap[MacroInstanceName].vec_pin[i].rect_y1 = new_RectY1;
                MacroMlistMap[MacroInstanceName].vec_pin[i].rect_y2 = new_RectY2;
            }
        }
        else
        {
            iter_macroLef = MacroLefMap.find(MacroCellName);
            if( iter_macroLef != MacroLefMap.end() ) {
                MacroLefStruct tempMacro = iter_macroLef->second;
                float sizex = tempMacro.sizex; float sizey = tempMacro.sizey;

                // case: flip y axis
                if (MacroMlistMap[MacroInstanceName].orientation == "FN" ) {
                    for (int i=0; i<MacroMlistMap[MacroInstanceName].vec_pin.size(); i++) {
                        // Lef's pin location is orientation 'N'
                        float new_RectX1 = sizex - tempMacro.vec_pin[i].rect_x2;
                        float new_RectX2 = sizex - tempMacro.vec_pin[i].rect_x1;
                        float new_RectY1 = tempMacro.vec_pin[i].rect_y1;
                        float new_RectY2 = tempMacro.vec_pin[i].rect_y2;
                        // update to MlistMap
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_x1 = new_RectX1;
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_x2 = new_RectX2;
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_y1 = new_RectY1;
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_y2 = new_RectY2;
                    }
                }
                // case: flip x axis
                if (MacroMlistMap[MacroInstanceName].orientation == "FS" ) {
                    for (int i=0; i<MacroMlistMap[MacroInstanceName].vec_pin.size(); i++) {
                        // Lef's pin location is orientation 'N'
                        float new_RectX1 = tempMacro.vec_pin[i].rect_x1;
                        float new_RectX2 = tempMacro.vec_pin[i].rect_x2;
                        float new_RectY1 = sizey - tempMacro.vec_pin[i].rect_y2 ;
                        float new_RectY2 = sizey - tempMacro.vec_pin[i].rect_y1;
                        // update to MlistMap
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_x1 = new_RectX1;
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_x2 = new_RectX2;
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_y1 = new_RectY1;
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_y2 = new_RectY2;
                    }
                }
                if (MacroMlistMap[MacroInstanceName].orientation == "S") {
                    for (int i=0; i<MacroMlistMap[MacroInstanceName].vec_pin.size(); i++) {
                        // Lef's pin location is orientation 'N'
                        float new_RectX1 = sizex - tempMacro.vec_pin[i].rect_x2;
                        float new_RectX2 = sizex - tempMacro.vec_pin[i].rect_x1;
                        float new_RectY1 = sizey - tempMacro.vec_pin[i].rect_y2 ;
                        float new_RectY2 = sizey - tempMacro.vec_pin[i].rect_y1;
                        // update to MlistMap
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_x1 = new_RectX1;
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_x2 = new_RectX2;
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_y1 = new_RectY1;
                        MacroMlistMap[MacroInstanceName].vec_pin[i].rect_y2 = new_RectY2;
                    }
                }

            }
        }



//     Check
//    if(MacroInstanceName == "A3_B17_C131_D2_E1_F1_o1271927")
//    {
//        cout << "Name: " << MacroInstanceName << "\n";
//        cout << "\tOrientation: " << MacroMlistMap[MacroInstanceName].orientation << endl;
//        for (int j=0; j<MacroMlistMap[MacroInstanceName].vec_pin.size(); j++) {
//            if(MacroMlistMap[MacroInstanceName].vec_pin[j].pinname =="i6")
//            {
//                cout << "\tpin name: " << MacroMlistMap[MacroInstanceName].vec_pin[j].pinname << endl;
//                cout << "\t\tpin location x1: " << MacroMlistMap[MacroInstanceName].vec_pin[j].rect_x1 << "\n";
//                cout << "\t\tpin location x2: " << MacroMlistMap[MacroInstanceName].vec_pin[j].rect_x2 << "\n";
//                cout << "\t\tpin location y1: " << MacroMlistMap[MacroInstanceName].vec_pin[j].rect_y1 << "\n";
//                cout << "\t\tpin location y2: " << MacroMlistMap[MacroInstanceName].vec_pin[j].rect_y2 << "\n";
//            }
//
//        }
//        cout << endl;
//    }



}
