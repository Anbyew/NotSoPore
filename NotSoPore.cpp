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
using namespace std;

void printHelp();
int getScore(int argc, char *argv[]);

int main(int argc, char * argv[]) {
    int qscoret = 0;
    qscoret = getScore(argc, argv);
    
    string filenm = argv[0];
    string outfnm = argv[1];
    ifstream infile;
    infile.open(filenm);
    if (!infile.is_open()) {
        cout << "error opening infile" << endl;
        exit(1);
    }
    ofstream offile;
    offile.open(outfnm);
    if (!offile.is_open()) {
        cout << "error opening outfile" << endl;
        exit(1);
    }
    
    
    string gene;
    string quality;
    int totqs = 0;
    
    string trash;
    while (getline(infile, trash)) {
        if(trash[5] == 'n' && trash[6] == 'u'&& trash[7] == 'm' &&
           trash[8] == '_' && trash[9] == 's' && trash[10] == 't') {
           
            gene = "";
            quality = "";
            getline(infile, gene);
            getline(infile, trash);
            getline(infile, quality);
            
            totqs = 0;
            for (int i = 0; i < quality.length(); ++i) {
                totqs += int(quality[i]);
            }
            filenm += "_qscore_";
            filenm += to_string(totqs / quality.length());
            offile << filenm << gene;
            
        }
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
