//
//  DArray.h
//  OS-lab2-process-scheduling
//
//  Created by Tyler Blanton on 10/11/16.
//  Copyright © 2016 Tyler Blanton. All rights reserved.
//

#ifndef DArray_h
#define DArray_h
#include "Process.h"
#include <string>
#include <iostream>
using namespace std;


class DArray
{
public:
    Process *arr;
    int capacity;
    int size;
    int contextSwitches;
    string name = "";
    
    DArray()
    {
        capacity = 5;
        arr = new Process[capacity];
        size = 0;
        contextSwitches = 0;
    }
    DArray(string n)
    {
        name = n;
        capacity = 5;
        arr = new Process[capacity];
        size = 0;
        contextSwitches = 0;
    }
    
    void resize();
    
    int index(int name);
    
    void pidOrder();
    
    bool insert(Process p, string typeOfScheduling);
    
    int readIn(string fileName, string typeOfScheduling);
    
    void SRTFOrder();
    
    void display(string typeOfScheduling, int quantum = 0);
    
    void pop();
    
    bool AreAllProcessesCompleted();
        
    void FCFS();
    void SRTF();
    void RR(int quantum);
    
    ~DArray()
    {
        //std::cout << "DESTRUCTING " << name << " HERE" << endl;
        if(size > 0)
        {
            delete []arr;
        }
    }

    
};

#endif /* dArray_h */
