//SAmap
#include "parser3.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include "create_wire_connection.h"
#include "update_wire_connection.h"
using namespace std;

void update_wire_connection_SA( string MacroCellName, string MacroInstanceName )
{
//    cout << "Strart Update_wire_connection" << endl;
    map<string, WireStructV>::iterator iter_out;
    map<string, WireStructV>::iterator iter_in;

    Connect_wireVecStructV tempVec;
    auto iter_v = MacroWireMap.find(MacroInstanceName);

    for (const auto& k : iter_v->second.macro_InWireMap) {
        Macro_Connect_WireStructV temp;
        for (auto& i : MacroWireMap) {
            // to see if there is any same wireName in other macro's OutputWireMap
            iter_out = i.second.macro_OutWireMap.find(k.second.NetName);
            if ( iter_out != i.second.macro_OutWireMap.end() ) { // if find in OutWireMap
                auto iter_macroMlist = MacroMlistMap_SA.find(i.second.InstanceName);

                for (int j=0; j<iter_macroMlist->second.vec_pin.size(); j++) {
                    if (iter_macroMlist->second.vec_pin[j].pinname == iter_out->second.PinName) {

                        // rect: absolute coordinates
                        tempVec.rect_x1 = iter_macroMlist->second.xLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_x1);
                        tempVec.rect_x2 = iter_macroMlist->second.xLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_x2);
                        tempVec.rect_y1 = iter_macroMlist->second.yLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_y1);
                        tempVec.rect_y2 = iter_macroMlist->second.yLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_y2);
                    }
                }
                tempVec.macro_cellName = i.second.CellName;
                tempVec.macro_instanceName = i.second.InstanceName;
//                    tempVec.bigMacro= iter_macroLef->second.bigMacro;
                tempVec.macro_PinName = iter_out->second.PinName;
                temp.macro_connectVec.push_back(tempVec);
//                    cout<<i.first<<" "<<i.second.InstanceName<<" "<<iter_macroLef->second.bigMacro<<" "<<endl;

            }
        }
        for (auto& i : MacroWireMap) {
            // to see if there is any same wireName in other macro's InputWireMap
            iter_in = i.second.macro_InWireMap.find(k.second.NetName);
            if ( iter_in != i.second.macro_InWireMap.end() ) { // if find in InputWireMap
                auto iter_macroMlist = MacroMlistMap_SA.find(i.second.InstanceName);

                for (int j=0; j<iter_macroMlist->second.vec_pin.size(); j++) {
                    if (iter_macroMlist->second.vec_pin[j].pinname == iter_in->second.PinName) {
                        // rect: absolute coordinates
                        tempVec.rect_x1 = iter_macroMlist->second.xLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_x1);
                        tempVec.rect_x2 = iter_macroMlist->second.xLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_x2);
                        tempVec.rect_y1 = iter_macroMlist->second.yLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_y1);
                        tempVec.rect_y2 = iter_macroMlist->second.yLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_y2);

                    }

                }

                tempVec.macro_cellName = i.second.CellName;
                tempVec.macro_instanceName = i.second.InstanceName;
//                    tempVec.bigMacro= iter_macroLef->second.bigMacro;
                tempVec.macro_PinName = iter_in->second.PinName;
                temp.macro_connectVec.push_back(tempVec);
//                    cout<<i.first<<" "<<i.second.InstanceName<<" "<<iter_macroLef->second.bigMacro<<" "<<endl;
            }
        }
        temp.NetName = k.second.NetName;
        Macro_Connect_WireMap[k.second.NetName] = temp;

    }
}

void update_wire_connection( string MacroCellName, string MacroInstanceName )
{
//    cout << "Strart Update_wire_connection" << endl;
    map<string, WireStructV>::iterator iter_out;
    map<string, WireStructV>::iterator iter_in;

    Connect_wireVecStructV tempVec;
    auto iter_v = MacroWireMap.find(MacroInstanceName);

    for (const auto& k : iter_v->second.macro_InWireMap) {
        Macro_Connect_WireStructV temp;
        for (auto& i : MacroWireMap) {
            // to see if there is any same wireName in other macro's OutputWireMap
            iter_out = i.second.macro_OutWireMap.find(k.second.NetName);
            if ( iter_out != i.second.macro_OutWireMap.end() ) { // if find in OutWireMap
                auto iter_macroMlist = MacroMlistMap.find(i.second.InstanceName);

                for (int j=0; j<iter_macroMlist->second.vec_pin.size(); j++) {
                    if (iter_macroMlist->second.vec_pin[j].pinname == iter_out->second.PinName) {

                        // rect: absolute coordinates
                        tempVec.rect_x1 = iter_macroMlist->second.xLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_x1);
                        tempVec.rect_x2 = iter_macroMlist->second.xLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_x2);
                        tempVec.rect_y1 = iter_macroMlist->second.yLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_y1);
                        tempVec.rect_y2 = iter_macroMlist->second.yLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_y2);
                    }
                }
                tempVec.macro_cellName = i.second.CellName;
                tempVec.macro_instanceName = i.second.InstanceName;
//                    tempVec.bigMacro= iter_macroLef->second.bigMacro;
                tempVec.macro_PinName = iter_out->second.PinName;
                temp.macro_connectVec.push_back(tempVec);
//                    cout<<i.first<<" "<<i.second.InstanceName<<" "<<iter_macroLef->second.bigMacro<<" "<<endl;

            }
        }
        for (auto& i : MacroWireMap) {
            // to see if there is any same wireName in other macro's InputWireMap
            iter_in = i.second.macro_InWireMap.find(k.second.NetName);
            if ( iter_in != i.second.macro_InWireMap.end() ) { // if find in InputWireMap
                auto iter_macroMlist = MacroMlistMap.find(i.second.InstanceName);

                for (int j=0; j<iter_macroMlist->second.vec_pin.size(); j++) {
                    if (iter_macroMlist->second.vec_pin[j].pinname == iter_in->second.PinName) {
                        // rect: absolute coordinates
                        tempVec.rect_x1 = iter_macroMlist->second.xLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_x1);
                        tempVec.rect_x2 = iter_macroMlist->second.xLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_x2);
                        tempVec.rect_y1 = iter_macroMlist->second.yLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_y1);
                        tempVec.rect_y2 = iter_macroMlist->second.yLoc
                                        +(2000*iter_macroMlist->second.vec_pin[j].rect_y2);

                    }

                }

                tempVec.macro_cellName = i.second.CellName;
                tempVec.macro_instanceName = i.second.InstanceName;
//                    tempVec.bigMacro= iter_macroLef->second.bigMacro;
                tempVec.macro_PinName = iter_in->second.PinName;
                temp.macro_connectVec.push_back(tempVec);
//                    cout<<i.first<<" "<<i.second.InstanceName<<" "<<iter_macroLef->second.bigMacro<<" "<<endl;
            }
        }
        temp.NetName = k.second.NetName;
        Macro_Connect_WireMap[k.second.NetName] = temp;

    }
}

