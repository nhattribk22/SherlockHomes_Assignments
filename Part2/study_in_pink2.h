/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 02.02.2023
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class Robot;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class TestStudyInPink;

enum ItemType
{
    MAGIC_BOOK,
    ENERGY_DRINK,
    FIRST_AID,
    EXCEMPTION_CARD,
    PASSING_CARD
};
enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum RobotType
{
    C = 0,
    S,
    W,
    SW
};

class MapElement
{
protected:
    ElementType type;

public:
    MapElement(ElementType in_type) : type(in_type) {}
    virtual ~MapElement() {}
    virtual ElementType getType() const{ return type;}
};

class Path : public MapElement
{
public:
    Path() : MapElement(PATH){};
};

class Wall : public MapElement
{
public:
    Wall() : MapElement(WALL){};
};

class FakeWall : public MapElement
{
private:
    int exp_req;

public:
    FakeWall(int exp_req) : MapElement(FAKE_WALL), exp_req(exp_req){};
    int getExpReq() const
    {
        return exp_req;
    }
};
class Position
{
private:
    int r, c;

public:
    static const Position npos;
    Position(int r = 0, int c = 0) : r(r), c(c){}

    Position(const string &str_pos)
    {
        int index = str_pos.find(",");
        r = stoi(str_pos.substr(1, index - 1));
        c = stoi(str_pos.substr(index + 1, str_pos.length() - index - 2));
    }

    int getRow() const
    {
        return r;
    }
    int getCol() const
    {
        return c;
    }
    void setRow(int r)
    {
        this->r = r;
    }
    void setCol(int c)
    {
        this->c = c;
    }

    string str() const
    {
        return "(" + to_string(r) + "," + to_string(c) + ")";
    }
    int getExpReq() const
    {
        return (r * 257 + c * 139 + 89) % 900 + 1;
    }
    bool isEqual(const Position pos)
    {
        return this->c == pos.c && this->r == pos.r;
    }
    bool isEqual(int in_r, int in_c) const
    {
        return r == in_r && c == in_c;
    }
};
class Map
{
private:
    int num_rows, num_cols;
    MapElement ***map;
public:
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls) : num_rows(num_rows), num_cols(num_cols)
    {
        // Khởi tạo Path
        map = new MapElement **[num_rows];
        for (int i = 0; i < num_rows; i++)
        {
            map[i] = new MapElement *[num_cols];
            for (int j = 0; j < num_cols; j++)
            {
                map[i][j] = new Path();
            }
        }
        // KHởi tạo Walls
        for (int i = 0; i < num_walls; i++)
        {
            int row = array_walls[i].getRow();
            int col = array_walls[i].getCol();
            delete map[row][col];
            map[row][col] = new Wall();
        }
        // Khởi tạo FakeWalls
        for (int i = 0; i < num_fake_walls; i++)
        {
            int row = array_fake_walls[i].getRow();
            int col = array_fake_walls[i].getCol();
            int expReq = array_fake_walls[i].getExpReq();
            delete map[row][col];
            map[row][col] = new FakeWall(expReq);
        }
    }
    ~Map()
    {
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
    }
    MapElement ***getMap() const
    {
        return map;
    }
    bool isValid(const Position &pos, MovingObject *mv_obj) const{
        int r = pos.getRow();
        int c = pos.getCol();
        if (r < 0 || r >= num_rows || c < 0 || c >= num_cols)
        {
            return false;
        }
        return map[r][c]->getType() == PATH;
    }
};


class MovingObject
{
protected:
    int index;
    Position pos;
    Map *map;
    string name;
public:
    static const Position npos; 
    MovingObject(int index, const Position pos, Map *map, const string &name = ""): index(index), pos(pos), map(map), name(name) {}
    virtual ~MovingObject() {}
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const
    {
        return pos;
    }
    virtual void move() = 0;
    virtual string str() const = 0;
    
};
const Position Position::npos = Position(-1,-1);
const Position MovingObject::npos = Position::npos; 

