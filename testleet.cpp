//
// Created by Vince Tu on 2019/7/22.
//

#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include "string"
#include "vector"
#include "map"
#include "set"

using namespace std;

class Solution {
public:
    vector<string> splitIpAddress(string s,int num,int bIndex,int eIndex){
        vector<string> tmp;
        vector<string> result;


        if(num<3){
            for(int i=bIndex;i<eIndex;i++){
                if(i-bIndex<3){
                    if(stol(s.substr(bIndex,i-bIndex+1))<256){
                        tmp=splitIpAddress(s,num+1,i+1,eIndex);
                        if(!tmp.empty()){
                            for(string str:tmp){
                                result.push_back(s.substr(bIndex,i-bIndex+1)+"."+str);
                            }
                        }
                    }
                }else{
                    return result;
                }
            }
            return result;
        }
        else{
            if(stol(s.substr(bIndex))<256){
                result.push_back(s.substr(bIndex));
                return result;
            }else{
                return result;
            }

        }

    }

    vector<string> restoreIpAddresses(string s) {
        int lth=s.size();
        vector<string> result;
        return splitIpAddress(s,0,0,lth);
    }

    double minAreaFreeRect(vector<vector<int>>& points) {
        map<string,vector<int>>mid;
        stringstream keys;
        string key;
        vector<int> value;
        vector<string> pro;

        for (int i = 0; i < points.size(); ++i) {
            for (int j = i+1; j < points.size(); ++j) {
                string key;
                stringstream keys;
                keys<<points[i][0]+points[j][0]<<","<<points[i][1]+points[j][1];
                keys>>key;
                value.push_back(i);
                value.push_back(j);
                auto tmp=mid.find(key);
                if(tmp!=mid.end()){
                    for (int k=0;k<tmp->second.size();k++){
                        value.push_back(tmp->second[k]);
                    }
                    mid.insert_or_assign(key,value);
                    pro.push_back(key);
                }else{
                    mid.insert(std::make_pair(key,value));
                }
                value.clear();
            }
        }

//        points[tmp->second[i]]
//        points[tmp->second[i+1]]
//        points[tmp->second[j]]
//        points[tmp->second[j+1]]

        double result=0;

        for (string str:pro) {
            auto tmp=mid.find(str);
            for (int i = 0; i <((tmp->second.size())) ; i+=2) {
                for (int j = i+2; j <(tmp->second.size()) ; j+=2) {
                    if(((points[tmp->second[j]][0]-points[tmp->second[i]][0])*(points[tmp->second[j+1]][0]-points[tmp->second[i]][0])+
                            (points[tmp->second[j]][1]-points[tmp->second[i]][1])*(points[tmp->second[j+1]][1]-points[tmp->second[i]][1]))){
                        continue;
                    }else{
                        if(result==0){
                            result=(std::max(abs(points[tmp->second[j]][0]-points[tmp->second[j+1]][0]),abs(points[tmp->second[i]][0]-points[tmp->second[i+1]][0]))*
                                    std::max(abs(points[tmp->second[j]][1]-points[tmp->second[j+1]][1]),abs(points[tmp->second[i]][1]-points[tmp->second[i+1]][1])))-
                                    abs(points[tmp->second[j]][0]-points[tmp->second[i]][0])*abs(points[tmp->second[j]][1]-points[tmp->second[i]][1])-
                                    abs(points[tmp->second[j+1]][0]-points[tmp->second[i]][0])*abs(points[tmp->second[j+1]][1]-points[tmp->second[i]][1]);

                        }
                        else{
                            result=std::min(result,(double)(std::max(abs(points[tmp->second[j]][0]-points[tmp->second[j+1]][0]),abs(points[tmp->second[i]][0]-points[tmp->second[i+1]][0]))*
                                                    std::max(abs(points[tmp->second[j]][1]-points[tmp->second[j+1]][1]),abs(points[tmp->second[i]][1]-points[tmp->second[i+1]][1])))-
                                                   abs(points[tmp->second[j]][0]-points[tmp->second[i]][0])*abs(points[tmp->second[j]][1]-points[tmp->second[i]][1])-
                                                   abs(points[tmp->second[j+1]][0]-points[tmp->second[i]][0])*abs(points[tmp->second[j+1]][1]-points[tmp->second[i]][1]));
                        }
                        cout<<points[tmp->second[j]][0]<<" "<<points[tmp->second[j]][1]<<endl;
                        cout<<points[tmp->second[j+1]][0]<<" "<<points[tmp->second[j+1]][1]<<endl;
                        cout<<points[tmp->second[i]][0]<<" "<<points[tmp->second[i]][1]<<endl;
                        cout<<points[tmp->second[i+1]][0]<<" "<<points[tmp->second[i+1]][1]<<endl;
                    }
                }
            }
        }
        return result;
    }

    int maxSumAfterPartitioning(vector<int>& A, int K) {
        int* results=new int[A.size()+1];
        for(int i=0;i<=A.size();i++){
            int tmp=0;
            if(i==0) results[0]=0;
            else{
                int maxval=A[i-1];
                for(int j=i-1;(j>=(i-K))&&j>=0;j--){
                    maxval=max(maxval,A[j]);
                    tmp=max(tmp,results[j]+(i-j)*maxval);
                    cout<<i<<" "<<j<<" "<<tmp<<" "<<maxval<<endl;
                    results[i]=tmp;
                }
            }

        }
        return results[A.size()];
        }

