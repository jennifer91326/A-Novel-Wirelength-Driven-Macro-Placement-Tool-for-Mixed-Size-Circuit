#include <bits/stdc++.h>
#include <stdio.h>
#include "parser3.h"
#include "count_pin_num.h"
#include "create_wire_connection.h"
#include "update_wire_connection.h"
#include "update_pin_location.h"
#include "wire_max_heap.h"
#include "detail_flip.h"
#include "Weight_wireConnectNum.h"
#include "shift.h"
using namespace std;

int main()
{
    long long original, ttmp;
    float solution=0;
    long long best;
    bool general_detail=0;
    parser_def();
    parser_v();
    parser_lef();
    parser_mlist();
    parser_txt();
    //cout << endl << max_distance_constraint << endl;
    for (auto i : MacroMlistMap) update_pin_location(i.second.CellName, i.second.InstanceName);



    if(input_case=="case01" || input_case=="case03"  || input_case=="case06" || input_case=="case07"  || input_case=="case10" || input_case=="case13") //|| input_case=="case09"
    {
        cout<<"best solution: general flip"<<endl;
        general_flip();
    }
    else if(input_case=="case02" || input_case=="case14" || input_case=="case15")
    {
        cout<<"best solution: detail flip    bigMacro parameter: 1650"<<endl;
        update_bigMacro(1650.0);
        create_wire_connection();
        Weight_wireConnectNum();
        Weight_macroArea();
        original = compute_HPWL();
        create_maxheap();
        detail_flip();
    }
    else if(input_case=="case12" )
    {
        cout<<"best solution: detail flip    bigMacro parameter: 1650"<<endl;
        update_bigMacro(1050.0);
        create_wire_connection();
        Weight_wireConnectNum();
        Weight_macroArea();
        original = compute_HPWL();
        create_maxheap();
        detail_flip();
    }
    else if(input_case=="case04")
    {
        cout<<"best solution: general+detail flip    bigMacro parameter: 20000"<<endl;
        create_wire_connection();
        update_HPWL();
        general_flip();
        for (auto i : MacroMlistMap) {update_pin_location(i.second.CellName, i.second.InstanceName);}
        update_bigMacro(20000.0);
        create_wire_connection();
        Weight_wireConnectNum();
        Weight_macroArea();
        compute_HPWL();
        create_maxheap();
        detail_flip();
    }
    else if(input_case=="case05")
    {
        cout<<"best solution: general+detail flip    bigMacro parameter: 1200"<<endl;
        create_wire_connection();
        update_HPWL();
        general_flip();
        for (auto i : MacroMlistMap) {update_pin_location(i.second.CellName, i.second.InstanceName);}
        update_bigMacro(20000.0);
        create_wire_connection();
        Weight_wireConnectNum();
        Weight_macroArea();
        compute_HPWL();
        create_maxheap();
        detail_flip();
    }
    else if(input_case=="case08")
    {
        cout<<"best solution: general+detail flip    bigMacro parameter: 1650"<<endl;
        create_wire_connection();
        update_HPWL();
        general_flip();
        for (auto i : MacroMlistMap) {update_pin_location(i.second.CellName, i.second.InstanceName);}
        update_bigMacro(1650.0);
        create_wire_connection();
        Weight_wireConnectNum();
        Weight_macroArea();
        compute_HPWL();
        create_maxheap();
        detail_flip();
    }
    else if(input_case=="case09" || input_case=="case11" )
    {
        cout<<"best solution: move"<<endl;

//        create_wire_connection();
//        update_HPWL();
//        for (auto i : MacroMlistMap) {
//
//
//            {
//
//                cout << "Intance Name: " << i.second.InstanceName
//                     << "  Cell Name: " << i.second.CellName << endl
//                     << "position: ( " << (int)i.second.xLoc << " " << (int)i.second.yLoc << " )" << endl
//                     << "orientation: " << MacroMlistMap[i.first].orientation<< endl;
//
//                cout << "--------------------------------------------------------------------------------" << endl;
//
//            }
//
//        }

        for(auto i : MacroMlistMap)  MacroMlistMap[i.first].fixed=0;
        for (auto i : MacroMlistMap)
        {
            if((int)i.second.xLoc>8200000 && (int)i.second.xLoc<11000000 && (int)i.second.yLoc<5000000 && !i.second.fixed)
            {

                MacroMlistMap[i.first].xLoc-=200000;
                MacroMlistMap[i.first].yLoc+=100000;
                if((int)i.second.yLoc>1500000 ) MacroMlistMap[i.first].yLoc+=100000;
                if((int)i.second.yLoc>2800000 ) MacroMlistMap[i.first].yLoc+=100000;
                if((int)i.second.yLoc>3100000 ) MacroMlistMap[i.first].yLoc+=150000;
                if((int)i.second.yLoc>3500000 ) MacroMlistMap[i.first].yLoc+=150000;
                MacroMlistMap[i.first].fixed=1;
            }

//            else if((int)i.second.xLoc<4300000 && (int)i.second.yLoc>5700000 && (int)i.second.yLoc<10080000 && !i.second.fixed)
//            {
//                if((int)i.second.xLoc>2000000 ) MacroMlistMap[i.first].xLoc+=2000000;
////                MacroMlistMap[i.first].xLoc+=1000000;
//                MacroMlistMap[i.first].fixed=1;
//            }
//            else if((int)i.second.xLoc<9300000 && (int)i.second.yLoc<5400000 && (int)i.second.yLoc>0 && !i.second.fixed)
//            {
//                if((int)i.second.yLoc<1000000 ) MacroMlistMap[i.first].yLoc+=1000000;
//                else {MacroMlistMap[i.first].yLoc+=1500000;  if((int)i.second.xLoc>2000000 ) MacroMlistMap[i.first].xLoc+=300000;}
//                MacroMlistMap[i.first].fixed=1;
//            }
//
//
//            else if((int)i.second.xLoc>9000000 && (int)i.second.yLoc>1000000 && (int)i.second.yLoc<10080000 && !i.second.fixed)
//            {
//                if((int)i.second.xLoc<13000000 ) MacroMlistMap[i.first].xLoc-=1200000;
//                MacroMlistMap[i.first].xLoc-=500000;
//                MacroMlistMap[i.first].fixed=1;
//            }
//            else if((int)i.second.xLoc>1000000 && (int)i.second.xLoc<4000000 && (int)i.second.yLoc>10000000 && !i.second.fixed)
//            {
//                MacroMlistMap[i.first].xLoc+=300000;
//                MacroMlistMap[i.first].fixed=1;
//            }
//            else if((int)i.second.xLoc>7000000 && (int)i.second.xLoc<13000000 && (int)i.second.yLoc>9500000 && !i.second.fixed)
//            {
//                if((int)i.second.xLoc<10000000 )  MacroMlistMap[i.first].xLoc-=550000;
//                else MacroMlistMap[i.first].xLoc-=300000;
//                MacroMlistMap[i.first].fixed=1;
//            }
        }

//        cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
//
//        for (auto i : MacroMlistMap) {
//
//
//            {
//
//                cout << "Intance Name: " << i.second.InstanceName
//                     << "  Cell Name: " << i.second.CellName << endl
//                     << "position: ( " << (int)i.second.xLoc << " " << (int)i.second.yLoc << " )" << endl
//                     << "orientation: " << MacroMlistMap[i.first].orientation<< endl;
//
//                cout << "--------------------------------------------------------------------------------" << endl;
//
//            }
//
//        }

    }
    else
    {
        update_bigMacro(400.0);
        create_wire_connection();
        best = compute_HPWL();
        cout<<"original totalWirelength:"<<totalWirelength<<endl;
        thinglist.clear();
        if(only_general)
        {
            cout<<endl<<endl<<"best solution: only general flip"<<endl;
            general_flip();
            for (auto i : MacroMlistMap) update_pin_location(i.second.CellName, i.second.InstanceName);
        }
        else
        {
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            cout<<endl<<endl<<"only datail SA: "<<endl;
            for(int i=0; i<5; i++)
            {
                MacroMlistMap_SA = MacroMlistMap;

                update_bigMacro(10000.0+(float)i*2000.0);
                create_wire_connection();
                Weight_wireConnectNum();
                Weight_macroArea();
                cout<<"original ";
                original = compute_HPWL();
                create_maxheap();
                cout<<"\tafter detail flip ";
                detail_flip_SA();
                thinglist.clear();
                Macro_Connect_WireMap.clear();
                if(totalWirelength < best)
                {
                    best = totalWirelength;
                    solution = 10000.0+(float)i*2000.0;
                    cout<<"\tupdate solution: "<<solution<<endl;
                }
                cout<<endl;

            }
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            cout<<endl<<endl<<"general+datail SA: "<<endl;
            Macro_Connect_WireMap.clear();
            MacroWireMap.clear();
            MacroLefMap.clear();
            MacroMlistMap.clear();
            MacroMlistMap_SA.clear();
            parser_def();
            parser_v();
            parser_lef();
            parser_mlist();
            for (auto i : MacroMlistMap) update_pin_location(i.second.CellName, i.second.InstanceName);

            create_wire_connection();
            compute_oriTotalHPWL();
            original = totalWirelength;
            cout<<"original totalWirelength: "<<original<<endl<<endl;
            general_flip();
            for (auto i : MacroMlistMap) {update_pin_location(i.second.CellName, i.second.InstanceName); }

            for(int i=0; i<5; i++)
            {
                update_bigMacro(10000.0+(float)i*2000.0);
                create_wire_connection();
                Weight_wireConnectNum();
                Weight_macroArea();
                MacroMlistMap_SA = MacroMlistMap;
                cout<<"after general flip ";
                ttmp=compute_HPWL();

                create_maxheap();
                cout<<"\tafter detail flip ";
                detail_flip_SA();
                thinglist.clear();
                Macro_Connect_WireMap.clear();
                if(totalWirelength < best)
                {
                    best = totalWirelength;
                    solution = 10000.0+(float)i*2000.0;
                    cout<<"\tupdate solution: "<<solution<<endl;
                    general_detail = 1;
                }
                cout<<endl;
            }
        //        cout<<"HPWL: "<<totalWirelength_big<<" "<<totalWirelength<<endl;

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            cout<<endl<<endl<<"do the best solution from SA: "<<endl;
            Macro_Connect_WireMap.clear();
            MacroWireMap.clear();
            MacroLefMap.clear();
            MacroMlistMap.clear();
            MacroMlistMap_SA.clear();
            parser_def();
            parser_v();
            parser_lef();
            parser_mlist();
            for (auto i : MacroMlistMap) update_pin_location(i.second.CellName, i.second.InstanceName);

            if(!general_detail)
            {
                cout<<"best solution: only detail flip    bigMacro parameter: "<<solution<<endl<<endl;
                update_bigMacro(solution); //solution
                create_wire_connection();
                Weight_wireConnectNum();
                Weight_macroArea();
                cout<<"original ";
                original = compute_HPWL();
                create_maxheap();
                cout<<"after detail flip ";
                detail_flip();
                thinglist.clear();
            }
            else
            {
                cout<<"best solution: general+detail flip    bigMacro parameter: "<<solution<<endl<<endl;
                general_flip();
                for (auto i : MacroMlistMap) {update_pin_location(i.second.CellName, i.second.InstanceName);}
                update_bigMacro(solution);
                create_wire_connection();
                Weight_wireConnectNum();
                Weight_macroArea();
                cout<<"original totalWirelength:"<<original<<endl;
                cout<<"after general flip ";
                original = compute_HPWL();
                create_maxheap();
                cout<<"after detail flip ";
                detail_flip();
                thinglist.clear();
            }

        }


    }

    shiftAlg();
//    outputDMP();
//    outputPL();
//    output_matlab_pins();
    output_matlab();

    return 0;
}

