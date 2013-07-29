#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <sstream>

// Using Declarations
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

//This class produces a new file containing the menus for each restaurant, to make it be the input for LDA in graphLab
int main()
{
  string line;
  ifstream infile;
  ofstream outfile;
  outfile.open("menu.txt");
  const int filenum = 100;
  vector<string> vecmenu;
  for(int i = 0; i != filenum; i++){
    std::stringstream ss;
    ss << i;
    string s = ss.str();
    string filename = "menus/"+s+".json";
    infile.open(filename.c_str());
    while(!infile.eof())
    {
      getline(infile, line);
      vecmenu.push_back(line.substr(0));
    }
    infile.close();
  }
  //The following steps are deleting the duplicate menus, making each menu appear once in the output file
  for(int i = 0; i != vecmenu.size(); i++){
    for(int j = i+1; j != vecmenu.size(); j++)
      if(vecmenu.at(j) == vecmenu.at(i))
        vecmenu.at(j) = "";
  }
  vector<string> vecmenusingle;
  for(int i = 0; i != vecmenu.size(); i++)
    if(vecmenu.at(i) != "")
      vecmenusingle.push_back(vecmenu.at(i));
  for(int i = 0; i != vecmenusingle.size(); i++)
    outfile<<vecmenusingle.at(i)<<endl; 
  outfile.close();
  return 0;
}