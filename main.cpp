#include <iostream>
using namespace std;

struct gameboard
{
    string player;
    char symbol;
};

void funct_current_board(char array_game[3][3], gameboard player_details[2])
{
    // Display the current state of the game board
    cout << "Current Board:\n";
    cout << "-------------\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (array_game[i][j] == 'X' || array_game[i][j] == 'O')
                cout << "| " << array_game[i][j] << " ";
            else
                cout << "| " << i * 3 + j + 1 << " ";
        }
        cout << "|\n";
        cout << "-------------\n";
    }

    // Display player details
    for (int i = 0; i < 2; i++)
    {
        cout << "Player " << player_details[i].player << ": " << player_details[i].symbol << endl;
    }
}

bool funct_gameFunctnality(char array_game[3][3], gameboard player_details[2])
{
    for (int i = 0; i < 2; i++)
    {
        bool validMove = false;

        do
        {
            cout << "Player " << player_details[i].player << ", where do you want to move? \n";
            int position;
            cin >> position;

            int horizontal = (position - 1) / 3;
            int vertical = (position - 1) % 3;

            if (array_game[horizontal][vertical] == 'X' || array_game[horizontal][vertical] == 'O')
            {
                cout << "Invalid move. Cell already occupied. Try again.\n";
            }
            else
            {
                array_game[horizontal][vertical] = player_details[i].symbol;
                validMove = true;
            }

        } while (!validMove);

        // Display the current state of the game board after each move
        funct_current_board(array_game, player_details);
    }

    return true; // Return true to indicate that the moves were valid
}

bool funct_WINNER(char array_game[3][3], gameboard player_details[2])
{
    for (int playerIndex = 0; playerIndex < 2; ++playerIndex)
    {
        char symbol = player_details[playerIndex].symbol;

        // Check rows, columns, and diagonals
        for (int i = 0; i < 3; i++)
        {
            if ((array_game[i][0] == symbol && array_game[i][1] == symbol && array_game[i][2] == symbol) ||
                (array_game[0][i] == symbol && array_game[1][i] == symbol && array_game[2][i] == symbol))
            {
                cout << "Player " << player_details[playerIndex].player << " WINS! Congratulations!\n";
                return true; // Return true to indicate a winner
            }
        }

        // Check diagonals
        if ((array_game[0][0] == symbol && array_game[1][1] == symbol && array_game[2][2] == symbol) ||
            (array_game[0][2] == symbol && array_game[1][1] == symbol && array_game[2][0] == symbol))
        {
            cout << "Player " << player_details[playerIndex].player << " WINS! Congratulations!\n";
            return true; // Return true to indicate a winner
        }
    }

    return false; // Return false if no winner
}

bool funct_checkWinner(char array_game[3][3], gameboard player_details[2])
{
    if (funct_WINNER(array_game, player_details))
    {
        return true; // Return true if there is a winner
    }
    else
    {
        // Check for a draw
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (array_game[i][j] != 'X' && array_game[i][j] != 'O')
                {
                    return false; // Return false if there are still empty cells
                }
            }
        }

        cout << "It's a DRAW! No more moves available.\n";
        return true; // Return true to indicate a draw
    }
}

int main()
{
    char array_game[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}};

    gameboard player_details[2];

    for (int i = 0; i < 2; i++)
    {
        cout << "ENTER PLAYER " << i + 1 << " NAME: ";
        cin >> player_details[i].player;

        do
        {
            cout << "PLAYER " << i + 1 << ", CHOOSE X OR O: ";
            cin >> player_details[i].symbol;

            if (player_details[i].symbol != 'X' && player_details[i].symbol != 'O')
            {
                cout << "Invalid choice. Please choose either X or O.\n";
            }
            else if (player_details[i].symbol == 'X')
            {
                cout << "Player " << i + 1 << " already took X. Player " << (i == 0 ? 2 : 1) << " is forced to take O.\n";
                player_details[(i == 0 ? 1 : 0)].symbol = 'O';
            }
            else if (player_details[i].symbol == 'O')
            {
                cout << "Player " << i + 1 << " already took O. Player " << (i == 0 ? 2 : 1) << " is forced to take X.\n";
                player_details[(i == 0 ? 1 : 0)].symbol = 'X';
            }

        } while (player_details[i].symbol != 'X' && player_details[i].symbol != 'O');
    }

    funct_current_board(array_game, player_details);

    bool gameInSession = true;
    while (gameInSession)
    {
        gameInSession = funct_gameFunctnality(array_game, player_details);
        if (gameInSession)
        {
            gameInSession = !funct_checkWinner(array_game, player_details);
        }
    }

    return 0;
}