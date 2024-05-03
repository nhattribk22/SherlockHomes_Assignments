#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

class Robot : public MovingObject{
    protected:
        RobotType robot_type;
        long long NUM = INT_MAX; 
        BaseItem *items;
        Position intPos; // inital position of Robot
    public:
        string robotType[4] = {"C", "S", "W", "SW"};
        Robot(int index, const Position& int_pos, Map*map, string name)
        : MovingObject(index, int_pos, map, name ), items(items) {}
        void setRobotType(RobotType robot_type){
            this->robot_type = robot_type;
        }
        RobotType getRobotType(){
            return this->robot_type;
        }
        void setItems(BaseItem *items){
            this->items = items;
        }
        BaseItem *getItems(){
            return this->items;
        }
        ~Robot();
       
};
class RobotC : public Robot{

};
class RobotS : public Robot{

};
class RobotW : public Robot{

};
class RobotSW : public Robot{
  
};
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////