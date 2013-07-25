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

//This class produces a new file which is the attribute similarity metric
int main()
{
  ifstream infile1, infile2;
  ofstream outfile;
  infile1.open("price.txt");
  infile2.open("ratings.txt");
  outfile.open("attrsimilarity.txt");
  string line;
  int fileline = 0;
  while(!infile1.eof())
  {
    getline(infile1, line);
    ++fileline;
  }
  fileline--;
  infile1.close();
  infile1.open("price.txt");
  int mark = 0;
  vector<double> vecprice;
  for(int mark=0; mark!=fileline; mark++){
    getline(infile1, line);
    std::stringstream convert(line.substr(0));
    double value1;
    if(!(convert >> value1))
      value1 = 0;
    vecprice.push_back(value1);
  }
  infile1.close();
  vector<double> vecrating;
  for(int mark=0; mark!=fileline; mark++){
    getline(infile2, line);
    std::stringstream convert2(line.substr(0));
    double value2;
    if(!(convert2 >> value2))
      value2 = 0;
    vecrating.push_back(value2);
    cout<<value2<<endl;
  }
  infile2.close();
  cout<<vecprice[0]<<"\t"<<vecrating[0]<<endl;
  vector<vector<double> > vecattr;
  //sum(q,d) = v(q) * v(d) / |v(q)|*|v(d)|
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