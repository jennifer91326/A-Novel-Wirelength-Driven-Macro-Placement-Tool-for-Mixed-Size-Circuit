#include "parser3.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include "shift.h"
using namespace std;
string input_case;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////.def
int max_distance_constraint=0;

void parser_txt ()
{
    input_case = "case03";
    ifstream ifs("case03.txt", ios::in);
    if (!ifs)
        cout << "Failed to open file.\n";

    string s1, s2;  //tmp:
    ifs >> s1 >> s2;
    max_distance_constraint = stoi(s2);
    ifs.close();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////.def
float DieArea;
map<string,component> map_component;
map<string,pin> map_pin;
float x_die, y_die;

int string_to_int(string s)
{
    stringstream strm;
    strm << s;
    int num = stoi(strm.str());
    return num;
}
const std::string split(const std::string &str, const char &delimiter) {
    std::stringstream ss(str);
    std::string tok;
    std::getline(ss, tok, delimiter);
    std::getline(ss, tok, delimiter);
    return tok;
}
void parser_def ()
{
    input_case = "case03";
    ifstream ifs("case03.def", ios::in);
    if (!ifs)
    {
        cout << "Failed to open file.\n";
    }
    string s, name,type, tmp[25], in_or_out;  //tmp:
    component temp1;
    pin temp2;
    while(!ifs.eof())
    {
        getline(ifs, s);
        if(s.find("END PROPERTYDEFINITIONS") != string::npos)
        {
            ifs>>tmp[1]>>tmp[2]>>tmp[3]>>tmp[4]>>tmp[5]>>tmp[6]>>x_die>>y_die;
            DieArea = x_die*y_die;
//            cout<<"area: "<<x_die<<endl<<y_die<<endl<<DieArea<<endl;
            break;
        }

//
//        else if(s.find("COMPONENTS") != string::npos) //COMPONENTS 1209716 ;
//        {
//            string ret = split(s, ' ');
//            int num = string_to_int(ret);
//            for(int j=0;j<num;j++)
//            {
//                ifs>>tmp[0]>>temp1.name>>temp1.type>>tmp[1]>>tmp[2]>>tmp[3]>>temp1.x>>temp1.y>>tmp[6]>>temp1.dir>>tmp[8];
////                component temp1 = component(name, type, x, y);
//                map_component[temp1.name] = temp1;
////                cout<<name<<"   "<<type<<"   "<<x<<"   "<<y<<"   "<<endl;
//
//            }
//            break;
//            ifs>>tmp[0]>>tmp[1]>>tmp[2]>>num>>tmp[3];
//            for(int j=0;j<num;j++)
//            {
//                ifs>>tmp[0]>>temp2.name>>tmp[1]>>tmp[2]>>tmp[3]>>tmp[4]>>tmp[5]>>temp2.in_or_out>>tmp[6]>>tmp[7]>>tmp[8]>>temp2.x>>temp2.y>>tmp[9]>>temp2.dir;
//                ifs>>tmp[11]>>tmp[12]>>tmp[13]>>tmp[14]>>tmp[15]>>tmp[16]>>tmp[17]>>tmp[18]>>tmp[19]>>tmp[20]>>tmp[21]>>tmp[22];
////                temp2 = pin(name, in_or_out, x, y);
//                map_pin[temp2.name] = temp2;
////                cout<<name<<"   "<<in_or_out<<"   "<<x<<"   "<<y<<"   "<<endl;
//            }
//            break;
//        }
    }

//    for(int i=0;i<vec_standard_cell.size();i++)
//    {
//        map_component[vec_standard_cell[i].name]=i;
//    }
//    for(int i=0;i<vec_pin.size();i++)
//    {
//        map_pin[vec_pin[i].name]=i;
//    }
    // cout map
//    for (const auto& n :map_pin) {
//        cout << "key: " << n.first << " value: " << n.second << "\n";
//    }
    ifs.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////.v
map<string, MacroStructV> MacroWireMap;
void parser_v()
{
//    cout << "STRAT V \n";

    string fileLine; //檔案一行一行讀進來

    //fstream inVfile ("/Users/jeannie068/Documents/program/cases-0824/case03/lefdef/case03.v", ios::in);
    fstream inVfile ("case03.v", ios::in);
    if (!inVfile)
        cout << "Failed to open V file.\n";
    // 讀檔案
    do {
            getline(inVfile, fileLine);
            size_t block_found = fileLine.find("block");
            // Only save block's infromation
            if ( block_found != string::npos ) {
                MacroStructV newMacro;
                WireStructV blockWire;
                // Find macro's name
                string blockName = fileLine.substr(0, fileLine.find(" "));
                newMacro.CellName = blockName;

                       blockName = fileLine.substr(fileLine.find(" ")+1, fileLine.find("(")-fileLine.find(" ")-2);
                newMacro.InstanceName = blockName;
                fileLine.erase(0, fileLine.find(".")+1);

                // Find macro's input,output wire
                size_t comma_pos;
                    // Separate output wire's infromation and save into vector
                while ( (comma_pos = fileLine.find(", .o") ) != string::npos) {
                    blockWire.PinName = fileLine.substr(0, fileLine.find("("));
                    fileLine.erase(0, fileLine.find("(")+1);
                    blockWire.NetName = fileLine.substr(0, fileLine.find(")"));
                    newMacro.macro_OutWireMap[blockWire.NetName] = blockWire;
                    fileLine.erase(0, fileLine.find(".")+1);
                }
                blockWire.PinName = fileLine.substr(0, fileLine.find("("));
                fileLine.erase(0, fileLine.find("(")+1);
                blockWire.NetName = fileLine.substr(0, fileLine.find(")"));
                newMacro.macro_OutWireMap[blockWire.NetName] = blockWire;
                fileLine.erase(0, fileLine.find(".")+1);

                    // Separate input wire's infromation and save into vector
                while ( (comma_pos = fileLine.find(", .i") ) != string::npos) {
                    blockWire.PinName = fileLine.substr(0, fileLine.find("("));
                    fileLine.erase(0, fileLine.find("(")+1);

                    blockWire.NetName = fileLine.substr(0, fileLine.find(")"));
                    newMacro.macro_InWireMap[blockWire.NetName] = blockWire;;
                    fileLine.erase(0, fileLine.find(".")+1);
                }
                blockWire.PinName = fileLine.substr(0, fileLine.find("("));
                fileLine.erase(0, fileLine.find("(")+1);
                blockWire.NetName = fileLine.substr(0, fileLine.find(")"));
                newMacro.macro_InWireMap[blockWire.NetName] = blockWire;

                MacroWireMap[newMacro.InstanceName] = newMacro; // save this macro into Map

            }
            else cin.sync(); // 清空cin的緩衝區
        } while ( !inVfile.eof() ); // 遇到eof停止
        inVfile.close();

        //cout << "MacroWire[] size: " << MacroWire.size() << endl;
        /*
            for (const auto& n : MacroWireMap) {
                cout << "key(cell): " << n.first << " (instance): " << n.second.InstanceName << endl ;
                cout << "\tInWire size: " << n.second.macro_InWireMap.size() << "\n";
                for (const auto& k : n.second.macro_InWireMap) {
                    cout << "\t\t" << "pinName: " << k.second.PinName << " netName: " << k.second.NetName<< endl;
                }

                cout << "\tOutWire size: " << n.second.macro_OutWireMap.size() << "\n";
                for (const auto& k : n.second.macro_OutWireMap) {
                    cout << "\t\t" << "pinName: " << k.second.PinName << " netName: " << k.second.NetName<< endl;
                }
            }
         */

//        cout << "END V \n";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////.lef
site core;
//vector<layer> vec_layer;//vector<macro> vec_macro;
map<string,LayerLefStruct> LayerLefMap;//map_layer;
map<string,MacroLefStruct> MacroLefMap;//map_macro;
void parser_lef()
{
    ifstream ifs("case03.lef",ios::in);
    //fstream ifs ("/Users/jeannie068/Documents/program/cases-0824/case03/lefdef/case03.lef", ios::in);
    if(!ifs) cout << "Failed to open .lef" << endl;

    string s,nonsense,name,direction;
    string mclass,foreign,symx,symy,site,pinname,layername,endpin,endobs;
    float x,y,pitch,width;
    float foreignx,foreigny,sizex,sizey,rtemp;//,originx,originy
    while(!ifs.eof())//SITE
    {
        getline(ifs,s);
        if(s.find("SITE") != string::npos)//have found
        {
            ifs >> nonsense >> x >> nonsense >> y >> nonsense;
            core.x = x;
            core.y = y;
            break;
        }
    }

    while(!ifs.eof())//LAYER
    {
        getline(ifs,s);
        if(s[0] == 'M') break;//MACRO

        if(s.find("LAYER") != string::npos)
        {
            LayerLefStruct temp;
            temp.name = s.substr(6);//metal1

            getline(ifs,s);//TYPE ROUTING ;
            ifs >> nonsense >> direction >> nonsense;
            ifs >> nonsense >> pitch >> nonsense;
            ifs >> nonsense >> width >> nonsense;
            temp.direction = direction;
            temp.pitch = pitch;
            temp.width = width;
            getline(ifs,s);//END metal1
            LayerLefMap[temp.name] = temp;//vec_layer.push_back(temp);
        }
    }
    do//MACRO
    {
        if(s.find("MACRO") != string::npos)
        {
            MacroLefStruct mtemp;

            mtemp.name = s.substr(6);
            ifs >> nonsense >> nonsense >> nonsense;
            //ifs >> nonsense >> mclass >> nonsense;
            //mtemp.mclass = mclass;
            ifs >> nonsense >> foreign >> foreignx >> foreigny >> nonsense;
            mtemp.foreign = foreign;
            mtemp.foreignx = foreignx;
            mtemp.foreigny = foreigny;
            ifs >> nonsense >> nonsense >> nonsense >> nonsense;
            //ifs >> nonsense >> originx >> originy >> nonsense;
            //mtemp.originx = originx;//mtemp.originy = originy;
            ifs >> nonsense >> sizex >> nonsense >> sizey >> nonsense;
            mtemp.sizex = sizex;
            mtemp.sizey = sizey;
            mtemp.area = 2000*2000*sizex*sizey;

//            if(input_case=="case03" && (2000.0*2000.0*sizex*sizey) > (DieArea/650.0)) mtemp.bigMacro = 1;
//            else if(input_case=="case03" && (2000.0*2000.0*sizex*sizey) > (DieArea/1200.0)) mtemp.bigMacro = 1;
//            else mtemp.bigMacro = 0;
//            cout<<2000.0*2000.0*sizex*sizey<<endl<<DieArea<<endl;
//            cout<<mtemp.bigMacro<<"  ";
            ifs >> nonsense >> nonsense >> nonsense >> nonsense;
            //ifs >> nonsense >> symx >> symy >> nonsense;
            //mtemp.symx = symx;//mtemp.symy = symy;
            if(s.find("SITE") != string::npos)//mclass!="BLOCK")
                ifs >> nonsense >> site >> nonsense;
            else
                site = {};
            mtemp.site = site;
            do
            {
                getline(ifs,s);
                if(s.find("PIN") != string::npos) break;//PIN
                else if(s.find("OBS") != string::npos) break;
            }while(!ifs.eof());

            //pin
            do
            {
                if(s.find("OBS") != string::npos) break;
                PinLefStruct ptemp;
                s.erase(0, 1);
                ptemp.pinname = s.substr(4);
                ifs >> nonsense >> direction >> nonsense;
                ptemp.direction = direction;
                while(!ifs.eof())
                {
                    getline(ifs,s);
                    if(s.find("LAYER") != string::npos)
                    {
                        ptemp.layername = s.substr(6,6);
                        break;
                    }
                }
                while(1)
                {
                    ifs >> endpin;
                    if(endpin == "END") break;
                    ifs >> rtemp;//rect_x1
                    ptemp.rect_x1 = rtemp;
                    ifs >> rtemp;//rect_y1
                    ptemp.rect_y1 = rtemp;
                    ifs >> rtemp;//rect_x2
                    ptemp.rect_x2 = rtemp;
                    ifs >> rtemp >> nonsense;//rect_y2
                    ptemp.rect_y2 = rtemp;
                }
                mtemp.vec_pin.push_back(ptemp);
                ifs >> nonsense >> nonsense;//END pinname

                do
                {
                    getline(ifs,s);
                    if(s.find("PIN") != string::npos) break;//PIN
                    else if(s.find("END") != string::npos) break;//END macro name
                    else if(s.find("OBS") != string::npos) break;

                }while(!ifs.eof());

                if(s.find("END") != string::npos) break;
                if(s.find("OBS") != string::npos) break;
            }while(s.substr(4)!=name);

            //obs
            if(s == "OBS")
            {
                cout <<"in if obs"<<endl;
                while(1)
                {
                    ifs >> endobs;
                    if(endobs == "END") break;
                    /*ifs >> layername >> nonsense;
                    otemp.poname = layername;
                    ifs >> nonsense >> rtemp;//rect_x1
                    otemp.rect_x1 = rtemp;
                    ifs >> rtemp;//rect_y1
                    otemp.rect_y1 = rtemp;
                    ifs >> rtemp;//rect_x2
                    otemp.rect_x2 = rtemp;
                    ifs >> rtemp >> nonsense;//rect_y2
                    otemp.rect_y2 = rtemp;
                    mtemp.vec_po.push_back(otemp);*/
                }
            }
            MacroLefMap[mtemp.name] = mtemp;
        }
        getline(ifs,s);
    }while(!ifs.eof());
    ifs.close();

//    map<string, MacroLefStruct>::iterator it;
//    it = MacroLefMap.find("block_684x2925_380yf");
//       for (auto n : MacroLefMap) {
//           cout << "key: " << n.first << endl ;
//           cout<< "big: "<<n.second.bigMacro<<endl;
//           for (int i=0; i<n.second.vec_pin.size(); i++) {
//               cout << "\tPin_Name:" << n.second.vec_pin[i].pinname << endl;
//               cout << "\t\tPin_rectX1: " << n.second.vec_pin[i].rect_x1 << " Pin_rectX2: " << n.second.vec_pin[i].rect_x2 << " Pin_rectY1: " << n.second.vec_pin[i].rect_y1 << " Pin_rectY2: " << n.second.vec_pin[i].rect_y2 << endl;
//           }
//       }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////// .mlist
map<string, ComponentStructMlist> MacroMlistMap;
map<string, ComponentStructMlist> MacroMlistMap_SA;
int ComponentNum;

void parser_mlist(){
//        cout << "START MLIST \n";
        long long int UnitDistance;

        string fileLine; //檔案一行一行讀進來的儲存變數

        //fstream inMLISTfile ("/Users/jeannie068/Documents/program/cases-0824/case03/lefdef/case03.mlist", ios::in);
        fstream inMLISTfile ("case03.mlist", ios::in);
        // 讀檔案
            // 讀 UNITS DISTANCE MICRONS
        for (short int i=0; i<3; i++)
            getline(inMLISTfile, fileLine);
        size_t UD_found = fileLine.find("UNITS DISTANCE MICRONS");
        if (UD_found != string::npos) {
            string temp = "UNITS DISTANCE MICRONS ";
            string UD = fileLine.substr(temp.size(), fileLine.find(" ;")-temp.size());
            UnitDistance = stoll(UD);
        }

            // 讀 DIEAREA
        for (short int i=0; i<2; i++)
            getline(inMLISTfile, fileLine);
        fileLine.erase(0, fileLine.find(") (")+4); // 刪掉 "DIEAREA ( 0 0 ) ( "
        string DA_x = fileLine.substr( 0, fileLine.find(" ") ); // Die Area的x座標
        fileLine.erase(0, fileLine.find(" ")+1); // 刪掉切割好的x座標
        string DA_y = fileLine.substr( 0, fileLine.find(" ") ); // Die Area的y座標
//        DieArea = stoll(DA_x) * stoll(DA_y); // 計算 Die Area
            // 讀 COMPONENTS 數量
        for (short int i=0; i<2; i++)
            getline(inMLISTfile, fileLine);
        fileLine.erase(0, fileLine.find(" ")+1); // 刪掉"COMPONENTS "
        ComponentNum = stoll( fileLine.substr(0, fileLine.find(" ")) );

            //存block的資訊
        do {
            getline(inMLISTfile, fileLine);
            if (fileLine.find("END COMPONENTS") != string::npos) {
                break;
            }
            else {
                ComponentStructMlist newComponent;
                string str;
                    // 找macro的InstanceName
                fileLine.erase(0, fileLine.find("-")+2); // 刪掉 "   - "
                newComponent.InstanceName = fileLine.substr(0, fileLine.find(" "));
                    // 找macro的CellName
                fileLine.erase(0, fileLine.find(" ")+1); // 刪掉 InstanceName
                newComponent.CellName = fileLine.substr(0, fileLine.find(" "));

                    // 找macro的place設定
                getline(inMLISTfile, fileLine);
                fileLine.erase(0, fileLine.find("+")+2); // 刪掉 "      + "
                newComponent.placeSet = fileLine.substr(0, fileLine.find(" "));
                    // 找macro的x座標
                fileLine.erase(0, fileLine.find("(")+2); // 刪掉 place設定 + " ( "
                newComponent.xLoc = stoll( fileLine.substr(0, fileLine.find(" ")) );
                    // 找macro的y座標
                fileLine.erase(0, fileLine.find(" ")+1); // 刪掉 x座標
                newComponent.yLoc = stoll( fileLine.substr(0, fileLine.find(" ")) );
                    // 找macro的orientation
                fileLine.erase(0, fileLine.find(")")+2); // 刪掉 y座標 + ") "
                newComponent.orientation = fileLine.substr( 0, fileLine.find(" ") ) ;
                    // copy cell's pin_vector to newComponent
                newComponent.vec_pin.assign ( MacroLefMap[newComponent.CellName].vec_pin.begin(), MacroLefMap[newComponent.CellName].vec_pin.end()     );
                newComponent.fixed=0;
                MacroMlistMap[ newComponent.InstanceName ] = newComponent; // 把此component存進去Map
            }
        } while ( !inMLISTfile.eof() ); // 遇到eof停止

        inMLISTfile.close();
    /*
        cout << "UD: " << UnitDistance << endl;
        cout << "DA_x: " << DA_x << endl;
        cout << "DA_y: " << DA_y << endl;
        cout << "DA: " << DieArea << endl;
        cout << "ComponentNum: " << ComponentNum << endl;
     */

        // cout map資料



//        cout << "END MLIST \n"<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////update bigMacro

void update_bigMacro(float v)
{
    for(auto n:MacroLefMap)
    {

        if((2000.0*2000.0*n.second.sizex*n.second.sizey) > (DieArea/v)) MacroLefMap[n.first].bigMacro = 1;
//        if((MacroLefMap[n.first].area) > (DieArea/v)) MacroLefMap[n.first].bigMacro = 1;
        else MacroLefMap[n.first].bigMacro = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////// dmp output

void outputDMP()
{
//    ifstream ifs("case03.def", ios::in);
    ofstream ofs("case03.dmp", ios::out);

    map<string,ComponentStructMlist>::iterator it;
    ComponentStructMlist value;

    ofs << "VERSION 5.7 ;\nDESIGN case03 ;\nUNITS DISTANCE MICRONS 2000 ;\n";
    ofs << endl << "DIEAREA  ( 0 0 ) ( " << (int)x_die << " " << (int)y_die << " ) ;\n" << endl;
    ofs << "COMPONENTS " << ComponentNum << ";\n";
    for (const auto& it : MacroMlistMap)
    {
        value = it.second;
        ofs <<"- "<<value.InstanceName<<" "<<value.CellName<<endl;
        ofs <<"\t+ PLACED ( "<<(int)value.xLoc<<" "<<(int)value.yLoc<<" ) "<<value.orientation<<"\n";
    }
    ofs << "END COMPONENTS\n";
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////// txt output for matlab
void output_matlab()
{
    ofstream ofs("case03out_1.txt", ios::out);
    for (auto i : MacroMlistMap)
    {

//        if(i.second.quadrant==2 )
//        {
            map<string,MacroLefStruct>::iterator it;
            it = MacroLefMap.find(i.second.CellName); //enter"FE_OFC158074_n706156"
            if(it != MacroLefMap.end() )
            {
//                    if(it->second.sizex*it->second.sizey > 100000 && it->second.sizex*it->second.sizey >20000 && i.first == "A2_B2_C3_D1_E1_F1_o1045880" )//&& i.first == "A2_B2_C7_D1_E1_F1_o1045889" A2_B2_C3_D1_E1_F1_o1045880
                    {

                        ofs << i.first << " " <<i.second.CellName<<" "<< (int)i.second.xLoc<<" "<<(int)i.second.yLoc;
                        ofs<<" "<<it->second.sizex<<" "<<it->second.sizey<<endl;

                    }

            }
//        }
    }

//    ofs << "xy" << " " <<"boundary"<<" "<< (int)xboundary<<" "<<(int)yboundary;
//    ofs<<" "<<100<<" "<<100<<endl;


//    ofstream ofs1("case03out_2.txt", ios::out);
//    for (auto i : MacroMlistMap)
//    {
//
//        map<string,MacroLefStruct>::iterator it;
//        it = MacroLefMap.find(i.second.CellName); //enter"FE_OFC158074_n706156"
//        if(it != MacroLefMap.end() )
//        {
//            if(it->second.bigMacro)
//            {
////                cout<<i.first<<endl;
//                ofs1 << i.first << " " <<i.second.CellName<<" "<< (int)i.second.xLoc<<" "<<(int)i.second.yLoc;
//                ofs1<<" "<<it->second.sizex<<" "<<it->second.sizey<<" "<<it->second.bigMacro<<endl;
//            }
//        }
//    }


}
void output_matlab_pins()
{
    ofstream ofs("case03out_pin.txt", ios::out);
        for (auto n : MacroMlistMap)
        {
//            cout << "key: " << MacroMlistMap[n.first].InstanceName << endl ;
//            cout << "\tCellName: " << MacroMlistMap[n.first].CellName << "\n";
//            cout << "\tplaceSet: " << MacroMlistMap[n.first].placeSet << "\n";
//            cout << "\txLoc: " << MacroMlistMap[n.first].xLoc << "\n";
//            cout << "\tyLoc: " << MacroMlistMap[n.first].yLoc << "\n";
//            cout << "\torientation: " << MacroMlistMap[n.first].orientation << "\n";
            for(int j=0; j<MacroMlistMap[n.first].vec_pin.size(); j++){
//                cout << "\tpin name: " << MacroMlistMap[n.first].vec_pin[j].pinname << endl;
                ofs << (int)MacroMlistMap[n.first].xLoc + 2000*MacroMlistMap[n.first].vec_pin[j].rect_x1 << " ";
                ofs << (int)MacroMlistMap[n.first].yLoc + 2000*MacroMlistMap[n.first].vec_pin[j].rect_y1 << " ";
                ofs << 2000*(MacroMlistMap[n.first].vec_pin[j].rect_x2 - MacroMlistMap[n.first].vec_pin[j].rect_x1)<< " ";

                ofs << 2000*(MacroMlistMap[n.first].vec_pin[j].rect_y2 - MacroMlistMap[n.first].vec_pin[j].rect_y1)<< endl;
            }
        }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////// outputPL
void outputPL()
{
    ifstream ifs("case03.pl",ios::in);
    ofstream ofs("case03_.pl",ios::out);
    //fstream fs("case03-2.pl",ios::in | ios::out);
    string s,x,y,tempPlMacroName,tempMacroName,tempOrientation,fix,t;
    float X,Y;
    ComponentStructMlist tempComponent;

    map<string,ComponentStructMlist>::iterator itMacroMlist;

    getline(ifs,s);
    ofs << s << endl;
    getline(ifs,s);
    ofs << s << endl;
    getline(ifs,s);
    ofs << s << endl;

    while(!ifs.eof())
    {
        fix = "";

        getline(ifs,s);
        if(s=="") break;

        tempPlMacroName = s.substr(0,s.find(" "));
            s.erase(0,s.find(" ")+1);
        x = s.substr(0,s.find(" "));
            s.erase(0,s.find(" ")+1);
        y = s.substr(0,s.find(" "));
            s.erase(0,s.find(":")+2);
            //s.erase(0,s.find(" ")+1);
            //s.erase(0,s.find(" ")+1);
        tempOrientation = s.substr(0,s.find(" "));
            s.erase(0,s.find(" ")+1);

        itMacroMlist = MacroMlistMap.find(tempPlMacroName);//find macro from mlist
        if(itMacroMlist != MacroMlistMap.end())
        {
            tempOrientation = itMacroMlist->second.orientation;
            X = itMacroMlist->second.xLoc;
            Y = itMacroMlist->second.yLoc;
            ofs << tempPlMacroName <<" "<< (int)X <<" "<< (int)Y <<" : "<< tempOrientation <<" ";

        }

            //tempComponent = itMacroMlist->second;
        //tempOrientation = tempComponent.orientation;

        //ofs<< tempOrientation;
        else ofs << tempPlMacroName <<" "<< x <<" "<< y <<" : "<< tempOrientation <<" ";

        if(s=="/FIXED") ofs << s;
        ofs << endl;
        //ofs << tempPlMacroName <<" "<< x <<" "<< y <<" : "<< tempOrientation <<" "<< fix <<endl;
    }
    ifs.close();
    ofs.close();
}
