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
using namespace std;

typedef tuple<int, int, int, int, int> ijijw;
typedef tuple<int,int,int,int> srctosink;
struct typeSort{
    bool operator()(const ijijw& a,const ijijw& b){
        return get<4>(a)>get<4>(b);
    }
};
int rowSize;
int columnSize;
vector< ijijw> result;
priority_queue<ijijw,vector<ijijw>,typeSort> Q;
priority_queue<ijijw,vector<ijijw>,typeSort> Qresult;
struct position{
  int x=0;int y= 0;
    bool operator !=(const position& p_other){
        if(x!=p_other.x||y!=p_other.y){
            return true;
        }
        else return false;

    }

  bool operator ==(const position& p_other){
      if(x==p_other.x&&y==p_other.y){
          return true;
      }
      else return false;

  }
  position(int x,int y){
        this->x = x;
        this->y = y;
    }
    position(){}
};
struct subset{
    position parent;
    int rank;
    int weight;
    subset(){}
};
vector< vector<subset> > subseting;
vector< vector< list<position> > > tere;

position find(int x,int y){
    if(subseting[x][y].parent.x!=x || subseting[x][y].parent.y!=y)
        return find(subseting[x][y].parent.x,subseting[x][y].parent.y);

    else
        return     subseting[x][y].parent;
}
void unify(int x,int y,int xo,int yo){
    position xroot = find(x,y);
    position yroot =find(xo,yo);
    if(subseting[xroot.x][xroot.y].rank<subseting[yroot.x][yroot.y].rank){
        subseting[xroot.x][xroot.y].parent = yroot;
    }
    else if(subseting[xroot.x][xroot.y].rank>subseting[yroot.x][yroot.y].rank){
        subseting[yroot.x][yroot.y].parent = xroot;
    }
    else{
        subseting[yroot.x][yroot.y].parent = xroot;
        subseting[xroot.x][xroot.y].rank++;
    }


}

/*void findTheDad(int x,int y, int xo, int yo){
    if      (subseting[x][y].rank<subseting[xo][yo].rank) {
        findTheDad(subseting[x][y].parent.x,subseting[x][y].parent.y,xo,yo);

    }
    else if (subseting[x][y].rank>subseting[xo][yo].rank) {
        findTheDad(subseting[xo][yo].parent.x,subseting[xo][yo].parent.y,x,y);

    }
    else{

    }




}*/

struct tree{

    struct node{
        int x,y;
        int depth;
        int parentx,parenty;
        ijijw nerden;
        node(ijijw a){
            this->nerden = a;
            x=get<2>(nerden);
            y=get<3>(nerden);
            parentx=get<0>(nerden);
            parenty=get<1>(nerden);
        }
    };

    vector< vector<node> > treeMatrix;


};


int main(int argc, char** argv) {

    ofstream out(argv[2]);
    ifstream in(argv[1]);
    queue<int> *prevLine = new queue<int>();
    in>>rowSize>>columnSize;
   
    for(int i = 0;i<rowSize;i++){
        int temp = -1;
        for(int j=0;j<columnSize;j++){
            int height;
            in>>height;
            prevLine->push(height);

            if(j!=0){
                Q.push(make_tuple(i,j-1,i,j,abs(height-temp)));}
                if(i!=0){
                    Q.push(make_tuple(i-1,j,i,j,abs(prevLine->front()-height)));
                    prevLine->pop();
                }

            temp = height;

        }
    }
    int queries;
    in>>queries;
    vector< srctosink > listqu;
    for(int iga = 0;iga<queries; iga++){
        int x,y,xo,yo;
        in>>x>>y>>xo>>yo;
        x--;y--;xo--;yo--;
        listqu.push_back(make_tuple(x,y,xo,yo));
    }








    if(queries>1) {
        subseting.resize(rowSize);
        for (int i = 0; i < rowSize; i++) {
            subseting[i].resize(columnSize);

            for (int j = 0; j < columnSize; j++) {
                subseting[i][j].parent.x = i;
                subseting[i][j].parent.y = j;
                subseting[i][j].rank = 0;
            }
        }
        ///////////////////////////////////////////////////////////////
        int e = 0;
        while (e < rowSize * columnSize - 1) {
            ijijw mfker = Q.top();
            Q.pop();
            if (find(get<0>(mfker), get<1>(mfker)) != find(get<2>(mfker), get<3>(mfker))) {
                result.push_back(mfker);
                Qresult.push(mfker);
                unify(get<0>(mfker), get<1>(mfker), get<2>(mfker), get<3>(mfker));
                e++;
            }

        }
        ////////////////////////////////////////////////////////

        for (srctosink aaa : listqu) {
            for (int i = 0; i < rowSize; i++) {
                for (int j = 0; j < columnSize; j++) {
                    subseting[i][j].parent.x = i;
                    subseting[i][j].parent.y = j;
                    subseting[i][j].rank = 0;
                }
            }
            for(ijijw mfker : result) {
                    unify(get<0>(mfker), get<1>(mfker), get<2>(mfker), get<3>(mfker));
                if (find(get<0>(aaa), get<1>(aaa)) == find(get<2>(aaa), get<3>(aaa))) {
                    out<<get<4>(mfker)<<" ";
                    break;
                }
            }

        }

    }
    ////////////////////////////////////////////////////////////////
    else{


        subseting.resize(rowSize);
        for (int i = 0; i < rowSize; i++) {
            subseting[i].resize(columnSize);

            for (int j = 0; j < columnSize; j++) {
                subseting[i][j].parent.x = i;
                subseting[i][j].parent.y = j;
                subseting[i][j].rank = 0;
            }
        }
        srctosink aaa = listqu[0];
        int e = 0;
        while (e < rowSize * columnSize - 1) {
            ijijw mfker = Q.top();
            Q.pop();
            if (find(get<0>(mfker), get<1>(mfker)) != find(get<2>(mfker), get<3>(mfker))) {
                result.push_back(mfker);
                Qresult.push(mfker);
                unify(get<0>(mfker), get<1>(mfker), get<2>(mfker), get<3>(mfker));
                e++;
            }
            if (find(get<0>(aaa), get<1>(aaa)) == find(get<2>(aaa), get<3>(aaa))) {
               out<< get<4>(mfker)<<" ";
                break;
            }
        }
    }




    return 0;
}
