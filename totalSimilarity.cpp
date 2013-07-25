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

//This class produces a new file which contains the user ID and their corresponding rated movies based on ratings.dat
inline double strtodouble(string ss)
{
  std::stringstream convert(ss);
  double value;
  if(!(convert >> value))
    value = 0;
  return value;
}
inline vector<vector<double> >getdouble(int fileline, string filename)
{
  ifstream infile;
  infile.open(filename.c_str());
  int mark = 0;
  string line;
  vector<vector<double> > vecattr;
  for(int mark=0; mark!=fileline; mark++){
    getline(infile, line);
    vector<double> vec1;
    int pos1 = 0, pos2 = pos1 + 1;
    for(int i = 0; i != line.size(); i++){
      if(line.at(i) == '\t'){
        pos2 = i;
        double d1 = strtodouble(line.substr(pos1, pos2-pos1));
        vec1.push_back(d1);
        pos1 = pos2+1;
      }
    }
    double d2 = strtodouble(line.substr(pos1));
    vec1.push_back(d2);
    vecattr.push_back(vec1);
  }
  infile.close();
  return vecattr;
}
int main()
{
  ifstream infile1;
  infile1.open("attrsimilarity.txt");
  ofstream outfile;
  outfile.open("similarity.txt");
  string line;
  int fileline = 0;
  while(!infile1.eof())
  {
    getline(infile1, line);
    ++fileline;
  }
  fileline--;
  infile1.close();
  vector<vector<double> >vecattr = getdouble(fileline, "attrsimilarity.txt");
  vector<vector<double> >vecmenu = getdouble(fileline, "menusimilarity.txt");
  vector<double> vecsim;
  for(int i = 0; i != vecattr.size(); i++){
    vector<double> vec2;
    double sim = vecattr[i].at(2) * 0.5 + vecmenu[i].at(2) * 0.5;
    vec2.push_back(sim);
    outfile<<vecattr[i].at(0)<<"\t"<<vecattr[i].at(1)<<"\t"<<sim<<endl;
  }
  outfile.close();
  return 0;
}