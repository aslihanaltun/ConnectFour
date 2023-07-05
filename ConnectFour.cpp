#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


vector<string> board(11);
vector<string> moves(10);

class Player {

public:
    char pawn = 0;
    int playorder = 0;
    Player(char pawn, int playorder) {
        this->pawn = pawn;
        this->playorder = playorder;
    }

};

Player player1 = Player('0', 1);
Player player2 = Player('0', 2);

void drawboard() {
    system("cls");
    for (int i = 0; i < 11; i++)
        cout << board[i] << endl;
}

void saveboard() {
    fstream out;

    out.open("tahta.txt", fstream::out);
    for (int i = 0; i < board.size(); i++) {
        out << board[i] << endl;
    }
    out.close();
}

void loadboard() {
    fstream in;
    string line;

    in.open("tahta.txt", fstream::in);
    int index = 0;

    while (getline(in, line))
        board[index++] = line;
}

void    initboard(string decision) {
    if (decision == "LOAD")
        loadboard();
    if (!board[0].size())
        board = {
            "_  _  _  _  _  _  _  _  _",
            "_  _  _  _  _  _  _  _  _",
            "_  _  _  _  _  _  _  _  _",
            "_  _  _  _  _  _  _  _  _",
            "_  _  _  _  _  _  _  _  _",
            "_  _  _  _  _  _  _  _  _",
            "_  _  _  _  _  _  _  _  _",
            "_  _  _  _  _  _  _  _  _",
            "_  _  _  _  _  _  _  _  _",
            "*  *  *  *  *  *  *  *  *",
            "0  1  2  3  4  5  6  7  8",
    };
    saveboard();
}

void    savemove() {
    fstream out;

    out.open("hamle.txt", fstream::out);
    for (int i = 0; i < moves.size(); i++) {
        out << moves[i] << endl;
    }
    out.close();
}

void getPlayers() {
    string pawn1;
    string pawn2;
    string line;
    fstream in;
    in.open("hamle.txt", fstream::in);

    getline(in, line);
    pawn1 = line.substr(0, line.find(':'));
    getline(in, line);
    pawn2 = line.substr(0, line.find(':'));

    while (getline(in, line)) {

    }
    if (stoi(line.substr(line.find(';') + 1, 1)) % 2 == 1)
    {
        player1.pawn = pawn2[0];
        player2.pawn = pawn1[0];
    }
    else {
        player1.pawn = pawn1[0];
        player2.pawn = pawn2[0];
    }

}

void initplayers(string decision) {
    if (decision == "yukle") {
        ifstream myFile;
        myFile.open("hamle.txt");
        if (myFile) {
            getPlayers();
        }
    }
    else {
        char pawn1;
        char pawn2;

        cout << "lutfen pul secin" << endl;
        cout << "1. pul" << endl;
        cin >> pawn1;
        player1.pawn = pawn1;
        cout << "2. pul" << endl;
        cin >> pawn2;
        player2.pawn = pawn2;
    }
}

char turn() {
    fstream in;
    string str;
    loadboard();
    in.open("hamle.txt", fstream::in);
    for (int i = 0; i <= 1; i++) {
        getline(in, str);
    }
    in.close();
    return str[0];
}

void    turnMessage(char player) {
    cout << "player " << player << " enter your move:" << endl;;
}

bool isPlayable(int column) {
    return board[0][column] == '_';
}

bool isFull() {
    int counter = 0;
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i <= 8; i++) {
            if (board[0][i * 3] != '_')
                counter++;
        }
    }
    if (counter == 80)
        return false;
    return true;
}

bool checkMove(int move) {
    if (isPlayable(move) == true && isFull() == true)
        return true;
    else
        return false;
}

int rowFinder(char pawn, int column) {

    for (int i = 0; i < 9; i++) {
        if (board[i][3 * column] == pawn) {
            return i;
        }
    }
    return -1;
}

bool isConnected(int column, char pawn) {

    int row = rowFinder(pawn, column);
    int counter = 0;


    //Horizontal Check
    for (int i = 0; i <= 8; i++) {

        if (board[row][i * 3] == pawn)
            counter++;
        else
            counter = 0;
        if (counter == 4)
            return true;
    }



    counter = 0;
    //Vertical Check
    for (int i = 0; i < 9; i++) {

        if (board[i][3 * column] == pawn)
            counter++;
        else
            counter = 0;
        if (counter == 4)
            return true;
    }

    //Diagonal Check 
    counter = 0;
    int i = row;
    int j = column;
    while (i < 9 && j * 3 < 25 && board[i][j * 3] == pawn) {

        counter++;
        i++;
        j++;
    }
    i = row - 1;
    j = column - 1;

    while (i >= 0 && j * 3 >= 0 && board[i][j * 3] == pawn) {

        counter++;
        i--;
        j--;;
    }
    if (counter == 4)
        return true;

    //Diagonal Check 
    counter = 0;
    i = row;
    j = column;
    while (i < 9 && j * 3 >= 0 && board[i][j * 3] == pawn) {

        counter++;
        i++;
        j--;
    }
    i = row - 1;
    j = column + 1;
    while (i >= 0 && j * 3 < 25 && board[i][j * 3] == pawn) {

        counter++;
        i--;
        j++;
    }
    if (counter == 4)
        return true;


    return false;

}

void playMove(int column, char playerpawn, int* counter) {
    int i = 0;
    string p = string(1, playerpawn);
    moves[*counter - 1] = (p + ":" + to_string(column) + ";" + to_string(*counter));
    if (checkMove(3 * column)) {
        for (i = 8; i > 0; i--) {
            if (board[i][3 * column] == '_')
            {
                board[i][3 * column] = playerpawn;
                break;
            }

        }

    }

    if (i == 0)
        board[i][3 * column] = playerpawn;
    saveboard();
    savemove();
}


int play(int* counter) {


    if (*counter % 2 == 1) {
        drawboard();
        int column;
        turnMessage(player1.pawn);
        cin >> column;
        playMove(column, player1.pawn, counter);

        if (isConnected(column, player1.pawn))
            return 0;

    }
    else {
        drawboard();
        int column;
        turnMessage(player2.pawn);
        cin >> column;
        playMove(column, player2.pawn, counter);
        if (isConnected(column, player2.pawn))
            return 0;

    }


    return 1;
}

int main()
{

    string decision;
    while (decision != "yeni" && decision != "yukle") {
        cout << "Onceki oyunu oynamak icin (varsa) yukle,\nyeni bir oyuna baslamak icin yeni yaziniz: ";
        cin >> decision;
    }

    initboard(decision);
    initplayers(decision);


    int counter = 1;
    while (counter != 80 && play(&counter)) {
        counter++;
    }
    saveboard();
    cout << "TEBRIKLER OYUNCU " << (counter % 2 == 1 ? player1.pawn : player2.pawn) << " KAZANDI" << endl;

    return 0;

}