#include "study_in_pink2.h"

MapElement::MapElement(ElementType in_type) {
    this->type = in_type;
}

MapElement::~MapElement() {}

ElementType MapElement::getType() const {
    return type;
}

Path::Path(): MapElement(PATH){}

Wall::Wall(): MapElement(WALL){}

FakeWall::FakeWall(int in_req_exp): MapElement(FAKE_WALL) {
    this->req_exp = in_req_exp;
}

int FakeWall::getReqExp() const {
    return req_exp;
}

Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls) {
    this->num_rows=num_rows;
    this->num_cols=num_cols;

    map = new MapElement**[num_rows];
    for(int i=0; i<num_rows; i++){
        map[i] = new MapElement*[num_cols];
    }

    for(int i=0; i<num_rows; i++){
        for(int j=0; j<num_cols; j++){
            map[i][j] = new Path();
        }
    }

    for (int i=0; i<num_walls; i++){
        int r_wall = array_walls[i].getRow();
        int c_wall = array_walls[i].getCol();
        map[r_wall][c_wall] = new Wall();
    }
    for (int i=0; i<num_fake_walls; i++){
        int r_fwall = array_fake_walls[i].getRow();
        int c_fwall = array_fake_walls[i].getCol();
        map[r_fwall][c_fwall] = new FakeWall((r_fwall * 257 + c_fwall * 139 + 89)%900 + 1);
    }
}
Map::~Map() {

    for(int i=0; i<num_rows; i++){
        delete[] map[i];
    }
    delete[] map;
}


bool Map::isValid(const Position &pos, MovingObject *mv_obj) const {
    int r = pos.getRow();
    int c = pos.getCol();

   

    if ((r>=0 && r<num_rows) && (c>=0 && c<num_cols)){
        if (map[r][c]->getType() == PATH) return true;
        else if (map[r][c]->getType() == WALL) return false;
        else if (map[r][c]->getType() == FAKE_WALL){
            if (mv_obj->getName() == "Sherlock" || mv_obj->getName() == "Criminal" || mv_obj->getName() == "RobotC" ||
            mv_obj->getName() == "RobotS" || mv_obj->getName() == "RobotW" || mv_obj->getName() == "RobotSW")
                return true;
            else if (mv_obj->getName() == "Watson"){
                int temp = (r * 257 + c * 139 + 89) % 900 + 1;
                Watson * pWatson = dynamic_cast<Watson*>(mv_obj);
                if (pWatson->get_exp() >= temp) return true;
            }
        }
    }
    return false;
}

Position::Position(int r, int c) {
    this->r=r;
    this->c=c;
}

Position::Position(const string &str_pos) {
    string fake_str = "";
    for (int i = 0; i < str_pos.length(); i++){
        if (str_pos[i] != '(' && str_pos[i] != ')'){
            fake_str += str_pos[i];
        }
    }
    int pos = 0;
    for (int i = 0; i < fake_str.length(); i++){
        pos++;
        if (fake_str[i] == ',') break;
    }
    string fake_r = fake_str.substr(0, pos);
    string fake_c = fake_str.substr(pos, fake_str.length());
    this->r = stoi(fake_r);
    this->c = stoi(fake_c);
}

int Position::getRow() const {
    return r;
}

int Position::getCol() const {
    return c;
}

void Position::setRow(int in_r) {
    this->r = in_r;
}

void Position::setCol(int in_c) {
    this->c = in_c;
}

string Position::str() const {
    string temp = "(" + to_string(r) + "," + to_string(c) + ")";
    return temp;
}

const Position Position::npos = Position(-1,-1);

bool Position::isEqual(int in_r, int in_c) const {
    if (in_r == r && in_c == c) return true;
    return false;
}

bool Position::isEqual(Position pos) const {
    if (this->r == pos.getRow() && this->c == pos.getCol()) return true;
    else return false;
}


MovingObject::MovingObject(int index, const Position pos, Map * map, const string & name) {
    this->index = index;
    this->pos = pos;
    this->map = map;
    this->name = name;
}
MovingObject::~MovingObject() {}

string MovingObject::getName() {
    return name;
}

Position MovingObject::getCurrentPosition() const {
    return pos;
}

int MovingObject::Distance(Position x, Position y) {
    return abs(x.getRow()-y.getRow()) + abs(x.getCol()-y.getCol());
}

void Character::check_hp(int hp) {
    if (hp > 500) this->set_hp(500);
    if (hp < 0) this->set_hp(0);
}

void Character::check_exp(int exp) {
    if (exp > 900) this->set_hp(900);
    if (exp < 0) this->set_hp(0);
}

Character::Character(int index, const Position& pos, Map * map, const string & name, int init_hp, int init_exp): MovingObject(index, pos, map, name){
    check_hp(init_hp);
    hp = init_hp;
    check_exp(init_exp);
    exp = init_exp;
}

Character::Character(int index, const Position& pos, Map *map, const string &name): MovingObject(index, pos, map, name) {}

int Character::get_hp() const {
    return hp;
}

int Character::get_exp() const{
    return exp;
}

void Character::set_hp(int hp) {
    this->hp = hp;
}

void Character::set_exp(int exp) {
    this->exp = exp;
}

