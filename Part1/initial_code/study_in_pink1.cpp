#include "study_in_pink1.h"

bool readFile(
    const string &filename,
    int &HP1,
    int &HP2,
    int &EXP1,
    int &EXP2,
    int &M1,
    int &M2,
    int &E1,
    int &E2,
    int &E3)
{
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open())
    {
        ifs >> HP1 >> HP2 >> EXP1 >> EXP2 >> M1 >> M2 >> E1 >> E2 >> E3;
        return true;
    }
    else
    {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

void resetEXP(int &exp)
{
    if (exp < 0)
        exp = 0;
    else if (exp > 600)
        exp = 600;
}
void resetHP(int &hp)
{
    if (hp < 0)
        hp = 0;
    else if (hp > 666)
        hp = 666;
}
void resetMONEY(int &money)
{
    if (money < 0)
        money = 0;
    else if (money > 3000)
        money = 3000;
}
//  Task 1
int firstMeet(int &exp1, int &exp2, int e1)
{
    // TODO: Complete this function
    if (e1 < 0 || e1 > 99)
    {
        return -99;
    }
    resetEXP(exp1);
    resetEXP(exp2);
    // Reset exp1 and exp2 values if invalid
    /* exp1 : exp of Sherlock Homes
       exp2 : exp of Watson
       E1: index event1 */
    // Trường hợp 1: E1 thuộc [0:3]
    if (e1 >= 0 && e1 <= 3)
    {
        switch (e1)
        {
        case 0:
            exp2 += 29;
            break;
        case 1:
            exp2 += 45;
            break;
        case 2:
            exp2 += 75;
            break;
        case 3:
            exp2 += (29 + 45 + 75);
            break;
        }
        // Chỉ số quyết định của Sherlock Homes
        int d = e1 * 3 + exp1 * 7;
        float D = d;
        if (d % 2 == 0)
        {
            exp1 = ceil(exp1 + D / 200);
        }
        else
        {
            exp1 = ceil(exp1 - D / 100);
        }
        resetEXP(exp1);
        resetEXP(exp2);
    }
    // Trường hợp 2: E1 thuộc [4:99]
    else if (e1 >= 4 && e1 <= 99)
    {
        float E1 = e1;
        // Thông tin số 1
        if (e1 >= 4 && e1 <= 19)
        {
            exp2 = ceil(exp2 + E1 / 4 + 19);
        }
        // Thông tin số 2
        else if (e1 >= 20 && e1 <= 49)
        {
            exp2 = ceil(exp2 + E1 / 9 + 21);
        }
        // Thông tin số 3
        else if (e1 >= 50 && e1 <= 65)
        {
            exp2 = ceil(exp2 + E1 / 16 + 17);
        }
        // Thông tin số 4
        else if (e1 >= 66 && e1 <= 79)
        {
            exp2 = ceil(exp2 + E1 / 4 + 19);
            if (exp2 > 200)
            {
                exp2 = ceil(exp2 + E1 / 9 + 21);
            }
        }
        else if (e1 >= 80 && e1 <= 99)
        {
            exp2 = ceil(exp2 + E1 / 4 + 19);
            exp2 = ceil(exp2 + E1 / 9 + 21);
            if (exp2 > 400)
            {
                exp2 = ceil(exp2 + E1 / 16 + 17);
                exp2 = ceil(exp2 * 1.15);
            }
        }
        exp1 -= e1;
        resetEXP(exp1);
        resetEXP(exp2);
    }
    return exp1 + exp2;
}

// Task 2
int findSochinhphuong(int EXP1)
{
    int n = sqrt(EXP1);
    int lower = n * n;
    int upper = (n + 1) * (n + 1);

    int dis_lower = abs(EXP1 - lower);
    int dis_upper = abs(EXP1 - upper);

    if (dis_lower < dis_upper)
    {
        return lower;
    }
    else if (dis_lower > dis_upper)
    {
        return upper;
    }
    return lower;
}
int multiplication(int value, float num)
{
    double result = value * num;
    if (result - static_cast<int>(result) > 0.001)
    {
        result = ceil(result);
    }
    return result;
}
int traceLuggage(int &HP1, int &EXP1, int &M1, int E2)
{
   // TODO: Complete this function
    if (E2 < 0 || E2 > 99)
    {
        return -99;
    }
    resetHP(HP1);
    resetEXP(EXP1);
    resetMONEY(M1);
    // Way 1
    float P1;
    int S1 = findSochinhphuong(EXP1);
    if (EXP1 >= S1)
    {
        P1 = 1; 
    }
    else
    {
        float exp1 = EXP1;
        float s1 = S1;
        P1 = round(((exp1 / s1 + 80) / 123) * 100) / 100; 
    }
    // Way 2
    float P2;
    if (E2 % 2 != 0)
    {
        const double check = (float)M1 / 2;
        bool checkFlag = true;
        while (checkFlag)
        {
            // Mua nước
            if (HP1 < 200 && M1 > 0)
            {
                HP1 = multiplication(HP1, 1.3);
                M1 -= 150;
                resetHP(HP1);
                resetMONEY(M1);
                if (M1 < check || M1 == 0)
                {
                    checkFlag = false;
                    break;
                }
            }
            else if (HP1 >= 200 && M1 > 0)
            {
                HP1 = multiplication(HP1, 1.1);
                M1 -= 70;
                resetHP(HP1);
                resetMONEY(M1);
                if (M1 < check || M1 == 0)
                {
                    checkFlag = false;
                    break;
                }
            }
            // Thuê xe
            if (EXP1 < 400 && M1 > 0)
            {
                M1 -= 200; // xe taxi
                EXP1 = multiplication(EXP1, 1.13);
                resetMONEY(M1);
                resetEXP(EXP1);
                if (M1 < check || M1 == 0)
                {
                    checkFlag = false;
                    break;
                }
            }
            else if (EXP1 >= 400 && M1 > 0)
            {
                M1 -= 120; // xe ngựa
                EXP1 = ceil(EXP1 * 1.13);
                resetMONEY(M1);
                resetEXP(EXP1);
                if (M1 < check || M1 == 0)
                {
                    checkFlag = false;
                    break;
                }
            }

            // Người vô gia cư
            if (EXP1 < 300 && M1 > 0)
            {
                M1 -= 100;
                EXP1 = multiplication(EXP1, 0.9);
                resetMONEY(M1);
                resetEXP(EXP1);
                if (M1 < check || M1 == 0)
                {
                    checkFlag = false;
                    break;
                }
            }
            else if (EXP1 >= 300 && M1 > 0)
            {
                M1 -= 120;
                EXP1 = multiplication(EXP1, 0.9);
                resetMONEY(M1);
                resetEXP(EXP1);
                if (M1 < check || M1 == 0)
                {
                    checkFlag = false;
                    break;
                }
            }
            if (M1 < check || M1 == 0)
            {
                checkFlag = false;
                break;
            }
        }
        HP1 = multiplication(HP1, 0.83);
        EXP1 = multiplication(EXP1, 1.17);
        resetHP(HP1);
        resetEXP(EXP1);
    }
    else // E2 là số chẵn
    {
        // Mua nước
        if (HP1 < 200 && M1 > 0)
        {
            HP1 = multiplication(HP1, 1.3);
            M1 -= 150;
            resetHP(HP1);
            resetMONEY(M1);
        }
        else if (HP1 >= 200 && M1 > 0)
        {
            HP1 = multiplication(HP1, 1.1);
            M1 -= 70;
            resetHP(HP1);
            resetMONEY(M1);
        }
        // Thuê xe
        if (EXP1 < 400 && M1 > 0)
        {
            M1 -= 200; // xe taxi
            EXP1 = multiplication(EXP1, 1.13);
            resetEXP(EXP1);
            resetMONEY(M1);
        }
        else if (EXP1 >= 400 && M1 > 0)
        {
            M1 -= 120; // xe ngựa
            EXP1 = multiplication(EXP1, 1.13);
            resetEXP(EXP1);
            resetMONEY(M1);
        }
        // Người vô gia cư
        if (EXP1 < 300 && M1 > 0)
        {
            M1 -= 100;
            EXP1 = multiplication(EXP1, 0.9);
            resetMONEY(M1);
            resetEXP(EXP1);
        }
        else if (EXP1 >= 300 && M1 > 0)
        {
            M1 -= 120;
            EXP1 = multiplication(EXP1, 0.9);
            resetMONEY(M1);
            resetEXP(EXP1);
        }
        EXP1 = multiplication(EXP1, 1.17);
        HP1 = multiplication(HP1, 0.83);
        resetEXP(EXP1);
        resetHP(HP1);
    }
    int S2 = findSochinhphuong(EXP1);
    if (EXP1 >= S2)
    {
        P2 = 1;
    }
    else
    {
        float exp1 = EXP1;
        float s2 = S2;
        P2 = round(((exp1 / s2 + 80) / 123) * 100) / 100;
    }
    // Way 3
    float P3;
    float arr[] = {0.32, 0.47, 0.28, 0.79, 1, 0.5, 0.22, 0.83, 0.64, 0.11};
    float *p = new float[10];
    for (int i = 0; i < 10; i++)
    {
        p[i] = arr[i];
    }
    int index;
    if (E2 < 10)
    {
        index = E2;
    }
    else
    {
        int sum = E2 / 10 + E2 % 10;
        index = sum % 10;
    }
    P3 = p[index];
    if (P1 == 1 && P2 == 1 && P3 == 1)
    {
        EXP1 = multiplication(EXP1, 0.75);
    }
    else
    {
        float P = (P1 + P2 + P3) / 3;
        if (P < 0.5)
        {
            HP1 = multiplication(HP1, 0.85);
            EXP1 = multiplication(EXP1, (1.15));
        }
        else
        {
            HP1 = multiplication(HP1, 0.9);
            EXP1 = multiplication(EXP1, 1.2);
        }
    }
    resetHP(HP1);
    resetEXP(EXP1);
    delete[] p;
    return HP1 + EXP1 + M1;
}

// Task 3
int point(int arrTaxi[][10], int i, int j)
{
    // Tìm giá trị lớn nhất trên đường chéo trái
    int max_diagonal_left = arrTaxi[i][j];
    int x = i - min(i, j);
    int y = j - min(i, j);
    while (x <= 9 && y <= 9)
    {
        max_diagonal_left = max(max_diagonal_left, arrTaxi[x][y]);
        ++x;
        ++y;
    }
    // Tìm giá trị lớn nhất trên đường chéo phải
    int max_diagonal_right = arrTaxi[i][j];
    x = i - min(i, 9 - j);
    y = j + min(i, 9 - j);
    while (x <= 9 && y >= 0)
    {
        max_diagonal_right = max(max_diagonal_right, arrTaxi[x][y]);
        ++x;
        --y;
    }
    return abs(max(max_diagonal_left, max_diagonal_right));
}
int chaseTaxi(int &HP1, int &EXP1, int &HP2, int &EXP2, int E3)
{
    // TODO: Complete this function
    if (E3 < 0 || E3 > 99)
    {
        return -99;
    }
    resetHP(HP1);
    resetHP(HP2);
    resetEXP(EXP1);
    resetEXP(EXP2);
    int count1 = 0, count2 = 0;
    int arrTaxi[10][10] = {};
    int arrMain[10][10] = {};
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            arrTaxi[i][j] = ((E3 * j) + (i * 2)) * (i - j);
            if (arrTaxi[i][j] > E3 * 2)
            {
                count1++;
            }
            else if (arrTaxi[i][j] < -E3)
            {
                count2++;
            }
        }
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            arrMain[i][j] = point(arrTaxi, i, j);
        }
    }
    while (count1 >= 10)
    {
        int num1 = count1 / 10;
        int num2 = count1 % 10;
        count1 = num1 + num2;
        if (count1 < 10)
            break;
    }
    while (count2 >= 10)
    {
        int num1 = count2 / 10;
        int num2 = count2 % 10;
        count2 = num1 + num2;
        if (count2 < 10)
            break;
    }
    if (abs(arrTaxi[count1][count2]) > arrMain[count1][count2])
    {
        EXP1 = multiplication(EXP1, 0.88);
        EXP2 = multiplication(EXP2, 0.88);
        HP1 = multiplication(HP1, 0.9);
        HP2 = multiplication(HP2, 0.9);
        resetEXP(EXP1);
        resetEXP(EXP2);
        resetHP(HP1);
        resetHP(HP2);
        return arrTaxi[count1][count2];
    }
    else
    {
        EXP1 = multiplication(EXP1, 1.12);
        EXP2 = multiplication(EXP2, 1.12);
        HP1 = multiplication(HP1, 1.1);
        HP2 = multiplication(HP2, 1.1);
        resetEXP(EXP1);
        resetEXP(EXP2);
        resetHP(HP1);
        resetHP(HP2);
    }
    return arrMain[count1][count2];
}

