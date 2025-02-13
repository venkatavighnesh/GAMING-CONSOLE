#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>

using namespace std;

fstream file;
char board[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
class Snake {
private:
    bool gameOver;
    const int width = 25;
    const int height = 15;
    int x, y, foodx, foody, score;
    int tailx[100], taily[100];
    int ntail;
    enum Direction
    {
        STOP = 0,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    Direction dir;
    const string highScoreFileName = "highscore.txt";

public:
    Snake() {
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        foodx = rand() % width;
        foody = rand() % height;
        score = 0;
        ntail = 0;
    }

    void Setup() {
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        foodx = rand() % width;
        foody = rand() % height;
        score = 0;
        ntail = 0;
    }

    void SaveHighScore() {
        ifstream highScoreFileIn(highScoreFileName);

        int existingHighScore = 0;
        highScoreFileIn >> existingHighScore;
        highScoreFileIn.close();
        if (score > existingHighScore) {
            ofstream highScoreFileOut(highScoreFileName);
            highScoreFileOut << score;
            highScoreFileOut.close();
        }
    }
    int GetHighScore() {
        ifstream highScoreFileIn(highScoreFileName);

        int existingHighScore;
        highScoreFileIn >> existingHighScore;
        return existingHighScore;
        highScoreFileIn.close();
    }

    void Draw() {
        system("cls");

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "#";
                if (i == y && j == x)
                    cout << "O";
                else if (i == foody && j == foodx)
                    cout << "Q";
                else {
                    bool printTail = false;
                    for (int k = 0; k < ntail; k++) {
                        if (tailx[k] == j && taily[k] == i) {
                            cout << "o";
                            printTail = true;
                        }
                    }
                    if (!printTail)
                        cout << " ";
                }

                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        cout << "Score:" << score <<" | "<<"Highscore: "<< GetHighScore()<< endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a':
                    dir = LEFT;
                    break;
                case 'd':
                    dir = RIGHT;
                    break;
                case 'w':
                    dir = UP;
                    break;
                case 's':
                    dir = DOWN;
                    break;
                case 'x':
                    gameOver = true;
                    break;
            }
        }
    }

    void Algorithm() {
        int prevX = tailx[0];
        int prevY = taily[0];
        int prev2X, prev2Y;
        tailx[0] = x;
        taily[0] = y;

        for (int i = 1; i < ntail; i++) {
            prev2X = tailx[i];
            prev2Y = taily[i];
            tailx[i] = prevX;
            taily[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        switch (dir) {
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            default:
                break;
        }

        if (x >= width) x = 0;
        else if (x < 0) x = width - 1;

        if (y >= height) y = 0;
        else if (y < 0) y = height - 1;

        for (int i = 0; i < ntail; i++)
            if (tailx[i] == x && taily[i] == y)
                gameOver = true;

        if (x == foodx && y == foody) {
            score += 1;
            foodx = rand() % width;
            foody = rand() % height;
            ntail++;
        }
    }

    void RunGame() {
        Setup();

        while (!gameOver) {
            Draw();
            Input();
            Algorithm();
            Sleep(70);
        }
        SaveHighScore();
    }
};

class tictactoe
{
    private:
        string p1,p2;
        char a,b,ch;
        char playerturn='X';
        int r,c;
        bool draw=false;
    public:
    void create()
    {
        cout<<"Enter player 1 name: "<<endl;
        cin>>p1;
        cout<<"Enter player 2 name: "<<endl;
        cin>>p2;
        cout<<"Choose X or O for "<<p1<<" : ";
        cin>>a;
        if(a=='X' || a=='x')
        {
            b = 'O';
        }
        else
        {
            b = 'X';
        }
    }
    void displayboard()
    {
        system("cls");
        cout<<"\t\t    TIC TAC TOE\n"<<endl;
        cout<<"\t"<<p1<<" is '"<<a<<"'\t\t"<<p2<<" is '"<<b<<"'"<<endl;
        cout<<"\t\t     |     |     "<<endl;
        cout<<"\t\t  "<<board[0][0]<<"  |  "<<board[0][1]<<"  |  "<<board[0][2]<<endl;
        cout<<"\t\t_____|_____|_____"<<endl;
        cout<<"\t\t     |     |     "<<endl;
        cout<<"\t\t  "<<board[1][0]<<"  |  "<<board[1][1]<<"  |  "<<board[1][2]<<endl;
        cout<<"\t\t_____|_____|_____"<<endl;
        cout<<"\t\t     |     |     "<<endl;
        cout<<"\t\t  "<<board[2][0]<<"  |  "<<board[2][1]<<"  |  "<<board[2][2]<<endl;
        cout<<"\t\t     |     |     "<<endl;
    }
    void turn()
    {
        if(playerturn=='X')
        {
            cout<<p1<<" turn: ";
        }
        else
        {
            cout<<p2<<" turn: ";
        }
        start:
            cin>>ch;
        switch(ch)
        {
            case '1': r=0; c=0; break;
            case '2': r=0; c=1; break;
            case '3': r=0; c=2; break;
            case '4': r=1; c=0; break;
            case '5': r=1; c=1; break;
            case '6': r=1; c=2; break;
            case '7': r=2; c=0; break;
            case '8': r=2; c=1; break;
            case '9': r=2; c=2; break;
            default:
                cout<<"Invalid Move";
                goto start;
        }
        if(playerturn=='X' && board[r][c]!='X' && board[r][c]!='O')
        {
            board[r][c] = 'X';
            playerturn = 'O';
        }
        else if(playerturn=='O' && board[r][c]!='X' && board[r][c]!='O')
        {
            board[r][c] = 'O';
            playerturn = 'X';
        }
        else
        {
            cout<<"Box is not empty"<<endl;
            turn();
        }
    }
    bool gameover()
    {
        for(int i=0; i<3; i++)
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return false;
        }
        if(board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0])
        {
            return false;
        }
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(board[i][j] != 'X' && board[i][j] != 'O')
                {
                    return true;
                }
            }
        }
        draw = true;
        return false;
    }
    void woncheck()
    {
        if(playerturn == 'O' && draw == false)
        {
            cout<<endl<<p1<<" with 'X' has won the game"<<endl;
        }   
        else if(playerturn == 'X' && draw == false)
        {
            cout<<endl<<p2<<" with 'O' has won the game"<<endl;
        }
        else
        {
            cout<<endl<<"The game is draw"<<endl;
        }
    }
    void Run()
    {
        create();
        while(gameover())
        {
            displayboard();
            turn();
            gameover();
        }
        displayboard();
        woncheck();
    }
};