Position Sherlock::getNextPosition() {
    Position temp_pos = pos;
    switch (mvrule_temp[0]) {
        case 'U':
            temp_pos.setRow(pos.getRow()+1);
            break;
        case 'D':
            temp_pos.setRow(pos.getRow()-1);
            break;
        case 'L':
            temp_pos.setCol(pos.getCol()-1);
            break;
        case 'R':
            temp_pos.setCol(pos.getCol()+1);
            break;
        default:
            break;
    }

    if (map->isValid(temp_pos, this)) return temp_pos;
    else return Position::npos;
}

void Sherlock::move() {
    if (!Sherlock::getNextPosition().isEqual(Position::npos)){
        pos = Sherlock::getNextPosition();
    }
    mvrule_temp = mvrule_temp.substr(1, mvrule_temp.length()-1) + mvrule_temp[0];
}

Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp): Character(index, init_pos, map, "Sherlock", init_hp, init_exp) {
    this->moving_rule = moving_rule;
    mvrule_temp = moving_rule;
    this->hp = init_hp;
    this->exp = init_exp;
}

string Sherlock::str() const {
    string temp = "Sherlock[index=" + to_string(index) +";" + "pos=" + this->pos.str() + ";" + "moving_rule=" + moving_rule +"]";
    return temp;
}

int Sherlock::get_hp() {
    return hp;
}

int Sherlock::get_exp() {
    return exp;
}

void Sherlock::set_hp(int hp) {
    this->hp = hp;
}

void Sherlock::set_exp(int exp) {
    this->exp = exp;
}

void Sherlock::check_hp(int hp) {
    if (hp > 500) this->set_hp(500);
    if (hp < 0) this->set_hp(0);
}

void Sherlock::check_exp(int exp) {
    if (exp > 900) this->set_hp(900);
    if (exp < 0) this->set_hp(0);
}



Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp): Character(index, init_pos, map, "Watson", init_hp, init_exp) {
    this->moving_rule = moving_rule;
    mvrule_temp = moving_rule;
    this->hp = init_hp;
    this->exp = init_exp;
}

Position Watson::getNextPosition() {
    Position temp_pos = pos;
    switch (mvrule_temp[0]) {
        case 'U':
            temp_pos.setRow(pos.getRow()+1);
            break;
        case 'D':
            temp_pos.setRow(pos.getRow()-1);
            break;
        case 'L':
            temp_pos.setCol(pos.getCol()-1);
            break;
        case 'R':
            temp_pos.setCol(pos.getCol()+1);
            break;
        default:
            break;
    }

    if (map->isValid(temp_pos, this)) return temp_pos;
    else return Position::npos;
}

void Watson::move() {
    if (!Watson::getNextPosition().isEqual(Position::npos)){
        pos = Watson::getNextPosition();
    }
    mvrule_temp = mvrule_temp.substr(1, mvrule_temp.length()-1) + mvrule_temp[0];
}

string Watson::str() const{
    string temp = "Watson[index=" + to_string(index) +";" + "pos=" + this->pos.str() + ";" + "moving_rule=" + moving_rule +"]";
    return temp;
}

int Watson::get_hp() {
    return hp;
}

int Watson::get_exp() {
    return exp;
}

void Watson::set_hp(int hp) {
    this->hp = hp;
}

void Watson::set_exp(int exp) {
    this->exp = exp;
}

void Watson::check_hp(int hp) {
    if (hp > 500) this->set_hp(500);
    if (hp < 0) this->set_hp(0);
}

void Watson::check_exp(int exp) {
    if (exp > 900) this->set_hp(900);
    if (exp < 0) this->set_hp(0);
}


Criminal::Criminal(int index, const Position &pos, Map *map,
                   Sherlock *sherlock, Watson *watson): Character(index, pos, map, "Criminal")
                   ,sherlock(sherlock), watson(watson) {
}

Position Criminal::getPreviousPosition() {
    return prev_pos;
}

Position Criminal::getNextPosition() {
    Position new_pos[4];
    for (int i=0; i<4; i++){
        new_pos[i] = this->getCurrentPosition();
    }
    new_pos[0].setRow(pos.getRow()+1);
    new_pos[1].setCol(pos.getCol()-1);
    new_pos[2].setRow(pos.getRow()-1);
    new_pos[3].setCol(pos.getCol()+1);
    int temp[4];
    for (int i=0; i<4; i++){
        temp[i] = Distance(new_pos[i], sherlock->getCurrentPosition())
                + Distance(new_pos[i], watson->getCurrentPosition());
    }
    int max = temp[0];

    Position ans = Position::npos;
    for (int i=0; i<4; i++){
        if (map->isValid(new_pos[i], this)){
            ans = new_pos[i];
            break;
        } else continue;
    }
    for (int i=0; i<4; i++){
        if (map->isValid(new_pos[i], this)){
            if (max < temp[i]){
                max = temp[i];
                ans = new_pos[i];
            }
        } else continue;
    }
    return ans;
}

void Criminal::move() {
    prev_pos = Criminal::getCurrentPosition();
    if (!Criminal::getNextPosition().isEqual(Position::npos)) {
        pos = Criminal::getNextPosition();
        step_count++;
    } else pos = Criminal::getCurrentPosition();
}

string Criminal::str() const {
    string temp = "Criminal[index=" + to_string(index) +";" + "pos=" + this->pos.str() +"]";
    return temp;
}

int Criminal::getStepCount() {
    return step_count;
}

