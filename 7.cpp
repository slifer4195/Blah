#include <iostream>
#include <thread>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include "Semaphore.h"
using namespace std;


int buffer = 0;
Semaphore A(0);
Semaphore B(0);
Semaphore C(1);
Semaphore mtx (1); // will use as mutex

void threadA() {
    bool run = true;
    while (run){
        C.P();
        mtx.P();
        cout << 'A' << endl;
        mtx.V();
        A.V();
        A.V(); 
    }
}

void threadB() {
    bool run = true;
    while (run){
        A.P();
        mtx.P();
        cout << 'B' << endl;
        buffer += 1;
        if (buffer == 2){
            buffer = 0;
            B.V();
        }
        mtx.V();
    }
}

void threadC() {
    bool run = true;
    while (run){
        B.P();
        mtx.P();
        cout << 'C' << endl;
        mtx.V();
        C.V();
    }
}


int main (){
	vector<thread> threadAvec;
	vector<thread> threadBvec;
    vector<thread> threadCvec;
    int i =0;
	while (i < 100){
        threadAvec.push_back(thread(threadA));
        threadBvec.push_back(thread(threadB));
        threadCvec.push_back(thread(threadC));
        i++;
    }
    int j = 0;
    while (j < 100){
        threadAvec[j].join();
        threadBvec[j].join();
        threadCvec[j].join();
        j++;
    }
}