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

//This class produces a new file count.txt which can be the input for LDA in graphLab

//this function transfers integers to string
inline string inttostr(int a)
{
  std::stringstream ss;
  ss << a;
  string s = ss.str();
  return s;
}

int main()
{
  ifstream infile1;
  ifstream infile2;
  ofstream outfile;
  infile1.open("menu.txt");
  outfile.open("count.txt");
  const int totalfiles = 100;
  string line;

  //vecmenu is the vector storing the lines in menu.txt
  vector<string> vecmenu;
  while(!infile1.eof())
  {
    getline(infile1, line);
    vecmenu.push_back(line.substr(0));
  }
  infile1.close();

  //countmenu is the vector storing the menus of all the restaurants
  vector<vector<string> > countmenu;
  for(int i = 0; i != totalfiles; i++){
    string s = inttostr(i);
    infile2.open(("menus/" + s + ".json").c_str());
    vector<string> veceachmenu;
    while(!infile2.eof())
    {
      getline(infile2, line);
      veceachmenu.push_back(line.substr(0));
    }
    countmenu.push_back(veceachmenu);
    infile2.close();
  }

  
  //doc_word_count is the vector storing the output format for LDA
  vector<string> doc_word_count;
  for(int i = 0; i != countmenu.size(); i++){
    for(int k = 0; k != vecmenu.size()-1; k++){
      int count = 0;
      for(int j = 0; j != countmenu[i].size()-1; j++){
        if(countmenu[i].at(j) == vecmenu[k])
          count++;
      }
      if(count != 0){
        string si = inttostr(i);
        string sk = inttostr(k);
        string sc = inttostr(count);
        doc_word_count.push_back(si+"\t"+sk+"\t"+sc);
      }
    }
  }

  //write the output file
  for(vector<int>::size_type i = 0; i != doc_word_count.size(); i++)
      outfile<<doc_word_count.at(i)<<endl;
  outfile.close();
}