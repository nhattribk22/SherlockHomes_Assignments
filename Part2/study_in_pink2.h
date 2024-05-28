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

bool isCharacter(char c);
bool isNumber(char c) ;
int sumChar(long long &num);
long long mainNum(long long num);

class MapElement
{
protected:
    ElementType type;

public:
    MapElement(ElementType in_type) : type(in_type) {}
    virtual ~MapElement() {}
    virtual ElementType getType() const { return type; }
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
    int getReqExp() const
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
    Position(int r = 0, int c = 0) : r(r), c(c) {}

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
    bool isValid(const Position &pos, MovingObject *mv_obj) const
    {
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
    Position init;
    Map *map;
    string name;

public:
    // static const Position npos;
    MovingObject(int index, const Position pos, Map *map, const string &name = "") : index(index), pos(pos), map(map), name(name), init(pos) {}
    virtual ~MovingObject() {}
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const
    {
        return pos;
    }
    virtual void move() = 0;
    virtual string str() const = 0;
    Position getInit() const
    {
        return init;
    }
    string getName(){
        return name;
    }
};
// const Position MovingObject::npos = Position::npos;

class Character : public MovingObject
{
public:
    Character(int index, const Position pos, Map *map, const string &name) : MovingObject(index, pos, map, name) {}
    // int temp_moving = 0;
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
    void move() override
    {
        Position new_pos = getNextPosition();
        if (!new_pos.isEqual(Position::npos))
        {
            pos = new_pos;
        }
    }
    string str() const override
    {
        return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
    }
    void setInitHp(int hp)
    {
        if(hp > 500){
            this->hp = 500;
        }
        else if(hp < 0){
            this->hp = 0;
        }
        else 
            this->hp = hp;
    }
    void setInitExp(int exp)
    {
        if(exp > 900){
            this->exp = 900;
        }
        else if(exp < 0){
            this->exp = 0;
        }
        else 
            this->exp = exp;
    }
    int getInitHp() const
    {
        return hp;
    }
    int getInitExp() const
    {
        return exp;
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
    void setInitHp(int hp)
    {
        if(hp > 500){
            this->hp = 500;
        }
        else if(hp < 0){
            this->hp = 0;
        }
        else 
            this->hp = hp;
    }
    void setInitExp(int exp)
    {
        if(exp > 900){
            this->exp = 900;
        }
        else if(exp < 0){
            this->exp = 0;
        }
        else 
            this->exp = exp;
    }
    int getInitHp() const
    {
        return hp;
    }
    int getInitExp() const
    {
        return exp;
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
    ArrayMovingObject(int capacity) : capacity(capacity), count(0)
    {
        arr = new MovingObject *[capacity];
    }

    bool isFull() const
    {
        return count == capacity;
    }
    bool add(MovingObject *mv_obj)
    {
        if (!isFull())
        {
            arr[count++] = mv_obj;
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
    ~ArrayMovingObject()
    {
        // for (int i = 0; i < count; ++i)
        // {
        //     delete arr[i];
        // }
        delete[] arr;
    }
};

class Configuration
{
private:
    // Các thuộc tính riêng tư
    int map_num_rows, map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position *array_walls;
    int num_fake_walls;
    Position *array_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;

    void parseArrayPositions(const string &str, Position *&array, int &count)
    {
        count = 0;
        stringstream ss(str);
        char c;
        while (ss >> c)
        {
            if (c == '(')
            {
                while (ss >> c)
                {
                    if (c == ')')
                    {
                        count++;
                        break;
                    }
                }
            }
        }
        array = new Position[count];
        ss.clear();
        ss.seekg(0);
        ss >> c; // Skip [
        for (int i = 0; i < count; ++i)
        {
            ss >> c; // Skip '('
            int r = 0, p = 0;
            while (ss >> c)
            {
                if ((int)(c - '0') >= 0 && (int)(c - '0') <= 9)
                    r = r * 10 + (int)(c - '0');
                else
                {
                    break;
                }
            }
            while (ss >> c)
            {
                if ((int)(c - '0') >= 0 && (int)(c - '0') <= 9)
                    p = p * 10 + (int)(c - '0');
                else
                {
                    break;
                }
            }
            array[i] = Position(r, p);
            ss >> c; // Skip ';'
        }
    }

public:
    Configuration(const string &filepath)
    {
        ifstream file(filepath);
        if (!file.is_open())
        {
            throw runtime_error("Could not open file");
        }

        string line;
        while (getline(file, line))
        {
            if (line.find("MAP_NUM_ROWS=") == 0)
            {
                map_num_rows = stoi(line.substr(strlen("MAP_NUM_ROWS=")));
            }
            else if (line.find("MAP_NUM_COLS=") == 0)
            {
                map_num_cols = stoi(line.substr(strlen("MAP_NUM_COLS=")));
            }
            else if (line.find("MAX_NUM_MOVING_OBJECTS=") == 0)
            {
                max_num_moving_objects = stoi(line.substr(strlen("MAX_NUM_MOVING_OBJECTS=")));
            }
            else if (line.find("ARRAY_WALLS=") == 0)
            {
                parseArrayPositions(line.substr(strlen("ARRAY_WALLS=")), array_walls, num_walls);
            }
            else if (line.find("ARRAY_FAKE_WALLS=") == 0)
            {
                parseArrayPositions(line.substr(strlen("ARRAY_FAKE_WALLS=")), array_fake_walls, num_fake_walls);
            }
            else if (line.find("SHERLOCK_MOVING_RULE=") == 0)
            {
                sherlock_moving_rule = line.substr(strlen("SHERLOCK_MOVING_RULE="));
            }
            else if (line.find("SHERLOCK_INIT_POS=") == 0)
            {
                int r, c;
                sscanf(line.c_str(), "SHERLOCK_INIT_POS=(%d,%d)", &r, &c);
                sherlock_init_pos = Position(r, c);
            }
            else if (line.find("SHERLOCK_INIT_HP=") == 0)
            {
                sherlock_init_hp = stoi(line.substr(strlen("SHERLOCK_INIT_HP=")));
            }
            else if (line.find("SHERLOCK_INIT_EXP=") == 0)
            {
                sherlock_init_exp = stoi(line.substr(strlen("SHERLOCK_INIT_EXP=")));
            }
            else if (line.find("WATSON_MOVING_RULE=") == 0)
            {
                watson_moving_rule = line.substr(strlen("WATSON_MOVING_RULE="));
            }
            else if (line.find("WATSON_INIT_POS=") == 0)
            {
                int r, c;
                sscanf(line.c_str(), "WATSON_INIT_POS=(%d,%d)", &r, &c);
                watson_init_pos = Position(r, c);
            }
            else if (line.find("WATSON_INIT_HP=") == 0)
            {
                watson_init_hp = stoi(line.substr(strlen("WATSON_INIT_HP=")));
            }
            else if (line.find("WATSON_INIT_EXP=") == 0)
            {
                watson_init_exp = stoi(line.substr(strlen("WATSON_INIT_EXP=")));
            }
            else if (line.find("CRIMINAL_INIT_POS=") == 0)
            {
                int r, c;
                sscanf(line.c_str(), "CRIMINAL_INIT_POS=(%d,%d)", &r, &c);
                criminal_init_pos = Position(r, c);
            }
            else if (line.find("NUM_STEPS=") == 0)
            {
                num_steps = stoi(line.substr(strlen("NUM_STEPS=")));
            }
        }
        file.close();
    }

    ~Configuration()
    {
        delete[] array_walls;
        delete[] array_fake_walls;
    }

    string str() const
    {
        stringstream result;
        result << "Configuration[\n";
        result << "MAP_NUM_ROWS=" << map_num_rows << "\n";
        result << "MAP_NUM_COLS=" << map_num_cols << "\n";
        result << "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << "\n";
        result << "NUM_WALLS=" << num_walls << "\n";
        result << "ARRAY_WALLS=[";
        for (int i = 0; i < num_walls; i++)
        {
            result << "(" << array_walls[i].getRow() << "," << array_walls[i].getCol() << ")";
            if (i < num_walls - 1)
                result << ";";
        }
        result << "]\n";
        result << "NUM_FAKE_WALLS=" << num_fake_walls << "\n";
        result << "ARRAY_FAKE_WALLS=[";
        for (int i = 0; i < num_fake_walls; i++)
        {
            result << "(" << array_fake_walls[i].getRow() << "," << array_fake_walls[i].getCol() << ")";
            if (i < num_fake_walls - 1)
                result << ";";
        }
        result << "]\n";
        result << "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << "\n";
        result << "SHERLOCK_INIT_POS=(" << sherlock_init_pos.getRow() << "," << sherlock_init_pos.getCol() << ")\n";
        result << "SHERLOCK_INIT_HP=" << sherlock_init_hp << "\n";
        result << "SHERLOCK_INIT_EXP=" << sherlock_init_exp << "\n";
        result << "WATSON_MOVING_RULE=" << watson_moving_rule << "\n";
        result << "WATSON_INIT_POS=(" << watson_init_pos.getRow() << "," << watson_init_pos.getCol() << ")\n";
        result << "WATSON_INIT_HP=" << watson_init_hp << "\n";
        result << "WATSON_INIT_EXP=" << watson_init_exp << "\n";
        result << "CRIMINAL_INIT_POS=(" << criminal_init_pos.getRow() << "," << criminal_init_pos.getCol() << ")\n";
        result << "NUM_STEPS=" << num_steps << "\n";
        result << "]";
        return result.str();
    }

    // Các hàm getter
    int getMapNumRows() const { return map_num_rows; }
    int getMapNumCols() const { return map_num_cols; }
    int getMaxNumMovingObjects() const { return max_num_moving_objects; }
    int getNumWalls() const { return num_walls; }
    const Position *getArrayWalls() const { return array_walls; }
    int getNumFakeWalls() const { return num_fake_walls; }
    const Position *getArrayFakeWalls() const { return array_fake_walls; }
    string getSherlockMovingRule() const { return sherlock_moving_rule; }
    Position getSherlockInitPos() const { return sherlock_init_pos; }
    int getSherlockInitHp() const { return sherlock_init_hp; }
    int getSherlockInitExp() const { return sherlock_init_exp; }
    string getWatsonMovingRule() const { return watson_moving_rule; }
    Position getWatsonInitPos() const { return watson_init_pos; }
    int getWatsonInitHp() const { return watson_init_hp; }
    int getWatsonInitExp() const { return watson_init_exp; }
    Position getCriminalInitPos() const { return criminal_init_pos; }
    int getNumSteps() const { return num_steps; }
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
    SherlockBag * sherlockBag;
    WatsonBag * watsonBag;

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
        for (int istep = 0; istep < config->getNumSteps(); ++istep)
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
    void SherMeet(MovingObject *sher, MovingObject *object);
    void WatMeet(MovingObject* wat, MovingObject *object);
    ~StudyPinkProgram();
};

class Robot : public MovingObject
{
protected:
    RobotType robot_type;
    long long NUM = INT_MIN;
    BaseItem *items;

public:
    string typeRobot[4] = {"C", "S", "W", "SW"};
    Robot(int index, const Position &int_pos, Map *map, string name)
        : MovingObject(index, int_pos, map, name){
            Position init = this->getInit();
        this->NUM = mainNum(init.getCol()*init.getRow());
        if (this->NUM <= 1){
            this->items = new MagicBook();
        } 
        else if (this->NUM <= 3) {
            this->items = new EnergyDrink();
        }
        else if (this->NUM <= 5) {
            this->items = new FirstAid();
        }
        else if (this->NUM <= 7) {
            this->items = new ExcemptionCard();
        }
        else {
            this->items = new PassingCard();
        }
        }

    void setRobotType(RobotType robot_type)
    {
        this->robot_type = robot_type;
    }

    RobotType getRobotType()
    {
        return this->robot_type;
    }

    void setItems(BaseItem *items)
    {
        this->items = items;
    }

    BaseItem *getItems()
    {
        return this->items;
    }

    void move() override
    {
        if (getNextPosition().isEqual(Position::npos))
        {
            return;
        }
        else
        {
            pos = getNextPosition();
        }
    };

    int MahattanDistance(Position pos1, Position pos2) const
    {
        return abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
    }

    ~Robot(){
        // delete items;
    };
};
class RobotC : public Robot
{
private:
    Criminal *criminal;

public:
    RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal)
        : Robot(index, init_pos, map, "RobotC"), criminal(criminal)
    {
        robot_type = C;
    };
    Position getNextPosition() override
    {
        return criminal->getCurrentPosition();
    };
    string str() const
    {
        return "Robot[pos=" + pos.str() + ";type=" + "C" + ";dist=]";
    };
    int getDistance(Sherlock *sherlock)
    {
        return MahattanDistance(this->pos, sherlock->getCurrentPosition());
    }
    int getDistance(Watson *watson)
    {
        return MahattanDistance(this->pos, watson->getCurrentPosition());
    }
};
class RobotS : public Robot
{
private:
    Criminal *criminal;
    Sherlock *sherlock;

public:
    RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock) : Robot(index, init_pos, map, "RobotS"), criminal(criminal), sherlock(sherlock)
    {
        robot_type = S;
    };
    Position getNextPosition() override
    {
        Position *validPositions = new Position[4];
        validPositions[0] = Position(pos.getRow() - 1, pos.getCol()); // UP
        validPositions[1] = Position(pos.getRow(), pos.getCol() + 1); // RIGHT
        validPositions[2] = Position(pos.getRow() + 1, pos.getCol()); // DOWN
        validPositions[3] = Position(pos.getRow(), pos.getCol() - 1); // LEFT

        // Tìm vị trí hợp lệ
        int minDistance = getDistance();
        Position nextPos = Position::npos;
        for (int i = 0; i < 4; i++)
        {
            if (map->isValid(validPositions[i], this))
            {
                int distanceToSherlock = MahattanDistance(validPositions[i], sherlock->getCurrentPosition());
                if (distanceToSherlock < minDistance)
                {
                    minDistance = distanceToSherlock;
                    nextPos = validPositions[i];
                }
            }
        }
        return nextPos;
    };
    string str() const override
    {
        return "Robot[pos=" + pos.str() + ";type=" + "S" + ";dist=" + to_string(getDistance()) + "]";
    };
    int getDistance() const
    {
        return MahattanDistance(this->pos, sherlock->getCurrentPosition());
    }
};
class RobotW : public Robot
{
private:
    Criminal *criminal;
    Watson *watson;

public:
    RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson) : Robot(index, init_pos, map, "RobotW"), criminal(criminal), watson(watson)
    {
        robot_type = W;
    };
    Position getNextPosition() override
    {
        Position *validPositions = new Position[4];
        validPositions[0] = Position(pos.getRow() - 1, pos.getCol()); // UP
        validPositions[1] = Position(pos.getRow(), pos.getCol() + 1); // RIGHT
        validPositions[2] = Position(pos.getRow() + 1, pos.getCol()); // DOWN
        validPositions[3] = Position(pos.getRow(), pos.getCol() - 1); // LEFT

        // Tìm vị trí hợp lệ
        int minDistance = getDistance();
        Position nextPos = Position::npos;
        for (int i = 0; i < 4; i++)
        {
            if (map->isValid(validPositions[i], this))
            {
                int distanceToWatson = MahattanDistance(validPositions[i], watson->getCurrentPosition());
                if (distanceToWatson < minDistance)
                {
                    minDistance = distanceToWatson;
                    nextPos = validPositions[i];
                }
            }
        }
        return nextPos;
    };
    string str() const
    {
        return "Robot[pos=" + pos.str() + ";type=" + "W" + ";dist=" + to_string(getDistance()) + "]";
    };
    int getDistance() const
    {
        return MahattanDistance(this->pos, watson->getCurrentPosition());
    }
};
class RobotSW : public Robot
{
private:
    Criminal *criminal;
    Sherlock *sherlock;
    Watson *watson;

public:
    RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson) : Robot(index, init_pos, map, "RobotSW"), criminal(criminal), sherlock(sherlock), watson(watson)
    {
        robot_type = SW;
    };
    Position getNextPosition() override
    {
        Position *validPositions = new Position[4];
        validPositions[0] = Position(pos.getRow() - 1, pos.getCol()); // UP
        validPositions[1] = Position(pos.getRow(), pos.getCol() + 1); // RIGHT
        validPositions[2] = Position(pos.getRow() + 1, pos.getCol()); // DOWN
        validPositions[3] = Position(pos.getRow(), pos.getCol() - 1); // LEFT

        // Tìm vị trí hợp lệ
        int minDistance = getDistance();
        Position nextPos = Position::npos;
        for (int i = 0; i < 4; i++)
        {
            if (map->isValid(validPositions[i], this))
            {
                int distanceToSherlock = MahattanDistance(validPositions[i], sherlock->getCurrentPosition());
                int distanceToWatson = MahattanDistance(validPositions[i], watson->getCurrentPosition());
                int totalDistance = distanceToSherlock + distanceToWatson;
                if (totalDistance < minDistance)
                {
                    minDistance = distanceToWatson;
                    nextPos = validPositions[i];
                }
            }
        }
        return nextPos;
    };
    string str() const
    {
        return "Robot[pos=" + pos.str() + ";type=" + "SW" + ";dist=" + to_string(getDistance()) + "]";
    };
    int getDistance() const
    {
        return MahattanDistance(this->pos, sherlock->getCurrentPosition()) + MahattanDistance(this->pos, watson->getCurrentPosition());
    }
};

class BaseItem
{
public:
    virtual bool canUse(Character *obj, Robot *robot) = 0;
    virtual void use(Character *obj, Robot *robot) = 0;
    virtual ItemType getType() const = 0;
};
class MagicBook : public BaseItem
{
public:
    bool canUse(Character *obj, Robot *robot) override;
    void use(Character *obj, Robot *robot) override;
    ItemType getType() const override;
};
class EnergyDrink : public BaseItem
{
public:
    bool canUse(Character *obj, Robot *robot) override;
    void use(Character *obj, Robot *robot) override;
    ItemType getType() const override;
};
class FirstAid : public BaseItem
{
public:
    bool canUse(Character *obj, Robot *robot) override;
    void use(Character *obj, Robot *robot) override;
    ItemType getType() const override;
};
class ExcemptionCard : public BaseItem
{
public:
    bool canUse(Character *obj, Robot *robot) override;
    void use(Character *obj, Robot *robot) override;
    ItemType getType() const override;
};
class PassingCard : public BaseItem
{
private:
    string challenge = "";
public:
    bool canUse(Character *obj, Robot *robot) override;
    void use(Character *obj, Robot *robot) override;
    ItemType getType() const override;
};
// Túi đồ
class ItemNode{
public:
    BaseItem* item;
    ItemNode * next;
    ItemNode * prev;
    ItemNode(BaseItem* item, ItemNode* next, ItemNode* prev) : item(item), next(next), prev(prev){}
};
class BaseBag
{
public:
    Character *obj;
    int size;
    int capacity;
    virtual bool insert(BaseItem *item) = 0;
    virtual BaseItem *get() = 0;
    virtual BaseItem *get(ItemType type) = 0;
    virtual string str() const = 0;
    int getCount()
    {
        return this->size;
    }
    bool isFull()
    {
        return this->size == this->capacity;
    }
};
class SherlockBag : public BaseBag
{
private:
    ItemNode *head;
    ItemNode *tail;
public:
    SherlockBag(Sherlock *shrk)
    {
        this->obj = (Character *)shrk;
        this->size = 0;
        this->capacity = 13;
        this->head = nullptr;
    }
    BaseItem *get() override;
    string str() const override
    {
        string arr[5] = {"MagicBook", "EnergyDrink", "FirstAid", "ExcemptionCard", "PassingCard"};
        string result = "Bag[count=" + to_string(this->size) + ";";
        ItemNode *node = this->head;
        if (node == nullptr)
            return result + "]";
        while (node->next != nullptr)
        {
            result += arr[node->item->getType()] + ", ";
        }
        result += arr[node->item->getType()] + "]";
    }
    BaseItem *get(ItemType type) override
    {
        ItemNode *curr = this->head;
        while (curr != nullptr)
        {
            if (curr->item->getType() == type)
            {
                return curr->item;
            }
        }
        return nullptr;
    }
    bool insert(BaseItem *item) override
    {
        ItemNode *curr = new ItemNode(item, nullptr, nullptr);
        if (size == 0)
        {
            head = curr;
            tail = curr;
            size++;
            return true;
        }
        else if (size < capacity)
        {
            head->prev = curr;
            curr->next = head;
            head = curr;
            size++;
            return true;
        }
        return false;
    }
    void dequeue() {
        if (this->head == nullptr) {
            return;
        }
        ItemNode * node = this->head;
        if (this->size == 1){
            this->head = nullptr;
        } else {
            this->head = this->head->next;
        }
        this->size--;
        delete node;
    }
    // void deleteAllPassingCard(){
    //     BaseItem* it = this->head;
    //     while (it!= nullptr) {
    //         if (it->getType() == PASSING_CARD) {
    //             bring_to_head(it);
    //             this->dequeue();
    //         } else {
    //             it = it->next;
    //         }
    //     }
    // }
    int getPassingCard(){
        int result = 0;
        ItemNode* node = this->head;
        while(node) {
            if (node->item->getType() == ItemType::PASSING_CARD) {
                result++;
            }
            node = node->next;
        }
        return result;
    }
};
class WatsonBag : public BaseBag
{
private:
    ItemNode *head;
    ItemNode* tail;
public:
    WatsonBag(Watson *wast)
    {
        this->obj = (Character *)wast;
        this->size = 0;
        this->capacity = 15;
        this->head = nullptr;
    }
    BaseItem *get() override;
    string str() const override
    {
        string arr[5] = {"MagicBook", "EnergyDrink", "FirstAid", "ExcemptionCard", "PassingCard"};
        string result = "Bag[count=" + to_string(this->size) + ";";
        ItemNode *node = this->head;
        if (node == nullptr)
            return result + "]";
        while (node->next != nullptr)
        {
            result += arr[node->item->getType()] + ", ";
        }
        result += arr[node->item->getType()] + "]";
    }
    BaseItem *get(ItemType type) override
    {
        ItemNode *curr = this->head;
        while (curr != nullptr)
        {
            if (curr->item->getType() == type)
            {
                return curr->item;
            }
        }
        return nullptr;
    }
    bool insert(BaseItem *item) override
    {
        ItemNode *curr = new ItemNode(item, nullptr, nullptr);
        if (size == 0)
        {
            head = curr;
            tail = curr;
            size++;
            return true;
        }
        else if (size < capacity)
        {
            head->prev = curr;
            curr->next = head;
            head = curr;
            size++;
            return true;
        }
        return false;
    }
};
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