class Character : public MovingObject {
public:
    Character(int index, const Position pos, Map * map, const string & name) : MovingObject(index, pos, map, name) {}    
    //int temp_moving = 0;
};

class Sherlock : public Character /* TODO */
{
private:
    // TODO
    string moving_rule;
    int hp;
    int exp;
    size_t current_rule_index;

public:
    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
        : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(init_hp > 500 ? 500 : init_hp), exp(init_exp > 900 ? 900 : init_exp), current_rule_index(0){};
    
    Position getNextPosition() override
    {
        if (hp == 0 || exp == 0)
        {
            return this->npos;
        }
        char move = moving_rule[current_rule_index];
        Position current = getCurrentPosition();
        int r = current.getRow();
        int c = current.getCol();
        switch (move)
        {
        case 'U': // Up
            r--;
            break;
        case 'D': // Down
            r++;
            break;
        case 'L': // Left
            c--;
            break;
        case 'R': // Right
            c++;
            break;
        default:
            return this->npos;
        }
        // Update the rule index for the next move
        current_rule_index = (current_rule_index + 1) % moving_rule.length();
        Position new_pos(r, c);
        return map->isValid(new_pos, this) ? new_pos : this->npos;
    }
    void move() override
    {
        Position new_pos = getNextPosition();
        if (!new_pos.isEqual(this->npos))
        {
            pos = new_pos;
        }
    }
    string str() const override
    {
        return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
    }
    ~Sherlock() {}
};

class Watson : public Character /* TODO */
{
private:
    // TODO
    string moving_rule;
    int hp;
    int exp;
    size_t current_rule_index;
public:
    Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
        : Character(index, init_pos, map, "Waston"), moving_rule(moving_rule), hp(init_hp > 500 ? 500 : init_hp), exp(init_exp > 900 ? 900 : init_exp), current_rule_index(0){};
    // ...
    // getNextPosition
    Position getNextPosition() override
    {
        if (hp == 0 || exp == 0)
        {
            return Position::npos;
        }
        char move = moving_rule[current_rule_index];
        Position current = getCurrentPosition();
        int r = current.getRow();
        int c = current.getCol();
        switch (move)
        {
        case 'U': // Up
            r--;
            break;
        case 'D': // Down
            r++;
            break;
        case 'L': // Left
            c--;
            break;
        case 'R': // Right
            c++;
            break;
        default:
            return Position::npos;
        }
        // Update the rule index for the next move
        current_rule_index = (current_rule_index + 1) % moving_rule.length();
        Position new_pos(r, c);
        return map->isValid(new_pos, this) ? new_pos : Position::npos;
    }
    // move
    void move() override
    {
        Position new_pos = getNextPosition();
        if (!new_pos.isEqual(Position::npos))
        {
            pos = new_pos;
        }
    }
    // str
    string str() const override
    {
        return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
    }
    ~Watson() {}
};
class Criminal : public MovingObject
{
private:
    Sherlock *sherlock;
    Watson *watson;

public:
    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson)
        : MovingObject(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson){};
    int MahattanDistance(Position pos1, Position pos2)
    {
        return abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
    }
    // getNextPosition
    Position getNextPosition() override
    {
        Position validPositions[4];
        validPositions[0] = Position(pos.getRow() - 1, pos.getCol()); // UP
        validPositions[1] = Position(pos.getRow(), pos.getCol() - 1); // LEFT
        validPositions[2] = Position(pos.getRow() + 1, pos.getCol()); // DOWN
        validPositions[3] = Position(pos.getRow(), pos.getCol() + 1); // RIGHT

        // Tìm vị trí hợp lệ
        int maxDistance = INT_MIN;
        Position nextPos = Position::npos;
        for (int i = 0; i < 4; i++)
        {
            if (map->isValid(validPositions[i], this))
            {
                int distanceToSherlock = MahattanDistance(validPositions[i], sherlock->getCurrentPosition());
                int distanceToWatson = MahattanDistance(validPositions[i], watson->getCurrentPosition());
                int minDistanceToTarget = distanceToSherlock + distanceToWatson;
                if (minDistanceToTarget > maxDistance)
                {
                    maxDistance = minDistanceToTarget;
                    nextPos = validPositions[i];
                }
            }
        }
        return nextPos;
    }
    // move
    void move() override
    {
        Position new_pos = getNextPosition();
        if (!new_pos.isEqual(Position::npos))
        {
            pos = new_pos;
        }
    }
    // str
    string str() const override
    {
        return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
    }
    // ...
    ~Criminal() {}
};

