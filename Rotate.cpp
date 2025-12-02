#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

void centerPrint(const string& text, int width = 80)
{
    int padding = (width - text.length()) / 2;
    cout << setw(padding + text.length()) << text << endl;
}

void printBoard(char letters[])
{
    for (int i = 1; i <= 16; i++)
    {
        cout << letters[i] << "\t";
        if (i % 4 == 0)
        {
            cout << endl << "\n";
        }
    }
}

bool checkWin(char letters[])
{
    for (int i = 1; i <= 16; i++)
    {
        if (letters[i] != 'A' + i - 1)
        {
            return false;
        }
    }
    return true;
}

void rotateClockwise(char letters[], int position)
{
    int topLeft = position;
    int topRight = position + 1;
    int bottomLeft = position + 4;
    int bottomRight = position + 5;
    char temp = letters[topLeft];
    letters[topLeft] = letters[bottomLeft];
    letters[bottomLeft] = letters[bottomRight];
    letters[bottomRight] = letters[topRight];
    letters[topRight] = temp;
}

bool isValidPosition(int position)
{
    int validPositions[] = { 1, 2, 3, 5, 6, 7, 9, 10, 11 };
    for (int pos : validPositions)
    {
        if (position == pos) return true;
    }
    return false;
}

void specialMove(char letters[])
{
    int pos1, pos2;
    cout << "EXCHANGE WHICH TWO POSITIONS";
    cin >> pos1 >> pos2;

    if (abs(pos1 - pos2) == 1)
    {
        swap(letters[pos1], letters[pos2]);
    }
    else
    {
        cout << "ILLEGAL. AGAIN..." << endl;
        specialMove(letters);
    }
}

int game()
{
    srand(time(0));
    char letters[17];
    int moves = 0;
    bool specialMoveUsed = false;

    for (int i = 1; i <= 16; i++)
    {
        letters[i] = 'A' + i - 1;
    }
    for (int i = 1; i <= 16; i++)
    {
        int a = rand() % 16 + 1;
        int b = rand() % 16 + 1;
        swap(letters[a], letters[b]);
    }

    cout << "HERE'S THE STARTING BOARD..." << endl << "\n";
    printBoard(letters);

    while (true)
    {
        cout << "POSITION TO ROTATE ";
        int position;
        cin >> position;

        if (position == 0)
        {
            cout << endl << endl;
            return 0;
        }

        if (position == -1)
        {
            if (!specialMoveUsed)
            {
                specialMove(letters);
                specialMoveUsed = true;
                moves++;
            }
            else
            {
                cout << "ONLY ONE SPECIAL MOVE PER GAME." << endl;
                continue;
            }
        }
        else if (isValidPosition(position))
        {
            rotateClockwise(letters, position);
            moves++;
        }
        else
        {
            cout << "ILLEGAL.  AGAIN..." << endl;
            continue;
        }

        cout << "AFTER MOVE " << moves << ":" << endl << "\n";
        printBoard(letters);

        if (checkWin(letters))
        {
            cout << "YOU ORDERED THE BOARD IN " << moves << " MOVES." << endl;
            cout << char(7);
            if (moves <= 20)
            {
                cout << "EXCELLENT PLAYING!" << endl;
            }
            else if (moves <= 30)
            {
                cout << "GOOD PLAYING!" << endl;
            }
            else
            {
                cout << "TRY AGAIN TO DO BETTER!" << endl;
            }

            string playAgain;
            cout << endl;
            cout << "PLAY AGAIN";
            cin >> playAgain;

            if (playAgain == "YES" || playAgain == "yes" || playAgain == "Y" || playAgain == "y")
            {
                return game();
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}

int main()
{
    centerPrint("ROTATE");
    centerPrint("CREATIVE COMPUTING");
    centerPrint("MORRISTOWN, NEW JERSEY");

    string answer;
    cout << "INSTRUCTIONS ? ";
    cin >> answer;

    if (answer == "YES" || answer == "yes" || answer == "Y" || answer == "y")
    {
        cout << "IN THIS GAME THE BOARD IS LAID OUT AS FOLLOWS:" << endl << "\n";
        for (int i = 1; i <= 16; i++)
        {
            cout << i << "\t";
            if (i % 4 == 0) {
                cout << endl << "\n";
            }
        }
        cout << "BOARD POSITIONS ARE OCCUPIED RANDOMLY BY THE LETTERS A TO P." << endl;
        cout << "THE OBJECT OF THE GAME IS TO ORDER THE LETTERS BY ROTATING" << endl;
        cout << "ANY FOUR LETTERS CLOCKWISE ONE POSITION.  YOU SPECIFY THE" << endl;
        cout << "UPPER LEFT POSITION OF THE FOUR YOU WISH TO ROTATE, I.E.," << endl;
        cout << "VALID MOVES ARE 1, 2, 3, 5, 6, 7, 9, 10 AND 11." << endl;
        cout << "CONSEQUENTLY, IF THE BOARD LOOKED LIKE:" << endl << "\n";

        char letters[17];
        for (int i = 1; i <= 16; i++)
        {
            letters[i] = 'A' + i - 1;
        }
        letters[2] = 'C';
        letters[3] = 'G';
        letters[6] = 'B';
        letters[7] = 'F';

        printBoard(letters);
        cout << "AND YOU ROTATED POSITION 2, THE BOARD WOULD BE:" << endl << "\n";
        rotateClockwise(letters, 2);
        printBoard(letters);
        cout << "AND YOU WOULD WIN!" << endl << "\n";
        cout << "YOU ALSO GET ONE 'SPECIAL' MOVE PER GAME WHICH YOU MAY OR" << endl;
        cout << "MAY NOT NEED.  THE SPECIAL MOVE ALLOWS YOU TO EXCHANGE" << endl;
        cout << "ANY TWO ADJACENT LETTERS IN A ROW.  TO MAKE THIS MOVE" << endl;
        cout << "INPUT A '-1' AS YOUR MOVE AND YOU WILL BE ASKED FOR THE" << endl;
        cout << "POSITIONS OF THE TWO LETTERS TO EXCHANGE. REMEMBER --" << endl;
        cout << "ONLY ONE SPECIAL MOVE PER GAME!" << endl << "\n";
        cout << "TO GIVE UP AT ANY TIME, TYPE A '0'." << endl << "\n";
        cout << "GOOD LUCK !" << endl << "\n";
    }
    game();
    return 0;
}