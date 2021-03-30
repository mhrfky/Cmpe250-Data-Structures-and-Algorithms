#include <iostream>
#include <fstream>
#include <queue>
#include <cassert>
#include <utility>
#include <tuple>

using namespace std;

// max num of passengers
const int maxP = 5000;
ofstream myfile;
// number of cases we have
const int nCases = 8;

int P, L, S;

struct passenger {
    // we'll need that
    int id;

    // we're reading those things
    int arrive_at;
    int board_at;

    int luggage_time;
    int security_time;

    bool is_vip;
    bool luggageFree;

};

enum event_type {
    arriving,
    luggageSuccess,
    yallah
};

// renaming for convenience
// (time, id, type) tuple
typedef tuple<int, int, event_type> tiie;

struct typeSort{
    bool operator()(const tiie& a,const tiie& b){
        if(get<0>(a)!=get<0>(b))return get<0>(a)<get<0>(b);
        else if(get<2>(a)!=get<2>(b))return get<2>(a)<get<2>(b);
        else                             return get<1>(a)>get<1>(b);
    }


};

// only holds the read stuff, is not used during the actual execution
passenger passengers[maxP + 1];

// holds a pair of (arrival_time, passenger)
// the time is negative so we can use this as a min queue
// (there's a more 'proper' way but i don't exactly remember what it was)

// the queue is cleared and regenearated (with the new times)
// after each 'case'.
priority_queue<tiie,vector<tiie>,typeSort> Q;

void add_event(int time, int id, event_type type) {
    Q.push(make_tuple(time, id, type));
}

// taking a constant reference just for micro-optimization reasons
// (can't help it)
// doesn't return anything, just populates the passengers array
void read(const string& filename) {
    ifstream in(filename);

    in >> P >> L >> S;

    for(int i=0; i<P; i++) {
        passengers[i].id = i;

        in >> passengers[i].arrive_at >> passengers[i].board_at >>
           passengers[i].luggage_time >> passengers[i].security_time;

        char vipchar, luggagechar;
        in >> vipchar >> luggagechar;

        passengers[i].is_vip = (vipchar == 'V');
        passengers[i].luggageFree = (luggagechar == 'N');
    }

    in.close();
}

void write(const string& filename) {
    ofstream out(filename);

    out.close();
}
struct nofirstfly{
    bool operator() (passenger a, passenger b) {
        return a.arrive_at>b.arrive_at;

    }
};
struct firsttofly {
    bool operator()(const passenger& p1,const passenger& p2) {
        if(p1.board_at == p2.board_at) return p1.arrive_at>p2.arrive_at;
        else  return p1.board_at > p2.board_at;
    }

};

