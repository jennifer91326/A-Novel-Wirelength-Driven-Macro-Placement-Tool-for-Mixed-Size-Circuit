#include "parser3.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include "wire_max_heap.h"
#include "create_wire_connection.h"
#include "update_wire_connection.h"
using namespace std;
bool only_general;
long long totalWirelength;
long long totalWirelength_big;
int bigwire_num;
long long compute_HPWL()
{
//    cout<<"-------------------------------start compute_HPWL"<<endl;
    totalWirelength_big=0;
    totalWirelength=0;
    int a=0;
    for (auto n : Macro_Connect_WireMap) {
        int bigSum=0;
        vector<int> vec_x;
        vector<int> vec_y;
        for (int i=0; i<n.second.macro_connectVec.size(); i++) {

            if(n.second.macro_connectVec[i].bigMacro) bigSum++;

            vec_x.push_back((int)(n.second.macro_connectVec[i].rect_x1));
            vec_y.push_back((int)(n.second.macro_connectVec[i].rect_y1));
        }

        sort(vec_x.rbegin(), vec_x.rend());// max:vec_x[0]
        sort(vec_y.rbegin(), vec_y.rend());
        Macro_Connect_WireMap[n.first].HPWL = (vec_x[0]-vec_x.back()+vec_y[0]-vec_y.back());
        totalWirelength+=(long long)Macro_Connect_WireMap[n.first].HPWL;
        if(bigSum>0)
        {
            totalWirelength_big+=Macro_Connect_WireMap[n.first].HPWL;
            thinglist.push_back(Macro_Connect_WireMap[n.first]);
            a++;
        }
//        cout<<bigSum<<" ";

    }

    if(a<1)  only_general=1;
    else  only_general=0;
    bigwire_num = thinglist.size();
//    cout<<endl<<bigwire_num<<endl;

//    insert_max_heap();


//check
//    cout<<bigwire_num<<endl;
//    Macro_Connect_WireStructV item;
//    for (int i = 1 ; i <= bigwire_num; i++ )
//    {
//        if(thinglist[i-1].NetName == "n1084086")
//        cout << "NetName: " << thinglist[i-1].NetName << "\tHPWL: " << thinglist[i-1].HPWL << endl;

//        cout<<i<<endl;
//        item = delete_max_heap();
//        cout <<"NetName: "<< item.NetName<<endl<<"\tHPWL: "<<item.HPWL << endl;
//    }

//    cout<<"totalWirelength_big:"<<totalWirelength_big<<endl;
//    cout<<"totalWirelength:"<<totalWirelength<<endl;
//    cout<<"-------------------------------End compute_HPWL"<<endl;
    return totalWirelength;
}


bool compare(Macro_Connect_WireStructV s1, Macro_Connect_WireStructV s2)
{
   return s1.HPWL > s2.HPWL;
}

vector <Macro_Connect_WireStructV> thinglist;
Macro_Connect_WireStructV heap[500];

void create_maxheap()
{
    sort(thinglist.begin(), thinglist.end(), compare);
}
void insert_max_heap()
{
    int j;
    for (int i = 0 ; i < bigwire_num ; i++ )
    {
        j = i+1;
        while( (j != 1) && (thinglist[i].HPWL > heap[j/2].HPWL) )
        {
            heap[j] = heap[j/2];
            j /= 2;
        }
        heap[j] = thinglist[i];
    }
}

Macro_Connect_WireStructV delete_max_heap()
{
    Macro_Connect_WireStructV item, temp;
    int parent, child;
    item = heap[1]; //store the deleted element
    temp = heap[bigwire_num];
    parent = 1;
    child = 2;
    do
    {
        if ( child < bigwire_num && heap[child].HPWL < heap[child+1].HPWL )
            child++;
        if ( temp.HPWL >= heap[child].HPWL )
            break;

        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }while ( child <= bigwire_num);

    heap[parent] = temp;
    return item;
}

void update_HPWL()
{
//    cout<<"-------------------------------------------------------------------------------------start update_HPWL"<<endl;
    totalWirelength=0;
    totalWirelength_big=0;
    for (auto n : Macro_Connect_WireMap) {
        int bigSum=0;
        vector<int> vec_x;
        vector<int> vec_y;
        for (int i=0; i<n.second.macro_connectVec.size(); i++) {//

            if(n.second.macro_connectVec[i].bigMacro) bigSum++;

            vec_x.push_back((int)(n.second.macro_connectVec[i].rect_x1));
            vec_y.push_back((int)(n.second.macro_connectVec[i].rect_y1));

        }

        sort(vec_x.rbegin(), vec_x.rend());// max:vec_x[0]
        sort(vec_y.rbegin(), vec_y.rend());
        Macro_Connect_WireMap[n.first].HPWL = (vec_x[0]-vec_x.back()+vec_y[0]-vec_y.back());
        totalWirelength+=(long long)Macro_Connect_WireMap[n.first].HPWL;
        if(bigSum>0)
        {
            totalWirelength_big+=Macro_Connect_WireMap[n.first].HPWL;
        }
        else
        {
            Macro_Connect_WireMap[n.first].HPWL = 0;
        }
    }
    bigwire_num = thinglist.size();
//    cout<<"totalWirelength:"<<totalWirelength<<endl;
//    cout<<"totalWirelength_big:"<<totalWirelength_big<<endl;
//    cout<<"-------------------------------------------------------------------------------------End update_HPWL"<<endl;
}

void compute_oriTotalHPWL()
{
    totalWirelength=0;
    for (auto n : Macro_Connect_WireMap)
    {
        vector<int> vec_x;
        vector<int> vec_y;
        for (int i=0; i<n.second.macro_connectVec.size(); i++)
        {
            vec_x.push_back((int)(n.second.macro_connectVec[i].rect_x1));
            vec_y.push_back((int)(n.second.macro_connectVec[i].rect_y1));
        }

        sort(vec_x.rbegin(), vec_x.rend());// max:vec_x[0]
        sort(vec_y.rbegin(), vec_y.rend());
        Macro_Connect_WireMap[n.first].HPWL = (vec_x[0]-vec_x.back()+vec_y[0]-vec_y.back());
        totalWirelength+=(long long)Macro_Connect_WireMap[n.first].HPWL;
    }
}
