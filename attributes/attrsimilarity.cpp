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
//This class computes the metric for the attributes similarity

//This method transfers the string to double 
inline double strtodouble(string s)
{
  std::stringstream convert(s);
  double value;
  if(!(convert >> value))
    value = 0;
  return value;
}

int main()
{
  ifstream infile1, infile2;
  ofstream outfile;
  infile1.open("price.txt");
  infile2.open("ratings.txt");
  outfile.open("attrsimilarity.txt");
  string line;
  vector<double> vecprice;  //vecprice stores the price for each restaurant
  while(!infile1.eof()){
    getline(infile1, line);
    if(line.size() > 0){
      double value = strtodouble(line.substr(0));
      vecprice.push_back(value);
    }
  }
  infile1.close();

  vector<double> vecrating;  //vecrating stores the rating for each restaurant
  while(!infile2.eof()){
    getline(infile2, line);
    if(line.size() > 0){
      double value = strtodouble(line.substr(0));
      vecrating.push_back(value);
    }
  }
  infile2.close();

  vector<vector<double> > vecattr;
  //vecattr is the vector stoing the similarity metric for the attributes

  const int filenum = 100; 
  for(int i = 0; i != filenum; i++){
    vector<double> vec2;
    double diffprice, diffrating;
    for(int j = 0; j != filenum; j++){
      double sim = vecprice[i] * vecprice[j] + vecrating[i] * vecrating[j];
      double sim1 = sqrt(vecprice[i] * vecprice[i] + vecrating[i] * vecrating[i]);
      double sim2 = sqrt(vecprice[j] * vecprice[j] + vecrating[j] * vecrating[j]);
      double  d = sim/(sim1 * sim2);          
      vec2.push_back(d);
      outfile<<i+1<<"\t"<<j+1<<"\t"<<d<<endl;
    }
    vecattr.push_back(vec2);
  }
  outfile.close();
  return 0;
}