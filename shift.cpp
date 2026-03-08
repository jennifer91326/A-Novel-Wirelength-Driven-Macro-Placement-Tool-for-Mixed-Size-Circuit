#include "parser3.h"
#include <bits/stdc++.h>
#include <cmath>
#include <stdio.h>
#include "shift.h"
using namespace std;

vector<shiftstruct> firstQBST;
vector<shiftstruct> secondQBST;
vector<shiftstruct> thirdQBST;
vector<shiftstruct> fourthQBST;
vector<shiftstruct> minHeap;

bool lessSort(shiftstruct a,shiftstruct b)
{
    return a.index<b.index;
}
void divideQuadrant()
{
    float distanceTCX,distanceTCY;
    shiftstruct newstruct;
    MacroLefStruct tempmacro;
    float die_centerx,die_centery;
    die_centerx = x_die/2; die_centery = y_die/2;
    //int num = 0;//demo

    for(auto ttt:MacroMlistMap)
    {
        tempmacro = MacroLefMap[ttt.second.CellName];//xcoor = ttt.second.xLoc; ycoor = ttt.second.yLoc;

        newstruct.CellName = ttt.second.CellName;
        newstruct.InstanceName = ttt.second.InstanceName;
        newstruct.xLoc = ttt.second.xLoc;
        newstruct.yLoc = ttt.second.yLoc;

        distanceTCX = fabs(ttt.second.xLoc-die_centerx);
        distanceTCY = fabs(ttt.second.yLoc-die_centery);
        ttt.second.distanceToCenter = sqrt(distanceTCX*distanceTCX + distanceTCY*distanceTCY);
        newstruct.index = sqrt(distanceTCX*distanceTCX + distanceTCY*distanceTCY);//++num;

        //min heap
        minHeap.push_back(newstruct);

        //BST
        if(ttt.second.xLoc+tempmacro.sizex*1000 >= (x_die/2))//1,4 Q
        {
            if(ttt.second.yLoc+tempmacro.sizey*1000 >= (y_die/2))//1Q
            {
                firstQBST.push_back(newstruct);
                MacroMlistMap[newstruct.InstanceName].quadrant = 1;
                MacroMlistMap[newstruct.InstanceName].shiftBoundaryX = newstruct.xLoc;
                MacroMlistMap[newstruct.InstanceName].shiftBoundaryY = newstruct.yLoc;
            }
            else if(ttt.second.yLoc+tempmacro.sizey*1000 <= (y_die/2))//4Q
            {
                fourthQBST.push_back(newstruct);
                MacroMlistMap[newstruct.InstanceName].quadrant = 4;
                MacroMlistMap[newstruct.InstanceName].shiftBoundaryX = newstruct.xLoc;
                MacroMlistMap[newstruct.InstanceName].shiftBoundaryY = newstruct.yLoc + MacroLefMap[newstruct.CellName].sizey*2000;
            }
        }
        else if(ttt.second.xLoc+tempmacro.sizex*1000 <= (x_die/2))//2,3 Q
        {
            if(ttt.second.yLoc+tempmacro.sizey*1000 >= (y_die/2))//2Q
            {
                secondQBST.push_back(newstruct);
                MacroMlistMap[newstruct.InstanceName].quadrant = 2;
                MacroMlistMap[newstruct.InstanceName].shiftBoundaryX = newstruct.xLoc + MacroLefMap[newstruct.CellName].sizex*2000;
                MacroMlistMap[newstruct.InstanceName].shiftBoundaryY = newstruct.yLoc;
            }
            else if(ttt.second.yLoc+tempmacro.sizey*1000 <= (y_die/2))//3Q
            {
                thirdQBST.push_back(newstruct);
                MacroMlistMap[newstruct.InstanceName].quadrant = 3;
                MacroMlistMap[newstruct.InstanceName].shiftBoundaryX = newstruct.xLoc + MacroLefMap[newstruct.CellName].sizex*2000;
                MacroMlistMap[newstruct.InstanceName].shiftBoundaryY = newstruct.yLoc + MacroLefMap[newstruct.CellName].sizey*2000;

            }
        }
    }
    sort(minHeap.begin(), minHeap.end(), lessSort);
    sort(firstQBST.begin(), firstQBST.end(), lessSort);
    sort(secondQBST.begin(), secondQBST.end(), lessSort);
    sort(thirdQBST.begin(), thirdQBST.end(), lessSort);
    sort(fourthQBST.begin(), fourthQBST.end(), lessSort);
/*
    cout<< "Q1: "<<firstQBST.size()<<endl;
    for(int i=0;i<firstQBST.size();i++)
        cout <<i<<" "<<firstQBST[i].InstanceName<<"// "<<firstQBST[i].index<<endl;
    cout<<endl<< "Q2: "<<secondQBST.size()<<endl;
    for(int i=0;i<secondQBST.size();i++)
        cout <<i<<" "<<secondQBST[i].InstanceName<<" // "<<secondQBST[i].index<<endl;
    cout<<endl<< "Q3: "<<thirdQBST.size()<<endl;
    //for(int i=0;i<thirdQBST.size();i++)
        //cout <<i<<" "<<thirdQBST[i].InstanceName<<endl;
    cout<<endl<< "Q4: "<<fourthQBST.size()<<endl;
    //for(int i=0;i<fourthQBST.size();i++)
        //cout <<i<<" "<<fourthQBST[i].InstanceName<<endl;
    cout<<endl<<endl<< "MH: "<<minHeap.size()<<endl;
    //for(int i=0;i<minHeap.size();i++)
        //cout <<i<<" "<<minHeap[i].index<<endl;
 */
}

