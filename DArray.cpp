//
//  DArray.cpp
//  OS-lab2-process-scheduling
//
//  Created by Tyler Blanton on 10/11/16.
//  Copyright © 2016 Tyler Blanton. All rights reserved.
//

#include <stdio.h>
#include "DArray.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

/************************
 INSERT 
 //returns true if a process was removed from the CPU and put into the queue
 ************************/
bool DArray::insert(Process p, string typeOfScheduling)
{
    if(size == capacity)
    {
        resize();
    }
    if(typeOfScheduling == "FCFS" || typeOfScheduling == "RR")
    {
        arr[size] = p;
        ++size;
    }
    else if(typeOfScheduling == "SRTF")
    {
        arr[size] = p;
        ++size;
        int top = arr[0].name;
        SRTFOrder();
        if(top != arr[0].name)
        {
            return true;
        }
    }
    return false;
}


/************************
 RESIZE
 ************************/
void DArray::resize()
{
    int newCapacity = capacity * 100;
    //creating new large one
    Process *newArr = new Process[newCapacity];
    
    //copying values from small one into large one
    for(int i = 0; i < size; ++i)
    {
        newArr[i] = arr[i];
    }
    
    //assigning small one's name to large one's address and changing capacity variable
    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
}


/************************
 READ IN
 ************************/
int DArray::readIn(string fileName, string typeOfScheduling)
{
    ifstream inFile(fileName);
    if(!inFile)
    {
        return EXIT_FAILURE;
    }
    
    int tempName, tempArrival, tempBurst;
    
    inFile >> tempName;
    inFile >> tempArrival;
    inFile >> tempBurst;
    Process tempProcess(tempName, tempArrival, tempBurst);
    insert(tempProcess, typeOfScheduling);
    while(inFile >> tempName)
    {
        inFile >> tempArrival;
        inFile >> tempBurst;
        Process tempProcess(tempName, tempArrival, tempBurst);
        insert(tempProcess, typeOfScheduling);
    }
    return 0;
}


/************************
 SRTF ORDER
 ************************/
void DArray::SRTFOrder()
{
    bool swap = true;
    int x = 0;
    Process temp;
    
    //simple bubble sort
    while(swap)
    {
        swap = false;
        ++x;
        for(int i = 0; i < size - x; ++i)
        {
            if(arr[i].burstTime > arr[i+1].burstTime)
            {
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                swap = true;
            }
        }
    }
}


/************************
 PID ORDER
 ************************/
void DArray::pidOrder()
{
    bool swap = true;
    int x = 0;
    Process temp;
    
    //simple bubble sort
    while(swap)
    {
        swap = false;
        ++x;
        for(int i = 0; i < size - x; ++i)
        {
            if(arr[i].name > arr[i+1].name)
            {
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                swap = true;
            }
        }
    }
}


/************************
 INDEX
 ************************/
