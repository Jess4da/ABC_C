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
    int i, j, row1 = -1, row2 = -1, col1 = -1, col2 = -1;
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

    ctemp = AlphaTable[Player-1][row1][col1];
    AlphaTable[Player-1][row1][col1] = AlphaTable[Player-1][row2][col2];
    AlphaTable[Player-1][row2][col2] = ctemp;

}

int CheckInRange(int Pos){
    if (Pos < 1 || Pos > 49)
        return 0;
    return 1;
}

int CheckPattern(){
    int i, j, k;
    int _score[] = {
        0, 0
    };
    for (i = 0; i < 2; i++){

        //เช็คแนวนอน
        for (j = 0; j < 7; j++){
            for (k = 1; k < 6; k++){
                if (AlphaTable[i][j][k] == ' ')
                    continue;
                //เหมือนกัน 3
                if (AlphaTable[i][j][k-1] == AlphaTable[i][j][k] &&
                    AlphaTable[i][j][k] == AlphaTable[i][j][k+1]){
                        _score[i] += 1;
                    }
                //เหมือนกัน 6
                if (AlphaTable[i][j][k-1] == AlphaTable[i][j][k] &&
                    AlphaTable[i][j][k] == AlphaTable[i][j][k+1]&&
                    AlphaTable[i][j][k+1] == AlphaTable[i][j][k+2]&&
                    AlphaTable[i][j][k+2] == AlphaTable[i][j][k+3]&&
                    AlphaTable[i][j][k+3] == AlphaTable[i][j][k+4]){
                        _score[i] += 2;
                    }
            }
        }

        //เช็คแนวตั้ง
        for (j = 1; j < 6; j++){
            for (k = 0; k < 7; k++){
                if (AlphaTable[i][j][k] == ' ')
                    continue;

                //เหมือนกัน 3
                if (AlphaTable[i][j-1][k] == AlphaTable[i][j][k] &&
                    AlphaTable[i][j][k] == AlphaTable[i][j+1][k]){
                        _score[i] += 1;
                        continue;
                    }
                //เหมือนกัน 6
                if (AlphaTable[i][j-1][k] == AlphaTable[i][j][k] &&
                    AlphaTable[i][j][k] == AlphaTable[i][j+1][k] &&
                    AlphaTable[i][j+1][k] == AlphaTable[i][j+2][k] &&
                    AlphaTable[i][j+2][k] == AlphaTable[i][j+3][k] &&
                    AlphaTable[i][j+3][k] == AlphaTable[i][j+4][k]){
                        _score[i] += 2;
                    }
            }
        }
        //เช็คตามแพทเทิร์น
        if (AlphaTable[i][0][0] == ' ' || AlphaTable[i][0][6] == ' ')
            continue;

        //เช็คซ้ำตามจุดที่กำหนด
        if (AlphaTable[i][0][0] == AlphaTable[i][0][6] &&
            AlphaTable[i][0][6] == AlphaTable[i][3][3] &&
            AlphaTable[i][3][3] == AlphaTable[i][6][0] &&
            AlphaTable[i][6][0] == AlphaTable[i][6][6])
            _score[i] += 10;
        //ซ้ำแนวทะแยงซ้าย
        if (AlphaTable[i][0][0] == AlphaTable[i][1][1] &&
            AlphaTable[i][1][1] == AlphaTable[i][2][2] &&
            AlphaTable[i][2][2] == AlphaTable[i][3][3] &&
            AlphaTable[i][3][3] == AlphaTable[i][4][4] &&
            AlphaTable[i][4][4] == AlphaTable[i][5][5] &&
            AlphaTable[i][5][5] == AlphaTable[i][6][6])
            _score[i] += 20;
        //ซ้ำแนวทะแยงขวา
        if (AlphaTable[i][0][6] == AlphaTable[i][1][5] &&
            AlphaTable[i][1][5] == AlphaTable[i][2][4] &&
            AlphaTable[i][2][4] == AlphaTable[i][3][3] &&
            AlphaTable[i][3][3] == AlphaTable[i][4][2] &&
            AlphaTable[i][4][2] == AlphaTable[i][5][1] &&
            AlphaTable[i][5][1] == AlphaTable[i][6][0])
            _score[i] += 20;
    }
    Score[0] = _score[0];
    Score[1] = _score[1];
}