void findInfluencer(string instanceName,string cellName)
{
    shiftstruct influStruct;
    MacroLefStruct lefmacro,otherMacro;
    float boundaryCoorX,boundaryCoorY,otherBoundX,otherBoundY;
    float die_centerx,die_centery;
    die_centerx = x_die/2; die_centery = y_die/2;//DieArea = x_die*y_die;
    MacroMlistMap[instanceName].influencerVec.clear();
    lefmacro = MacroLefMap[cellName];//xcoor = ttt.second.xLoc; ycoor = ttt.second.yLoc;

        switch(MacroMlistMap[instanceName].quadrant)
        {
            case 1:
            {
                //int kk=0;
                //cout <<"name: "<<MacroMlistMap[instanceName].InstanceName<<endl;
                boundaryCoorX = MacroMlistMap[instanceName].xLoc + lefmacro.sizex*2000;
                boundaryCoorY = MacroMlistMap[instanceName].yLoc + lefmacro.sizey*2000;
                for(int i=0; i<minHeap.size(); i++)
                {
                    otherMacro = MacroLefMap[minHeap[i].CellName];
                    if(instanceName!=minHeap[i].InstanceName) {
                        otherBoundX = MacroMlistMap[minHeap[i].InstanceName].xLoc;
                        otherBoundY = MacroMlistMap[minHeap[i].InstanceName].yLoc;

                        if(otherBoundX<boundaryCoorX && otherBoundY<boundaryCoorY)
                        {
                            influStruct.InstanceName = minHeap[i].InstanceName;
                            influStruct.CellName = minHeap[i].CellName;
                            influStruct.index = MacroMlistMap[minHeap[i].InstanceName].xLoc;
                            influStruct.xLoc = MacroMlistMap[minHeap[i].InstanceName].xLoc;
                            influStruct.yLoc = MacroMlistMap[minHeap[i].InstanceName].yLoc;
                            MacroMlistMap[instanceName].influencerVec.push_back(influStruct);
                            //cout <<++kk<<"* "<<firstQBST[i].index<<endl;
                        }
                    }
                }
                sort(MacroMlistMap[instanceName].influencerVec.begin(), MacroMlistMap[instanceName].influencerVec.end(), lessSort);
                break;
            }
            case 2:
            {
                //int kk=0;
                //cout <<"name: "<<MacroMlistMap[instanceName].InstanceName<<endl;
                boundaryCoorX = MacroMlistMap[instanceName].xLoc;
                boundaryCoorY = MacroMlistMap[instanceName].yLoc + lefmacro.sizey*2000;
                for(int i=0; i<minHeap.size(); i++)
                {
                    otherMacro = MacroLefMap[minHeap[i].CellName];
                    if(instanceName!=minHeap[i].InstanceName) {
                        otherBoundX = MacroMlistMap[minHeap[i].InstanceName].xLoc + otherMacro.sizex*2000;
                        otherBoundY = MacroMlistMap[minHeap[i].InstanceName].yLoc;

                        if(otherBoundX>boundaryCoorX && otherBoundY<boundaryCoorY)
                        {
                            influStruct.InstanceName = minHeap[i].InstanceName;
                            influStruct.CellName = minHeap[i].CellName;
                            influStruct.index = MacroMlistMap[minHeap[i].InstanceName].xLoc;
                            influStruct.xLoc = MacroMlistMap[minHeap[i].InstanceName].xLoc;
                            influStruct.yLoc = MacroMlistMap[minHeap[i].InstanceName].yLoc;
                            MacroMlistMap[instanceName].influencerVec.push_back(influStruct);
                            //cout <<++kk<<"* "<<firstQBST[i].index<<endl;
                        }
                    }
                }
                sort(MacroMlistMap[instanceName].influencerVec.begin(), MacroMlistMap[instanceName].influencerVec.end(), lessSort);
                break;
            }
            case 3:
            {
                //int kk=0;
                //cout <<"name: "<<MacroMlistMap[instanceName].InstanceName<<endl;
                boundaryCoorX = MacroMlistMap[instanceName].xLoc;
                boundaryCoorY = MacroMlistMap[instanceName].yLoc;
                for(int i=0; i<minHeap.size(); i++)
                {
                    otherMacro = MacroLefMap[minHeap[i].CellName];
                    if(instanceName!=minHeap[i].InstanceName) {
                        otherBoundX = MacroMlistMap[minHeap[i].InstanceName].xLoc + otherMacro.sizex*2000;
                        otherBoundY = MacroMlistMap[minHeap[i].InstanceName].yLoc + otherMacro.sizey*2000;

                        if(otherBoundX>boundaryCoorX && otherBoundY>boundaryCoorY)
                        {
                            influStruct.InstanceName = minHeap[i].InstanceName;
                            influStruct.CellName = minHeap[i].CellName;
                            influStruct.index = MacroMlistMap[minHeap[i].InstanceName].xLoc;
                            influStruct.xLoc = MacroMlistMap[minHeap[i].InstanceName].xLoc;
                            influStruct.yLoc = MacroMlistMap[minHeap[i].InstanceName].yLoc;
                            MacroMlistMap[instanceName].influencerVec.push_back(influStruct);
                            //cout <<++kk<<"* "<<firstQBST[i].index<<endl;
                        }
                    }
                }
                sort(MacroMlistMap[instanceName].influencerVec.begin(), MacroMlistMap[instanceName].influencerVec.end(), lessSort);
                break;
            }
            case 4:
            {
                //int kk=0;
                //cout <<"name: "<<MacroMlistMap[instanceName].InstanceName<<endl;
                boundaryCoorX = MacroMlistMap[instanceName].xLoc + lefmacro.sizex*2000;
                boundaryCoorY = MacroMlistMap[instanceName].yLoc;
                for(int i=0; i<minHeap.size(); i++)
                {
                    otherMacro = MacroLefMap[minHeap[i].CellName];
                    if(instanceName!=minHeap[i].InstanceName) {
                        otherBoundX = MacroMlistMap[minHeap[i].InstanceName].xLoc;
                        otherBoundY = MacroMlistMap[minHeap[i].InstanceName].yLoc + otherMacro.sizey*2000;

                        if(otherBoundX<boundaryCoorX && otherBoundY>boundaryCoorY)
                        {
                            influStruct.InstanceName = minHeap[i].InstanceName;
                            influStruct.CellName = minHeap[i].CellName;
                            influStruct.index = MacroMlistMap[minHeap[i].InstanceName].xLoc;
                            influStruct.xLoc = MacroMlistMap[minHeap[i].InstanceName].xLoc;
                            influStruct.yLoc = MacroMlistMap[minHeap[i].InstanceName].yLoc;
                            MacroMlistMap[instanceName].influencerVec.push_back(influStruct);
                            //cout <<++kk<<"* "<<firstQBST[i].index<<endl;
                        }
                    }
                }
                sort(MacroMlistMap[instanceName].influencerVec.begin(),       MacroMlistMap[instanceName].influencerVec.end(), lessSort);
                break;
            }
            default:
                break;
        }

}

