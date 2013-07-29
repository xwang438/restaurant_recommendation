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

//This method transfers a string to an integer
inline int strtoint(string s)
{
  std::stringstream convert(s);
  int value;
  if(!(convert >> value))
    value = 0;
  return value;
}
//This method normalizes the values in the input file, and computes the similarity between two docs based on the output of LDA
double docsimilarity(int doc1, int doc2)
{
  ifstream infile;
  infile.open("ldaoutput.txt");
  string line;

  //document is the vector storing the strings in the input file
  vector<vector<int> >document;
  while(!infile.eof())
  {
    getline(infile, line);
    if(line.size() > 0){
      vector<int> cr;
      int pos1=0, pos2;
      int i = 1;
      while(i<line.size()){
        if(line.at(i) == '\t'){
          pos2 = i;
          string temp = line.substr(pos1, pos2-pos1);
          int value = strtoint(temp);
          cr.push_back(value);
          pos1 = pos2+1;
          i++;
        }
        else
          i++;
      }
      string temp = line.substr(pos1);
      int value = strtoint(temp);
      cr.push_back(value);
      document.push_back(cr);
    }
  }
  infile.close();

  //normalize is a vector storing the normalized values in the input file.    
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
  docsimilarity(1,2);
  return 0;
}