class RockPaperScissors {
public:
    enum Choice {
        ROCK,
        PAPER,
        SCISSORS
    };
    void playGame() {
        cout << "Welcome to Rock, Paper, Scissors!\n";
        while (true) {
            Choice player1 = getPlayerChoice(1);
            system("cls");
            Choice player2 = getPlayerChoice(2);

            cout << "\n\tPlayer 1 chose "<<printChoice(player1)<<"\t\t\tPlayer 2 chose "<<printChoice(player2);
            if(player1 == ROCK && player2 == ROCK)
            {
                cout <<R"(
                   _______                        ______
               ---'   ____)                     _(___   '---
                     (_____)                   (_____)
                     (_____)                   (_____)
                     (____)                     (____)
               ---.__(___)                        (___)__.---
               )";
            }
            else if(player1 == PAPER && player2 == ROCK)
            {
                cout <<R"(
                    _______                                ______
                ---'    ___)_____                        _(___   '---
                            ______)_                    (_____)
                             _______)                   (_____)
                            _______)                     (____)
                ---.____________)                         (___)__.---
                )";
            }
            else if(player1 == SCISSORS && player2 == ROCK)
            {
                cout << R"(
                    ______                                  ______
                ---'   ___)_______                        _(___   '---
                            ______)_                     (_____)
                       _____________)                    (_____)
                      (____)                              (____)
                ---.__(___)                                (___)__.---
                )";
            }
            if(player1 == ROCK && player2 == PAPER)
            {
                cout <<R"(
                   _______                             ______
               ---'   ____)                       ____(___   '---
                     (_____)                    _(_______
                     (_____)                   (_______
                     (____)                     (________
               ---.__(___)                         (__________.---
               )";
            }
            else if(player1 == PAPER && player2 == PAPER)
            {
                cout <<R"(
                    ______                                      ______
                ---'    ___)_____                          ____(___   '---
                            ______)_                     _(_______
                             _______)                   (_______
                            _______)                     (________
                ---.____________)                           (_________.---
                )";
            }
            else if(player1 == SCISSORS && player2 == PAPER)
            {
                cout << R"(
                    ______                                      ______
                ---'   ___)_______                         ____(___   '---
                            ______)_                     _(_______
                       _____________)                   (_______
                      (____)                             (________
                ---.__(___)                                 (_________.---
                )";
            }
            if(player1 == ROCK && player2 == SCISSORS)
            {
                cout <<R"(
                   _______                               ______
               ---'   ____)                       ______(___   '---
                     (_____)                    _(_____
                     (_____)                   (_________
                     (____)                           (____)
               ---.__(___)                             (___)___.---
               )";
            }
            else if(player1 == PAPER && player2 == SCISSORS)
            {
                cout <<R"(
                    ______                                        _______
                ---'    ___)_____                          ______(___    '---
                            ______)_                     _(______
                             _______)                   (_________
                            _______)                           (____)
                ---.____________)                               (___)____.---
                )";
            }
            else if(player1 == SCISSORS && player2 == SCISSORS)
            {
                cout << R"(
                    ______                                        _______
                ---'   ___)_______                         ______(___    '---
                            ______)_                     _(______
                       _____________)                   (_________
                      (____)                                   (____)
                ---.__(___)                                     (___)____.---
                )";
            }
            int result = determineWinner(player1, player2);
            if (result == 0) {
                cout << "\n\t\t\t\tIt's a tie!\n";
            } else if (result == 1) {
                cout << "\n\t\t\t\tPlayer 1 wins!\n";
            } else {
                cout << "\n\t\t\t\tPlayer 2 wins!\n";
            }
            cout << "Do you want to play again? (y/n): ";
            char playAgain;
            cin >> playAgain;
            if (playAgain != 'y' && playAgain != 'Y') {
                break;
            }
        }
        cout << "Thanks for playing!\n";
    }