//for debug
//float xboundary;
//float yboundary;
vector<float> xBoundary;
vector<float> yBoundary;

void FindShiftingRange(string instanceName, string cellName, int quadrant)
{
    findInfluencer(instanceName,cellName);
    for (int j=0; j<MacroMlistMap[instanceName].influencerVec.size(); j++) {
        shiftstruct influencerTemp = MacroMlistMap[instanceName].influencerVec[j];

        switch ( quadrant ) {
            case 1:
            {
                float influencerBoundaryX = MacroMlistMap[influencerTemp.InstanceName].xLoc + MacroLefMap[influencerTemp.CellName].sizex*2000;
                float influencerBoundaryY = MacroMlistMap[influencerTemp.InstanceName].yLoc + MacroLefMap[influencerTemp.CellName].sizey*2000;
                // find shifting range
                if (influencerBoundaryX <= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY >= MacroMlistMap[instanceName].shiftBoundaryY) {
                    if(fabs(influencerBoundaryX-MacroMlistMap[instanceName].shiftBoundaryX)+
                       fabs(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY)<1500*2000.0)
                    xBoundary.push_back(influencerBoundaryX);
                }

                else if
                   (influencerBoundaryX <= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY <= MacroMlistMap[instanceName].shiftBoundaryY) {
                    if(MacroMlistMap[instanceName].shiftBoundaryY-influencerBoundaryY<1000*2000.0)
                        xBoundary.push_back(influencerBoundaryX);
                    if(MacroMlistMap[instanceName].shiftBoundaryX-influencerBoundaryX<1000*2000.0)
                        yBoundary.push_back(influencerBoundaryY);
                    }

                else if
                   (influencerBoundaryX >= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY <= MacroMlistMap[instanceName].shiftBoundaryY) {
                    if(fabs(influencerBoundaryX-MacroMlistMap[instanceName].shiftBoundaryX)+
                       fabs(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY)<1500*2000.0)
                    yBoundary.push_back(influencerBoundaryY);
                }
                break;
            }
           
            case 2:
            {
                float influencerBoundaryX = influencerTemp.xLoc;
                float influencerBoundaryY = influencerTemp.yLoc + MacroLefMap[influencerTemp.CellName].sizey*2000;
                // find shifting range
                if (influencerBoundaryX >= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY >= MacroMlistMap[instanceName].shiftBoundaryY) {
                    if(fabs(influencerBoundaryX-MacroMlistMap[instanceName].shiftBoundaryX)+
                       fabs(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY)<2000*2000.0)
                        xBoundary.push_back(influencerBoundaryX);
                }
                else if
                   (influencerBoundaryX >= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY <= MacroMlistMap[instanceName].shiftBoundaryY) {
                       if(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY<1000*2000.0)
                           xBoundary.push_back(influencerBoundaryX);
                       if(influencerBoundaryX-MacroMlistMap[instanceName].shiftBoundaryX<1000*2000.0)
                           yBoundary.push_back(influencerBoundaryY);
                }
                else if
                   (influencerBoundaryX <= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY <= MacroMlistMap[instanceName].shiftBoundaryY) {
                       if(fabs(influencerBoundaryX-MacroMlistMap[instanceName].shiftBoundaryX)+
                          fabs(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY)<2000*2000.0)
                           yBoundary.push_back(influencerBoundaryY);
                }
                break;
            }
                
            case 3:
            {
                float influencerBoundaryX = MacroMlistMap[influencerTemp.InstanceName].xLoc;
                float influencerBoundaryY = MacroMlistMap[influencerTemp.InstanceName].yLoc;
                // find shifting range
                if (influencerBoundaryX >= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY <= MacroMlistMap[instanceName].shiftBoundaryY) {
                    if(fabs(influencerBoundaryX-MacroMlistMap[instanceName].shiftBoundaryX)+
                       fabs(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY)<2000*2000.0)
                    xBoundary.push_back(influencerBoundaryX);
                }

                else if
                   (influencerBoundaryX >= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY >= MacroMlistMap[instanceName].shiftBoundaryY) {
                    if(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY<1000*2000.0)
                        xBoundary.push_back(influencerBoundaryX);
                    if(influencerBoundaryX-MacroMlistMap[instanceName].shiftBoundaryX<1000*2000.0)
                        yBoundary.push_back(influencerBoundaryY);
                    }

                else if
                   (influencerBoundaryX <= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY >= MacroMlistMap[instanceName].shiftBoundaryY) {
                    if(fabs(influencerBoundaryX-MacroMlistMap[instanceName].shiftBoundaryX)+
                       fabs(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY)<2000*2000.0)
                        yBoundary.push_back(influencerBoundaryY);
                }
                break;
            }
                
            case 4:
            {
                float influencerBoundaryX = MacroMlistMap[influencerTemp.InstanceName].xLoc + MacroLefMap[influencerTemp.CellName].sizex*2000;;
                float influencerBoundaryY = MacroMlistMap[influencerTemp.InstanceName].yLoc;
                
                // find shifting range
                if (influencerBoundaryX <= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY <= MacroMlistMap[instanceName].shiftBoundaryY) {
                    if(fabs(influencerBoundaryX-MacroMlistMap[instanceName].shiftBoundaryX)+
                       fabs(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY)<2000*2000.0)
                    xBoundary.push_back(influencerBoundaryX);
                }

                else if
                   (influencerBoundaryX <= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY >= MacroMlistMap[instanceName].shiftBoundaryY) {
                    if(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY<1000*2000.0)
                        xBoundary.push_back(influencerBoundaryX);
                    if(MacroMlistMap[instanceName].shiftBoundaryX-influencerBoundaryX<1000*2000.0)
                        yBoundary.push_back(influencerBoundaryY);
                    }

                else if
                   (influencerBoundaryX >= MacroMlistMap[instanceName].shiftBoundaryX &&
                    influencerBoundaryY >= MacroMlistMap[instanceName].shiftBoundaryY) {
                    if(fabs(influencerBoundaryX-MacroMlistMap[instanceName].shiftBoundaryX)+
                       fabs(influencerBoundaryY-MacroMlistMap[instanceName].shiftBoundaryY)<2000*2000.0)
                        yBoundary.push_back(influencerBoundaryY);
                }
                break;
            }
                
            default:
                break;
        } // end switch
    } // end influence vec
}