// Task 4
bool checkChar(const char *s)
{
    size_t len = strlen(s);
    for (size_t i = 0; i < len - 2; i++)
    {
        if (s[i] == s[i + 1] && s[i + 1] == s[i + 2])
            return true;
    }
    return false;
}
bool specialCharacter(const char *s, const char *character)
{
    string password(s);
    for (auto c : password)
    {
        if (strchr(character, c) != nullptr)
        {
            return false;
        }
    }
    return true;
}
int checkPassword(const char *s, const char *email)
{
    // TODO: Complete this function
    const char *found = strchr(email, '@');
    char se[256];
    if (found != nullptr)
    {
        size_t len = found - email;
        strncpy(se, email, len);
        se[len] = '\0';
    }
    size_t length = strlen(s);
    const char *position = strstr(s, se);
    bool flag = checkChar(s);
    const char *characters = "@#%$!";
    if (length < 8) // mật khẩu ngắn
    {
        return -1;
    }
    else if (length > 20) // mật khẩu dài
    {
        return -2;
    }
    else if (position != nullptr) // s có chứa se hay không?
    {
        size_t index;
        size_t se_length = strlen(se);
        size_t s_length = strlen(s);
        // Tìm vị trí của kí tự bị trùng đầu tiên trong chuỗi s
        for (size_t i = 0; i < s_length - se_length + 1; ++i)
        {
            if (strncmp(&s[i], se, se_length) == 0)
            {
                index = i;
                break;
            }
        }
        int sei = static_cast<int>(index);
        return -(300 + sei);
    }
    else if (flag) // s có chứa nhiều hơn 2 kí tự liên tiếp
    {
        size_t len = strlen(s);
        int sci;
        for (size_t i = 0; i < len - 2; i++)
        {
            if (s[i] == s[i + 1] && s[i + 1] == s[i + 2])
            {
                sci = static_cast<int>(i);
                break;
            }
        }
        return -(400 + sci);
    }
    else if (specialCharacter(s, characters)) // s không chứa kí tự đặc biệt
    {
        return -5;
    }
    else
    { // s chứa kí tự đặc biệt nằm ngoài giá trị cho phép
        for (size_t i = 0; i < strlen(s); i++)
        {
            if (isalpha(s[i]) || isdigit(s[i]))
            {
                continue;
            }
            if (strchr(characters, s[i]) == nullptr)
            {
                return static_cast<int>(i);
            }
        }
    }
    return -10;
}