void DrawTable(int Player, int isClear){
    if (isClear == 1)
        ClearScr();
    printf("Player %d Score : %d\n", Player, Score[Player-1]);
    printf("Player %d Has %d Turn Left\n", Player, Turn[Player-1]);
    printf("----------------------\n");
    int i, j;
    for (i = 0; i < 7; i++){
        for (j = 0; j < 7; j++){
            if (AlphaTable[Player - 1][i][j] == ' '){
                if (NumTable[Player - 1][i][j] < 10)
                    printf("| %d", NumTable[Player - 1][i][j]);
                else
                    printf("|%d", NumTable[Player - 1][i][j]);
            }
            else{
                if (AlphaTable[Player - 1][i][j] == 'A')
                    printf("| \033[1;31m%c\033[0m", AlphaTable[Player - 1][i][j]);
                if (AlphaTable[Player - 1][i][j] == 'B')
                    printf("| \033[1;32m%c\033[0m", AlphaTable[Player - 1][i][j]);
                if (AlphaTable[Player - 1][i][j] == 'C')
                    printf("| \033[1;33m%c\033[0m", AlphaTable[Player - 1][i][j]);
                if (AlphaTable[Player - 1][i][j] == 'D')
                    printf("| \033[1;34m%c\033[0m", AlphaTable[Player - 1][i][j]);
                if (AlphaTable[Player - 1][i][j] == 'E')
                    printf("| \033[1;35m%c\033[0m", AlphaTable[Player - 1][i][j]);
                if (AlphaTable[Player - 1][i][j] == 'F')
                    printf("| \033[1;36m%c\033[0m", AlphaTable[Player - 1][i][j]);
                if (AlphaTable[Player - 1][i][j] == 'G')
                    printf("| \033[1;37m%c\033[0m", AlphaTable[Player - 1][i][j]);
            }
        }
        printf("|\n");
    }
    printf("----------------------\n");
}

void RandomAlpha(int Player, int Pos){
    char Alpha[7] = "ABCDEFG";
    int i, j, row, col, count = 0, _Alpha = 0;

    for (i = 0; i < 7; i++){
        for (j = 0; j < 7; j++){
            if (NumTable[Player - 1][i][j] == Pos){
                row = i;
                col = j;
            }
        }
    }
    while (1){
        _Alpha = (rand() %7);
        for (i = 0; i < 7; i++)
            for (j = 0; j < 7; j++)
                if (AlphaTable[Player - 1][i][j] == _Alpha)
                    count += 1;
        if (count < 7 && AlphaTable[Player - 1][row][col] == ' '){
            AlphaTable[Player - 1][row][col] = Alpha[_Alpha];
            break;
        }
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
}

int main(){

    Init();

    int Player = 1;
    while (1){

        int Pos1 = 0, Pos2 = 0;

        do{
            DrawTable(Player,1);
            printf("Player %d Choose 1 Number : ", Player);
            scanf("%d", &Pos1);

        }while (CheckInRange(Pos1) == 0);

        RandomAlpha(Player, Pos1);

        do{
            DrawTable(Player,1);
            printf("Player %d Choose a Place to Swap\n[Choose Same number to not Swap]: ", Player);
            scanf("%d", &Pos2);

        }while (CheckInRange(Pos2) == 0);
        
        SwapNum(Player, Pos1, Pos2);
        CheckPattern();
        
        Turn[Player - 1] -= 1;
        Player += 1;
        if (Player > 2)
            Player = 1;
        if (Turn[0] <= 0 && Turn[1] <= 0)
            break;
    }
    DrawTable(1,1);
    DrawTable(2,0);
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