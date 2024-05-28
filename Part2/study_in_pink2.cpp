#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const Position Position::npos = Position(-1, -1);
// bool MagicBook::canUse(Character *obj, Robot*robot) {
//         if (!obj->getCurrentPosition().isEqual(robot->getCurrentPosition())) {
//             return false;
//         }
//         // if they don't meet each other
//         if (obj->getName() == "Watson"){
//             Watson* watson = (Watson*)obj;
//             if (watson->getInitExp() <= 350) return true;
//         }
//         else if (obj->getName() == "Sherlock") {
//             Sherlock* sherlock = (Sherlock*)obj;
//             if (sherlock->getInitExp() <= 350) return true;
//         }
//     return false;
//     }

// void MagicBook::use(Character *obj, Robot* robot)  {
//     if (obj->getName() == "Watson"){
//         Watson* watson = (Watson*)obj;
//         watson->setInitExp(ceil(watson->getInitExp()*1.25));
//     }
//     else if (obj->getName() == "Sherlock") {
//         Sherlock* sherlock = (Sherlock*)obj;
//         sherlock->setInitExp(ceil(sherlock->getInitExp()*1.25));
//     }
// }


// bool EnergyDrink::canUse(Character *obj, Robot* robot) {
//     if (!obj->getCurrentPosition().isEqual(robot->getCurrentPosition())) {
//         return false;
//     }
//     // if they don't meet each other
//     if (obj->getName() == "Watson"){
//         Watson* watson = (Watson*)obj;
//         if (watson->getInitHp() <= 100) return true;
//     }
//     else if (obj->getName() == "Sherlock") {
//         Sherlock* sherlock = (Sherlock*)obj;
//         if (sherlock->getInitHp() <= 100) return true;
//     }
//     return false;
// }

// void EnergyDrink::use(Character *obj, Robot* robot)  {
//     if (obj->getName() == "Watson"){
//         Watson* watson = (Watson*)obj;
//         watson->setInitHp(ceil(watson->getInitHp()*1.2));
//     }
//     else if (obj->getName() == "Sherlock") {
//         Sherlock* sherlock = (Sherlock*)obj;
//         sherlock->setInitHp(ceil(sherlock->getInitHp()*1.2));
//     }
// }
// bool FirstAid::canUse(Character *obj, Robot *robot) {
//     // if they don't meet each other
//     if (!obj->getCurrentPosition().isEqual(robot->getCurrentPosition())) {
//         return false;
//     }
//     if (obj->getName() == "Watson"){
//         Watson* watson = (Watson*)obj;
//         if (watson->getInitHp() <= 100 || watson->getInitExp() <= 350) return true;
//     }
//     else if (obj->getName() == "Sherlock") {
//         Sherlock* sherlock = (Sherlock*)obj;
//         if (sherlock->getInitHp() <= 100 || sherlock->getInitExp() <= 350) return true;
//     }
//     return false;
// }


// void FirstAid::use(Character* obj, Robot* robot) {
//     if (obj->getName() == "Watson"){
//         Watson* watson = (Watson*)obj;
//         watson->setInitHp(ceil(watson->getInitHp()*1.5));
//     }
//     else if (obj->getName() == "Sherlock") {
//         Sherlock* sherlock = (Sherlock*)obj;
//         sherlock->setInitHp(ceil(sherlock->getInitHp()*1.5));
//     }
// }
// bool ExcemptionCard::canUse(Character *obj, Robot* robot) {
//     // if they don't meet each other
//     if (!obj->getCurrentPosition().isEqual(robot->getCurrentPosition())) {
//         return false;
//     }
//     else if (obj->getName() == "Sherlock") {
//         Sherlock* sherlock = (Sherlock*)obj;
//         if (sherlock->getInitHp() %2 == 1) return true;
//     }
//     return false;
// }

// void ExcemptionCard::use(Character *obj, Robot* robot) {
//     // TODO:
// }
// bool PassingCard::canUse(Character *obj, Robot* robot) {
//     // if they don't meet each other
//     if (!obj->getCurrentPosition().isEqual(robot->getCurrentPosition())) {
//         return false;
//     }
//     else if (obj->getName() == "Watson") {
//         Watson* watson = (Watson*)obj;
//         if (watson->getInitHp() %2 == 0) return true;
//     }
//     return false;
// }