class ArrayMovingObject
{
private:
    // TODO
    MovingObject **arr;
    int count;    // current number of elements in the array
    int capacity; // maximum number of elements in the array
public:
    ArrayMovingObject(int capacity) : capacity(capacity) {}

    ~ArrayMovingObject();
    bool isFull() const
    {
        if (count == capacity)
        {
            return true;
        }
        return false;
    }
    bool add(MovingObject *mv_obj)
    {
        if (count < capacity)
        {
            arr[count] = mv_obj;
            count++;
            return true;
        }
        return false;
    }
    MovingObject *get(int index) const
    {
        if (index >= 0 && index < count)
        {
            return arr[index];
        }
        return nullptr;
    }
    // return current number of elements in the array
    int size() const
    {
        return count;
    }
    string str() const
    {
        string result = "ArrayMovingObject [ count =" + to_string(count) + "; capacity =" + to_string(capacity) + ";";
        for (int i = 0; i < count; i++)
        {
            result += " " + arr[i]->str() + ";";
        }
        result += "]";
        return result;
    }
};

class Configuration
{
    friend class StudyPinkProgram;

private:
    // TODO
    int map_num_rows, map_num_cols; // Number of rows and columns of the map
    int max_num_moving_objects;     // max elements in the array of moving objects
    int num_walls;                  // Number of walls
    Position *array_walls;          // Array of wall positions
    int num_fake_walls;             // Number of fake walls
    Position *array_fake_walls;     // Array of fake wall positions
    string sherlock_moving_rule;    // Sherlock's moving rule
    Position sherlock_init_pos;     // Sherlock's initial position
    int sherlock_init_hp;           // Sherlock's initial HP
    int sherlock_init_exp;          // Sherlock's initial EXP
    string watson_moving_rule;      // Watson's moving rule
    Position watson_init_pos;       // Watson's initial position
    int watson_init_hp;             // Watson's initial HP
    int watson_init_exp;            // Watson's initial EXP
    Position criminal_init_pos;     // Criminal's initial position
    int num_steps;                  // Number of steps

public:
    Configuration(const string &filepath);
    ~Configuration();
    string str() const
    {
        string result = "Configuration[\n";
        result += "MAP_NUM_ROWS=" + to_string(map_num_rows) + "\n";
        result += "MAP_NUM_COLS=" + to_string(map_num_cols) + "\n";
        result += "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\n";
        result += "NUM_WALLS=" + to_string(num_walls) + "\n";

        result += "ARRAY_WALLS=[";
        for (int i = 0; i < num_walls; i++)
        {
            result += "(" + to_string(array_walls[i].getRow()) + "," + to_string(array_walls[i].getCol()) + ")";
            if (i < num_walls - 1)
                result += ";";
        }
        result += "]\n";

        result += "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + "\n";

        result += "ARRAY_FAKE_WALLS=[";
        for (int i = 0; i < num_fake_walls; i++)
        {
            result += "(" + to_string(array_fake_walls[i].getRow()) + "," + to_string(array_fake_walls[i].getCol()) + ")";
            if (i < num_fake_walls - 1)
                result += ";";
        }
        result += "]\n";

        result += "SHERLOCK_MOVING_RULE=" + sherlock_moving_rule + "\n";
        result += "SHERLOCK_INIT_POS=(" + to_string(sherlock_init_pos.getRow()) + "," + to_string(sherlock_init_pos.getCol()) + ")\n";
        result += "SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + "\n";
        result += "SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + "\n";
        result += "WATSON_MOVING_RULE=" + watson_moving_rule + "\n";
        result += "WATSON_INIT_POS=(" + to_string(watson_init_pos.getRow()) + "," + to_string(watson_init_pos.getCol()) + ")\n";
        result += "WATSON_INIT_HP=" + to_string(watson_init_hp) + "\n";
        result += "WATSON_INIT_EXP=" + to_string(watson_init_exp) + "\n";
        result += "CRIMINAL_INIT_POS=(" + to_string(criminal_init_pos.getRow()) + "," + to_string(criminal_init_pos.getCol()) + ")\n";
        result += "NUM_STEPS=" + to_string(num_steps) + "\n";
        result += "]\n";

        return result;
    }
};