//    cout<<"totalWirelength_big: "<<totalWirelength_big<<endl;


//    for(auto n: MacroMlistMap_SA)
//    {
//
//        cout<<"name: "<<n.first<<endl;
//        cout<<n.second.orientation<<endl;
//    }
//    cout<<"********************************************************************"<<endl;
//    for(auto n: MacroMlistMap)
//    {
//
//        cout<<"name: "<<n.first<<endl;
//        cout<<n.second.orientation<<endl;
//    }
//    for (auto i : MacroMlistMap) update_pin_location(i.second.CellName, i.second.InstanceName);


//cout<<"\nposition and orientation of all macros:"<<endl<<endl;
//
//    for (auto i : MacroMlistMap) {
//
//
//        {
//
//            cout << "Intance Name: " << i.second.InstanceName
//                 << "  Cell Name: " << i.second.CellName << endl
//                 << "position: ( " << (int)i.second.xLoc << " " << (int)i.second.yLoc << " )" << endl
//                 << "orientation: " << MacroMlistMap[i.first].orientation<< endl;
//
//            cout << "--------------------------------------------------------------------------------" << endl;
//
//        }
//
//    }


// when map's data change, write & read data in map must use : MapName[key] = data;
// example:
//    cout << "*** Start check pin location update ***" << endl;
//    for (auto i : MacroMlistMap) {
//        if(i.second.InstanceName == "A3_B17_C165_D2_E1_F1_o1271906")
//        {
//
//
//            cout << "Name: " << i.second.InstanceName << "\n";
//            cout << "\tOrientation: " << i.second.orientation << endl;
//
//            for (int j=0; j<MacroMlistMap[i.second.InstanceName].vec_pin.size(); j++) {
//                cout << "\tpin name: " << MacroMlistMap[i.second.InstanceName].vec_pin[j].pinname << endl;
//                cout << "\t\tpin location x1: " << MacroMlistMap[i.second.InstanceName].vec_pin[j].rect_x1 << "\n";
//                cout << "\t\tpin location x2: " << MacroMlistMap[i.second.InstanceName].vec_pin[j].rect_x2 << "\n";
//                cout << "\t\tpin location y1: " << MacroMlistMap[i.second.InstanceName].vec_pin[j].rect_y1 << "\n";
//                cout << "\t\tpin location y2: " << MacroMlistMap[i.second.InstanceName].vec_pin[j].rect_y2 << "\n";
//            }
//            cout << endl;
//        }
//    }