private:
    string printChoice(Choice choice) {
        switch (choice) {
            case ROCK:
                return "Rock";
                break;
            case PAPER:
                return "Paper";
                break;
            case SCISSORS:
                return "Scissors";
                break;
        }
    }
    Choice getPlayerChoice(int playerNumber) {
        cout << "Player " << playerNumber << ", enter your choice (1 for Rock, 2 for Paper, 3 for Scissors): ";
        int choice;
        cin >> choice;
        if (choice < 1 || choice > 3) {
            cout << "Invalid choice. Please enter a number between 1 and 3.\n";
            return getPlayerChoice(playerNumber);
        }
        return static_cast<Choice>(choice - 1);
    }
    int determineWinner(Choice player1, Choice player2) {
        if (player1 == player2) {
            return 0; // It's a tie
        } else if ((player1 == ROCK && player2 == SCISSORS) ||
                   (player1 == PAPER && player2 == ROCK) ||
                   (player1 == SCISSORS && player2 == PAPER)) {
            return 1; // Player 1 wins
        } else {
            return 2; // Player 2 wins
        }
    }
};

int main()
{
    int a;
    label:
        cout<<"\t\t\t GAMING CONSOLE\n\n"<<endl;
        cout<<"\t1 ----->  Tic tac toe"<<endl;
        cout<<"\t2 ----->  Snake game"<<endl;
        cout<<"\t3 ----->  Rock Paper Scissors"<<endl;
        cout<<"\t4 ----->  Exit"<<endl;
        cin>>a;
    while(1)
    {
        if(a==1)
        {
            tictactoe obj1;
            obj1.Run();
            goto label;
        }
        if(a==2)
        {
            Snake obj2;
            obj2.RunGame();
            goto label;
        }
        if(a==3)
        {
            RockPaperScissors obj3;
            obj3.playGame();
            goto label;
        }
        if(a==4)
        {
            return 0;
        }
    }
}