// Robot, BaseItem, BaseBag,...

class StudyPinkProgram
{
private:
    // Sample attributes
    Configuration *config;

    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;

    Map *map;
    ArrayMovingObject *arr_mv_objs;

public:
    StudyPinkProgram(const string &config_file_path);

    bool isStop() const;

    void printResult() const
    {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Watson caught the criminal" << endl;
        }
        else
        {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const
    {
        cout << "Step: " << setw(4) << setfill('0') << si
             << "--"
             << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose)
    {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep)
        {
            for (int i = 0; i < arr_mv_objs->size(); ++i)
            {
                arr_mv_objs->get(i)->move();
                if (isStop())
                {
                    printStep(istep);
                    break;
                }
                if (verbose)
                {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};
class Robot : public MovingObject{
protected:
    RobotType robot_type;
    long long NUM = INT_MAX;
    BaseItem *items;
    Position intPos; // inital position of Robot
public:
    Robot(int index, const Position& init_pos, Map*map)
            : MovingObject(index, init_pos, map), items(items) {}
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
    void move() override { }
    string str() const override { return ""; }
    ~Robot(){}
};
class RobotC : public Robot {
private:
    Criminal *criminal;

public:
    RobotC(int index, const Position& init_pos, Map* map, Criminal* criminal)
            : Robot(index, init_pos, map), criminal(criminal) {
        setRobotType(RobotType::C);
    }
    Position getNextPosition() override {
        Position nextPos = criminal->getCurrentPosition();
        return nextPos;
    }

    ~RobotC() {}
};
class RobotS : public Robot {
private:
    Criminal *criminal;
    Sherlock *sherlock;
public:
    RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock)
            : Robot(index, init_pos, map), criminal(criminal), sherlock(sherlock) {
        setRobotType(RobotType::S);
    }
    Position getNextPosition() override {
        Position nextPos = criminal->getCurrentPosition();
        return nextPos;
    }

    ~RobotS() {}
};
class RobotW : public Robot {
private:
    Criminal *criminal;
    Watson *watson;
public:
    RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal, Watson* watson)
            : Robot(index, init_pos, map), criminal(criminal), watson(watson) {
        setRobotType(RobotType::W);
    }
    Position getNextPosition() override {
        Position nextPos = criminal->getCurrentPosition();
        return nextPos;
    }

    ~RobotW() {}
};
class RobotSW : public Robot {
private:
    Criminal *criminal;
    Watson *watson;
    Sherlock *sherlock;
public:
    RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson)
            : Robot(index, init_pos, map), criminal(criminal), sherlock(sherlock), watson(watson) {
        setRobotType(RobotType::SW);
    }
    Position getNextPosition() override {
        Position nextPos = criminal->getCurrentPosition();
        return nextPos;
    }

    ~RobotSW() {}
};
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
