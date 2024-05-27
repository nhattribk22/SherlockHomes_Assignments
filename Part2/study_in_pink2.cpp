#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const Position Position::npos = Position(-1, -1);


// class RobotS : public Robot{
//     private:
//         Criminal * criminal;
//         Sherlock * sherlock;
//     public:
//         RobotS(int index, const Position& init_pos, Map*map, Criminal * criminal, Sherlock * sherlock)
//         : Robot(index, init_pos, map), criminal(criminal), sherlock(sherlock) {}
//         Position getNextPosition() override {
//             Position sherPos = sherlock->getCurrentPosition();
//             int dx = sherPos.getRow() - init_pos.getRow();
//         }
// };
// class RobotW : public Robot{
//     private:
//         Criminal * criminal;
//         Watson * watson;
//     public:
//         RobotW(int index, const Position& int_pos, Map*map, Criminal * criminal, Watson * watson)
//         : Robot(index, int_pos, map), criminal(criminal), watson(watson) {}
// };
// class RobotSW : public Robot{
//     private:
//         Criminal * criminal;
//         Sherlock * sherlock;
//         Watson * watson;
//     public:
//         RobotSW(int index, const Position& int_pos, Map*map, Criminal * criminal, Sherlock * sherlock, Watson * watson)
//         : Robot(index, int_pos, map), criminal(criminal), sherlock(sherlock), watson(watson) {}
// };  
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////