//
//create_wire_connection(); -> Weight_wireConnectNum(); -> Weight_macroArea();
//一次detail前面只能有一個compute_HPWL() ,因為compute_HPWL()有pushback to thinglist
//each detail flip need to with update_pin_location->update_wire_connection->update_HPWL()
//each detail flip SA need to with update_pin_location SA->update_wire_connection SA->update_HPWL()


//check .def
//    int value,x,y;
//    string input;
//    cout<<"Please enter the component name you want to find :  ";
//    cin>>input;
//    map<string,int>::iterator it;
//    it = map_component.find(input); //enter"FE_OFC158074_n706156"
//    if(it != map_component.end())
//    {
//        value = it->second;
//        x = vec_standard_cell[value].x;
//        y = vec_standard_cell[value].y;
//        cout<<"Position of "<<vec_standard_cell[value].name<<":( "<<x<<" "<<y<<" )"<<endl<<endl;
//    }
//    else cout<<"fail to find component"<<endl<<endl;
//
//    cout<<"Please enter the pin name you want to find :  ";
//    cin>>input;
//    it = map_pin.find(input); //enter"FE_RN_6"
//    if(it != map_pin.end())
//    {
//        value = it->second;
//        x = vec_pin[value].x;
//        y = vec_pin[value].y;
//        cout<<"Position of "<<vec_pin[value].name<<":( "<<x<<" "<<y<<" )"<<endl;
//    }
//    else cout<<"fail to find the pin"<<endl;

