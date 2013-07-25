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

// Using Declarations
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

//This class produces a new file which is the nomalized ratings for each restaurant
int main()
{
  string line;
  ofstream outfile;
  outfile.open("ratings.txt");
  vector<double> vecRate;
  const int filenum = 100;
  for(int num = 0; num < filenum; num ++){
    ifstream infile;
    std::stringstream ss;
    ss << num;
    string s = ss.str();
    infile.open((s+".txt").c_str());
    int ratenum=0;
    string previousline = "";
    int count1, count2;
    int linenum=0;
    while(!infile.eof())
    {
      getline(infile, line);
      ++linenum;
    }
    linenum--;
    infile.close();
    infile.open((s+".txt").c_str());
    cout<<"number of lines:"<<linenum<<endl;
    int mark = 0;
    string rating, review_count;
    double value, value2;
    while(mark<linenum){
      getline(infile, line);
//      if(line.size() > 22) cout<<line.substr(22)<<endl;
      if(line.size() > 6 && line.substr(5,7) == "rating]"){
        rating = line.substr(16,3);
      }
      std::stringstream convert(rating);
      if(!(convert >> value))
        value = 0;
      if(line.size() > 18 && line.substr(5,12) == "review_count"){
        review_count = line.substr(22);
      }
      std::stringstream convert2(review_count);
      if(!(convert2 >> value2))
        value2 = 0;
      mark++;
    } 
    double rr = value * value2;
    vecRate.push_back(rr);   
    infile.close();
  }
  //normalize the ratings
  double total = 0;
  for(int i = 0; i != vecRate.size(); i++)
    total += vecRate.at(i) * vecRate.at(i);
  total = sqrt(total);
  for(int i = 0; i != vecRate.size(); i++){   
    vecRate.at(i) = vecRate.at(i)/total;
    outfile<<vecRate.at(i)<<endl;
  }
  outfile.close();
  return 0;
}