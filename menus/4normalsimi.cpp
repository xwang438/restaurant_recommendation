#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <ctime>
#include <sstream>
#include <set>

// Using Declarations
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

//This class produces a new file which contains the user ID and their corresponding rated movies based on ratings.dat
double docsimilarity(int doc1, int doc2)
{
  ifstream infile;
  ofstream outfile;
  infile.open("3_doc100afterlda.txt");
  string line;
  int fileline = 0;
  while(!infile.eof())
  {
    getline(infile, line);
    ++fileline;
  }
  fileline--;
  infile.close();
  cout<<"number of lines: "<<fileline<<endl;
  infile.open("3_doc100afterlda.txt");
  vector<vector<int> >document;
  int mark = 0;
  string previousline = "";
  for(int mark=0; mark!=fileline; mark++){
    getline(infile, line);
    if(line != previousline)
    {
      vector<int> cr;
      previousline = line;
      int pos1=0, pos2;
      int i=1;
      while(i<line.size()){
        if(line.at(i) == '\t'){
          pos2 = i;
          string temp = line.substr(pos1, pos2-pos1);
          std::stringstream convert(temp);
          int value;
          if(!(convert >> value))
            value = 0;
          cr.push_back(value);
          pos1 = pos2+1;
          i++;
        }
        else
          i++;
      }
      string temp = line.substr(pos1);
      std::stringstream convert(temp);
      int value;
      if(!(convert >> value))
        value = 0;
      cr.push_back(value);
      document.push_back(cr);
    }
  }
  vector<vector<double> > normalize;
  for(int i = 0; i != document.size(); i++){
    double sum = 0;
    for(int j = 1; j != document[i].size(); j++)
      sum += document[i].at(j) * document[i].at(j);
    sum = sqrt(sum);
    vector<double>vec1;
    for(int j = 1; j != document[i].size(); j++){   
      double norm = (double)document[i].at(j)/sum;
      vec1.push_back(norm);
    }
    normalize.push_back(vec1);
  }

//compute the similarity
  double sum1 = 0, sum2 = 0, sum = 0;
  for(int i = 0; i != normalize[doc1].size(); i++){
    sum1 += normalize[doc1].at(i) * normalize[doc1].at(i);
    sum2 += normalize[doc2].at(i) * normalize[doc2].at(i);
    sum += normalize[doc1].at(i) * normalize[doc2].at(i);
  }
  sum1 = sqrt(sum1);
  sum2 = sqrt(sum2);
  double simila = sum/(sum1 * sum2);
  return simila;
  infile.close();
}
//create the similarity metric for menus
int main(){
  ofstream outfile;
  outfile.open("menusimilarity.txt");
  vector<vector<double> > vecmenu;
  int docNum = 100;
  for(int i = 0; i != docNum; i++){
    vector<double> vec2;
    for(int j = 0; j != docNum; j++){
      double  d = docsimilarity(i, j);          
      vec2.push_back(d);
      outfile<<i+1<<"\t"<<j+1<<"\t"<<d<<endl;
    }
    vecmenu.push_back(vec2);
  }
  outfile.close();
  return 0;
}