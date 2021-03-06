#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

// Using Declarations
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

//This class organizes the original files, produces a new file containing the menus for each restaurant
int main()
{
  string line;
  const int filenum = 100;
  for(int num = 0; num < filenum; num ++){
    ifstream infile;
    ofstream outfile;
    std::stringstream ss;
    ss << num;
    string s = ss.str();
    infile.open((s+".txt").c_str());
    outfile.open((s+".json").c_str());
    vector<string> vecMenu;

    //find the menu strings in each file.
    while(!infile.eof()){
      getline(infile, line);
      if(line.size() > 0){
        int pos1, pos2;
        if(line.size() > 26 && line.substr(21,4) == "name"){
          for(int i = 25; i != line.size(); i++){
            if(line.at(i) == ':')
              pos1 = i;
          }
          for(int j = pos1+1; j != line.size(); j++){
            if(line.at(j) == ',')
              pos2 = j-1;
          }
          vecMenu.push_back(line.substr(pos1+3, pos2-pos1-3));
        }
      }
    }

    //put the menus into the new file
    for(vector<int>::size_type i = 0; i != vecMenu.size(); i++)
      outfile<<vecMenu.at(i)<<endl;
    
    infile.close();
    outfile.close();
  }
    return 0;
}