void ShiftMacro(string instanceName, string cellName, int quadrant)
{
    FindShiftingRange(instanceName, cellName, quadrant);
    sort(xBoundary.begin(), xBoundary.end());
    sort(yBoundary.begin(), yBoundary.end());
    int lastX = xBoundary.size()-1;
    int lastY = yBoundary.size()-1;

    float maxShiftDistance = max_distance_constraint/2*2000.0;
    if (max_distance_constraint>1000) maxShiftDistance=500*2000.0;
    float movable_distanceX,movable_distanceY;

    // shift
    switch (MacroMlistMap[instanceName].quadrant) {
        case 1:
        {
//                cout << xBoundary.size() << " " << yBoundary.size() << endl;
            if (xBoundary.size() != 0) {
//                    xboundary = xBoundary[lastX];

                movable_distanceX = MacroMlistMap[instanceName].shiftBoundaryX - xBoundary[lastX];
                if (movable_distanceX <= 0)
                    MacroMlistMap[instanceName].xLoc = MacroMlistMap[instanceName].xLoc;

                else if (movable_distanceX > maxShiftDistance)
                    MacroMlistMap[instanceName].xLoc -= maxShiftDistance;

                else if (movable_distanceX < maxShiftDistance)
                    MacroMlistMap[instanceName].xLoc -= (movable_distanceX*0.8);
            }
            else MacroMlistMap[instanceName].xLoc -= maxShiftDistance;

            if (yBoundary.size() != 0) {
//                    yboundary = yBoundary[lastY];

                movable_distanceY = MacroMlistMap[instanceName].shiftBoundaryY - yBoundary[lastY];
                if (movable_distanceY <= 0)
                    MacroMlistMap[instanceName].yLoc = MacroMlistMap[instanceName].yLoc;

                else if (movable_distanceY > maxShiftDistance)
                    MacroMlistMap[instanceName].yLoc -= maxShiftDistance;

                else if (movable_distanceY < maxShiftDistance)
                    MacroMlistMap[instanceName].yLoc -= (movable_distanceY*0.8);
            }
            else MacroMlistMap[instanceName].yLoc -= maxShiftDistance;

            break;
        }
        
        case 2:
        {
//                cout << xBoundary.size() << " " << yBoundary.size() << endl;
            if (xBoundary.size() != 0) {
//                    xboundary = xBoundary[lastX];
                movable_distanceX = xBoundary[0] - MacroMlistMap[instanceName].shiftBoundaryX;
                if (movable_distanceX <= 0)
                    MacroMlistMap[instanceName].xLoc = MacroMlistMap[instanceName].xLoc;

                else if (movable_distanceX > maxShiftDistance)
                    MacroMlistMap[instanceName].xLoc += maxShiftDistance;

                else if (movable_distanceX < maxShiftDistance)
                    MacroMlistMap[instanceName].xLoc += (movable_distanceX*0.8);
            }
            else MacroMlistMap[instanceName].xLoc += maxShiftDistance;

            if (yBoundary.size() != 0) {
//                    yboundary = yBoundary[lastY];
                movable_distanceY = MacroMlistMap[instanceName].shiftBoundaryY - yBoundary[lastY];
                if (movable_distanceY <= 0)
                    MacroMlistMap[instanceName].yLoc = MacroMlistMap[instanceName].yLoc;

                else if (movable_distanceY > maxShiftDistance)
                    MacroMlistMap[instanceName].yLoc -= maxShiftDistance;

                else if (movable_distanceY < maxShiftDistance)
                    MacroMlistMap[instanceName].yLoc -= (movable_distanceY*0.8);
            }
            else MacroMlistMap[instanceName].yLoc -= maxShiftDistance;

            break;
        }
         
        case 3:
        {
//               cout << xBoundary.size() << " " << yBoundary.size() << endl;
            if (xBoundary.size() != 0) {
//                    xboundary = xBoundary[lastX];
                movable_distanceX = xBoundary[0] - MacroMlistMap[instanceName].shiftBoundaryX;
                
                if (movable_distanceX <= 0)
                    MacroMlistMap[instanceName].xLoc = MacroMlistMap[instanceName].xLoc;

                else if (movable_distanceX > maxShiftDistance)
                    MacroMlistMap[instanceName].xLoc += maxShiftDistance;

                else if (movable_distanceX < maxShiftDistance)
                    MacroMlistMap[instanceName].xLoc += (movable_distanceX*0.8);
            }
            else MacroMlistMap[instanceName].xLoc += maxShiftDistance;

            if (yBoundary.size() != 0) {
//                    yboundary = yBoundary[lastY];
                movable_distanceY = yBoundary[0] - MacroMlistMap[instanceName].shiftBoundaryY;
                
                if (movable_distanceY <= 0)
                    MacroMlistMap[instanceName].yLoc = MacroMlistMap[instanceName].yLoc;

                else if (movable_distanceY > maxShiftDistance)
                    MacroMlistMap[instanceName].yLoc += maxShiftDistance;

                else if (movable_distanceY < maxShiftDistance)
                    MacroMlistMap[instanceName].yLoc += (movable_distanceY*0.8);
            }
            else MacroMlistMap[instanceName].yLoc += maxShiftDistance;

            break;
        }
            
        case 4:
        {
//               cout << xBoundary.size() << " " << yBoundary.size() << endl;
            if (xBoundary.size() != 0) {
//                    xboundary = xBoundary[lastX];
                movable_distanceX = MacroMlistMap[instanceName].shiftBoundaryX - xBoundary[lastX];
                
                if (movable_distanceX <= 0)
                    MacroMlistMap[instanceName].xLoc = MacroMlistMap[instanceName].xLoc;

                else if (movable_distanceX > maxShiftDistance)
                    MacroMlistMap[instanceName].xLoc -= maxShiftDistance;

                else if (movable_distanceX < maxShiftDistance)
                    MacroMlistMap[instanceName].xLoc -= (movable_distanceX*0.8);
            }
            else MacroMlistMap[instanceName].xLoc -= maxShiftDistance;

            if (yBoundary.size() != 0) {
//                    yboundary = yBoundary[lastY];
                movable_distanceY = yBoundary[0] - MacroMlistMap[instanceName].shiftBoundaryY;
                
                if (movable_distanceY <= 0)
                    MacroMlistMap[instanceName].yLoc = MacroMlistMap[instanceName].yLoc;

                else if (movable_distanceY > maxShiftDistance)
                    MacroMlistMap[instanceName].yLoc += maxShiftDistance;

                else if (movable_distanceY < maxShiftDistance)
                    MacroMlistMap[instanceName].yLoc += (movable_distanceY*0.8);
            }
            else MacroMlistMap[instanceName].yLoc += maxShiftDistance;

            break;
        }
        default:
            break;
    }
    xBoundary.clear();
    yBoundary.clear();
}

