#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void print_memory_block();
void print_instruction_register();
void print_general_purpose_register();
void Load();
void INIT();
void START_EXECUTION();
void EXECUTE_USER_PROGRAM();
void MOS();
void GD();
void PD();
void H();
void BT();
void SR();
void LR();
void CR();

int flag = 0;
int currentLine;

char M[100][4];
char IR[4];
char R[4];
char buffer[40];
int IC;
int C;
int SI;

void print_memory_block() {
    cout << "Memory block is:\n\n";
    for (int i = 0; i < 100; i++) {
        if (i >= 10)
            cout << i << "  ";
        else
            cout << i << "   ";
        for (int j = 0; j < 4; j++) {
            cout << "|" << M[i][j];
        }
        cout << "|\n";
    }
}

void print_instruction_register() {
    for (int i = 0; i < 4; i++) {
        cout << IR[i];
    }
    cout << "\n";
}

void print_general_purpose_register() {
    for (int i = 0; i < 4; i++) {
        cout << R[i];
    }
    cout << "\n";
}

void Load() {
    int i = 0;
    ifstream fp("input1.txt");
    string str;

    while (getline(fp, str)) {
        if (str.substr(0, 4) == "$AMJ") {
            cout << "AMJ instruction found\n";
            int row = 0, col = 0;

            while (getline(fp, str)) {
                if (str.substr(0, 4) == "$DTA")
                    break;

                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == ' ')
                        break;
                    M[row][col++] = str[i];
                    if (col == 4) {
                        row++;
                        col = 0;
                    }
                }
            }
            currentLine = (int)fp.tellg();
            cout << "Loading is completed\n";
        }

        if (str.substr(0, 4) == "$DTA") {
            START_EXECUTION();
        }

        if (str.substr(0, 4) == "$END") {
            i++;
            print_memory_block();
            cout << "\n\n\nEND OF JOB no. " << i << "\n\n\n";
            cout << "Press Enter to load another job:\n";
            cin.get();
            INIT();
        }
    }
}

void INIT() {
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 4; j++)
            M[i][j] = ' ';

    for (int i = 0; i < 4; i++) {
        IR[i] = ' ';
        R[i] = ' ';
    }

    IC = 0;
    SI = 0;
    C = 0;
    currentLine = 0;
}

void START_EXECUTION() {
    IC = 0;
    EXECUTE_USER_PROGRAM();
}

void EXECUTE_USER_PROGRAM() {
    while (true) {
        for (int i = 0; i < 4; i++) {
            IR[i] = M[IC][i];
        }

        cout << "\n\nInstruction register has:\n\n";
        print_instruction_register();

        if (IR[0] == '\0' && IR[1] == '\0') {
            cout << "Error: Instruction register contains invalid data.\n";
            break;
        }

        IC++;

        if (IR[0] == 'G' && IR[1] == 'D') {
            SI = 1;
            MOS();
        } else if (IR[0] == 'P' && IR[1] == 'D') {
            SI = 2;
            MOS();
        } else if (IR[0] == 'H' && IR[1] == '*') {
            SI = 3;
            MOS();
            break;
        } else if (IR[0] == 'L' && IR[1] == 'R') {
            LR();
        } else if (IR[0] == 'S' && IR[1] == 'R') {
            SR();
        } else if (IR[0] == 'B' && IR[1] == 'T') {
            BT();
        } else if (IR[0] == 'C' && IR[1] == 'R') {
            CR();
        } else {
            cout << "Unknown instruction encountered.\n";
            break;
        }
    }
}

void MOS() {
    if (SI == 1)
        GD();
    else if (SI == 2)
        PD();
    else if (SI == 3)
        H();
}

void GD() {
    int row = (IR[2] - '0') * 10 + (IR[3] - '0');
    int col = 0;
    string str;
    ifstream fp("input1.txt");

    fp.seekg(currentLine);
    getline(fp, str);

    for (int i = 0; i < str.length(); i++) {
        M[row][col++] = str[i];
        if (col == 4) {
            row++;
            col = 0;
        }
    }

    currentLine = (int)fp.tellg();
}

void PD() {
    ofstream fp("output1.txt", ios::app);
    if (flag == 0)
        flag++;
    else
        fp << "\n";

    int row = (IR[2] - '0') * 10 + (IR[3] - '0');
    for (int i = row; i < row + 10; i++) {
        for (int j = 0; j < 4; j++) {
            if (M[i][j] == '_')
                break;
            fp << M[i][j];
        }
    }
}

void H() {
    ofstream fp("output1.txt", ios::app);
    fp << "\n\n";
}

void LR() {
    int row = (IR[2] - '0') * 10 + (IR[3] - '0');
    for (int i = 0; i < 4; i++) {
        R[i] = M[row][i];
    }
}

void SR() {
    int row = (IR[2] - '0') * 10 + (IR[3] - '0');
    for (int i = 0; i < 4; i++) {
        M[row][i] = R[i];
    }
}

void CR() {
    int row = (IR[2] - '0') * 10 + (IR[3] - '0');
    C = 1;
    for (int i = 0; i < 4; i++) {
        if (R[i] != M[row][i]) {
            C = 0;
            break;
        }
    }
}

void BT() {
    if (C == 1) {
        IC = (IR[2] - '0') * 10 + (IR[3] - '0');
        C = 0;
    }
}

int main() {
    cout << "Implementation of OS phase 1\n";
    INIT();
    Load();
    return 0;
}