// void PassingCard::use(Character *obj, Robot* robot) {
//     // TODO:
//     Position init = robot->getInit();
//     int t = (init.getRow()*11 + init.getCol())%4;
//     if (t == 0) this->challenge = "RobotS";
//     if (t == 1) this->challenge = "RobotC";
//     if (t == 2) this->challenge = "RobotSW";
//     if (t == 3) this->challenge = "all";
//     cout << robot->getName() << " " << this->challenge << endl;
//     if (robot->getName() != this->challenge && this->challenge != "all") {
//         if (obj->getName() == "Watson") {
//             Watson* watson = (Watson*)obj;
//             watson->setInitExp(watson->getInitExp() - 50);
//             cout << "Watson,  exp: " << watson->getInitExp() << endl;
//         }
//     }
// }
// ItemType PassingCard::getType() const {
//     return PASSING_CARD;
// }

// ItemType ExcemptionCard::getType() const {
//     return EXCEMPTION_CARD;
// }

// ItemType MagicBook::getType() const {
//     return MAGIC_BOOK;
// }

// ItemType EnergyDrink::getType() const {
//     return ENERGY_DRINK;
// }

// ItemType FirstAid::getType() const {
//     return FIRST_AID;
// }
// void StudyPinkProgram:: SherMeet(MovingObject *sher, MovingObject *object) {
//     Sherlock *sherlock = (Sherlock *)sher;
//     if (sherlock->getInitHp() == 0 || sherlock->getInitExp() == 0) return;
//         // nếu là watson thì trao đổi thẻ với watson, sherlock thực hiện trước.
//         // Sherlock tặng PassingCard, Watson tặng ExcemptionCard nếu có
//         if (object->getName() == "Watson") {
//             Watson *watson = (Watson *)object;
//             // Sherlock gives
//             int numPassingCard = sherlockBag->getPassingCard();
//             while (!watsonBag->isFull() && numPassingCard > 0) {
//                 // get PassingCard from sherlockBag
//                 ItemNode *item = sherlockBag->getItem(PASSING_CARD);
//                 // bring it to the top of the list
//                 sherlockBag->bring_to_head(item);
//                 // delete it from the top of the list
//                 sherlockBag->dequeue();
//                 // add to watsonBag
//                 PassingCard *pass = new PassingCard();
//                 watsonBag->insert(pass);
//                 numPassingCard--;
//             }

//             // Watson gives
//             int numExcemptionCard = watsonBag->getExcepmtionCard();
//             while (!sherlockBag->isFull() && numExcemptionCard > 0) {
//                 // get ExcemptionCard from watsonBag
//                 ItemNode *item = watsonBag->getItem(EXCEMPTION_CARD);
//                 // bring it to the top of the list
//                 watsonBag->bring_to_head(item);
//                 // delete it from the top of the list
//                 watsonBag->dequeue();
//                 ExcemptionCard *excemptionCard = new ExcemptionCard();
//                 // add to sherlockBag
//                 sherlockBag->insert(excemptionCard);
//                 numExcemptionCard--;
//             }
//         }
//         else if (object->getName() == "RobotS") {
//             RobotS* robotS = (RobotS*)object;

//             // Kiểm tra xem Sherlock có ExcemptionCard để vượt thử thách
//             ExcemptionCard * card = new ExcemptionCard();
//             ItemNode* item = sherlockBag->getItem(EXCEMPTION_CARD);
//             if (item) {
//                     sherlockBag->bring_to_head(item);
//                     sherlockBag->dequeue();
//                     sherlockBag->insert(robotS->getItem());
//                     return;
//             }

//             // if Sherlock EXP > 400. SHerlock win
//             if (sherlock->getInitExp() > 400) {
//                 sherlockBag->insert(robotS->getItem());
//             }
//             // else Sherlock will search for something to pass robot's challenge
//             else {
//                     sherlock->setInitExp(sherlock->getInitExp()*0.9);
//             }
            
//             // Sau khi gặp thử thách thì dùng thuốc hồi exp, hp
//         }

//         else if (object->getName() == "RobotW") {
//             RobotW* robotW = (RobotW*)object;
//             // Sherlock gains item from this robot
//             sherlockBag->insert(robotW->getItem());
//         }
        
//         else if (object->getName() == "RobotSW") {
//             RobotSW* robotSW = (RobotSW*)object;
//             // Kiểm tra xem Sherlock có ExcemptionCard để vượt thử thách
//             ExcemptionCard * card = new ExcemptionCard();
//             ItemNode* item = sherlockBag->getItem(EXCEMPTION_CARD);
//             // if there is something to pass
//             if (item != nullptr){
//                 // if sherlock can use this card then return
//                 if (card->canUse(sherlock, robotSW)) {
//                     // bring it to the head and delete that item
//                     sherlockBag->bring_to_head(item);
//                     sherlockBag->dequeue();
//                     sherlockBag->insert(robotSW->getItem());
//                     return;
//                 }
//             }
//             // if Sherlock EXP > 400. SHerlock win
//             if (sherlock->getInitExp() > 300 && sherlock->getInitHp() > 335) {
//                 sherlockBag->insert(robotSW->getItem());
//             }
//             else {
//                     sherlock->setInitExp(sherlock->getInitExp()*0.85);
//                     sherlock->setInitHp(sherlock->getInitHp()*0.85);
//             }
//         }

