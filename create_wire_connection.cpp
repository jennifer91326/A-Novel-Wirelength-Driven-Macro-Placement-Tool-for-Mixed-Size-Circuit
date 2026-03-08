#include "parser3.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include "create_wire_connection.h"
using namespace std;

map<string, Macro_Connect_WireStructV> Macro_Connect_WireMap;
void create_wire_connection()
{

//    cout << "--------------------------------------------------------Start Create_wire_connection" << endl;
    map<string, WireStructV>::iterator iter_out;
    map<string, WireStructV>::iterator iter_in;
    map<string, MacroLefStruct>::iterator iter_macroLef;
    map<string, componentStructMlist>::iterator it;//
    //Macro_Connect_WireStructV temp;
    Connect_wireVecStructV tempVec;

    for (const auto& n : MacroWireMap) {
        for (const auto& k : n.second.macro_InWireMap) {
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
                    iter_macroLef = MacroLefMap.find(i.second.CellName);
                    tempVec.bigMacro= iter_macroLef->second.bigMacro;
                    tempVec.macro_PinName = iter_out->second.PinName;
                    temp.macro_connectVec.push_back(tempVec);
//                    cout<<i.first<<" "<<i.second.InstanceName<<" "<<iter_macroLef->second.bigMacro<<" "<<endl;

                }
            }
            for (auto& i : MacroWireMap) {
                iter_in = i.second.macro_InWireMap.find(k.second.NetName); // to see if there is any same wireName in other macro's InputWireMap
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
                    iter_macroLef = MacroLefMap.find(i.second.CellName);
                    tempVec.bigMacro= iter_macroLef->second.bigMacro;
                    tempVec.macro_PinName = iter_in->second.PinName;
                    temp.macro_connectVec.push_back(tempVec);
//                    cout<<i.first<<" "<<i.second.InstanceName<<" "<<iter_macroLef->second.bigMacro<<" "<<endl;
                }
            }
            if (temp.macro_connectVec.size() > 1) {
                temp.NetName = k.second.NetName;
                Macro_Connect_WireMap[k.second.NetName] = temp;
            }
        }
    }





//
//
//
//    int sum=0;
//
//    for (auto n : Macro_Connect_WireMap) {
//    if(n.first == "n1084086")
//    {
//
//
//        cout << "NetName: " << n.first << endl;
//        cout << "\tmacro_connectVec.size: " << n.second.macro_connectVec.size() << endl;
////        sum++;
////
//        for (int i=0; i<n.second.macro_connectVec.size(); i++) {
////
//            cout << "\t\tmacro_name(cell Name): "
//                 << n.second.macro_connectVec[i].macro_cellName
//                 << "\n\t\tmacro_name(instance Name): "
//                 << n.second.macro_connectVec[i].macro_instanceName<<endl
//                 << " \t\tbig_macro: "<<n.second.macro_connectVec[i].bigMacro
//                 << " PinName: " << n.second.macro_connectVec[i].macro_PinName << endl;
//
//            cout << "\t\tPin_rectX1: " << n.second.macro_connectVec[i].rect_x1
//                 << " Pin_rectX2: " << n.second.macro_connectVec[i].rect_x2
//                 << " Pin_rectY1: " << n.second.macro_connectVec[i].rect_y1
//                 << " Pin_rectY2: " << n.second.macro_connectVec[i].rect_y2 << endl;
//
//        }
//    }
//    }
//    cout<<Wirelength_big<<endl;
//    cout << "--------------------------------------------------------End Create_wire_connection" << endl;
};





