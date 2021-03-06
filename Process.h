//
//  Process.h
//  OS-lab2-process-scheduling
//
//  Created by Tyler Blanton on 10/11/16.
//  Copyright © 2016 Tyler Blanton. All rights reserved.
//

#ifndef Process_h
#define Process_h

struct Process
{

    int name, arrivalTime, burstTime;
    double waitTime, turnAroundTime, completionTime, responseTime, contextSwitches, executionStartTime;
    bool completed; //flag that is set to true when process has simulated its execution.
    
    // constructor
    // every process sould come in with a known name, arrivalTime, and burstTime
    Process(int nm, int aT, int bT)
    {
        name = nm;
        arrivalTime = aT;
        burstTime = bT;
        waitTime = 0;
        turnAroundTime = -1;
        completed = false;
        responseTime = 0;
        contextSwitches = 0;
        completionTime = -1;
        executionStartTime = -1;
    }
    
    Process()
    {
        name = -1;
        arrivalTime = -1;
        burstTime = -1;
    }

    // Overloaded assignment operator so processes can easily be moved around and copied
    void operator =(Process & pr)
    {
        name = pr.name;
        arrivalTime = pr.arrivalTime;
        burstTime = pr.burstTime;
        waitTime = pr.waitTime;
        turnAroundTime = pr.turnAroundTime;
        completed = pr.completed;
        completionTime = pr.completionTime;
        responseTime = pr.responseTime;
        contextSwitches = pr.contextSwitches;
        executionStartTime = pr.executionStartTime;
    }
};


#endif /* Process_h */
