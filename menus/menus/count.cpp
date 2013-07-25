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
int main()
{
  ifstream infile1;
  ifstream infile2;
  ofstream outfile;
  infile1.open("menu.txt");
  outfile.open("count.txt");
  int file1line=0;
  int file2line=0;
  string previousline1 = "";
  int totalfiles = 100;
  int linenum[totalfiles];
  string line;
  while(!infile1.eof())
  {
    getline(infile1, line);
    ++file1line;
  }
  file1line--;

  for(int i = 0; i != totalfiles; i++){
    std::stringstream ss;
    ss << i;
    string s = ss.str();
    infile2.open((s+".json").c_str());
    file2line = 0;
    while(!infile2.eof())
    {
      getline(infile2, line);
      ++file2line;
    }
    file2line--;
    linenum[i] = file2line;
    infile2.close();
  }
  infile1.close();
  infile1.open("menu.txt");
  vector<string> vecmenu;
  int mark = 0;
  while(mark<file1line){
    getline(infile1, line);
    vecmenu.push_back(line.substr(0));
    mark++;
  }
//countmenu is the vector storing the menus of all the restaurants
  vector<vector<string> > countmenu;
  for(int i = 0; i != totalfiles; i++){
    std::stringstream ss;
    ss << i;
    string s = ss.str();
    infile2.open((s+".json").c_str());
    int mark = 0;
    vector<string> vecnew;
    while(mark != linenum[i]){
      getline(infile2, line);
      vecnew.push_back(line.substr(0));
      mark++;
    }
    countmenu.push_back(vecnew);
    infile2.close();
  }
  
//doc_word_count
  vector<string> doc_word_count;
  for(int i = 0; i != countmenu.size(); i++){
    for(int k = 0; k != vecmenu.size(); k++){
      int count = 0;
      for(int j = 0; j != countmenu[i].size(); j++){
        if(countmenu[i].at(j) == vecmenu[k])
          count++;
      }
      if(count != 0){
        std::stringstream ss;
        ss<<i;
        string si = ss.str();
        std::stringstream ssk;
        ssk<<k;
        string sk = ssk.str();
        std::stringstream ssc;
        ssc<<count;
        string sc = ssc.str();
        doc_word_count.push_back(si+"\t"+sk+"\t"+sc);
      }
    }
  }
  for(vector<int>::size_type i = 0; i != doc_word_count.size(); i++)
      outfile<<doc_word_count.at(i)<<endl;
  outfile.close();
}