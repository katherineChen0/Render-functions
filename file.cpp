//
//  file.cpp
//  CS 31
//
//  Created by Katherine on 11/13/23.
//

#include <iostream>
#include <fstream>

using namespace std;


int countLines(istream& inf)   // inf is a name of our choosing
    {
        int lineCount = 0;
        string line;
        while (getline(inf, line))
            lineCount++;
        return lineCount;
    }

    int main()
    {
        ifstream infile("/Users/kat/Desktop/results.txt");
        system("pwd");
        
        if ( ! infile )
        {
            cerr << "Error: Cannot open results.txt!" << endl;
            return 1;
        }
        int fileLines = countLines(infile);  // reads from the file data.txt
        cout << "results.txt has " << fileLines << " lines." << endl;
        cout << "Type lines, then ctrl-Z (Windows) or ctrl-D (macOS/Linux):" << endl;
        int keyboardLines = countLines(cin); // reads from keyboard
        cout << "You typed " << keyboardLines << " lines." << endl;
    }