void Criminal::createRobot(ArrayMovingObject *arr, Map *map) {
    if (!arr->isFull()) {
        if (this->getStepCount() % 3 == 0) {
            int index = arr->size();
            if (this->getStepCount() == 3) {
                RobotC* robotC = new RobotC(index, this->getPreviousPosition(), map, this);
                arr->add(robotC);
            } else {
                int DistanceS = Distance(this->getPreviousPosition(), sherlock->getCurrentPosition());
                int DistanceW = Distance(this->getPreviousPosition(), watson->getCurrentPosition());
                if (DistanceS < DistanceW) {
                    RobotS* robotS = new RobotS(index, this->getPreviousPosition(), map, this, sherlock);
                    arr->add(robotS);
                }
                if (DistanceS > DistanceW) {
                    RobotW* robotW = new RobotW(index, this->getPreviousPosition(), map, this, watson);
                    arr->add(robotW);
                }
                if (DistanceS == DistanceW) {
                    RobotSW* robotSW = new RobotSW(index, this->getPreviousPosition(), map, this, sherlock, watson);
                    arr->add(robotSW);
                }
            }
        }
    }

}

ArrayMovingObject::ArrayMovingObject(int in_capacity) {
    this->capacity = in_capacity;
    arr_mv_objs = new MovingObject* [capacity];
}

ArrayMovingObject::~ArrayMovingObject() {
    delete[]arr_mv_objs;
}

bool ArrayMovingObject::isFull() const {
    if (count == capacity) return true; else return false;
}

bool ArrayMovingObject::add(MovingObject* mv_obj) {
    if(isFull()) return false; else{
        arr_mv_objs[count] = mv_obj;
        count++;
        return true;
    }
}

MovingObject* ArrayMovingObject::get(int index) const {
    if (index < 0 || index >= count) {
        return nullptr;
    }
    return arr_mv_objs[index];
}

int ArrayMovingObject::size() const {
    return count;
}

string ArrayMovingObject::str() const {
    ostringstream ans;
    ans << "ArrayMovingObject[count=" << to_string(count) << ";capacity=" << to_string(capacity) << ";";
    for (int i = 0; i < count; i++) {
        if (i == count - 1) {
            ans << arr_mv_objs[i]->str();
        }
        else {ans << arr_mv_objs[i]->str() << ";";}

    }
    ans << "]";
    return ans.str();
}

Configuration::Configuration(const string & filepath){
    ifstream fileInput;
    fileInput.open(filepath);
    string config;
    if(fileInput.is_open()){
        while (fileInput){
            getline(fileInput, config);
            int count = 0;
            while (config[count] != '='){
                count++;
            }

            string data = config.substr(0, count);
            if (data == "MAP_NUM_ROWS") {
                map_num_rows = stoi(config.substr(count + 1, config.length()));
            }

            if (data == "MAP_NUM_COLS") {
                map_num_cols = stoi(config.substr(count + 1, config.length()));
            }

            if (data == "MAX_NUM_MOVING_OBJECTS") {
                max_num_moving_objects = stoi(config.substr(count + 1, config.length()));
            }

            if (data == "ARRAY_WALLS") {
                string num = config.substr(count + 1, config.length());
                string num1 = "";
                for (int i = 0; num[i] != '\0'; i++){
                    if (num[i] != '[' && num[i] != ']'){
                        num1 += num[i];
                    }
                }
                stringstream s(num1);
                string temp;
                int i = 0;
                while (getline(s, temp, ';')){
                    i++;
                }
                num_walls = i;
                arr_walls = new Position [num_walls];
                stringstream s1(num1);
                string temp1;
                int j = 0;
                while (getline(s1, temp1, ';')){
                    arr_walls[j] = Position (temp1);
                    j++;
                }
            }

            if (data == "ARRAY_FAKE_WALLS") {
                string num = config.substr(count + 1, config.length());
                string num1 = "";
                for (int i = 0; num[i] != '\0'; i++){
                    if (num[i] != '[' && num[i] != ']'){
                        num1 += num[i];
                    }
                }
                stringstream s(num1);
                string temp;
                int i = 0;
                while (getline(s, temp, ';')){
                    i++;
                }
                num_fake_walls = i;
                arr_fake_walls = new Position [num_fake_walls];
                stringstream s1(num1);
                string temp1;
                int j = 0;
                while (getline(s1, temp1, ';')){
                    arr_fake_walls[j] = Position (temp1);
                    j++;
                }
            }

            if (data == "SHERLOCK_MOVING_RULE") {
                sherlock_moving_rule = config.substr(count + 1, config.length());
            }

            if (data == "SHERLOCK_INIT_POS") {
                sherlock_init_pos = Position (config.substr(count + 1, config.length()));
            }

            if (data == "SHERLOCK_INIT_HP") {
                sherlock_init_hp = stoi(config.substr(count + 1, config.length()));
            }

            if (data == "SHERLOCK_INIT_EXP") {
                sherlock_init_exp = stoi(config.substr(count + 1, config.length()));
            }

            if (data == "WATSON_MOVING_RULE") {
                watson_moving_rule = config.substr(count + 1, config.length());
            }

            if (data == "WATSON_INIT_POS") {
                watson_init_pos = Position (config.substr(count + 1, config.length()));
            }

            if (data == "WATSON_INIT_HP") {
                watson_init_hp = stoi(config.substr(count + 1, config.length()));
            }

            if (data == "WATSON_INIT_EXP") {
                watson_init_exp = stoi(config.substr(count + 1, config.length()));
            }

            if (data == "CRIMINAL_INIT_POS") {
                criminal_init_pos = Position (config.substr(count + 1, config.length()));
            }

            if (data == "NUM_STEPS") {
                num_steps = stoi(config.substr(count + 1, config.length()));
            }
        }
    }
    fileInput.close();
}

