/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
// class MovingObject;
// class Position;
// class Configuration;
// class Map;

// class Criminal;
// class RobotS;
// class RobotW;
// class RobotSW;
// class RobotC;

// class ArrayMovingObject;
// class StudyPinkProgram;

// class BaseItem;
// class BaseBag;
// class SherlockBag;
// class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
protected:
    ElementType type;
public:
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement {
    public:
        Path() : MapElement(PATH) {};
};

class Wall : public MapElement {
    public:
        Wall() : MapElement(WALL) {};
};

class FakeWall : public MapElement {
    private:
        int exp_req;
    public:
        FakeWall(int exp_req) : MapElement(FAKE_WALL), exp_req(exp_req) {};
        int getExpReq() const{
            return exp_req;
        }
};

class Map {
private:
    int num_rows, num_cols;
    MapElement *** map;
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

    bool isValid ( const Position & pos , MovingObject * mv_obj ) const ;
};

class Position {
private:
    int r, c;
public:
    static const Position npos =;

    Position(int r=0, int c=0) : r(r), c(c) {};

    Position(const string & str_pos){
        int index = str_pos.find(",");
        r = stoi(str_pos.substr(1, index - 1));
        c = stoi(str_pos.substr(index + 1, str_pos.length() - index - 2));
    }

    int getRow() const{
        return r;
    }
    int getCol() const{
        return c;
    }
    void setRow(int r){
        this->r = r;
    }
    void setCol(int c){
        this->c = c;
    }

    string str() const{
        return "(" + to_string(r) + "," + to_string(c) + ")";
    }
    int getExpReq() const{
        return (r * 257 + c * 139 + 89) % 900 + 1;
    }
    bool isEqual(int in_r, int in_c) const;
};
const Position Position::npos;
class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    string name;

public:
    MovingObject(int index, const Position pos, Map * map, const string & name="");
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
};

class Sherlock : public MovingObject/* TODO */ {
private:
    // TODO
    string moving_rule;
    int hp;
    int exp;
    size_t current_rule_index;

public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) 
    : MovingObject(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(init_hp > 500 ? 500 : init_hp ), exp(init_exp > 900 ? 900 : init_exp), current_rule_index(0) {}; 
    // getNextPosition
    // move
    // str
    // ...
    Position getNextPosition() override {
        if (hp == 0 || exp == 0) {
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
            default: return Position::npos;
        }
        // Update the rule index for the next move
        current_rule_index = (current_rule_index + 1) % moving_rule.length();
        Position new_pos(r, c);
        return map->isValid(new_pos, this) ? new_pos : Position::npos;
    }
    void move() override{
        Position new_pos = getNextPosition();
        if (new_pos != Position::npos) {
            pos = new_pos;
        }
    }
    string str() const override {
        return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
    }
    ~Sherlock() {}
};

class Watson : public MovingObject /* TODO */ {
private:
    // TODO
    string moving_rule;
    int hp;
    int exp;
    size_t current_rule_index;
public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp)
    : MovingObject(index, init_pos, map, "Waston"), moving_rule(moving_rule), hp(init_hp > 500 ? 500 : init_hp ), exp(init_exp > 900 ? 900 : init_exp), current_rule_index(0) {}; 
    // getNextPosition
    // move
    // str
    // ...
     Position getNextPosition() override {
        if (hp == 0 || exp == 0) {
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
            default: return Position::npos;
        }
        // Update the rule index for the next move
        current_rule_index = (current_rule_index + 1) % moving_rule.length();
        Position new_pos(r, c);
        return map->isValid(new_pos, this) ? new_pos : Position::npos;
    }
    void move() override{
        Position new_pos = getNextPosition();
        if (new_pos != Position::npos) {
            pos = new_pos;
        }
    }
    string str() const override {
        return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
    }
    ~Sherlock() {}
};

class Criminal /* TODO */ {
private:
    // TODO

public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    // getNextPosition
    // move
    // str
    // ...
};

class ArrayMovingObject {
private:
    // TODO

public:
    ArrayMovingObject(int capacity);

    ~ArrayMovingObject() ;
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class StudyPinkProgram;

private:
    // TODO

public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
};

// Robot, BaseItem, BaseBag,...

class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
