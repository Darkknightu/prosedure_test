//
// Created by Vince Tu on 2019/7/15.
//
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class CAnimal
{
public:
    CAnimal()
    {
        cout << "CAnimal()" << endl;
    }

    CAnimal(const CAnimal &other)
    {
        cout << "CAnimal(const CAnimal &other)" << endl;
    }

};

class CDog : public CAnimal
{
public:
    CDog(char* str):cdog(str)
    {
        cout << "CDog(str)" << endl;
    }

    CDog()
    {
        cout << "CDog()" << endl;
    }

    CDog(const CDog &other) : CAnimal(other)
    {
        cout << "CDog(const CDog &other)" << endl;
    }

    int TestDog(CDog cd){
        cout<<"TestDog"<<endl;
    }



public:
    CDog& operator=(const CDog &other)
    {
        CAnimal::operator=(other);
        cout << "CDog operator=" << endl;
        return *this;
    }

    char* cdog;
};

void testcb(){
    for (int i = 0; i <3 ; ++i) {
        for (int j = 0; j <4 ; ++j) {
            if(j!=2){
                cout<<"continue"<<j<<endl;
                continue;
            }
            cout<<"break"<<i<<endl;
            break;
        }
    }
}

vector<int> prisonAfterNDays(vector<int> cells, int N) {
    vector<int> tmp(8,0);
    int tc=0;
    for(int i=0;i<8;i++){
        if(cells[i]==1)
            tc^=1<<i;
    }
    map<int,int> seen;

    for(int i=0;i<N;i++){
        tc=(~(((tc&0b1111111)<<1)^(tc>>1)))&0b1111110;
        if(seen.find(tc)!=seen.end()){
            N=N%(i-seen.find(tc)->second);
            cout<<"test"<<endl;
            return prisonAfterNDays(cells,N);
        }
        seen.insert({tc,i});
        cout<<tc<<"  "<<i<<endl;
    }
    for(int i=0;i<8;i++){
        if((tc>>i)&1)
            tmp[i]=1;
    }
    return tmp;
}

//int main()
//{
////    const CDog dog("test");
////    CDog ndog;
////    CDog tdog="test";
////    tdog.TestDog("test");
////    testcb();
//
//    vector<int> test={1,1,0,1,1,0,1,1};
//    prisonAfterNDays(test,6);
//
//    return 0;
//}

