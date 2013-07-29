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

//This class computes the similarity between any two restaurants based on their menus, ratings and price.

//This method transfers string to double
inline double strtodouble(string ss)
{
  std::stringstream convert(ss);
  double value;
  if(!(convert >> value))
    value = 0;
  return value;
}

//This method put the numbers in the input file in a vector.
inline vector<vector<double> >getdouble(string filename)
{
  ifstream infile;
  infile.open(filename.c_str());
  int mark = 0;
  string line;
  vector<vector<double> > vecattr;
  while(!infile.eof()){
    getline(infile, line);
    if(line.size() > 0){
      vector<double> vec1;
      int pos1 = 0, pos2;
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
  }
  infile.close();
  return vecattr;
}

//The following main method produces the similarity metric for the restaurants.
int main()
{
  ofstream outfile;
  outfile.open("similarity.txt");
  string line;
  vector<vector<double> >vecattr = getdouble("attrsimilarity.txt");
  vector<vector<double> >vecmenu = getdouble("menusimilarity.txt");
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