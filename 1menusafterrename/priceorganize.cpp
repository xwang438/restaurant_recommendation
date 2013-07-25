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

//This class produces a new file which is the normalized general price for each restaurant.
int main()
{
  string line;
  ofstream outfile;
  outfile.open("price.txt");
  vector<double> vecavgPrice; //this vector stores the average price for each restaurant
  const int filenum = 100;
  for(int num = 0; num < filenum; num ++){
    ifstream infile;
    std::stringstream ss;
    ss << num;
    string s = ss.str();
    infile.open((s+".txt").c_str());
    int ratenum=0;
    string previousline = "";
    vector<string> vecRate;
    int count1, count2;
    int linenum=0;
    while(!infile.eof())
    {
      getline(infile, line);
      ++linenum;
    }
    linenum --;
    infile.close();
    infile.open((s+".txt").c_str());
    vector<string> vecPrice;
    cout<<"number of lines:"<<linenum<<endl;
    int mark = 0;
    while(mark<linenum){
      getline(infile, line);
      int pos1, pos2;
      for(int pos1 = 0; pos1 != line.size(); pos1 ++){
        if(line.size() > 8 && line.substr(pos1, 5) == "price" && line.substr(pos1+7,1) == ":"){
          string price = line.substr(pos1+10, line.size() - pos1 - 13);
          vecPrice.push_back(price);
        }
      }
      mark++;
    }
    double total = 0;
    int size = 0;
    for(vector<int>::size_type i = 0; i != vecPrice.size(); i++){
      std::stringstream convert(vecPrice.at(i));
      double value;
      if(!(convert >> value))
        value = 0;
      total += value;
      size ++;
    }
    double avg = total/size;
    vecavgPrice.push_back(avg); 
    infile.close();
  }
  //normalize the price
  double total2 = 0;
  for(int i = 0; i != vecavgPrice.size(); i++)
    total2 += vecavgPrice.at(i) * vecavgPrice.at(i);
  total2 = sqrt(total2); 
  for(int i = 0; i != vecavgPrice.size(); i++){   
    vecavgPrice.at(i) = vecavgPrice.at(i)/total2;
    outfile<<vecavgPrice.at(i)<<endl;
  }
  outfile.close();
  return 0;
}