//         else if (object->getName() == "RobotC") {
//             RobotC* robotC = (RobotC*)object;
//             // Kiểm tra xem Sherlock có ExcemptionCard để vượt thử thách
//             ExcemptionCard * card = new ExcemptionCard();
//             ItemNode* item = sherlockBag->getItem(EXCEMPTION_CARD);
//             // if there is something to pass
//             if (item != nullptr){
//                 // if sherlock can use this card then return
//                 if (card->canUse(sherlock, robotC)) {
//                     // bring it to the head and delete that item
//                     sherlockBag->bring_to_head(item);
//                     sherlockBag->dequeue();
//                     this->metCrim = 1;
//                     sherlock->setPosition(criminal->getCurrentPosition());
//                     return;
//                 }
//             }

//             if (sherlock->getInitExp() > 500) {
//                 // sherlock.
//                 this->metCrim = 1;
//                 sherlock->setPosition(criminal->getCurrentPosition());
//             }
//             else {
//                 sherlockBag->insert(robotC->getItem());
//             }
//         }
//         else if (object->getName() == "Criminal") {
//             this->metCrim = 1;            
//         }
//         else {
//             cout << "ERROR: " << object->getName() << "\t" << sher->getName() << "\n";
//         }
//     if (sherlock->getInitExp() == 0 || sherlock->getInitHp() ==0) sherlock->isStop = true;

// }



// void StudyPinkProgram::WatMeet(MovingObject *wat, MovingObject *object) {
//     Watson *watson = (Watson *)wat;
//     if (watson->getInitHp() == 0 || watson->getInitExp() == 0) return;

//     // meet robotS
//     if (object->getName() == "RobotS") return;
//     // meet robotW
//     else if (object->getName() == "RobotW") {
//         RobotW* robotW = (RobotW*)object;
//         PassingCard * card = new PassingCard();
//         // Kiểm tra xem Watson có PassingCard để vượt thử thách
//         ItemNode* item = watsonBag->getItem(PASSING_CARD);
//         // if there is something to pass
//         if (item != nullptr){
//             // if sherlock can use this card then return
//             if (card->canUse(sherlock, robotW)) {
//                 watsonBag->bring_to_head(item);
//                 watsonBag->dequeue();
//                 card->use(watson, robotW);
//                 watsonBag->insert(robotW->getItem());
//                 return;
//             }
//         }
//         // if Watson EXP > 350. Watson win
//         if (watson->getInitHp() > 350){
//             watsonBag->insert(robotW->getItem());
//         }
//         else {
//             watson->setInitHp(watson->getInitHp()*0.95);
//         }
//     }
//     // meet robotSW
//     else if (object->getName() == "RobotSW"){
//         RobotSW* robotSW = (RobotSW*)object;
//         // Kiểm tra xem Watson có PassingCard để vượt thử thách
//         PassingCard * card = new PassingCard();
//         ItemNode* item = watsonBag->getItem(PASSING_CARD);
//         // if there is something to pass
//         if (item != nullptr){
//             // if sherlock can use this card then return
//             if (card->canUse(sherlock, robotSW)) {
//                 watsonBag->bring_to_head(item);
//                 watsonBag->dequeue();
//                 card->use(watson, robotSW);
//                 return;
//             }
//             // else he lose the challenge and lost 10% exp
//             else {
//                 watson->setInitHp(watson->getInitHp()*0.85);
//                 watson->setInitExp(watson->getInitExp()*0.85);
//             }
//         }
//         if (watson->getInitExp() > 600 && watson->getInitHp() > 165) {
//             watsonBag->insert(robotSW->getItem());
//         }
//         else {
//             watson->setInitHp(watson->getInitHp()*0.85);
//             watson->setInitExp(watson->getInitExp()*0.85);
//         }
//     }


//     else if (object->getName() == "RobotC") {
//         RobotC* robotC = (RobotC*)object;
//         watsonBag->insert(robotC->getItem());
//     }
//     else if (object->getName() == "Criminal"){
//         this->metCrim = 1;
//         cout << "Watson caught criminal" << endl;
//     }
//     if (watson->getInitExp() == 0 || watson->getInitHp() ==0) watson->isStop = true;
// }


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////