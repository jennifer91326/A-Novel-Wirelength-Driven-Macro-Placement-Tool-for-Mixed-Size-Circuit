
#include "parser3.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include "update_pin_location.h"
using namespace std;

bool mycompare(weight_wireConnectNumStruct s1, weight_wireConnectNumStruct s2){
   return s1.wireConnectNum > s2.wireConnectNum;
}

bool mycompareArea(weight_macroAreaStruct s1, weight_macroAreaStruct s2){
   return s1.macroArea > s2.macroArea;
}

void Weight_wireConnectNum()
{
//    cout << "--------------------------------------------------------Strart Weight_wireConnectNum" << endl;
    for (const auto& k : Macro_Connect_WireMap) {
        for (int i=0; i<k.second.macro_connectVec.size(); i++) {
            weight_wireConnectNumStruct tempVec;
            int wireConnectNum=0;
            // count macro's wire connection number
            for (const auto& j : Macro_Connect_WireMap) {
                for (int j_vec=0; j_vec<j.second.macro_connectVec.size(); j_vec++) {
                    if (j.second.macro_connectVec[j_vec].macro_instanceName == k.second.macro_connectVec[i].macro_instanceName) {
                        wireConnectNum++;
                        break;
                    }
                }
            }
            tempVec.wireConnectNum = wireConnectNum; // finish this macro's counting
            tempVec.macro_instanceName = k.second.macro_connectVec[i].macro_instanceName;
            tempVec.macro_cellName = k.second.macro_connectVec[i].macro_cellName;
            tempVec.bigMacro = k.second.macro_connectVec[i].bigMacro;
            Macro_Connect_WireMap[k.first].weight_wireConnectNumVec.push_back(tempVec);
        }
        sort(Macro_Connect_WireMap[k.first].weight_wireConnectNumVec.begin(), Macro_Connect_WireMap[k.first].weight_wireConnectNumVec.end(), mycompare);
    }

    /*
    // cout check
    for (const auto& n : Macro_Connect_WireMap) {
        if (n.second.weight_wireConnectNumVec.size() != 0) {
            cout << "NetName: " << n.first << endl;
            cout << "\tweight_wireConnectNumVec.size: " << n.second.weight_wireConnectNumVec.size() << endl;

            for (int i=0; i<n.second.weight_wireConnectNumVec.size(); i++) {
                cout << "\t\tmacro_name(cell Name): "
                << n.second.weight_wireConnectNumVec[i].macro_cellName
                << "\n\t\tmacro_name(instance Name): "
                << n.second.weight_wireConnectNumVec[i].macro_instanceName<<endl
                << " \t\twireConnectNum: "<<n.second.weight_wireConnectNumVec[i].wireConnectNum
                << endl << endl;
            }
        }
    }
     */
//    cout << "--------------------------------------------------------End Weight_wireConnectNum" << endl;
}

void Weight_macroArea()
{
    for (const auto& k : Macro_Connect_WireMap) {
        for (int i=0; i<k.second.macro_connectVec.size(); i++) {
            weight_macroAreaStruct temp;
            temp.macro_cellName = k.second.macro_connectVec[i].macro_cellName;
            temp.macroArea = MacroLefMap[temp.macro_cellName].area;
            temp.macro_instanceName = k.second.macro_connectVec[i].macro_instanceName;
            temp.bigMacro = k.second.macro_connectVec[i].bigMacro;
            Macro_Connect_WireMap[k.first].weight_macroAreaVec.push_back(temp);
        }
        sort(Macro_Connect_WireMap[k.first].weight_macroAreaVec.begin(), Macro_Connect_WireMap[k.first].weight_macroAreaVec.end(), mycompareArea);
    }


    // cout check
//    for (const auto& n : Macro_Connect_WireMap) {
//        if (n.second.weight_macroAreaVec.size() != 0) {
//            cout << "NetName: " << n.first << endl;
//            cout << "\tweight_macroAreaVec.size: " << n.second.weight_macroAreaVec.size() << endl;
//
//            for (int i=0; i<n.second.weight_macroAreaVec.size(); i++) {
//                cout << "\t\tmacro_name(cell Name): "
//                << n.second.weight_macroAreaVec[i].macro_cellName
//                << "\n\t\tmacro_name(instance Name): "
//                << n.second.weight_macroAreaVec[i].macro_instanceName << endl
//                << " \t\twireConnectNum: " << n.second.weight_macroAreaVec[i].macroArea
//                << endl << endl;
//            }
//        }
//    }

}
