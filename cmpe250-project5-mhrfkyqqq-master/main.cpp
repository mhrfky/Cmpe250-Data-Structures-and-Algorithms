#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <queue>
#include <cassert>
#include <utility>
#include <tuple>
#include <list>
#include <set>
/* Following program is a C implementation of Rabin Karp
Algorithm given in the CLRS book */
#include<stdio.h>
#include<string.h>
#include <tgmath.h>

// d is the number of characters in the input alphabet
#define d 26
#define mod (int)1000000007



/* pat -> pattern
    txt -> text
    q -> A prime number
*/
using namespace std;
long long int length;
vector<long long int> adj[1005];
long long int hashvec[1005];
vector<long long int> dvector;
long long int pathCount = 0;
long long int answers[1005];


long long int numberOfWays(int k){
    if(k == length ) return 1;
   long long int asd = 0;
    if(answers[k]!=-1) return answers[k];
    for(int l : adj[k]){
       asd += numberOfWays(l);
       asd=asd%mod;
    }
    return answers[k]=asd;
}
long long int findHash(int begin,int end){
    if(begin==0){
        return hashvec[end];
    }
    else{
        return (((hashvec[end]-hashvec[begin-1]*dvector[end-begin+1])%mod)+mod)%mod;
    }
}
long long int myHash(string& s){
    long long int h = 0;
    for (int i = 0; i < s.length(); ++i) {
        h = (h*d+(s[i])-96)%mod;
        if(h<0){
            h += mod;
        }
    }
    return h;
}
/* Driver program to test above function */
int main(int argc, char** argv)
{
    for(int i = 0;i<1005;i++){
        answers[i] = -1;
    }
    ofstream out(argv[2]);
    ifstream in(argv[1]);
    string theLine;
    long long int count;
    in>>theLine>>count;

    length = theLine.length();





    for (int j = 0; j < theLine.length(); ++j) {
        if(j == 0){
            hashvec[j] = (theLine[j]-96)%mod;
        } else{
            hashvec[j] = (hashvec[j-1]*d+(theLine[j]-96))%mod;
        }
        if(hashvec[j]<0){
            hashvec[j] += d;
        }
    }




    dvector.push_back(1);
    for(int i =1;i<=theLine.length();i++){
        int a = (dvector[i-1]*d)%mod;
        if(a<0)a+=mod;
        dvector.push_back(a);
    }

    
        string aaa;
    for(int i = 0; i<count;i++){
        in>>aaa;
        int WordHash = 0;


            WordHash = myHash(aaa);


        for(int j = 0;j< theLine.length()-aaa.length()+1;j++){

            if(WordHash==findHash(j, j+aaa.length()-1)){
                adj[j].push_back(j+aaa.length());

            }

        }

    }
    out<<numberOfWays(0);
    return 0;

}