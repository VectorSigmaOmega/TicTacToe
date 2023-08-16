#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
using namespace std;

char board[3][3];

void clearBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}


int status()
{
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && (board[i][0] != ' '))
        {
            if (board[i][0] == 'X')
            {
                return -1;
            }
            else
            {
                return 1;
            }

        }
        if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) && (board[0][i] != ' '))
        {
            if (board[0][i] == 'X')
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }
    }

    if (((board[0][0] == board[1][1] && board[1][1] == board[2][2]) && (board[0][0] != ' ')) || ((board[0][2] == board[1][1] && board[1][1] == board[2][0]) && (board[1][1] != ' ')))
    {
        if (board[1][1] == 'X')
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return 2;
            }
        }
    }
    return 0;

}


void displayBoard()
{
    cout << "                   TIC-TAC-TOE" << endl;
    cout << "                  --------------" << endl << endl << endl;
    cout << "   Player = X  :  Computer = O" << endl << endl;
    cout << "         --- --- --- " << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "        | ";
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << " | ";
        }
        cout << endl << "         --- --- --- " << endl;
    }
    cout << endl << endl << endl;
}

int minimax(bool isMaximiser)
{
    int result = status();
    if (result != 2)
    {
        return result;
    }
    int score, bestScore;
    if (isMaximiser)
    {
        bestScore = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    score = minimax(false);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
    else
    {
        bestScore = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    score = minimax(true);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

void computer()
{
    int score, bestScore = -1000, position;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                score = minimax(false);
                board[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score;
                    position = i * 3 + j;
                }
            }
        }
    }
    board[(int)(position/3)][position%3] = 'O';
}


int player()
{
    int a, b;
    cout << "Player Move:";
    cout << endl << "       Enter row: ";
    cin >> a;
    cout << "       Enter column: ";
    cin >> b;
    if (board[a - 1][b - 1] == ' ' && (a <= 3 && a > 0) && (b <= 3 && a > 0))
    {
        board[a - 1][b - 1] = 'X';
    }
    else
    {
        cout << endl << "Invalid entry. Please retry.";
        Sleep(500);
        system("cls");
        displayBoard();
        return 0;
    }
    return 1;
}

void move(int i)
{
    int st;
    if (i % 2 != 0)
    {
        do
        {
            st = player();
        } while (st == 0);
    }
    else
    {
        computer();

    }
}

int main()
{
    int i = 1;
    clearBoard();
    do
    {
        system("cls");
        displayBoard();
        move(i);
        i++;
    } while (status() == 2);

    system("cls");
    displayBoard();

    if (status()==0)
    {
        cout << endl << "Draw !!";
    }
    else if (status() == -1)
    {
        cout << endl << "Player Won !!";
    }
    else
    {
        cout << endl << "Computer Won !!";
    }
    return 0;
}

