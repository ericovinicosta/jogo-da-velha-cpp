#include <iostream>
#include <iomanip>

using namespace std;

#define MAX 3

void init(int [][MAX]);
bool checkWin(int [][MAX]);
bool checkContinue(int [][MAX]);
void show(int [][MAX]);
char printBlock(int);
void playMove(int [][MAX], int);
int game(int [][MAX]);

int main(){
    int tabuleiro[MAX][MAX], result = 0;
    bool cont = true;
    char resp;

    do{
        init(tabuleiro);
        show(tabuleiro);
        result = game(tabuleiro);
        cout << "Deseja continuar? (S/n) ";
        cin >> resp;
        if(toupper(resp) != 'S'){
            cont = false;
        }
    }while(cont);

    return 0;
}

int game(int tabuleiro [][MAX]){
    int turn = 0;

    do{
        playMove(tabuleiro, turn % 2);
        show(tabuleiro);
        turn++;
    }while(checkContinue(tabuleiro) && !checkWin(tabuleiro));

    return turn++;
}

bool checkContinue(int tabuleiro[][MAX]){
    for(int row = 0; row < MAX; row++){
        for(int col = 0; col < MAX; col++){
            if(tabuleiro[row][col] == 0){
                return true;
            }
        }
    }
    return false;
}

bool checkWin(int tabuleiro[][MAX]){
    //return false somebody win
    //return true anybody win
    //check row
    int sum;
    for(int row = 0; row < MAX; row++){
        sum = 0;
        for(int col = 0; col < MAX; col++){
            sum += tabuleiro[row][col];
        }
        if(sum == 3 || sum == -3){
            return true;
        }
    }
    //check col
    for(int col = 0; col < MAX; col++){
        int sum = 0;
        for(int row = 0; row < MAX; row++){
            sum += tabuleiro[row][col];
        }
        if(sum == 3 || sum == -3){
            return true;
        }
    }
    //check diagonals
    //row == col
    int esum, dsum;
    for(int row = 0; row < MAX; row++){
        esum = 0;
        dsum = 0;
        for(int col = 0; col < MAX; col++){
            if(col == row){
                esum += tabuleiro[row][col];
            }
            if(row + col == MAX - 1){
                dsum += tabuleiro[row][col];
            }
        }
        if(esum == 3 || esum == -3 || dsum == 3 || dsum == -3){
            return true;
        }
    }
    //if anybody win
    return false;
}

void playMove(int tabuleiro[][MAX], int player){//player = 0 || 1
    int row, col;
    bool check;

    do{
        cout << "Linha: ";
        cin >> row;
        cout << "Coluna: ";
        cin >> col;
        row--;
        col--;

        check = tabuleiro[row][col] || row < 0 || row > 2 || col < 0  || col > 2;
    }while(check);

    if(player == 0){
        tabuleiro[row][col] = 1;
    }
    else{
        tabuleiro[row][col] = -1;
    }
    checkWin(tabuleiro);
}

void init(int tabuleiro[][MAX]){
    for(int m=0; m < MAX; m++ ){
        for(int n=0; n < MAX; n++){
            tabuleiro[m][n] = 0;
        }
    }
}

void show(int tabuleiro[][MAX]){
    cout << endl;
    for(int m=0; m < MAX; m++ ){
        for(int n=0; n < MAX; n++){
            if( n < MAX-1){
                cout << setw(2)<< printBlock(tabuleiro[m][n]) << " |";
            }
            else{
                cout << setw(2)<< printBlock(tabuleiro[m][n]) << endl;
            }
        }
        if(m < MAX -1){
        cout << "--- --- ---" << endl;
        }
    }
}

char printBlock(int posicao = 0){
    char result = '?';
    if(posicao == 1){
        result = 'X';
    }
    else if(posicao == -1){
        result = 'O';
    }
    return result;
}
