#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int NumTable[2][7][7];
char AlphaTable[2][7][7];

int Turn[2];

int Score[2];

void ClearScr(){
    system("@cls||clear");
}

void SwapNum(int Player, int Pos1, int Pos2){
    int i, j, ntemp, row1 = -1, row2 = -1, col1 = -1, col2 = -1;
    char ctemp;

    for (i = 0; i < 7; i++){
        for (j = 0; j < 7; j++){
            if (NumTable[Player-1][i][j] == Pos1){
                row1 = i;
                col1 = j;
            }
            if (NumTable[Player-1][i][j] == Pos2){
                row2 = i;
                col2 = j;
            }
        }
    }

    ntemp = NumTable[Player-1][row1][col1];
    NumTable[Player-1][row1][col1]= NumTable[Player-1][row2][col2];
    NumTable[Player-1][row2][col2] = ntemp;

    ctemp = AlphaTable[Player-1][row1][col1];
    AlphaTable[Player-1][row1][col1] = AlphaTable[Player-1][row2][col2];
    AlphaTable[Player-1][row2][col2] = ctemp;

}

int CheckInRange(int Pos1, int Pos2){
    if (Pos1 == Pos2 || Pos1 < 1 || Pos2 < 1 || Pos1 > 49 || Pos2 > 49)
        return 0;
    return 1;
}

int CheckPattern(){
    int i, j, k;
    for (i = 0; i < 2; i++){

        //เช็คแนวนอน
        for (j = 0; j < 7; j++){
            for (k = 1; k < 6; k++){
                //เหมือนกัน 3
                if (AlphaTable[i][j][k-1] == AlphaTable[i][j][k] &&
                    AlphaTable[i][j][k] == AlphaTable[i][j][k+1]){
                        Score[i] += 1;
                    }
                //เหมือนกัน 6
                if (AlphaTable[i][j][k-1] == AlphaTable[i][j][k] &&
                    AlphaTable[i][j][k] == AlphaTable[i][j][k+1]&&
                    AlphaTable[i][j][k+1] == AlphaTable[i][j][k+2]&&
                    AlphaTable[i][j][k+2] == AlphaTable[i][j][k+3]&&
                    AlphaTable[i][j][k+3] == AlphaTable[i][j][k+4]){
                        Score[i] += 2;
                    }
            }
        }

        //เช็คแนวตั้ง
        for (j = 1; j < 6; j++){
            for (k = 0; k < 7; k++){
                //เหมือนกัน 3
                if (AlphaTable[i][j-1][k] == AlphaTable[i][j][k] &&
                    AlphaTable[i][j][k] == AlphaTable[i][j+1][k]){
                        Score[i] += 1;
                        continue;
                    }
                //เหมือนกัน 6
                if (AlphaTable[i][j-1][k] == AlphaTable[i][j][k] &&
                    AlphaTable[i][j][k] == AlphaTable[i][j+1][k] &&
                    AlphaTable[i][j+1][k] == AlphaTable[i][j+2][k] &&
                    AlphaTable[i][j+2][k] == AlphaTable[i][j+3][k] &&
                    AlphaTable[i][j+3][k] == AlphaTable[i][j+4][k]){
                        Score[i] += 2;
                    }
            }
        }
        //เช็คตามแพทเทิร์น

        //เช็คซ้ำตามจุดที่กำหนด
        if (AlphaTable[i][0][0] == AlphaTable[i][0][6] &&
            AlphaTable[i][0][6] == AlphaTable[i][3][3] &&
            AlphaTable[i][3][3] == AlphaTable[i][6][0] &&
            AlphaTable[i][6][0] == AlphaTable[i][6][6])
            Score[i] += 10;
        //ซ้ำแนวทะแยงซ้าย
        if (AlphaTable[i][0][0] == AlphaTable[i][1][1] &&
            AlphaTable[i][1][1] == AlphaTable[i][2][2] &&
            AlphaTable[i][2][2] == AlphaTable[i][3][3] &&
            AlphaTable[i][3][3] == AlphaTable[i][4][4] &&
            AlphaTable[i][4][4] == AlphaTable[i][5][5] &&
            AlphaTable[i][5][5] == AlphaTable[i][6][6])
            Score[i] += 20;
        //ซ้ำแนวทะแยงขวา
        if (AlphaTable[i][0][6] == AlphaTable[i][1][5] &&
            AlphaTable[i][1][5] == AlphaTable[i][2][4] &&
            AlphaTable[i][2][4] == AlphaTable[i][3][3] &&
            AlphaTable[i][3][3] == AlphaTable[i][4][2] &&
            AlphaTable[i][4][2] == AlphaTable[i][5][1] &&
            AlphaTable[i][5][1] == AlphaTable[i][6][0])
            Score[i] += 20;
    }
}

