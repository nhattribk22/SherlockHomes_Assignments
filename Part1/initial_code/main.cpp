/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "study_in_pink1.h"

using namespace std;

void sa_tc_01() {
    cout << "----- Sample Testcase 01 -----" << endl;
    string input_file("sa_tc_01_input");
    int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;
    if (!readFile(input_file, HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3)) {
        return;
    }
    cout << "HP1: "<< HP1 << ", HP2: " << HP2 <<", M1: "<< M1 << endl;
    cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", E1: " << E1 << endl;
    int result = firstMeet(EXP1, EXP2, E1);
    cout<< "---------------------------"<<endl;
    cout << "HP1: "<< HP1 << ", HP2: " << HP2 <<", M1: "<< M1 << endl;
    cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", result: " << result << endl;
    //cout << result << endl;
}

void sa_tc_02() {
    cout << endl;
    cout << "----- Sample Testcase 02 -----" << endl;
    string input_file("sa_tc_01_input");
    int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;
    if (!readFile(input_file, HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3)) {
        return;
    }

    cout << "HP1: "<< HP1 << ", HP2: " << HP2 <<", M1: "<< M1 << endl;
    cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", E2: " << E2 << endl;
    int result = traceLuggage(HP1, EXP1, M1, E2);
    cout<< "---------------------------"<<endl;
    cout << "HP1: "<< HP1 << ", HP2: " << HP2 <<", M1: "<< M1 << endl;
    cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", E2: " << E2 << ", result: " << result << endl;
    //cout << result;
}
void sa_tc_03() {
    cout << endl;
    cout << "----- Sample Testcase 03 -----" << endl;
    string input_file("sa_tc_01_input");
    int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;
    if (!readFile(input_file, HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3)) {
        return;
    }

    cout << "HP1: "<< HP1 << ", HP2: " << HP2 << endl;
    cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", E3: " << E3 << endl;
    int result = chaseTaxi(HP1, EXP1, HP2, EXP2, E3);
    cout<< "---------------------------"<<endl;
    cout << "HP1: "<< HP1 << ", HP2: " << HP2 << endl;
    cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", E3: " << E3 << ", result: " << result << endl;
    //cout << result;
}
int main(int argc, const char * argv[]) {
    sa_tc_01();
    sa_tc_02();
    sa_tc_03();
    return 0;
}