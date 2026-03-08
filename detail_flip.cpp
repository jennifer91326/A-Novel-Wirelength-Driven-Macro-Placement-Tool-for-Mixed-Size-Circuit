//SAmap
#include "parser3.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include "wire_max_heap.h"
#include "create_wire_connection.h"
#include "update_wire_connection.h"
#include "update_pin_location.h"
#include "count_pin_num.h"
#include "Weight_wireConnectNum.h"
using namespace std;

void detail_flip_SA()
{
//    cout<<"--------------------------------------------------start detail flip"<<endl;
    create_maxheap();
    string instanceName="",cellName="";
    int HPWL_best=totalWirelength;

    for(int i=0; i<thinglist.size(); i++)
    {

        Macro_Connect_WireStructV tmp;
        tmp = thinglist[i];

//        cout<<"netname: "<<tmp.NetName<<endl;
//        cout<<"\tori HPWL: "<<Macro_Connect_WireMap[tmp.NetName].HPWL<<endl;
        for(int j=0; j<tmp.weight_wireConnectNumVec.size(); j++)
        {

            string solu="",ori_orientation;

//            if(tmp.weight_wireConnectNumVec[j].bigMacro )
            {
                instanceName = tmp.weight_wireConnectNumVec[j].macro_instanceName;
                cellName = tmp.weight_wireConnectNumVec[j].macro_cellName;

//               cout<< MacroMlistMap_SA[instanceName].InstanceName<<endl;
                if(MacroMlistMap_SA[instanceName].fixed==0)
                {
                    ori_orientation = MacroMlistMap_SA[instanceName].orientation;
//                    cout<<"\tori orientation:  "<<MacroMlistMap_SA[instanceName].orientation<<endl;

//                    cout<<"start N:"<<endl;
                    MacroMlistMap_SA[instanceName].orientation = "N" ;

                    update_pin_location_SA( cellName, instanceName );
                    update_wire_connection_SA( cellName, instanceName );
                    update_HPWL();

                    if(totalWirelength<HPWL_best)
                    {
                        HPWL_best = totalWirelength;
                        solu = "N";
                    }
//                    cout<<"end N:"<<endl;

//                    cout<<"start FN:"<<endl;
                    MacroMlistMap_SA[instanceName].orientation = "FN" ;

                    update_pin_location_SA( cellName, instanceName );
                    update_wire_connection_SA( cellName, instanceName );
                    update_HPWL();

                    if(totalWirelength<HPWL_best )
                    {
                        HPWL_best = totalWirelength;
                        solu = "FN";
                    }
//                    cout<<"end FN:"<<endl;

//                    cout<<"start FS:"<<endl;
                    MacroMlistMap_SA[instanceName].orientation = "FS" ;

                    update_pin_location_SA( cellName, instanceName );
                    update_wire_connection_SA( cellName, instanceName );
                    update_HPWL();

                    if(totalWirelength<HPWL_best)
                    {
                        HPWL_best = totalWirelength;
                        solu = "FS";
                    }
//                    cout<<"end FS:"<<endl;

//                    cout<<"start S:"<<endl;
                    MacroMlistMap_SA[instanceName].orientation = "S" ;

                    update_pin_location_SA( cellName, instanceName );
                    update_wire_connection_SA( cellName, instanceName );
                    update_HPWL();

                    if(totalWirelength<HPWL_best )
                    {
                        HPWL_best = totalWirelength;
                        solu = "S";
                    }
//                    cout<<"end S:"<<endl;

//                    cout<<"start solu:"<<endl;
                    if(solu!="")
                    {
                        MacroMlistMap_SA[instanceName].orientation = solu ;
                        MacroMlistMap_SA[instanceName].fixed=1;
                        update_pin_location_SA( cellName, instanceName );
                        update_wire_connection_SA( cellName, instanceName );
                        update_HPWL();
                    }
                    else
                    {
                        MacroMlistMap_SA[instanceName].orientation = ori_orientation ;
                        MacroMlistMap_SA[instanceName].fixed=1;
                        update_pin_location_SA( cellName, instanceName );
                        update_wire_connection_SA( cellName, instanceName );
                        update_HPWL();
                    }
//                    cout<<"end solu:"<<endl;

//                    cout<<"\tnow orientation:  "<<MacroMlistMap_SA[instanceName].orientation<<endl;
                }
            }
        }
//        cout<<"\tnow HPWL:  "<<Macro_Connect_WireMap[tmp.NetName].HPWL<<endl;
//        cout<<"totalWirelength_big: "<<totalWirelength_big<<endl;
//        cout<<"-----------------------------------------------------------------"<<endl;
    }
//    cout<<"\ttotalWirelength_big: "<<totalWirelength_big<<endl;
    cout<<"totalWirelength: "<<totalWirelength<<endl;
    for(auto i : MacroMlistMap_SA)  MacroMlistMap_SA[i.first].fixed=0;
//    cout<<"--------------------------------------------------finish detail flip"<<endl;
}

