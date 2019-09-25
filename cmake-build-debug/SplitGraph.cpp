//
// Created by Vince Tu on 2019/7/23.
//
#include <fstream>
#include <vector>
#include "iostream"

using namespace std;

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    v.clear();
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

int main(){
     string line;
     fstream file("graph.csv", std::ios::binary|ios::in);
     fstream fileout("graph.txt", std::ios::binary|ios::out);
     vector<string> elements;
     string name;
     string type;


     while(getline(file,line)){
         SplitString(line,elements,",");
         if(name!=elements[0]){
             fileout<<elements[0]<<endl;
             name=elements[0];
             type=elements[1];
            }
//         if(elements[2].size()>3){
//             if (elements[2].substr(elements[2].size()-3)==".SH"||elements[2].substr(elements[2].size()-3)==".SZ"){
//                 fileout<<elements[1]<<","<<elements[2]<<endl;
//             } else{
//                 fileout<<elements[1]<<","<<elements[3]<<endl;
//             }}
//         else{
//             fileout<<elements[1]<<","<<elements[3]<<endl;
//         }
     }
     fileout.close();
     file.close();
     return 0;
}