void simulate_cases(int cases) {
    for(int i = 0;i<P;i++){
        add_event(-passengers[i].arrive_at,i,arriving);
    }
    int failCount=0;
    double timeAVG=0;

    priority_queue<passenger, vector<passenger>, nofirstfly> luggageQ;
    queue<passenger> securityQ;


    int time = 0;
    while(!Q.empty()) {

        tiie evt = Q.top();
        Q.pop();
        time = get<0>(evt);
        if (get<2>(evt) == arriving) {
            luggageQ.push(passengers[get<1>(evt)]);
            if (L != 0 && !luggageQ.empty()) {
                L--;

                passenger p = luggageQ.top();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);


            }
        } else if (get<2>(evt) == luggageSuccess) {
            L++;
            if (!luggageQ.empty()) {
                L--;
                passenger p = luggageQ.top();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);
            }

            securityQ.push(passengers[get<1>(evt)]);
            if (S != 0 && !securityQ.empty()) {
                S--;
                passenger p = securityQ.front();
                securityQ.pop();
                add_event(time - p.security_time, p.id, yallah);
            }
        } else {
            S++;
            if (!securityQ.empty()) {
                S--;
                passenger p = securityQ.front();
                securityQ.pop();
                add_event(time - p.security_time, p.id, yallah);
            }
            failCount+= passengers[get<1>(evt)].board_at<(-time);
            timeAVG += (-passengers[get<1>(evt)].arrive_at-time);
        }


    }
    myfile<<timeAVG/P<<" " << failCount<<endl;

}
void simulatecase2(){
    for(int i = 0;i<P;i++){
        add_event(-passengers[i].arrive_at,i,arriving);
    }
    int failCount=0;
    double timeAVG=0;

    priority_queue<passenger, vector<passenger>, firsttofly> luggageQ;
    priority_queue<passenger, vector<passenger>, firsttofly> securityQ;


    int time = 0;
    while(!Q.empty()) {

        tiie evt = Q.top();
        Q.pop();
        time = get<0>(evt);
        if (get<2>(evt) == arriving) {
            luggageQ.push(passengers[get<1>(evt)]);
            if (L != 0 && !luggageQ.empty()) {
                L--;

                passenger p = luggageQ.top();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);


            }
        } else if (get<2>(evt) == luggageSuccess) {
            L++;
            if (!luggageQ.empty()) {
                L--;
                passenger p = luggageQ.top();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);
            }

            securityQ.push(passengers[get<1>(evt)]);
            if (S != 0 && !securityQ.empty()) {
                S--;
                passenger p = securityQ.top();
                securityQ.pop();
                add_event(time - p.security_time, p.id, yallah);
            }
        } else {
            S++;
            if (!securityQ.empty()) {
                S--;
                passenger p = securityQ.top();
                securityQ.pop();
                add_event(time - p.security_time, p.id, yallah);
            }
            failCount+= passengers[get<1>(evt)].board_at<(-time);
            timeAVG += (-passengers[get<1>(evt)].arrive_at-time);
        }


    }
    myfile<<timeAVG/P<<" " << failCount<<endl;
}
void simulatecase3() {
    for(int i = 0;i<P;i++){
        add_event(-passengers[i].arrive_at,i,arriving);
    }
    int failCount=0;
    double timeAVG=0;

    queue<passenger> luggageQ;
    queue<passenger> securityQ;


    int time = 0;
    while(!Q.empty()) {

        tiie evt = Q.top();
        Q.pop();
        time = get<0>(evt);
        bool vip = passengers[get<1>(evt)].is_vip;
        if (get<2>(evt) == arriving) {
            luggageQ.push(passengers[get<1>(evt)]);
            if (L != 0 && !luggageQ.empty()) {
                L--;

                passenger p = luggageQ.front();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);

            }
        } if (get<2>(evt) == luggageSuccess) {
            L++;
            if (!luggageQ.empty()) {
                L--;
                passenger p = luggageQ.front();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);
            }
            if(vip){get<2>(evt) = yallah;}
            else {
                securityQ.push(passengers[get<1>(evt)]);
                if (S != 0 && !securityQ.empty()) {
                    S--;
                    passenger p = securityQ.front();
                    securityQ.pop();
                    add_event(time - p.security_time, p.id, yallah);
                }
            }
        } if(get<2>(evt) ==yallah) {

            if(!vip) {
                S++;
                if (!securityQ.empty()) {
                    S--;
                    passenger p = securityQ.front();
                    securityQ.pop();
                    add_event(time - p.security_time, p.id, yallah);
                }
            }

            failCount+= passengers[get<1>(evt)].board_at<(-time);
            timeAVG += (-passengers[get<1>(evt)].arrive_at-time);
        }


    }
    myfile<<timeAVG/P<<" " << failCount<<endl;
}
void simulatecase4() {
    for(int i = 0;i<P;i++){
        add_event(-passengers[i].arrive_at,i,arriving);
    }
    int failCount=0;
    double timeAVG=0;

    priority_queue<passenger, vector<passenger>, firsttofly> luggageQ;
    priority_queue<passenger, vector<passenger>, firsttofly> securityQ;


    int time = 0;
    while(!Q.empty()) {

        tiie evt = Q.top();
        Q.pop();
        time = get<0>(evt);
        bool vip = passengers[get<1>(evt)].is_vip;
        if (get<2>(evt) == arriving) {
            luggageQ.push(passengers[get<1>(evt)]);
            if (L != 0 && !luggageQ.empty()) {
                L--;

                passenger p = luggageQ.top();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);

            }
        } if (get<2>(evt) == luggageSuccess) {
            L++;
            if (!luggageQ.empty()) {
                L--;
                passenger p = luggageQ.top();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);
            }
            if(vip){get<2>(evt) = yallah;}
            else {
                securityQ.push(passengers[get<1>(evt)]);
                if (S != 0 && !securityQ.empty()) {
                    S--;
                    passenger p = securityQ.top();
                    securityQ.pop();
                    add_event(time - p.security_time, p.id, yallah);
                }
            }
        } if(get<2>(evt) ==yallah) {

            if(!vip) {
                S++;
                if (!securityQ.empty()) {
                    S--;
                    passenger p = securityQ.top();
                    securityQ.pop();
                    add_event(time - p.security_time, p.id, yallah);
                }
            }

            failCount+= passengers[get<1>(evt)].board_at<(-time);
            timeAVG += (-passengers[get<1>(evt)].arrive_at-time);
        }


    }
    myfile<<timeAVG/P<<" " << failCount<<endl;
}
void simulatecase5() {
    for(int i = 0;i<P;i++){
        add_event(-passengers[i].arrive_at,i,arriving);
    }
    int failCount=0;
    double timeAVG=0;

    priority_queue<passenger, vector<passenger>, nofirstfly> luggageQ;
    queue<passenger> securityQ;


    int time = 0;
    while(!Q.empty()) {

        tiie evt = Q.top();
        Q.pop();
        time = get<0>(evt);
        bool luggageFree = passengers[get<1>(evt)].luggageFree;

        if (get<2>(evt) == arriving) {
            if(!luggageFree) {
                luggageQ.push(passengers[get<1>(evt)]);

            }else{
                get<2>(evt) = luggageSuccess;
            }
            if (L != 0 && !luggageQ.empty()) {
                L--;

                passenger p = luggageQ.top();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);


            }
        } if (get<2>(evt) == luggageSuccess) {
            if(luggageFree);
            else {
                L++;
                if (!luggageQ.empty()) {
                    L--;
                    passenger p = luggageQ.top();
                    luggageQ.pop();
                    add_event(time - p.luggage_time, p.id, luggageSuccess);
                }
            }

            securityQ.push(passengers[get<1>(evt)]);
            if (S != 0 && !securityQ.empty()) {
                S--;
                passenger p = securityQ.front();
                securityQ.pop();
                add_event(time - p.security_time, p.id, yallah);
            }
        } if(get<2>(evt) == yallah) {
            S++;
            if (!securityQ.empty()) {
                S--;
                passenger p = securityQ.front();
                securityQ.pop();
                add_event(time - p.security_time, p.id, yallah);
            }
            failCount+= passengers[get<1>(evt)].board_at<(-time);
            timeAVG += (-passengers[get<1>(evt)].arrive_at-time);
        }


    }
    myfile<<timeAVG/P<<" " << failCount<<endl;
}
void simulatecase6() {
    for(int i = 0;i<P;i++){
        add_event(-passengers[i].arrive_at,i,arriving);
    }
    int failCount=0;
    double timeAVG=0;

    priority_queue<passenger, vector<passenger>, firsttofly> luggageQ;
    priority_queue<passenger, vector<passenger>, firsttofly> securityQ;


    int time = 0;
    while(!Q.empty()) {

        tiie evt = Q.top();
        Q.pop();
        time = get<0>(evt);
        bool luggageFree = passengers[get<1>(evt)].luggageFree;

        if (get<2>(evt) == arriving) {
            if(!luggageFree) {
                luggageQ.push(passengers[get<1>(evt)]);

            }else{
                get<2>(evt) = luggageSuccess;
            }
            if (L != 0 && !luggageQ.empty()) {
                L--;

                passenger p = luggageQ.top();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);


            }
        } if (get<2>(evt) == luggageSuccess) {
            if(luggageFree);
            else {
                L++;
                if (!luggageQ.empty()) {
                    L--;
                    passenger p = luggageQ.top();
                    luggageQ.pop();
                    add_event(time - p.luggage_time, p.id, luggageSuccess);
                }
            }

            securityQ.push(passengers[get<1>(evt)]);
            if (S != 0 && !securityQ.empty()) {
                S--;
                passenger p = securityQ.top();
                securityQ.pop();
                add_event(time - p.security_time, p.id, yallah);
            }
        } if(get<2>(evt) == yallah) {
            S++;
            if (!securityQ.empty()) {
                S--;
                passenger p = securityQ.top();
                securityQ.pop();
                add_event(time - p.security_time, p.id, yallah);
            }
            failCount+= passengers[get<1>(evt)].board_at<(-time);
            timeAVG += (-passengers[get<1>(evt)].arrive_at-time);
        }


    }
    myfile<<timeAVG/P<<" " << failCount<<endl;
}

