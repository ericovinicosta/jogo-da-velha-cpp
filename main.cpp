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
void playAutoMove(int [][MAX], int);
int game(int [][MAX], int);
void scoreBoard(int, int &, int &);

int main(){
    int tabuleiro[MAX][MAX], result = 0, player1 = 0, player2 = 0;
    int iresp;
    bool cont = true;
    char resp;
    do{
        cout << "Deseja jogar contra uma [P]esssoa ou contra o [C]omputador? ";
        cin >> resp;
    }while(toupper(resp) != 'P' && toupper(resp) != 'C');

    iresp = (toupper(resp) == 'C' ? 1 : 2 );

    do{
        init(tabuleiro);
        scoreBoard(result, player1, player2);
        show(tabuleiro);
        result = game(tabuleiro,iresp);
        cout << endl;

        if(checkWin(tabuleiro)){
            cout <<"A vitória foi do Jogador "<< (result%2 == 0 ? 1 : 2)  <<endl;
        } else {
            cout <<"Empatou - Deu Velha!!" << endl;
            result = 0;
        }

        cout << "Deseja continuar? (S/n) ";
        cin >> resp;
        if(toupper(resp) != 'S'){
            cout << "Serie terminou" << endl;
            scoreBoard(result, player1, player2);
            cont = false;
        }

    }while(cont);

    return 0;
}

int game(int tabuleiro [][MAX], int gamers = 2){
    int turn = 0;

    do{
        cout << "Rodada: "<< turn+1 << endl;
        if(gamers == 2 || turn % 2 == 0){
            playMove(tabuleiro, turn % 2);
        }
        else{
            playAutoMove(tabuleiro, turn % 2);
        }
        show(tabuleiro);

        turn++;
    }while(checkContinue(tabuleiro) && !checkWin(tabuleiro));

    return --turn;
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

void scoreBoard(int result, int &player1, int &player2){
    if(result > 0){
        if(result%2 == 0){
            player1++;
        } else {
            player2++;
        }
    }
    cout << "Placar: " << endl;
    cout << "Jogador 1  X  Jogador 2" << endl;
    cout << setw(10) << player1 << " X " <<player2 << endl;
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
        sum = abs(sum);
        if(sum == 3){
            return true;
        }
    }
    //check col
    for(int col = 0; col < MAX; col++){
    sum = 0;
        for(int row = 0; row < MAX; row++){
            sum += tabuleiro[row][col];
        }
        sum = abs(sum);
        if(sum == 3){
            return true;
        }
    }

    //check diagonals
    //row == col
    int esum = 0, dsum = 0;

    for(int row = 0; row < MAX; row++){
        for(int col = 0; col < MAX; col++){
            if(col == row){
                esum += tabuleiro[row][col];
            }
            if(row + col == MAX - 1){
                dsum += tabuleiro[row][col];
            }
        }
    }
    esum = abs(esum);
    dsum = abs(dsum);
    if(esum == 3 || dsum == 3){
        return true;
    }
    //if anybody win
    return false;
}

void playAutoMove(int tabuleiro[][MAX], int player){//player =  1
    int row, col;
    bool check;
    srand(time(NULL)*1024/3075);
    do{
        row = rand() % 3;
        col = rand() % 3;

        check = tabuleiro[row][col] || row < 0 || row > 2 || col < 0  || col > 2;
    }while(check);

        tabuleiro[row][col] = -1;

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
