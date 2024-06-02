/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 01.03.2023
 */

// The library here is concretely set, students are not allowed to include any other libraries.

#include "study_in_pink2.h"
#include "study_in_pink2.cpp"
#include "extra_tc.h"

using namespace std;

int main(int argc, const char *argv[])
{
    // for (int i = 0; i < 381; i++)
    // {
    //     string temp = "/Users/honhattri/Downloads/SherlockHomes_Assignments/Part2/output1";
    //     temp += to_string(i + 1);
    //     temp += ".txt";
    //     ofstream outputFile(temp);
    //     if (!outputFile.is_open())
    //     {
    //         cout << "CANNOT WRITE FILE\n";
    //     }
    //     cout.rdbuf(outputFile.rdbuf());
    //     TestStudyInPink::test(i);
    // }
    TestStudyInPink::test(115);
    // StudyPinkProgram temp("sa_tc_02_config");
    // temp.run(true);
    return 0;
}