// Task 5
int findCorrectPassword(const char *arr_pwds[], int num_pwds)
{
    // TODO: Complete this function
    //  Mảng để lưu số lần xuất hiện của mỗi chuỗi
    int freq[1000] = {0};

    // Tính số lần xuất hiện của mỗi chuỗi
    for (int i = 0; i < num_pwds; ++i)
    {
        // Nếu chuỗi đã được đếm trước đó, không cần kiểm tra lại
        if (freq[i] != 0)
            continue;

        // Lặp qua các chuỗi còn lại trong mảng và so sánh với chuỗi hiện tại
        for (int j = i; j < num_pwds; ++j)
        {
            if (strcmp(arr_pwds[i], arr_pwds[j]) == 0)
            {
                freq[i]++; // Tăng tần suất xuất hiện của chuỗi
            }
        }
    }

    // Tìm chuỗi xuất hiện nhiều nhất
    int max_freq = 0;
    std::string most_common;
    for (int i = 0; i < num_pwds; ++i)
    {
        if (freq[i] > max_freq || (freq[i] == max_freq && strlen(arr_pwds[i]) > most_common.length()))
        {
            max_freq = freq[i];
            most_common = arr_pwds[i];
        }
    }

    // Tìm vị trí xuất hiện đầu tiên của chuỗi xuất hiện nhiều nhất trong arr_pwds
    for (int i = 0; i < num_pwds; ++i)
    {
        if (strcmp(arr_pwds[i], most_common.c_str()) == 0)
        {
            return i;
        }
    }

    return -1; // Không tìm thấy
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////