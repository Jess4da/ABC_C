#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int NumTable[2][49];
char AlphaTable[2][49];

int Turn[2];

int Score[2];

void ClearScr(){
    system("@cls||clear");
}

void SwapNum(int Player, int Pos1, int Pos2){
    int i, ntemp, ind1 = -1, ind2 = -1;
    char ctemp;

    for (i = 0; i < 49; i++){
        if (NumTable[Player-1][i] == Pos1)
            ind1 = i;
        if (NumTable[Player-1][i] == Pos2)
            ind2 = i;
        if (ind1 != -1 && ind2 != -1)
            break;
    }

    ntemp = NumTable[Player-1][ind1];
    NumTable[Player-1][ind1] = NumTable[Player-1][ind2];
    NumTable[Player-1][ind2] = ntemp;

    ctemp = AlphaTable[Player-1][ind1];
    AlphaTable[Player-1][ind1] = AlphaTable[Player-1][ind2];
    AlphaTable[Player-1][ind2] = ctemp;

}

void SwapAlpha(int Player, int Pos1, int Pos2){
    int i, ind1 = -1, ind2 = -1;
    char temp;

    for (i = 0; i < 49; i++){
        if (AlphaTable[Player-1][i] == Pos1)
            ind1 = i;
        if (AlphaTable[Player-1][i] == Pos2)
            ind2 = i;
        if (ind1 != -1 && ind2 != -1)
            break;
    }

    temp = NumTable[Player-1][ind1];
    NumTable[Player-1][ind1] = NumTable[Player-1][ind2];
    NumTable[Player-1][ind2] = temp;
}

int CheckInRange(int Pos1, int Pos2){
    if (Pos1 == Pos2 || Pos1 < 1 || Pos2 < 1 || Pos1 > 49 || Pos2 > 49)
        return 0;
    return 1;
}

int CheckPattern(){
    int i, j;
    for (i = 0; i < 2; i++){
        for (j = 0; j < 7; j++){
            //เช็คแนวตั้ง

            //เหมือนกัน 6
            if (AlphaTable[i][j] == AlphaTable[i][j+7] &&
                AlphaTable[i][j+7] == AlphaTable[i][j+14] &&
                AlphaTable[i][j+14] == AlphaTable[i][j+21] &&
                AlphaTable[i][j+21] == AlphaTable[i][j+28] &&
                AlphaTable[i][j+28] == AlphaTable[i][j+35])
                Score[i] += 1;
            //เหมือนกัน 3
            else if (AlphaTable[i][j] == AlphaTable[i][j+7] &&
                     AlphaTable[i][j+7] == AlphaTable[i][j+14])
                Score[i] += 1;
            
            //เช็คแนวนอน

            //เหมือนกัน 6
            if (AlphaTable[i][j] == AlphaTable[i][j+1] &&
                AlphaTable[i][j+1] == AlphaTable[i][j+2] &&
                AlphaTable[i][j+2] == AlphaTable[i][j+3] &&
                AlphaTable[i][j+3] == AlphaTable[i][j+4] &&
                AlphaTable[i][j+4] == AlphaTable[i][j+5])
                Score[i] += 1;
            //เหมือนกัน 3
            else if (AlphaTable[i][j] == AlphaTable[i][j+1] &&
                     AlphaTable[i][j+1] == AlphaTable[i][j+2])
                Score[i] += 1;

            //เช็คตามแพทเทิร์น
        }
        //เช็คซ้ำตามจุดที่กำหนด
        if (AlphaTable[i][0] == AlphaTable[i][6] &&
                AlphaTable[i][6] == AlphaTable[i][24] &&
                AlphaTable[i][24] == AlphaTable[i][42] &&
                AlphaTable[i][42] == AlphaTable[i][48])
                Score[i] += 10;

        //ซ้ำแนวทะแยงซ้าย
        if (AlphaTable[i][0] == AlphaTable[i][8] &&
                AlphaTable[i][8] == AlphaTable[i][16] &&
                AlphaTable[i][16] == AlphaTable[i][24] &&
                AlphaTable[i][24] == AlphaTable[i][32] &&
                AlphaTable[i][32] == AlphaTable[i][40] &&
                AlphaTable[i][40] == AlphaTable[i][48])
                Score[i] += 20;
        //ซ้ำแนวทะแยงขวา
        if (AlphaTable[i][6] == AlphaTable[i][12] &&
                AlphaTable[i][12] == AlphaTable[i][18] &&
                AlphaTable[i][18] == AlphaTable[i][24] &&
                AlphaTable[i][24] == AlphaTable[i][30] &&
                AlphaTable[i][30] == AlphaTable[i][36] &&
                AlphaTable[i][36] == AlphaTable[i][42])
                Score[i] += 20;
    }
}