int DArray::index(int name)
{
    for(int i = 0; i < size; ++i)
    {
        if(arr[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

/************************
DISPLAY
 ************************/
void DArray::display(string typeOfScheduling, int quantum)
{
    double burstSum=0, waitSum=0, turnaroundSum=0, responseSum=0;
    
    if(typeOfScheduling == "FCFS")
    {
        for(int i = 0; i < 48; ++i)
        {
            cout << '*';
        }
        cout << endl << "********   Scheduling Algorithm: FCFS   ********" << endl;
        for(int i = 0; i < 48; ++i)
        {
            cout << '*';
        }
        cout << endl;
    }
    else if(typeOfScheduling == "SRTF")
    {
        for(int i = 0; i < 48; ++i)
        {
            cout << '*';
        }
        cout << endl << "********   Scheduling Algorithm: SRTF   ********" << endl;
        for(int i = 0; i < 48; ++i)
        {
            cout << '*';
        }
        cout << endl;
    }
    else if(typeOfScheduling == "RR")
    {
        for(int i = 0; i < 48; ++i)
        {
            cout << '*';
        }
        cout << endl << "***** Scheduling Algorithm: Round Robin " << " *******";
        cout << endl << "***** ( No of tasks = " << size  << "  Quantum = " << quantum << " ) *********" << endl;
        for(int i = 0; i < 48; ++i)
        {
            cout << '*';
        }
        cout << endl;
    }
    for(int i = 0; i < 102; ++i)
    {
        cout << "_";
    }
    cout << endl <<"|" << setw(5) << "pid" << setw(3) << "|" << setw(8) << "arrival" << setw(2) <<"|" << setw(10) << "CPU-burst" << setw(2) << "|" << setw(7) << "finish" << setw(2) <<"|" << setw(13) << "waiting time" << setw(2) <<"|" << setw(12) <<"turn around" << setw(2) <<"|" << setw(14) << "response time" << setw(2) <<"|" << setw(15) << "No. of context" << setw(2) << "|" << endl;
    
    for(int i = 0; i < 102; ++i)
    {
        cout << "_";
    }
    pidOrder();
    for(int i = 0; i < size; ++i)
    {
        cout << endl <<"|" << setw(4) << arr[i].name << setw(4) << "|" << setw(5) << arr[i].arrivalTime << setw(5) << "|" << setw(6) << arr[i].burstTime << setw(6) << "|" << setw(5) << arr[i].completionTime << setw(4) << "|" << setw(7) << arr[i].waitTime << setw(8) <<"|" << setw(7) << arr[i].turnAroundTime << setw(7) <<"|" << setw(8) << arr[i].responseTime << setw(8) <<"|" << setw(9) << arr[i].contextSwitches << setw(8) << "|" << endl;
    }
    for(int i = 0; i < 102; ++i)
    {
        cout << "-";
    }
    cout << endl;
    
    for(int i = 0; i < size; ++i)
    {
        burstSum += arr[i].burstTime;
        waitSum += arr[i].waitTime;
        turnaroundSum += arr[i].turnAroundTime;
        responseSum += arr[i].responseTime;
        contextSwitches += arr[i].contextSwitches;
    }
    
    cout << "Average CPU burst time = " << (burstSum / size) << " ms\t\tAverage waiting time = " << (waitSum / size) << " ms" << endl;
    cout << "Average turn around time = " << (turnaroundSum / size) << " ms\t\tAverage response time = " << (responseSum / size) << " ms" << endl;
    cout << "Total No. of context switches performed = " << contextSwitches << endl;
    
    
}


/************************
 ARE ALL PROCESSES COMPLETED
 ************************/
bool DArray::AreAllProcessesCompleted()
{
    for(int i = 0; i < size; ++i)
    {
        if(arr[i].completed == false)
        {
            return false;
        }
    }
    return true;
}


/************************
 POP
 ************************/
void DArray::pop()
{
    if(size > 0)
    {
        for(int i = 1; i < size; ++i)
        {
            arr[i-1] = arr[i];
        }
    }
    --size;
}


/************************
 FCFS
 ************************/
void DArray::FCFS()
{
    DArray ganttArr;
    int timer = 0;
    int currentProcess = 0;
    int contextSwitchingTime = 0;
    while(!AreAllProcessesCompleted())
    {
        //if a process arrives at this time, then add it to the new array
        for(int i = 0; i < size; ++i)
        {
            if(arr[i].arrivalTime == timer)
            {
                ++contextSwitchingTime;
                ganttArr.insert(arr[i], "FCFS");
            }
        }
        //If the ganttArray is not empty, then subtract 1 from the top processes in it
        if(ganttArr.size != 0)
        {
            ganttArr.arr[currentProcess].burstTime--;
            if(ganttArr.arr[currentProcess].executionStartTime == -1)
            {
                ganttArr.arr[currentProcess].executionStartTime = timer;
            }
            for(int i = 0; i < ganttArr.size; ++i)
            {
                if(i != currentProcess && !arr[i].completed)
                {
                    ++arr[i].waitTime;
                }
            }
            if(ganttArr.arr[currentProcess].burstTime == 0)
            {
                arr[currentProcess].completionTime = timer+1;
                arr[currentProcess].completed = true;
                arr[currentProcess].turnAroundTime = arr[currentProcess].completionTime - arr[currentProcess].arrivalTime;
                arr[currentProcess].responseTime = ganttArr.arr[currentProcess].executionStartTime - ganttArr.arr[currentProcess].arrivalTime;
                ++currentProcess;
            }
        }
        ++timer;
    }
}


/************************
 SRTF
 ************************/
void DArray::SRTF()
{
    DArray ganttArr;
    int timer = 0;
    double actualTime = 0;
    int currentProcess = 0;
    int contextSwitchingTime = 0;
    bool justPopped = false;
    
    while(!AreAllProcessesCompleted())
    {
        for(int i = 0; i < size; ++i)
        {
            if(arr[i].arrivalTime == timer)
            {
                int previousTop = ganttArr.arr[currentProcess].name;
                ganttArr.insert(arr[i], "SRTF");
                int justInsertedName = arr[i].name;
                
                //once you've inserted, if there was context switches before you then you need to check if actualTime equals timer. If it does not, then you |||| at sub
                
                
                //incrementing waitTime by 0.5 for each contextSwitch that has happen before the justInserted process was inserted.
                for(int f = 0; f < contextSwitchingTime; ++f)
                {
                    if(!justPopped)
                    {
                        int sub_1 = ganttArr.index(justInsertedName);
                        ganttArr.arr[sub_1].waitTime += 0.5;
                    }
                }
                
                
                //If the thing that was on top had been moved to the bottom, then this incurs context switch time
                if(ganttArr.arr[currentProcess].name != previousTop && ganttArr.size != 1)
                {
                    int sub = ganttArr.index(previousTop);
                    
                    
                    for(int f = 0; f < contextSwitchingTime; ++f)
                    {
                        ganttArr.arr[currentProcess].waitTime += 0.5;
                    }
                   
                    //if you did NOT just pop
                    if(!justPopped)
                    {
                        ++contextSwitchingTime;

                        ++ganttArr.arr[sub].contextSwitches;
                        ganttArr.arr[currentProcess].responseTime += 0.5;
                        actualTime += 0.5;
                        for(int i = 0; i < ganttArr.size; ++i)
                        {
                            ganttArr.arr[i].waitTime += 0.5; //when there is a context switch, both processes are technically waiting
                        }
                        justPopped = false;
                    }
                   
                }
            }
        }
        
        if(ganttArr.size != 0)
        {
            --ganttArr.arr[currentProcess].burstTime;
            if(ganttArr.arr[currentProcess].executionStartTime == -1)
            {
                ganttArr.arr[currentProcess].executionStartTime = actualTime;
            }
            for(int x = 0; x < ganttArr.size; ++x)
            {
                if(x != currentProcess)
                {
                    ++ganttArr.arr[x].waitTime;
                }
            }
            if(ganttArr.arr[currentProcess].burstTime == 0)
            {
                int sub = index(ganttArr.arr[currentProcess].name);
                arr[sub].completionTime = actualTime+1;
                arr[sub].completed = true;
                arr[sub].turnAroundTime = arr[sub].completionTime - arr[sub].arrivalTime;
                arr[sub].waitTime = ganttArr.arr[currentProcess].waitTime;
                arr[sub].responseTime = ganttArr.arr[currentProcess].executionStartTime - ganttArr.arr[currentProcess].arrivalTime;
                arr[sub].contextSwitches = ganttArr.arr[currentProcess].contextSwitches;
                ganttArr.pop();
                justPopped = true;
                
            }
        }
        ++timer;
        ++actualTime;
    }
}



/************************
 RR
 ************************/
void DArray::RR(int quantum)
{
    DArray ganttArr("ganttArr");
    int timer = 0;
    double actualTime = 0;
    int currentProcess = 0;
    bool rotate = false;
    //int blah = 0, finished = 0;
    
    while(!AreAllProcessesCompleted())
    {
        //cout << "blah: " << blah++ << endl;
        for(int i = 0; i < quantum; ++i)
        {
            for(int x = 0; x < size; ++x)
            {
                if(arr[x].arrivalTime == timer)
                {
                    ganttArr.insert(arr[x], "RR");
                }
            }
            
            if(rotate)
            {
                //++contextSwitches;
                actualTime += 0.5;
                for(int f = 0; f < ganttArr.size; ++f)
                {
                        ganttArr.arr[f].waitTime += 0.5;
                }
                
                ++ganttArr.arr[currentProcess].contextSwitches;
                Process temp = ganttArr.arr[currentProcess];
                ganttArr.pop();
                ganttArr.insert(temp, "RR");
                rotate = false;
            }
            
            if(ganttArr.size != 0)
            {
                --ganttArr.arr[currentProcess].burstTime;
                if(ganttArr.arr[currentProcess].executionStartTime == -1)
                {
                    ganttArr.arr[currentProcess].executionStartTime = actualTime;
                }
                for(int k = 0; k < ganttArr.size; ++k)
                {
                    if(k != currentProcess)
                    {
                        ++ganttArr.arr[k].waitTime;
                    }
                }
            }
            
            if(ganttArr.size != 0 && ganttArr.arr[currentProcess].burstTime == 0)
            {
                int sub = index(ganttArr.arr[currentProcess].name);
                
                arr[sub].completionTime = actualTime+1;
                arr[sub].completed = true;
                arr[sub].turnAroundTime = arr[sub].completionTime - arr[sub].arrivalTime;
                arr[sub].waitTime = ganttArr.arr[currentProcess].waitTime;
                arr[sub].responseTime = ganttArr.arr[currentProcess].executionStartTime - ganttArr.arr[currentProcess].arrivalTime;
                arr[sub].contextSwitches = ganttArr.arr[currentProcess].contextSwitches;
                if(ganttArr.size == 0)
                {
                    cin.get();
                }
                ganttArr.pop();
                //cout << "SOMETHING JUST FINISHED: " << finished++ << endl;
                ++timer;
                ++actualTime;
                break;
            }
            if(i == (quantum-1))
            {
                rotate = true;
            }
            ++timer;
            ++actualTime;
            
        }
    }
}