void DrawTable(int Player){
    ClearScr();
    printf("Player %d Has %d Turn Left\n", Player, Turn[Player-1]);
    printf("----------------------\n");
    int i, j;
    for (i = 0; i < 7; i++){
        for (j = 0; j < 7; j++){
            if (NumTable[Player - 1][i][j] < 10)
                printf("| %d", NumTable[Player - 1][i][j]);
            else
                printf("|%d", NumTable[Player - 1][i][j]);
            }
        printf("|\n");
    }
    printf("----------------------\n");
}

void DrawAlpha(){
    ClearScr();
    printf("Player 1\n");
    printf("-----------------------------\n");
    int i, j;
    for (i = 0; i < 7; i++){
        for (j = 0; j< 7; j++){
            if (AlphaTable[0][i][j] == 'A')
                printf("| \033[1;31m%c \033[0m", AlphaTable[0][i][j]);
            if (AlphaTable[0][i][j] == 'B')
                printf("| \033[1;32m%c \033[0m", AlphaTable[0][i][j]);
            if (AlphaTable[0][i][j] == 'C')
                printf("| \033[1;33m%c \033[0m", AlphaTable[0][i][j]);
            if (AlphaTable[0][i][j] == 'D')
                printf("| \033[1;34m%c \033[0m", AlphaTable[0][i][j]);
            if (AlphaTable[0][i][j] == 'E')
                printf("| \033[1;35m%c \033[0m", AlphaTable[0][i][j]);
            if (AlphaTable[0][i][j] == 'F')
                printf("| \033[1;36m%c \033[0m", AlphaTable[0][i][j]);
            if (AlphaTable[0][i][j] == 'G')
                printf("| \033[1;37m%c \033[0m", AlphaTable[0][i][j]);
        }
        printf("|\n");
    }
    printf("-----------------------------\n");
    printf("Player 2\n");
    printf("-----------------------------\n");
    for (i = 0; i < 7; i++){
        for (j = 0; j < 7; j++){
            if (AlphaTable[1][i][j] == 'A')
                printf("| \033[1;31m%c \033[0m", AlphaTable[1][i][j]);
            if (AlphaTable[1][i][j] == 'B')
                printf("| \033[1;32m%c \033[0m", AlphaTable[1][i][j]);
            if (AlphaTable[1][i][j] == 'C')
                printf("| \033[1;33m%c \033[0m", AlphaTable[1][i][j]);
            if (AlphaTable[1][i][j] == 'D')
                printf("| \033[1;34m%c \033[0m", AlphaTable[1][i][j]);
            if (AlphaTable[1][i][j] == 'E')
                printf("| \033[1;35m%c \033[0m", AlphaTable[1][i][j]);
            if (AlphaTable[1][i][j] == 'F')
                printf("| \033[1;36m%c \033[0m", AlphaTable[1][i][j]);
            if (AlphaTable[1][i][j] == 'G')
                printf("| \033[1;37m%c \033[0m", AlphaTable[1][i][j]);
        }
        printf("|\n");
    }
    printf("-----------------------------\n");
}

void RandomAlpha(){
    char Alpha[] = "ABCDEFG";
    int i, j, k;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 7; j++)
            for (k = 0; k < 7; k++){
                int row = (rand() % 7);
                int col = (rand() % 7);
                if (AlphaTable[i][row][col] == ' ')
                    AlphaTable[i][row][col] = Alpha[j];
                else
                    k -= 1;
            }
}

void Init(){
    int i, j;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++){
        NumTable[0][i][j] = NumTable[0][i][j-1] + 1;
        NumTable[1][i][j] = NumTable[1][i][j-1] + 1;
        AlphaTable[0][i][j] = ' ';
        AlphaTable[1][i][j] = ' ';
        }

    Turn[0] = 10;
    Turn[1] = 10;
    Score[0] = 0;
    Score[1] = 0;
    srand ( time(NULL) );

    RandomAlpha();
}

int main(){

    Init();

    int Player = 1;
    while (1){

        int Pos1 = 0, Pos2 = 0;

        do{
            DrawTable(Player);
            printf("Player %d Choose 1 Number : ", Player);
            scanf("%d", &Pos1);
            printf("Player %d Choose Another Number to Swap : ", Player);
            scanf("%d", &Pos2);

        }while (CheckInRange(Pos1, Pos2) == 0);
        
        SwapNum(Player, Pos1, Pos2);
        
        Turn[Player - 1] -= 1;
        Player += 1;
        if (Player > 2)
            Player = 1;
        if (Turn[0] <= 0 && Turn[1] <= 0)
            break;
    }
    CheckPattern();
    DrawAlpha();
    printf("Player 1 Score : %d\n", Score[0]);
    printf("Player 2 Score : %d\n", Score[1]);
    if (Score[0] > Score[1])
        printf("!!Player 1 Win!!\n");
    else if (Score[0] < Score[1])
        printf("!!Player 2 Win!!\n");
    else
        printf("!!DRAW!!\n");

    printf("Press any key to continue...");

    getch();

    return 0;
}