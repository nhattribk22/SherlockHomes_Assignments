
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"


class MovingObject;
class Position;
class Configuration;
class Map;
class Character;
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

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
    friend class TestStudyInPink;
protected:
    ElementType type;
public:
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement {
    friend class TestStudyInPink;
public:
    Path();
};

class Wall : public MapElement {
    friend class TestStudyInPink;
public:
    Wall();
};

class FakeWall : public MapElement {
    friend class TestStudyInPink;
private:
    int req_exp;
public:
    FakeWall(int in_req_exp);
    int getReqExp() const;
};

class Map {
    friend class TestStudyInPink;
private:
    int num_rows, num_cols;
    MapElement*** map;
public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls);
    ~Map();
    bool isValid (const Position & pos, MovingObject * mv_obj) const;
};

class Position {
    friend class TestStudyInPink;
private:
    int r;
    int c;
public:
    static const Position npos;

    Position(int r=0, int c=0);

    Position(const string & str_pos);

    int getRow() const;
    int getCol() const;
    void setRow(int in_r);
    void setCol(int in_c);

    virtual string str() const;

    bool isEqual(int in_r, int in_c) const;
    bool isEqual(Position pos) const;
};

class MovingObject {
    friend class TestStudyInPink;
protected:
    int index;
    Position pos;
    Map * map;
    string name;
public:
    MovingObject(int index, Position pos, Map * map, const string & name="");
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;

    virtual int get_hp() const = 0;
    virtual int get_exp() const = 0;
    virtual string str() const = 0;
    int Distance(Position x, Position y);
    string getName();
};

class Character: public MovingObject {
    friend class TestStudyInPink;
protected:
    int hp, exp;
public:
    Character(int index, const Position& pos, Map * map, const string & name, int init_hp, int init_exp);
    Character(int index, const Position& pos, Map * map, const string & name);
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    int get_hp() const;
    int get_exp() const;
    void set_hp(int hp);
    void set_exp(int exp);
    void check_hp(int hp);
    void check_exp(int exp);
};

class Sherlock: public Character {
    friend class TestStudyInPink;
private:
    string moving_rule;
    string mvrule_temp;
public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    Position getNextPosition();
    void move();
    string str() const;
    // ...
    int get_hp();
    int get_exp();
    void set_hp(int hp);
    void set_exp(int exp);
    void check_hp(int hp);
    void check_exp(int exp);
    bool encounter (MovingObject* object);
};

class Watson: public Character {
    friend class TestStudyInPink;
private:
    string moving_rule;
    string mvrule_temp;
public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    Position getNextPosition();
    void move();
    string str() const;
    int get_hp();
    int get_exp();
    void set_hp(int hp);
    void set_exp(int exp);
    void check_hp(int hp);
    void check_exp(int exp);
    bool encounter (MovingObject* object);
};

class Criminal: public Character {
    friend class TestStudyInPink;
private:
    Sherlock* sherlock;
    Watson* watson;
    int step_count = 0;
    Position prev_pos;
public:
    Criminal(int index, const Position & pos, Map * map, Sherlock * sherlock, Watson * watson);
    Position getNextPosition();
    Position getPreviousPosition();
    void move();
    string str() const;
    int getStepCount();
    void createRobot(ArrayMovingObject* arr, Map* map);
};

class ArrayMovingObject {
    friend class TestStudyInPink;
private:
    MovingObject** arr_mv_objs;
    int count = 0;
    int capacity;
public:
    ArrayMovingObject(int in_capacity);
    ~ArrayMovingObject() ;
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class StudyPinkProgram;
    friend class TestStudyInPink;
private:
    int map_num_rows;
    int map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position* arr_walls;
    int num_fake_walls;
    Position* arr_fake_walls;
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
public:
    Configuration(const string & filepath);
    ~Configuration();
    int getMapNumRows() const;
    int getMapNumCols() const;
    int getMaxNumMovingObjects() const;
    int getNumWalls() const;
    Position * getArrWalls() const;
    int getNumFakeWalls() const;
    Position * getArrFakeWalls() const;
    string getSherlockMovingRule() const;
    Position getSherlockInitPos() const;
    int getSherlockInitHP() const;
    int getSherlockInitEXP() const;
    string getWatsonMovingRule() const;
    Position getWatsonInitPos() const;
    int getWatsonInitHP() const;
    int getWatsonInitEXP() const;
    Position getCriminalInitPos() const;
    int getNumSteps() const;
    string str() const;
};