void DrawTable(int Player){
    ClearScr();
    printf("Player %d Has %d Turn Left\n", Player, Turn[Player-1]);
    printf("----------------------\n");
    int i;
    for (i = 0; i < 49; i++){
        if (NumTable[Player - 1][i] < 10)
            printf("| %d", NumTable[Player - 1][i]);
        else
            printf("|%d", NumTable[Player - 1][i]);
        if ((i + 1) % 7 == 0)
            printf("|\n");
    }
    printf("----------------------\n");
}

void DrawAlpha(){
    ClearScr();
    printf("Player 1\n");
    printf("-----------------------------\n");
    int i;
    for (i = 0; i < 49; i++){
        if (AlphaTable[0][i] == 'A')
            printf("| \033[1;31m%c \033[0m", AlphaTable[0][i]);
        if (AlphaTable[0][i] == 'B')
            printf("| \033[1;32m%c \033[0m", AlphaTable[0][i]);
        if (AlphaTable[0][i] == 'C')
            printf("| \033[1;33m%c \033[0m", AlphaTable[0][i]);
        if (AlphaTable[0][i] == 'D')
            printf("| \033[1;34m%c \033[0m", AlphaTable[0][i]);
        if (AlphaTable[0][i] == 'E')
            printf("| \033[1;35m%c \033[0m", AlphaTable[0][i]);
        if (AlphaTable[0][i] == 'F')
            printf("| \033[1;36m%c \033[0m", AlphaTable[0][i]);
        if (AlphaTable[0][i] == 'G')
            printf("| \033[1;37m%c \033[0m", AlphaTable[0][i]);
        if ((i + 1) % 7 == 0)
            printf("|\n");
    }
    printf("-----------------------------\n");
    printf("Player 2\n");
    printf("-----------------------------\n");
    for (i = 0; i < 49; i++){
        if (AlphaTable[1][i] == 'A')
            printf("| \033[1;31m%c \033[0m", AlphaTable[1][i]);
        if (AlphaTable[1][i] == 'B')
            printf("| \033[1;32m%c \033[0m", AlphaTable[1][i]);
        if (AlphaTable[1][i] == 'C')
            printf("| \033[1;33m%c \033[0m", AlphaTable[1][i]);
        if (AlphaTable[1][i] == 'D')
            printf("| \033[1;34m%c \033[0m", AlphaTable[1][i]);
        if (AlphaTable[1][i] == 'E')
            printf("| \033[1;35m%c \033[0m", AlphaTable[1][i]);
        if (AlphaTable[1][i] == 'F')
            printf("| \033[1;36m%c \033[0m", AlphaTable[1][i]);
        if (AlphaTable[1][i] == 'G')
            printf("| \033[1;37m%c \033[0m", AlphaTable[1][i]);
        if ((i + 1) % 7 == 0)
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
                int index = (rand() % 49);
                if (AlphaTable[i][index] == ' ')
                    AlphaTable[i][index] = Alpha[j];
                else
                    k -= 1;
            }
}

void Init(){
    int i;
    for (i = 0; i < 49; i++){
        NumTable[0][i] = i + 1;
        NumTable[1][i] = i + 1;
        AlphaTable[0][i] = ' ';
        AlphaTable[1][i] = ' ';
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