Configuration::~Configuration(){
    delete[]arr_fake_walls;
    delete[]arr_walls;
}

int Configuration::getMapNumRows() const {
    return map_num_rows;
}
int Configuration::getMapNumCols() const {
    return map_num_cols;
}
int Configuration::getMaxNumMovingObjects() const {
    return max_num_moving_objects;
}
int Configuration::getNumWalls() const {
    return num_walls;
}
Position * Configuration::getArrWalls() const {
    return arr_walls;
}
int Configuration::getNumFakeWalls() const {
    return num_fake_walls;
}
Position * Configuration::getArrFakeWalls() const {
    return arr_fake_walls;
}
string Configuration::getSherlockMovingRule() const {
    return sherlock_moving_rule;
}
Position Configuration::getSherlockInitPos() const {
    return sherlock_init_pos;
}
int Configuration::getSherlockInitHP() const {
    return sherlock_init_hp;
}
int Configuration::getSherlockInitEXP() const {
    return sherlock_init_exp;
}
string Configuration::getWatsonMovingRule() const {
    return watson_moving_rule;
}
Position Configuration::getWatsonInitPos() const {
    return watson_init_pos;
}
int Configuration::getWatsonInitHP() const {
    return watson_init_hp;
}
int Configuration::getWatsonInitEXP() const {
    return watson_init_exp;
}
Position Configuration::getCriminalInitPos() const {
    return criminal_init_pos;
}
int Configuration::getNumSteps() const {
    return num_steps;
}

string print(Position * arr, int num) {
    if(arr == nullptr || num == 0) {
        return "[]";
    }
    string res;
    res += "[";
    for (int i = 0; i < num - 1; i++) {
        res += arr[i].str() + ";";
    }
    res += arr[num-1].str() + "]";
    return res;
}

string Configuration::str() const {
    ostringstream ans;
    ans << "Configuration[" << endl;
    ans << "MAP_NUM_ROWS=" << to_string(this->getMapNumRows()) << endl;
    ans << "MAP_NUM_COLS=" << to_string(this->getMapNumCols()) << endl;
    ans << "MAX_NUM_MOVING_OBJECTS=" << to_string(this->getMaxNumMovingObjects()) << endl;
    ans << "NUM_WALLS=" << to_string(this->getNumWalls()) << endl;
    ans << "ARRAY_WALLS=" << print(arr_walls, num_walls) << endl;
    ans << "NUM_FAKE_WALLS=" << to_string(this->getNumFakeWalls()) << endl;
    ans << "ARRAY_FAKE_WALLS=" << print(arr_fake_walls, num_fake_walls) << endl;
    ans << "SHERLOCK_MOVING_RULE=" << this->getSherlockMovingRule() << endl;
    ans << "SHERLOCK_INIT_POS=" << this->getSherlockInitPos().str() << endl;
    ans << "SHERLOCK_INIT_HP="  << to_string(this->getSherlockInitHP()) << endl;
    ans << "SHERLOCK_INIT_EXP=" << to_string(this->getSherlockInitEXP()) << endl;
    ans << "WATSON_MOVING_RULE=" << this->getWatsonMovingRule() << endl;
    ans << "WATSON_INIT_POS=" << this->getWatsonInitPos().str() << endl;
    ans << "WATSON_INIT_HP=" << to_string(this->getWatsonInitHP()) << endl;
    ans << "WATSON_INIT_EXP=" << to_string(this->getWatsonInitEXP()) << endl;
    ans << "CRIMINAL_INIT_POS=" << this->getCriminalInitPos().str() << endl;
    ans << "NUM_STEPS=" << to_string(this->getNumSteps()    ) << endl;
    ans << "]" << endl;
    return ans.str();
}

Robot::Robot(int index, const Position & init_pos, Map *map, RobotType robot_type, const string &name): MovingObject(index, init_pos, map, name) {
    this->robot_type = robot_type;
}

int Robot::get_hp() const {
    return hp;
}

int Robot::get_exp() const {
    return exp;
}

string Robot::str() const {
    return "";
}

RobotC::RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal): Robot(index, init_pos, map, C, "RobotC") {
    this->criminal = criminal;
}

RobotType RobotC::getType() const {
    return robot_type;
}

Position RobotC::getNextPosition() {
    return criminal->getPreviousPosition();
}

void RobotC::move() {
    if(!criminal->getNextPosition().isEqual(Position::npos)) {
        pos = getNextPosition();
    }
}

int RobotC::getDistance(Sherlock *sherlock) {
    return Distance(pos, sherlock->getCurrentPosition());
}

int RobotC::getDistance(Watson *watson) {
    return Distance(pos, watson->getCurrentPosition());
}

string RobotC::str() {
    string temp = "Robot[pos=" + pos.str() + ";type=C;dist=]";
    return temp;
}