void shiftAlg()
{

//    for (int num=0; num<2; num++) {
        xBoundary.clear();
        yBoundary.clear();
        minHeap.clear();
        divideQuadrant();
        for (int i=0; i<minHeap.size(); i++) {
            string instanceName = minHeap[i].InstanceName;
            string cellName = minHeap[i].CellName;
            ShiftMacro(instanceName, cellName, MacroMlistMap[instanceName].quadrant);
        }
//    }

/*
    for (int num=0; num<4; num++) {
        xBoundary.clear(); yBoundary.clear();
        minHeap.clear();
        firstQBST.clear(); secondQBST.clear();
        thirdQBST.clear(); fourthQBST.clear();
        divideQuadrant();
        for (int i=0; i<firstQBST.size(); i++) {
            string instanceName = firstQBST[i].InstanceName;
            string cellName = firstQBST[i].CellName;
            ShiftMacro(instanceName, cellName, 1);
        } // end firstQBST
        
        for (int i=0; i<fourthQBST.size(); i++) {
            string instanceName = fourthQBST[i].InstanceName;
            string cellName = fourthQBST[i].CellName;
            ShiftMacro(instanceName, cellName, 2);
        } // end fourthQBST
        
        for (int i=0; i<thirdQBST.size(); i++) {
            string instanceName = thirdQBST[i].InstanceName;
            string cellName = thirdQBST[i].CellName;
            ShiftMacro(instanceName, cellName, 3);
        } // end thirdQBST
        
        for (int i=0; i<secondQBST.size(); i++) {
            string instanceName = secondQBST[i].InstanceName;
            string cellName = secondQBST[i].CellName;
            ShiftMacro(instanceName, cellName, 2);
            
        } // end secondQBST
    }
 */
    

 
    cout << endl << "end shiftAlg" << endl;
}