void detail_flip()
{
//    cout<<"---------------------------------------------------------------start detail flip"<<endl;
    create_maxheap();
    string instanceName="",cellName="";
    int HPWL_best=totalWirelength;
//    ofstream ofs("case09out_1.txt", ios::out);
    for(int i=0; i<thinglist.size(); i++)
    {

        Macro_Connect_WireStructV tmp;
        tmp = thinglist[i];

//        cout<<"netname: "<<tmp.NetName<<endl;

//        cout<<"\tori HPWL: "<<Macro_Connect_WireMap[tmp.NetName].HPWL<<endl;
//        cout<<"\tori totalWirelength_big: "<<totalWirelength<<endl;
        for(int j=0; j<tmp.weight_wireConnectNumVec.size(); j++)
        {

            string solu="",ori_orientation;

//            if(tmp.weight_wireConnectNumVec[j].bigMacro )
            {
                instanceName = tmp.weight_wireConnectNumVec[j].macro_instanceName;
                cellName = tmp.weight_wireConnectNumVec[j].macro_cellName;

//               cout<< MacroMlistMap[instanceName].InstanceName<<endl;
                if(MacroMlistMap[instanceName].fixed==0)
                {
                    ori_orientation = MacroMlistMap[instanceName].orientation;
//                    cout<<"\t\tori orientation:  "<<MacroMlistMap[instanceName].orientation<<endl;

//                    cout<<"start N:"<<endl;
                    MacroMlistMap[instanceName].orientation = "N" ;

                    update_pin_location( cellName, instanceName );
                    update_wire_connection( cellName, instanceName );
                    update_HPWL();

                    if(totalWirelength<HPWL_best)
                    {
                        HPWL_best = totalWirelength;
                        solu = "N";
                    }
//                    cout<<"end N:"<<endl;

//                    cout<<"start FN:"<<endl;
                    MacroMlistMap[instanceName].orientation = "FN" ;

                    update_pin_location( cellName, instanceName );
                    update_wire_connection( cellName, instanceName );
                    update_HPWL();

                    if(totalWirelength<HPWL_best )
                    {
                        HPWL_best = totalWirelength;
                        solu = "FN";
                    }
//                    cout<<"end FN:"<<endl;

//                    cout<<"start FS:"<<endl;
                    MacroMlistMap[instanceName].orientation = "FS" ;

                    update_pin_location( cellName, instanceName );
                    update_wire_connection( cellName, instanceName );
                    update_HPWL();

                    if(totalWirelength<HPWL_best)
                    {
                        HPWL_best = totalWirelength;
                        solu = "FS";
                    }
//                    cout<<"end FS:"<<endl;

//                    cout<<"start S:"<<endl;
                    MacroMlistMap[instanceName].orientation = "S" ;

                    update_pin_location( cellName, instanceName );
                    update_wire_connection( cellName, instanceName );
                    update_HPWL();

                    if(totalWirelength<HPWL_best )
                    {
                        HPWL_best = totalWirelength;
                        solu = "S";
                    }
//                    cout<<"end S:"<<endl;

//                    cout<<"start solu:"<<endl;
//                    cout<<"solu: "<<solu<<endl;
                    if(solu!="")
                    {
                        MacroMlistMap[instanceName].orientation = solu ;
                        MacroMlistMap[instanceName].fixed=1;
                        update_pin_location( cellName, instanceName );
                        update_wire_connection( cellName, instanceName );
                        update_HPWL();
                    }
                    else
                    {
                        MacroMlistMap[instanceName].orientation = ori_orientation ;
                        MacroMlistMap[instanceName].fixed=1;
                        update_pin_location( cellName, instanceName );
                        update_wire_connection( cellName, instanceName );
                        update_HPWL();
//                        ofs << instanceName << " " << cellName <<" "<< (int)MacroMlistMap[instanceName].xLoc<<" "<<(int)MacroMlistMap[instanceName].yLoc;
//                        ofs<<" "<<MacroLefMap[cellName].sizex<<" "<<MacroLefMap[cellName].sizey<<endl;
                    }
//                    cout<<"end solu:"<<endl;

//                    cout<<"\t\tnow orientation:  "<<MacroMlistMap[instanceName].orientation<<endl;
                }
            }
        }
//        cout<<"\tnow HPWL:  "<<Macro_Connect_WireMap[tmp.NetName].HPWL<<endl;
//        cout<<"\tmow totalWirelength_big: "<<totalWirelength<<endl;
//        cout<<"-----------------------------------------------------------------"<<endl;
    }
//    cout<<"\ttotalWirelength_big: "<<totalWirelength_big<<endl;
    cout<<"totalWirelength: "<<totalWirelength<<endl;
    for(auto i : MacroMlistMap)  MacroMlistMap[i.first].fixed=0;
//    cout<<"---------------------------------------------------------------finish detail flip"<<endl;
}