RobotS::RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock): Robot(index, init_pos, map, S, "RobotS") {
    this->criminal = criminal;
    this->sherlock = sherlock;
}

RobotType RobotS::getType() const {
    return robot_type;
}

Position RobotS::getNextPosition() {
    Position new_pos[4];
    for (int i=0; i<4; i++){
        new_pos[i] = pos;
    }
    new_pos[0].setRow(pos.getRow()+1);
    new_pos[1].setCol(pos.getCol()+1);
    new_pos[2].setRow(pos.getRow()-1);
    new_pos[3].setCol(pos.getCol()-1);
    int temp[4];
    for (int i=0; i<4; i++){
        temp[i] = Distance(new_pos[i], sherlock->getCurrentPosition());
    }
    int min = temp[0];
    Position ans = Position::npos;
    for (int i=0; i<4; i++){
        if (map->isValid(new_pos[i], this)){
            ans = new_pos[i];
            break;
        } else continue;
    }
    for (int i=0; i<4; i++){
        if (map->isValid(new_pos[i], this)){
            if(min < temp[i]){
                min = temp[i];
                ans = new_pos[i];
            }
        } else continue;
    }
    return ans;
}

void RobotS::move(){
    if (!getNextPosition().isEqual(Position::npos)) {
        pos = getNextPosition();
    }
}

int RobotS::getDistance() {
    return Distance(pos, sherlock->getCurrentPosition());
}

string RobotS::str() {
    string temp = "Robot[pos=" + pos.str() + ";type=S;dist=" + to_string(getDistance()) + "]";
    return temp;
}

RobotW::RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson): Robot(index, init_pos, map, W, "RobotW") {
    this->criminal = criminal;
    this->watson = watson;
}

RobotType RobotW::getType() const {
    return robot_type;
}

Position RobotW::getNextPosition() {
    Position new_pos[4];
    for (int i=0; i<4; i++){
        new_pos[i] = pos;
    }
    new_pos[0].setRow(pos.getRow()+1);
    new_pos[1].setCol(pos.getCol()+1);
    new_pos[2].setRow(pos.getRow()-1);
    new_pos[3].setCol(pos.getCol()-1);
    int temp[4];
    for (int i=0; i<4; i++){
        temp[i] = Distance(new_pos[i], watson->getCurrentPosition());
    }
    int min = temp[0];
    Position ans = Position::npos;
    for (int i=0; i<4; i++){
        if (map->isValid(new_pos[i], this)){
            ans = new_pos[i];
            break;
        } else continue;
    }
    for (int i=0; i<4; i++){
        if (map->isValid(new_pos[i], this)){
            if(min < temp[i]){
                min = temp[i];
                ans = new_pos[i];
            }
        } else continue;
    }
    return ans;
}

void RobotW::move() {
    if (!getNextPosition().isEqual(Position::npos)) {
        pos = getNextPosition();
    }
}

int RobotW::getDistance() {
    return Distance(pos, watson->getCurrentPosition());
}

string RobotW::str() {
    string temp = "Robot[pos=" + pos.str() + ";type=W;dist=" + to_string(getDistance()) + "]";
    return temp;
}


RobotSW::RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock,
                 Watson *watson): Robot(index, init_pos, map, SW, "RobotSW") {
    this->criminal = criminal;
    this->sherlock = sherlock;
    this->watson = watson;
}

RobotType RobotSW::getType() const {
    return robot_type;
}

Position RobotSW::getNextPosition() {
    Position new_pos[8];
    for (int i=0; i<8; i++){
        new_pos[i] = pos;
    }
    new_pos[0].setRow(pos.getRow()+2);
    new_pos[1].setRow(pos.getRow()+1); new_pos[1].setCol(pos.getCol()+1);
    new_pos[2].setCol(pos.getCol()+2);
    new_pos[3].setRow(pos.getRow()-1); new_pos[3].setCol(pos.getCol()+1);
    new_pos[4].setRow(pos.getRow()-2);
    new_pos[5].setRow(pos.getRow()-1); new_pos[5].setCol(pos.getCol()-1);
    new_pos[6].setRow(pos.getRow()-2);
    new_pos[7].setRow(pos.getRow()+1); new_pos[7].setCol(pos.getCol()-1);
    int temp[8];
    for (int i=0; i<8; i++){
        temp[i] = Distance(new_pos[i], sherlock->getCurrentPosition())
                + Distance(new_pos[i], watson->getCurrentPosition());
    }
    int min = temp[0];
    Position ans = Position::npos;
    for (int i=0; i<8; i++){
        if (map->isValid(new_pos[i], this)){
            ans = new_pos[i];
            break;
        } else continue;
    }
    for (int i=0; i<8; i++){
        if (map->isValid(new_pos[i], this)){
            if(min < temp[i]){
                min = temp[i];
                ans = new_pos[i];
            }
        } else continue;
    }
    return ans;
}

void RobotSW::move() {
    if (!getNextPosition().isEqual(Position::npos)) {
        pos = getNextPosition();
    }
}

int RobotSW::getDistance() {
    return Distance(pos, sherlock->getCurrentPosition()) + Distance(pos, watson->getCurrentPosition());
}

string RobotSW::str() {
    string temp = "Robot[pos=" + pos.str() + ";type=SW;dist=" + to_string(this->getDistance()) + "]";
    return temp;
}