void simulatecase7() {

    for(int i = 0;i<P;i++){
        add_event(-passengers[i].arrive_at,i,arriving);
    }
    int failCount=0;
    double timeAVG=0;

    priority_queue<passenger, vector<passenger>, nofirstfly> luggageQ;
    queue<passenger> securityQ;


    int time = 0;
    while(!Q.empty()) {

        tiie evt = Q.top();
        Q.pop();
        bool luggageFree = passengers[get<1>(evt)].luggageFree;
        bool vip = passengers[get<1>(evt)].is_vip;
        time = get<0>(evt);
        if (get<2>(evt) == arriving) {
            if(luggageFree)get<2>(evt) = luggageSuccess;
            else {
                luggageQ.push(passengers[get<1>(evt)]);
            }
            if (L != 0 && !luggageQ.empty()) {
                L--;

                passenger p = luggageQ.top();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);


            }
        } if (get<2>(evt) == luggageSuccess) {
            if(!luggageFree) {
                L++;
                if (!luggageQ.empty()) {
                    L--;
                    passenger p = luggageQ.top();
                    luggageQ.pop();
                    add_event(time - p.luggage_time, p.id, luggageSuccess);
                }
            }
            if(vip) get<2>(evt)=yallah;
            else securityQ.push(passengers[get<1>(evt)]);
            if (S != 0 && !securityQ.empty()) {
                S--;
                passenger p = securityQ.front();
                securityQ.pop();
                add_event(time - p.security_time, p.id, yallah);
            }
        } if(get<2>(evt)==yallah) {
            if(!vip) {
                S++;
                if (!securityQ.empty()) {
                    S--;
                    passenger p = securityQ.front();
                    securityQ.pop();
                    add_event(time - p.security_time, p.id, yallah);
                }
            }
            failCount+= passengers[get<1>(evt)].board_at<(-time);
            timeAVG += (-passengers[get<1>(evt)].arrive_at-time);
        }


    }
    myfile<<timeAVG/P<<" " << failCount<<endl;






}
void simulatecase8() {

    for(int i = 0;i<P;i++){
        add_event(-passengers[i].arrive_at,i,arriving);
    }
    int failCount=0;
    double timeAVG=0;

    priority_queue<passenger, vector<passenger>, firsttofly> luggageQ;
    priority_queue<passenger, vector<passenger>, firsttofly> securityQ;


    int time = 0;
    while(!Q.empty()) {

        tiie evt = Q.top();
        Q.pop();
        bool luggageFree = passengers[get<1>(evt)].luggageFree;
        bool vip = passengers[get<1>(evt)].is_vip;
        time = get<0>(evt);
        if (get<2>(evt) == arriving) {
            if(luggageFree)get<2>(evt) = luggageSuccess;
            else {
                luggageQ.push(passengers[get<1>(evt)]);
            }
            if (L != 0 && !luggageQ.empty()) {
                L--;

                passenger p = luggageQ.top();
                luggageQ.pop();
                add_event(time - p.luggage_time, p.id, luggageSuccess);


            }
        } if (get<2>(evt) == luggageSuccess) {
            if(!luggageFree) {
                L++;
                if (!luggageQ.empty()) {
                    L--;
                    passenger p = luggageQ.top();
                    luggageQ.pop();
                    add_event(time - p.luggage_time, p.id, luggageSuccess);
                }
            }
            if(vip) get<2>(evt)=yallah;
            else securityQ.push(passengers[get<1>(evt)]);
            if (S != 0 && !securityQ.empty()) {
                S--;
                passenger p = securityQ.top();
                securityQ.pop();
                add_event(time - p.security_time, p.id, yallah);
            }
        } if(get<2>(evt)==yallah) {
            if(!vip) {
                S++;
                if (!securityQ.empty()) {
                    S--;
                    passenger p = securityQ.top();
                    securityQ.pop();
                    add_event(time - p.security_time, p.id, yallah);
                }
            }
            failCount+= passengers[get<1>(evt)].board_at<(-time);
            timeAVG += (-passengers[get<1>(evt)].arrive_at-time);
        }


    }
    myfile<<timeAVG/P<<" " << failCount<<endl;






}

// add the current results to the accumulated results thing
void add_to_results(int num_case) {

}

int main(int argc, char** argv) {
    assert(argc >= 2);

    string infile = argv[1];


    read(infile);

    myfile.open (argv[2]);



    simulate_cases(0);
    simulatecase2();
    simulatecase3();
    simulatecase4();
    simulatecase5();
    simulatecase6();
    simulatecase7();
    simulatecase8();
    add_to_results(0);

    // clear the queue between steps
    Q = priority_queue<tiie,vector<tiie>,typeSort>();
    myfile.close();


    add_to_results(1);



    return 0;
}
