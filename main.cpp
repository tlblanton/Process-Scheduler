//
//  main.cpp
//  OS-lab2-process-scheduling
//
//  Created by Tyler Blanton on 10/11/16.
//  Copyright © 2016 Tyler Blanton. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Process.h"
#include "DArray.h"
using namespace std;

DArray processArr("ProcessArr");

int main(int argc, char *argv[])
{
    string typeOfScheduling, fileName;
    int quantum = -1;

    /*
     * Logic for basic input and output.
     * The program is to be run from the command line.
     * Proper call could be "./a.out inputFIle.txt 1 outputFile.txt" where 1 would specify the SRTF algorithm
     */
    if(argc < 3 || atoi(argv[2]) > 2 || atoi(argv[2]) < 0)
    {
        cerr << "Improperly formatted command line arguments. Program terminated." << endl;
        return EXIT_FAILURE;
    }
    if(strncmp(argv[2], "0", 1) == 0)
    {
        typeOfScheduling = "FCFS";
        
        fileName = argv[1];
        
        if(processArr.readIn(fileName, typeOfScheduling) == EXIT_FAILURE)
        {
            cerr << "Could not open file. Program terminated." << endl;
            return EXIT_FAILURE;
        }
        processArr.FCFS();
    }
    else if(strncmp(argv[2], "1", 1) == 0)
    {
        typeOfScheduling = "SRTF";
        
        fileName = argv[1];
        
        if(processArr.readIn(fileName, typeOfScheduling) == EXIT_FAILURE)
        {
            cerr << "Could not open file. Program terminated." << endl;
            return EXIT_FAILURE;
        }
        processArr.SRTF();
    }
    else if(strncmp(argv[2], "2", 1) == 0)
    {
        if(argc < 4 || atoi(argv[3]) < 1)
        {
            cerr << "Improperly formatted command line arguments. Program terminated." << endl;
            return EXIT_FAILURE;
        }
        
        fileName = argv[1];
        typeOfScheduling = "RR";
        
        if(processArr.readIn(fileName, typeOfScheduling) == EXIT_FAILURE)
        {
            cerr << "Could not open file. Program terminated." << endl;
            return EXIT_FAILURE;
        }
        quantum = atoi(argv[3]);
        processArr.RR(quantum);
    }
    
    processArr.display(typeOfScheduling, quantum);
	cout << "Press enter to continue" << endl;
	cin.get();
}

