BaseItem *Robot::createItem(Position pos) {
    int p = pos.getRow() * pos.getCol();
    int s = 0;
    while(p!=0) {
        s += (p%10);
        p = p/10;
    }
    if (s==0 || s==1){
        MagicBook* magic_book = new MagicBook();
        return magic_book;
    }
    if (s==2 || s==3){
        EnergyDrink* energy_drink = new EnergyDrink();
        return energy_drink;
    }
    if (s==4 || s==5){
        FirstAid* first_aid = new FirstAid();
        return first_aid;
    }
    if (s==6 || s==7){
        ExcemptionCard* excemption_card = new ExcemptionCard();
        return excemption_card;
    }
    if (s==8 || s==9){
        PassingCard* passing_card = new PassingCard(pos.getRow(), pos.getCol());
        return passing_card;
    }
    return nullptr;
}

BaseItem::~BaseItem() {}

string BaseItem::getItemName() {
    switch (item) {
        case ItemType::MAGIC_BOOK:
            return "MagicBook";
        case ItemType::ENERGY_DRINK:
            return "EnergyDrink";
        case ItemType::FIRST_AID:
            return "FirstAid";
        case ItemType::EXCEMPTION_CARD:
            return "ExcemptionCard";
        case ItemType::PASSING_CARD:
            return "PassingCard";
    }
    return "";
}


bool MagicBook::canUse(Character *obj, Robot *robot) {
    if (obj->getName() == "Sherlock" || obj->getName() == "Watson") {
        if (obj->get_exp() <= 350 && robot == nullptr)
            return true;
    }
    return false;
}

void MagicBook::use(Character *obj, Robot *robot) {
    if(canUse(obj, robot)) {
        int exp = ceil(obj->get_exp()*1.25);
        obj->check_exp(exp);
        obj->set_exp(exp);
    }
}

ItemType MagicBook::getType() const {
    return MAGIC_BOOK;
}


bool EnergyDrink::canUse(Character *obj, Robot *robot) {
    if (obj->getName() == "Sherlock" || obj->getName() == "Watson") {
        if (obj->get_hp() <= 100 && robot == nullptr)
            return true;
    }
    return false;
}

void EnergyDrink::use(Character *obj, Robot *robot) {
    if(canUse(obj, robot)) {
        int hp = ceil(obj->get_hp()*1.2);
        obj->check_hp(hp);
        obj->set_hp(hp);
    }
}

ItemType EnergyDrink::getType() const {
    return ENERGY_DRINK;
}


bool FirstAid::canUse(Character *obj, Robot *robot) {
    if (obj->getName() == "Sherlock" || obj->getName() == "Watson") {
        if ((obj->get_hp() <= 100 || obj->get_exp() <= 350) && robot == nullptr)
            return true;
    }
    return false;
}

void FirstAid::use(Character *obj, Robot *robot) {
    if(canUse(obj, robot)) {
        int hp = ceil(obj->get_hp()*1.5);
        obj->check_hp(hp);
        obj->set_hp(hp);
    }
}

ItemType FirstAid::getType() const {
    return FIRST_AID;
}


bool ExcemptionCard::canUse(Character *obj, Robot *robot) {
    if (obj->getName() == "Sherlock") {
        if (obj->get_hp() % 2 == 1 && robot == nullptr)
            return true;
    }
    return false;
}

void ExcemptionCard::use(Character *obj, Robot *robot) {
    if(canUse(obj, robot)) {
        int exp = obj->get_exp();
        obj->check_exp(exp);
        obj->set_exp(exp);

        int hp = obj->get_hp();
        obj->check_hp(hp);
        obj->set_hp(hp);
    }
}

ItemType ExcemptionCard::getType() const {
    return EXCEMPTION_CARD;
}


bool PassingCard::canUse(Character *obj, Robot *robot) {
    if (obj->getName() == "Watson") {
        if (obj->get_hp() % 2 == 0 && robot == nullptr)
            return true;
    }
    return false;
}

bool PassingCard::check_challenge(Robot *robot) {
    if (robot != nullptr) {
        if (challenge == "all" || robot->getName() == challenge) {
            return true;
        }
    }
    return false;
}

void PassingCard::set_challenge(string in_challenge) {
    this->challenge = in_challenge;
}

string PassingCard::get_challenge() const {
    return challenge;
}

PassingCard::PassingCard(int i, int j) {
    int t = (i*11+j)%4;
    if (t==0) set_challenge("RobotS");
    else if(t==1) set_challenge("RobotW");
    else if(t==2) set_challenge("RobotSW");
    else if(t==3) set_challenge("all");
}

PassingCard::PassingCard(std::string s) {
    s = PassingCard::get_challenge();
}

void PassingCard::use(Character *obj, Robot *robot) {
    if(canUse(obj, robot)) {
        if(!check_challenge(robot)) {
            int exp = obj->get_exp()-50;
            obj->check_exp(exp);
            obj->set_exp(exp);
        }
    }
}

ItemType PassingCard::getType() const {
    return PASSING_CARD;
}

node::node(BaseItem *data): data(data), next(nullptr) {}

void LinkedList::insert(BaseItem* item) {
    node* new_node = new node(item);
    if (head == nullptr) {
        head = new_node;
    } else {
        node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
}

node * LinkedList::get_head() {
    return head;
}

void LinkedList::delete_node(node* Node) {
    if (head == nullptr || Node == nullptr)
        return;
    if (head == Node) {
        head = Node->next;
    }
    node* previous = nullptr;
    node* current = head;
    while (current != nullptr && current != Node) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr)
        return;

    previous->next = current->next;

    delete current;
}

