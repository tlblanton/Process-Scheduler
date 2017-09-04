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
 returns true if a process was removed from the CPU and put into the queue
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
 creates new array that is 100x the size of the original (data sets are quite large)
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
 reads in processes from a properly formatted text file and places them in a dynamic array.
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
 orders elements in ascending order of remaining processing time using bubble sort (as specified by assignment)
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
 puts processes in ascending order by the Process IDs
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
 returns a process's index in the dynamic array or -1 if the item does not exist
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
 displays results of different process-scheduling algorithms to the user
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
 checks if all processes have been given enough time in the simulated CPU to run
 ************************/
bool DArray::AreAllProcessesCompleted()
{
    for(int i = 0; i < size; ++i)
    {
        if(!arr[i].completed)
        {
            return false;
        }
    }
    return true;
}


/************************
 POP
 remove top element from the dynamic array
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
 first-come, first-served algorithm
 this algorithm simulates the process of performing these calculations by hand using a Gantt Chart
 processes are executed in the order that the reach the CPU
 ************************/
void DArray::FCFS()
{
    //creating a gantt array to simulate gantt chart operations (adding, removing, processing, etc)
    DArray ganttArr;
    int timer = 0;
    int currentProcess = 0;
    int contextSwitchingTime = 0;

    //loop starts at a count of zero and continues while there are still processes that need time in the CPU
    while(!AreAllProcessesCompleted())
    {
        //if a process arrives at this time ("timer"), then add it to the new array
        for(int i = 0; i < size; ++i)
        {
            if(arr[i].arrivalTime == timer)
            {
                //Adding a new process incurs time for a context switch
                ++contextSwitchingTime;
                ganttArr.insert(arr[i], "FCFS");
            }
        }

        /*
         * Algorithm for simulating execution of processes that have entered in to the CPU and are waiting
         * If the ganttArray is not empty, then subtract 1 from the top processes in it, simulating that it has had time to execute.
         */
        if(ganttArr.size != 0)
        {
            ganttArr.arr[currentProcess].burstTime--;
            if(ganttArr.arr[currentProcess].executionStartTime == -1)
            {
                //record execution start time of currently executing process.
                ganttArr.arr[currentProcess].executionStartTime = timer;
            }
            for(int i = 0; i < ganttArr.size; ++i)
            {
                if(i != currentProcess && !arr[i].completed)
                {
                    ++arr[i].waitTime;
                }
            }

            //if process is finished executing then calculate and record all relevant data
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
 shortest remaning time first algorithm
 this algorithm simulates the process of performing these calculations by hand using a Gantt Chart
 procsses are executed in order of their remaining time
 ************************/
void DArray::SRTF()
{
    //declare gant array that will house all processes as they simulate coming in to the CPU
    DArray ganttArr;
    int timer = 0;
    double actualTime = 0;
    int currentProcess = 0;
    int contextSwitchingTime = 0;
    bool justPopped = false;

    while(!AreAllProcessesCompleted())
    {
        /*
         * Logic for handling incoming processes
         */
        for(int i = 0; i < size; ++i)
        {
            if(arr[i].arrivalTime == timer)
            {
                int previousTop = ganttArr.arr[currentProcess].name;
                ganttArr.insert(arr[i], "SRTF");
                int justInsertedName = arr[i].name;
                
                //incrementing waitTime by 0.5 for each contextSwitch that has happen before the justInserted process was inserted.
                for(int f = 0; f < contextSwitchingTime; ++f)
                {
                    if(!justPopped)
                    {
                        int sub_1 = ganttArr.index(justInsertedName);
                        ganttArr.arr[sub_1].waitTime += 0.5;
                    }
                }
                
                
                //If the process that was on top had been moved to the bottom, then this incurs context switch time
                if(ganttArr.arr[currentProcess].name != previousTop && ganttArr.size != 1)
                {
                    int sub = ganttArr.index(previousTop);

                    for(int f = 0; f < contextSwitchingTime; ++f)
                    {
                        ganttArr.arr[currentProcess].waitTime += 0.5;
                    }
                   
                    //if you did NOT just pop, then the current process is still on top and needs to have context switching time added, and response time incremented
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

        /*
         * Algorithm for simulating execution of processes that have entered in to the CPU and are waiting
         */
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
            //If the current process has finished its execution, collect relevant information and remove it from the simulated CPU and gantt chart
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
 round-robin
 this algorithm simulates the process of performing these calculations by hand using a Gantt Chart
 procsses are executed in specific increments of time and keep looping until they are finished.
 input: quantum - the max number of consecutive iterations (simulated seconds) a process can have in the CPU
 ************************/
void DArray::RR(int quantum)
{
    DArray ganttArr("ganttArr");
    int timer = 0;
    double actualTime = 0;
    int currentProcess = 0;
    bool rotate = false;

    while(!AreAllProcessesCompleted())
    {

        for(int i = 0; i < quantum; ++i)
        {
            for(int x = 0; x < size; ++x)
            {
                if(arr[x].arrivalTime == timer)
                {
                    ganttArr.insert(arr[x], "RR");
                }
            }

            /*
             * Logic for handling processes moving arround in the round-robin line and entering into it
             */

            //if rotate is true then the current process has been in the CPU executing for n
            // iterations and now must cede the CPu to the next process in line.
            if(rotate)
            {
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

            /*
             * Algorithm for executing process whose turn it is to execute
             */
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

            //logic for when current process has finished executing
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
                ++timer;
                ++actualTime;
                break;
            }
            //if quantum is about to be reached then rotate is set to true, so we know to move the round-robin line
            if(i == (quantum-1))
            {
                rotate = true;
            }
            ++timer;
            ++actualTime;
        }
    }
}