    int dynamic(vector<int>& coins,int* len,int amount){
        int tmp=INT_MAX;
        int tmp0;
        if(amount<0) return -1;
        if(amount==0) return 0;
        if(len[amount-1]!=0) return len[amount-1];
        for(int i:coins){
            if((tmp0=dynamic(coins,len,amount-i))>-1){
                cout<<amount<<" "<<i<<" "<<" "<<tmp0<<endl;
                tmp=min(tmp,tmp0+1);
            }
        }
        if(tmp==INT_MAX){
            len[amount-1]=-1;
            return -1;
        }
        len[amount-1]=tmp;
        return tmp;
    }

    int coinChange(vector<int>& coins, int amount) {
        if(amount==0) return 0;
        int* len=new int[amount];
        for(int i=0;i<amount;i++){
            len[i]=0;
        }
        int ans=dynamic(coins,len,amount);
        return ans;
    }

    void sort(vector<int>& arr,int b,int e){
        if(b==e) return;
        int tmp=arr[b];
        int swap;
        int i=b,j=e;
        while(i!=j){
            while(arr[i]<tmp) i++;
            while(arr[j]>tmp) j--;
            swap=arr[i];
            arr[i]=arr[j];
            arr[j]=swap;
        }
        if(b!=i)
        sort(arr,b,i-1);
        if(i!=e)
        sort(arr,i+1,e);
    }

/*入口函数，不能删除，因为在下方有调用*/
    vector < int > arraySort(vector < int > arr) {
        int len=arr.size();
        sort(arr,0,len-1);
        vector<int> ans(arr);
        return ans;
    }

    string char_count(string str) {
        vector<int> counts;
        vector<char> ind;
        char tmp=str[0];
        int count=1;
        for(int i=1;i<str.length();i++){
            if(str[i]==tmp){
                count++;
                continue;
            } else{
                counts.push_back(count);
                ind.push_back(tmp);
                tmp=str[i];
                count=1;
            }
        }
        counts.push_back(count);
        ind.push_back(tmp);

        char* c=new char[4*str.length()];
        c[0]='\0';
        for(int i=0;i<counts.size();i++){
            sprintf(c+strlen(c),"%x",counts[i]);
            sprintf(c+strlen(c),"%c",ind[i]);
        }
        cout<<c<<endl;
        string ans;
        return ans;
    }

    int longestArithSeqLength(vector<int>& A) {
        vector<map<int,int>> counts;
        counts.resize(A.size());
        int len=2;
        for(int i=0;i<A.size();i++){
            for(int j=i+1;j<A.size();j++){
                int sub=A[j]-A[i];
                counts[j][sub]=max(max(counts[j][sub],2),counts[i][sub]+1);
                len=max(len,counts[j][sub]);
                cout<<len<<" "<<sub<<" "<<i<<" "<<counts[i][sub]<<" "<<j<<" "<<counts[j][sub]<<endl;
            }
        }
        return len;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        int idx[s.size()];
        idx[0]=1;
        for(int i=0;i<s.size();i++){
            cout<<i<<endl;
            if(idx[i]==1)
                for(string str:wordDict){
                    if(s.substr(i,str.size())==str){
                        cout<<s.substr(i,str.size())<<" "<<str<<endl;
                        if((i+str.size())==s.size()) return true;
                        idx[i+str.size()]=1;
                    }
                }
        }
        return false;
    }


    };

//int main(){
////    long long i,j;
////    cin>>i;
////    cin>>j;
////    int tmp=j%i;
////    int rst=i;
////    bool flg=true;
////    while(tmp!=0){
////        if(flg){
////            rst=tmp;
////            tmp=i%tmp;
////            flg=false;
////        }else{
////            rst=tmp;
////            tmp=j%tmp;
////            flg=true;
////        }
////    }
////    cout<<rst;
//
//
////    int n;
////    cin>>n;
////    int tmp=0;
////    std::set<int> rst;
////    for(int i=0;i<n;i++){
////        int a,b;
////        cin>>a>>b;
////        if(a==1){
////            rst.insert(b);
////            for(int s:rst){
////                rst.insert(s|b);
////            }
////        }else{
////            if(rst.find(b)!=rst.end()){
////                cout<<"YES"<<endl;
////            }else{
////                cout<<"NO"<<endl;
////            }
////        }
////    }
////
////    int n;
////    cin>>n;
////    int *pi=new int[n];
//////    int pi[]={1,3,2,4,6,5};
////    int *pr=new int[n];
////    for (int i = 0; i < n; ++i) {
////        cin>>pi[i];
////    }
////
////    int *dp=new int[n*n];
////    for (int j = 0; j < n; ++j) {
////        int tmin=INT_MAX;
////        for (int i = j; i < n; ++i) {
////            if(j==0){
////                dp[i]=pi[i];
////                tmin=std::min(dp[i],tmin);
////            }else{
////                dp[j*n+i]=max(dp[(j-1)*n+i-1],pi[i]);
////                tmin=min(dp[j*n+i],tmin);}
////        }
////        pr[j]=tmin;
////
////    }
////
////    for (int k = 0; k < n; ++k) {
////        cout<<pr[k]<<" ";
////    }
//
//
//    string s="Order";
//    if(s.find(',') != string::npos)
//    cout<<"!?";
//    return 0;
//}