class Robot: public MovingObject {
    friend class TestStudyInPink;
protected:
    Criminal* criminal;
    RobotType robot_type;
    BaseItem* item;
    int hp, exp;
public:
    Robot(int index, const Position & init_pos, Map * map, RobotType robot_type, const string& name);
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const;
    virtual RobotType getType() const = 0;

    int get_hp() const;
    int get_exp() const;
    BaseItem* createItem(Position pos);
};

class RobotC: public Robot {
    friend class TestStudyInPink;
public:
    RobotC(int index, const Position & init_pos, Map * map, Criminal * criminal);
    RobotType getType() const;
    Position getNextPosition();
    void move();
    int getDistance(Sherlock* sherlock);
    int getDistance(Watson* watson);
    string str();
};

class RobotS: public Robot {
    friend class TestStudyInPink;
private:
    Sherlock* sherlock;
public:
    RobotS(int index, const Position & init_pos, Map * map, Criminal * criminal, Sherlock * sherlock);
    RobotType getType() const;
    Position getNextPosition();
    void move();
    int getDistance();
    string str() ;
};

class RobotW: public Robot {
    friend class TestStudyInPink;
private:
    Watson* watson;
public:
    RobotW(int index, const Position & init_pos, Map * map, Criminal * criminal, Watson * watson);
    RobotType getType() const;
    Position getNextPosition();
    void move();
    int getDistance();
    string str();
};

class RobotSW: public Robot {
    friend class TestStudyInPink;
private:
    Sherlock* sherlock;
    Watson* watson;
public:
    RobotSW(int index, const Position & init_pos, Map * map, Criminal * criminal, Sherlock* sherlock ,Watson * watson);
    RobotType getType() const;
    Position getNextPosition();
    void move();
    int getDistance();
    string str();
};

class BaseItem {
    friend class TestStudyInPink;
private:
    ItemType item;
public:
    ~BaseItem();
    string getItemName();
    virtual bool canUse(Character* obj, Robot* robot) = 0;
    virtual void use(Character* obj, Robot* robot) = 0;
    virtual ItemType getType() const = 0;
};

class MagicBook : public BaseItem {
    friend class TestStudyInPink;
public:
    bool canUse(Character* obj, Robot* robot);
    void use(Character* obj, Robot* robot);
    ItemType getType() const;
};

class EnergyDrink : public BaseItem {
    friend class TestStudyInPink;
public:
    bool canUse(Character* obj, Robot* robot);
    void use(Character* obj, Robot* robot);
    ItemType getType() const;
};

class FirstAid: public BaseItem {
    friend class TestStudyInPink;
public:
    bool canUse(Character* obj, Robot* robot);
    void use(Character* obj, Robot* robot);
    ItemType getType() const;
};

class ExcemptionCard: public BaseItem {
    friend class TestStudyInPink;
public:
    bool canUse(Character* obj, Robot* robot);
    void use(Character* obj, Robot* robot);
    ItemType getType() const;
};

class PassingCard: public BaseItem {
    friend class TestStudyInPink;
private:
    string challenge;
public:
    PassingCard(int i, int j);
    PassingCard(string s);
    bool canUse(Character* obj, Robot* robot);
    void use(Character* obj, Robot* robot);
    ItemType getType() const;

    bool check_challenge(Robot* robot);
    void set_challenge(string in_challenge);
    string get_challenge() const;
};

class node {
public:
    BaseItem* data;
    node* next;
    node(BaseItem* data);
};

class LinkedList{
private:
    node* head;
public:
    void insert(BaseItem* item);
    node * get_head();
    void delete_node(node* Node);
    void swap_node(node* Node);
    void delete_head();
    int count_item();
    string List();
};

class BaseBag{
    friend class TestStudyInPink;
protected:
    Character* character;
    int count=0;
public:
    BaseBag(Character* owner);
    virtual bool insert (BaseItem* item) = 0;
    virtual BaseItem* get() = 0;
    virtual BaseItem* get(ItemType item_type) = 0;
    virtual string str() const = 0;
    int getCount();
    Character* getOwner();
};

class SherlockBag: public BaseBag {
    friend class TestStudyInPink;
private:
    LinkedList *sherlock_bag = new LinkedList();
    int bag_size = 13;
public:
    SherlockBag(Sherlock* sherlock);
    ~SherlockBag();
    bool insert(BaseItem * item);
    BaseItem* get();
    BaseItem* get(ItemType type);
    string str() const;
};