void LinkedList::swap_node(node* Node) {
    if (head == nullptr || Node == nullptr) return;
    BaseItem* temp = head->data;
    head->data = Node->data;
    Node->data = temp;
}

void LinkedList::delete_head() {
    if (head == nullptr) return;
    node* current = head;
    head = head->next;
    delete current;
}

int LinkedList::count_item() {
    node* current = head;
    if (current == nullptr) {
        return 0;
    }
    int count = 1;
    while (current->next != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

string LinkedList::List() {
    string ans = "";
    node* current = head;
    while (current != nullptr) {
        ans += current->data->getItemName() + " ";
        current = current->next;
    }
    return ans;
}



BaseBag::BaseBag(Character *owner): character(owner) {}

Character *BaseBag::getOwner() {
    return character;
}

int BaseBag::getCount() {
    return count;
}


SherlockBag::SherlockBag(Sherlock* sherlock): BaseBag(sherlock) {}

SherlockBag::~SherlockBag() {
    delete sherlock_bag;
}

bool SherlockBag::insert(BaseItem* item) {
    if (sherlock_bag->count_item() < bag_size) {
        sherlock_bag->insert(item);
        count++;
        return true;
    }
    return false;
}

BaseItem * SherlockBag::get() {
    node* current = sherlock_bag->get_head();
    while (current != nullptr) {
        if (current->data->canUse(this->getOwner(), nullptr)) {
            BaseItem* item = current->data;
            sherlock_bag->swap_node(current);
            sherlock_bag->delete_node(current);
            count--;
            return item;
        }
        current = current->next;
    }
    return nullptr;
}

BaseItem* SherlockBag::get(ItemType itemType) {
    node* current = sherlock_bag->get_head();
    while (current != nullptr) {
        if (current->data->getType() == itemType) {
            BaseItem* item = current->data;
            sherlock_bag->swap_node(current);
            sherlock_bag->delete_node(current);
            count--;
            return item;
        }
        current = current->next;
    }
    return nullptr;
}
string SherlockBag::str() const {
    ostringstream ans;
    ans << "Bag[count=" << sherlock_bag->count_item() << ";" << sherlock_bag->List() << "]";
    return ans.str();
}


WatsonBag::WatsonBag(Watson *watson): BaseBag(watson) {}

WatsonBag::~WatsonBag() {
    delete watson_bag;
}

bool WatsonBag::insert(BaseItem* item) {
    if (watson_bag->count_item() < bag_size) {
        watson_bag->insert(item);
        count++;
        return true;
    }
    return false;
}

BaseItem * WatsonBag::get() {
    node* current = watson_bag->get_head();
    while (current != nullptr) {
        if (current->data->canUse(this->getOwner(), nullptr)) {
            BaseItem* item = current->data;
            watson_bag->swap_node(current);
            watson_bag->delete_node(current);
            count--;
            return item;
        }
        current = current->next;
    }
    return nullptr;
}

BaseItem* WatsonBag::get(ItemType itemType) {
    node* current = watson_bag->get_head();
    while (current != nullptr) {
        if (current->data->getType() == itemType) {
            BaseItem* item = current->data;
            watson_bag->swap_node(current);
            watson_bag->delete_node(current);
            count--;
            return item;
        }
        current = current->next;
    }
    return nullptr;
}
string WatsonBag::str() const {
    ostringstream ans;
    ans << "Bag[count=" << watson_bag->count_item() << ";" << watson_bag->List() << "]";
    return ans.str();
}


bool Sherlock::encounter(MovingObject *object) {
    if(this->getCurrentPosition().isEqual(object->getCurrentPosition()))
        return true;
    return false;
}

bool Watson::encounter(MovingObject *object) {
    if(this->getCurrentPosition().isEqual(object->getCurrentPosition()))
        return true;
    return false;
}

bool StudyPinkProgram::Sherlock_win_robot(Sherlock *sherlock, Robot *robot, SherlockBag *sherlock_bag, bool &meetCriminal) {
    bool win = 0;
    if (robot->getName() == "RobotS") {
        if (sherlock->get_exp() > 400) {
            BaseItem* item = robot->createItem(robot->getCurrentPosition());
            if (item != nullptr) {
                sherlock_bag->insert(item);
            }
            win = 1;
        } else {
            sherlock->set_hp(sherlock->get_hp() * 0.9);
        }
    }
    else if (robot->getName() == "RobotW") {
        BaseItem* item = robot->createItem(robot->getCurrentPosition());
        if (item != nullptr) {
            sherlock_bag->insert(item);
        }
        win = 1;
    }
    else if (robot->getName() == "RobotSW") {
        if (sherlock->get_exp() > 300 && sherlock->get_hp() > 335) {
            BaseItem* item = robot->createItem(robot->getCurrentPosition());
            if (item != nullptr) {
                sherlock_bag->insert(item);
            }
        } else {
            sherlock->set_hp(sherlock->get_hp() * 0.85);
            sherlock->set_exp(sherlock->get_exp() * 0.85);
        }
    }
    else if(robot->getName() == "RobotC") {
        if(sherlock->get_exp() > 500) {
            meetCriminal = 1;
        } else {
            BaseItem* item = robot->createItem(robot->getCurrentPosition());
            if (item != nullptr) {
                sherlock_bag->insert(item);
            }
            win = 1;
        }
    }
    return win;
}

bool StudyPinkProgram::Watson_win_robot(Watson *watson, Robot *robot, WatsonBag *watson_bag, bool &meetCriminal) {
    bool win = 0;
    if (robot->getName() == "RobotS") {
        win = 1;
    }
    else if (robot->getName() == "RobotW") {
        if (watson->get_hp() > 350) {
            BaseItem* item = robot->createItem(robot->getCurrentPosition());
            if (item != nullptr) {
                watson_bag->insert(item);
            }
            win = 1;
        } else {
            watson->set_hp(watson->get_hp() * 0.95);
        }
    }
    else if (robot->getName() == "RobotSW") {
        if (watson->get_exp() > 600 && watson->get_hp() > 165) {
            BaseItem* item = robot->createItem(robot->getCurrentPosition());
            if (item != nullptr) {
                watson_bag->insert(item);
            }
            win = 1;
        } else {
            watson->set_hp(watson->get_hp() * 0.85);
            watson->set_exp(watson->get_exp() * 0.85);
        }
    }
    else if(robot->getName() == "RobotC") {
            BaseItem* item = robot->createItem(robot->getCurrentPosition());
            if (item != nullptr) {
                watson_bag->insert(item);
            }
            win = 1;
    }
    return win;
}

BaseItem* checkS_card(Sherlock* obj, SherlockBag* sherlock_bag) {
    BaseItem* item = sherlock_bag->get(ItemType::EXCEMPTION_CARD);
    if (item != nullptr) return item;
    item = sherlock_bag->get(ItemType::PASSING_CARD);
    return item;
}

BaseItem* checkW_card(Watson* obj, WatsonBag* watson_bag) {
    BaseItem* item = watson_bag->get(ItemType::EXCEMPTION_CARD);
    if (item != nullptr) return item;
    item = watson_bag->get(ItemType::PASSING_CARD);
    return item;
}

bool checkS_hp_exp(Sherlock* obj, SherlockBag* sherlock_bag) {
    BaseItem* item = nullptr;
    while (item == nullptr) {
        item = sherlock_bag->get(ItemType::MAGIC_BOOK);
    }
    while (item == nullptr) {
        item = sherlock_bag->get(ItemType::ENERGY_DRINK);
    }
    while (item == nullptr) {
        item = sherlock_bag->get(ItemType::FIRST_AID);
    }
    if (item == nullptr) return false;
    item->use(obj, nullptr);
    return true;
}

bool checkW_hp_exp(Watson* obj, WatsonBag* watson_bag) {
    BaseItem* item = nullptr;
    while (item == nullptr) {
        item = watson_bag->get(ItemType::MAGIC_BOOK);
    }
    while (item == nullptr) {
        item = watson_bag->get(ItemType::ENERGY_DRINK);
    }
    while (item == nullptr) {
        item = watson_bag->get(ItemType::FIRST_AID);
    }
    if (item == nullptr) return false;
    item->use(obj, nullptr);
    return true;
}

StudyPinkProgram::StudyPinkProgram(const string &config_file_path) {
    config = new Configuration (config_file_path);
    int map_num_rows = config->getMapNumRows();
    int map_num_cols = config->getMapNumCols();
    int max_num_moving_objects = config->getMaxNumMovingObjects();
    int num_walls = config->getNumWalls();
    Position* arr_walls = config->getArrWalls();
    int num_fake_walls = config->getNumFakeWalls();
    Position* arr_fake_walls = config->getArrFakeWalls();
    string sherlock_moving_rule = config->getSherlockMovingRule();
    Position sherlock_init_pos = config->getSherlockInitPos();
    int sherlock_init_hp = config->getSherlockInitHP();
    int sherlock_init_exp = config->getSherlockInitEXP();
    string watson_moving_rule = config->getWatsonMovingRule();
    Position watson_init_pos = config->getWatsonInitPos();
    int watson_init_hp = config->getWatsonInitHP();
    int watson_init_exp = config->getWatsonInitEXP();
    Position criminal_init_pos = config->getCriminalInitPos();
    int num_steps = config->getNumSteps();

    map = new Map (map_num_rows, map_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
    criminal = new Criminal (0, criminal_init_pos, map, sherlock, watson);
    sherlock = new Sherlock (1, sherlock_moving_rule, sherlock_init_pos, map, sherlock_init_hp, sherlock_init_exp);
    watson = new Watson (2, watson_moving_rule, watson_init_pos, map, watson_init_hp, watson_init_exp);

    arr_mv_objs = new ArrayMovingObject (max_num_moving_objects);

    arr_mv_objs -> add(sherlock);
    arr_mv_objs -> add(watson);
    arr_mv_objs -> add(criminal);

    BaseBag * sherlockBag = new SherlockBag (sherlock);
    BaseBag * watsonBag = new WatsonBag (watson);
}

bool StudyPinkProgram::isStop() const {
    if (sherlock->get_hp() <= 0 || watson->get_hp() <= 0 || meetCriminal) {
        return true;
    }
    return false;
}

StudyPinkProgram::~StudyPinkProgram(){};








////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
