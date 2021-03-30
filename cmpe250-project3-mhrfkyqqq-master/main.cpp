

#include <iostream>
#include <fstream>
#include <cassert>
#include <utility>
#include<iostream>
#include <list>
#include <stack>
#include <vector>
#include <set>
#include <array>


using namespace std;


class Graph
{
    int *disc ;
    int *low;
    bool *stackMember ;

    int sccCount=0;
    
    void SCCUtil(int u,
                 stack<int> *st);
public:
    list<int> *adj;   
    int V;   
    int* sccBool;
    int* scclist;

    Graph(int V);  
    void addEdge(int v, int w);  
    void SCC();    

};

Graph::Graph(int V)
{
    disc = new int[V];
    stackMember = new bool[V];
    low = new int[V];
    this->V = V;
    adj = new list<int>[V];
    scclist = new int[V];
    for (int i = 0; i < V; i++)
    {
        disc[i] =-1;
        low[i] =-1;
        stackMember[i] = false;
    }

}

void Graph::addEdge(int v, int w)
{
    adj[w-1].push_back(v);

}

void Graph::SCCUtil(int u,  stack<int> *st)
{
    static int time = 0;


     
    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;

  
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;   

        if (disc[v] == -1)
        {
            SCCUtil(v, st);

         
            low[u]  = min(low[u], low[v]);
        }

            
        else if (stackMember[v])
            low[u]  = min(low[u], disc[v]);
    }

    
    int w = 0;  
    if (low[u] == disc[u])
    {

        while (st->top() != u)
        {
            w = (int) st->top();

            stackMember[w] = false;
            scclist[w]=sccCount;

            st->pop();
        }
        w = (int) st->top();

        scclist[w]=sccCount;

        stackMember[w] = false;
        st->pop();
        sccCount++;

    }

}


void Graph::SCC()
{

    stack<int> *st = new stack<int>();



    for (int i = 0; i < V; i++)
        if (disc[i] == -1)
            SCCUtil(i,  st);


     sccBool = new int[sccCount];
     for(int i =0;i<sccCount;i++){
         sccBool[i] = 0;
     }
}



Graph read(const string& filename,const string& outname) {
    ifstream in(filename);
    ofstream out(outname);
    int ii;
    in >> ii;
    Graph gg(ii);

    for(int i=0; i<ii; i++) {
        int k;
        in >> k;
        for (int j = 0; j < k; j++) {
            int a;
            in >> a;
            gg.addEdge(i, a);
        }
    }


    gg.SCC();


    


    int cont = 0;
    for(int i= 0;i<gg.V;i++){
        if(gg.sccBool[gg.scclist[i]]!=-1){

            //
            for(int j :gg.adj[i]){
                if(gg.scclist[i]!=gg.scclist[j])
                { ; gg.sccBool[gg.scclist[i]] = -1;    break;   }}
            //

        }

    }
    list<int>* keyhs= new list<int>();
    for(int i= 0;i<gg.V;i++){
        if(gg.sccBool[gg.scclist[i]]!=-1){
            //
            cont++;

            keyhs->push_back(i);
            gg.sccBool[gg.scclist[i]]=-1;
        }

    }
    out<<cont;
    for(int i : *keyhs){
        out<<" "<<i+1;
    }



    

}

int main(int argc, char** argv)
{
    string infile = argv[1];
    string outfile=argv[2];

    read(infile,outfile);
    







    return 0;
} 
