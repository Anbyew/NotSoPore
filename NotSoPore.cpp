//
//  main.cpp
//  po
//
//  Created by 包雨薇 on 17/4/3.
//  Copyright © 2017年 包雨薇. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <getopt.h>
#include <string>
#include <algorithm>
using namespace std;

void printHelp();
int getScore(int argc, char *argv[]);

int main(int argc, char * argv[]) {
    int qscoret = 0;
    qscoret = getScore(argc, argv);
    
    string filenm = argv[3];
    string outfnm = argv[4];
    ifstream infile;
    infile.open(filenm.c_str());
    if (!infile.is_open()) {
        cout << "error opening infile" << endl;
        exit(1);
    }
    ofstream offile;
    //offile.open(outfnm);
    offile.open(outfnm.c_str(), std::ios_base::app);
    if (!offile.is_open()) {
        cout << "error opening outfile" << endl;
        exit(1);
    }

    
    string gene;
    string quality;
    int totqs = 0;
    string trash;
    string prev;
    
    getline(infile, trash);

    
    while (getline(infile, trash)) {
        
        
        if ((trash[0] == '+') &&
            (prev[0] == 'A' || prev[0] == 'G' || prev[0] == 'C' || prev[0] == 'T' || prev[0] == 'U') &&
            (prev[1] == 'A' || prev[1] == 'G' || prev[1] == 'C' || prev[1] == 'T' || prev[1] == 'U')) {
            gene = prev;
            quality = "";
            getline(infile, quality);
            
            totqs = 0;
            for (int i = 0; i < quality.length(); ++i) {
                totqs += int(quality[i]);
            }
            
            if ((double(totqs) / double(quality.length()) - 36.0) >= qscoret) {
                string strnm = "";
                strnm = filenm + "_qscore_";
                strnm += to_string(double(totqs) / double(quality.length()) - 36.0);
                offile << '>' << strnm << endl << gene << endl;

            }
            
        }
        
        swap(trash, prev);
        
    }

    
    infile.close();
    offile.close();
    return 0;
}


int getScore(int argc, char *argv[]) {
    
    int qscore = 0;
    int choice;
    int option_index = 0;
    option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"qscore", required_argument, nullptr, 'q'},
        {nullptr, 0, nullptr, '\0'}
    };
    
    while ((choice = getopt_long(argc, argv, "hq:", long_options,
                                 &option_index)) != -1) {
        switch (choice) {
            case 'h':
                printHelp();
                exit(0);
                break;

            case 'q':
                qscore = stoi(optarg);
                break;
            default:
                cerr << "Error: invalid command" << "\n";
                exit(1);
                break;
        }
    }
    
    return qscore;
}

void printHelp() {

    cout << "infile name, outfile name, -qscore/help" << endl;
}