class WatsonBag : public BaseBag {
    friend class TestStudyInPink;
private:
    LinkedList* watson_bag = new LinkedList();
    int bag_size = 15;
public:
    WatsonBag(Watson* watson);
    ~WatsonBag();
    bool insert(BaseItem * item);
    BaseItem* get();
    BaseItem* get(ItemType type);
    string str() const;
};

class StudyPinkProgram {
    friend class TestStudyInPink;
private:
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    Map * map;
    ArrayMovingObject * arr_mv_objs;

    SherlockBag* sherlockBag = new SherlockBag(sherlock);
    WatsonBag* watsonBag = new WatsonBag(watson);

public:
    bool meetCriminal = 0;
    StudyPinkProgram(const string & config_file_path);

    bool Sherlock_win_robot(Sherlock* sherlock, Robot* robot, SherlockBag* sherlock_bag, bool & meetCriminal);
    bool Watson_win_robot(Watson* watson, Robot* robot, WatsonBag* watson_bag, bool & meetCriminal);

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

        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if (arr_mv_objs->get(i)->getName() == "Criminal") {
                    criminal->createRobot(arr_mv_objs, map);
                }
                if (sherlock->getCurrentPosition().isEqual(arr_mv_objs->get(i)->getCurrentPosition())){
                    if (sherlock->encounter(watson)) {
                        BaseItem* item = sherlockBag->get(PASSING_CARD);
                        if (item != nullptr){
                            watsonBag->insert(item);
                        }
                    } else {
                        Robot* robot = dynamic_cast<Robot *>(arr_mv_objs->get(i));

                        if (robot->getType() == RobotType::S) {
                            robot = new RobotS(i, arr_mv_objs->get(i)->getCurrentPosition(), map, criminal, sherlock);
                            if (Sherlock_win_robot(sherlock, robot, sherlockBag, meetCriminal))
                                continue;

                        } else if (robot->getType() == RobotType::W) {
                            robot = new RobotW(i, arr_mv_objs->get(i)->getCurrentPosition(), map, criminal, watson);
                            if (Sherlock_win_robot(sherlock, robot, sherlockBag, meetCriminal))
                                continue;
                        } else if (robot->getType() == RobotType::C) {
                            robot = new RobotC(i, arr_mv_objs->get(i)->getCurrentPosition(), map, criminal);
                            if (Sherlock_win_robot(sherlock, robot, sherlockBag, meetCriminal))
                                continue;
                        } else if (robot->getType() == RobotType::SW) {
                            robot = new RobotSW(i, arr_mv_objs->get(i)->getCurrentPosition(), map, criminal, sherlock, watson);
                            if (Sherlock_win_robot(sherlock, robot, sherlockBag, meetCriminal))
                                continue;
                        }
                    }
                    if (watson->getCurrentPosition().isEqual(arr_mv_objs->get(i)->getCurrentPosition())) {
                        if (watson->encounter(sherlock)) {
                            BaseItem *item = watsonBag->get(EXCEMPTION_CARD);
                            if (item != nullptr) {
                                sherlockBag->insert(item);
                            }
                        } else {
                            Robot *robot = dynamic_cast<Robot *>(arr_mv_objs->get(i));

                            if (robot->getType() == RobotType::S) {
                                robot = new RobotS(i, arr_mv_objs->get(i)->getCurrentPosition(), map, criminal,
                                                   sherlock);
                                if (Watson_win_robot(watson, robot, watsonBag, meetCriminal))
                                    continue;

                            } else if (robot->getType() == RobotType::W) {
                                robot = new RobotW(i, arr_mv_objs->get(i)->getCurrentPosition(), map, criminal, watson);
                                if (watsonBag->get(PASSING_CARD) != nullptr && watsonBag->get(PASSING_CARD)->canUse(watson, robot))
                                    continue;
                                if (Watson_win_robot(watson, robot, watsonBag, meetCriminal))
                                    continue;
                            } else if (robot->getType() == RobotType::C) {
                                robot = new RobotC(i, arr_mv_objs->get(i)->getCurrentPosition(), map, criminal);
                                if (Watson_win_robot(watson, robot, watsonBag, meetCriminal))
                                    continue;
                            } else if (robot->getType() == RobotType::SW) {
                                robot = new RobotSW(i, arr_mv_objs->get(i)->getCurrentPosition(), map, criminal,
                                                    sherlock, watson);
                                if (watsonBag->get(PASSING_CARD) != nullptr && watsonBag->get(PASSING_CARD)->canUse(watson, robot))
                                    continue;
                                if (Watson_win_robot(watson, robot, watsonBag, meetCriminal))
                                    continue;
                            }
                        }
                    }
                }
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

#endif 
