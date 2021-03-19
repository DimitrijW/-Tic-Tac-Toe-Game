#include <iostream>     // Ausgabe
#include <stdlib.h>     // Zufalzahl genirieren
#include <time.h>       // aktuelle Zeit

using namespace std;
// Globalen Variable
char field[10];

void singleplayer();
void multiplayer();
void help();
bool checkFull();
bool checkWin(char);
char keyInput(bool x);
void AI(int);

// Funktion Console inhalt löschen
void clearConsole()
{
    system("cls");  // Windows "cls" // Linux "clear"
}

// Funktion
void resetField()
{
    for(int i = 0; i < 10; i++)
    {
        field[i] = ' ';
    }
}

// Funktion Menu
void menu()
{
    while(true)
    {
        resetField();
        char inputmenu;
        cout << "\n\n"
             << "MENU \n\n"
             << "1: Singleplayer \n"
             << "2: Multiplayer \n"
             << "3: Help \n"
             << "4: Quit \n\n\n"
             << "Input: ";
        cin >> inputmenu;

        if(inputmenu == '1')singleplayer();
        else if(inputmenu == '2')multiplayer();
        else if(inputmenu == '3')help();
        else if(inputmenu == '4' || inputmenu == 'q')return;
        else {clearConsole(); cout << "\n Invalid Input!";}
    }
}

// Funktion
void drawField()
{
    clearConsole();
    cout << "\n\n\n"
         << "    " << field[1] << " | " << field[2] << " | " << field[3] << endl
         << "   ---|---|---" << endl
         << "    " << field[4] << " | " << field[5] << " | " << field[6] << endl
         << "   ---|---|---" << endl
         << "    " << field[7] << " | " << field[8] << " | " << field[9] << endl;
}

// Funktion "singler player"
void singleplayer()
{
    clearConsole();
    char input = ' ';
    int difficulty = 0;
    cout << "\n\n\n DIFFICULTY \n\n\n 1: Easy"
         <<                     "\n\n 2: Medium"
         <<                     "\n\n 3: Hard \n\n";
    cout << "\n\n\n Input: ";
    cin >> input;
    switch(input)
    {
        case '1': difficulty = 1; break;
        case '2': difficulty = 2; break;
        case '3': difficulty = 3; break;
        case 'q': return; break;
        default:    cout << "\n Invalid Input!"; singleplayer(); break;
    }
    while(true)
    {
        drawField();
        if(checkWin('O'))
        {
            cout << "\n Computer has won \n\n";
            return;
        }
        if(checkFull())
        {
            cout << "\n Tie \n\n";
        }
        input = keyInput(true);
        drawField();
        if(input == 'q')
        {
            return;
        }
        if(checkWin('X'))
        {
            cout << "\n Player has won \n\n";
            return;
        }
        AI(difficulty);
    }
}

// Funktion
void multiplayer()
{
    char input = ' ';
    bool player1Turn = true;
    while(true)
    {
        drawField();
        if(checkWin('X'))
        {
            cout << "\n Player1 has won \n\n";
            return;
        }
        else if(checkWin('O'))
        {
            cout << "\n Player2 has won \n\n ";
            return;
        }
        if(checkFull())
        {
            cout << "Tie \n\n";
        }
        input = keyInput(player1Turn);
        if(input == 'q')
        {
            return;
        }
        player1Turn = !player1Turn;
    }
}

// Funktion Help
void help()
{
    clearConsole();
    cout << "\n\n\n HELP"
         << "\n\n Singleplayer:"
         << "\n In Singleplayermode you play against the Computer"
         << "\n Multiplayer:"
         << "\n Multiplayermode you play again";
}


// Funktion keyinput
char keyInput (bool x)
{
    while(true)
    {
        cout << "\n\n Input: ";
        char input = ' ';
        cin >> input;
        int inputNumber = input - '0';
        if(inputNumber > 9 || inputNumber < 1)
        {
            if(input == 'q')
            {
                return input;
            }
            else
            {
                cout << "\n Invalid Input!";
            }
        }
        else if (field[inputNumber] != ' ')
        {
            cout << "\n This field is already used";
        }
        else{
            if(x)
            {
                field[inputNumber] = 'X';
            }
            else
            {
                field[inputNumber] = 'O';
            }
            return input;
        }
    }
}

// Funktion
bool checkWin(char sing)
{
    if (field[1] == sing && field[2] == sing && field[3] == sing || field[1] == sing && field[4] == sing && field[7] == sing ||
        field[1] == sing && field[5] == sing && field[9] == sing || field[2] == sing && field[5] == sing && field[8] == sing ||
        field[3] == sing && field[6] == sing && field[9] == sing || field[3] == sing && field[5] == sing && field[7] == sing ||
        field[4] == sing && field[5] == sing && field[6] == sing || field[7] == sing && field[8] == sing && field[9] == sing)
        {
            return true;
        }
    return false;
}

// Funktion
bool checkFull(){
    for(int i = 1; i <= 9; i++){
        if(field[i] == ' '){
            return false;
        }
    }
    return true;
}

void AI(int difficulty)
{
    if(checkFull())
    {
        return;
    }
    srand(time(nullptr));
    if(difficulty == 1)
    {
        int check = rand() % 3;
        if(check != 1)
        {
            for(int i=1; i<10; i++)
            {
               if(field[i] == ' ')
               {
                   field[i] = 'O';
                   if(checkWin('O'))
                   {
                        return;
                   }
                    else
                    {
                    field[i] = ' ';
                    }
                }
            }
        }
        else if(check != 2)
        {
            for(int i=1; i<10; i++)
            {
                if(field[i] == ' ')
                {
                    field[i] = 'X';
                    if(checkWin('X'))
                    {
                        field[i] = 'O';
                        return;
                    }
                    else
                    {
                        field[i] = ' ';
                    }
                }
            }
        }
        while (true)
        {
            int i = rand() % 9 + 1;
            if (field[i] == ' ')
            {
                field[i] = 'O';
                return;
            }
        }
    }
    else if(difficulty == 2)
    {
        int check = rand() % 5 + 1;
        if (check != 3)
        {
           for(int i=1; i<10; i++)
           {
               if(field[i] == ' ')
               {
                   field[i] = 'O';
           if(checkWin('O'))
           {
                    return;
                }
                else {
                    field[i] = ' ';
                }
            }
            }
        }
        else if(check != 2)
        {
            for(int i=1; i<10; i++)
            {
                if(field[i] == ' ')
                {
                    field[i] = 'X';
                    if(checkWin('X'))
                    {
                        field[i] = 'O';
                        return;
                    }
                    else
                    {
                        field[i] = ' ';
                    }
                }
            }
        }
        while (true)
        {
            int i = rand() % 9 + 1;
            if (field[i] == ' ')
            {
                field[i] = 'O';
                return;
            }
        }
    }
    else if(difficulty == 3)
    {
        // Hard
        // Check if AI can win
        for(int i=1; i<10; i++)
        {
            if(field[i] == ' ')
            {
                field[i] = 'O';
                if(checkWin('O'))
                {
                    return;
                }
                else
                {
                    field[i] = ' ';
                }
            }
        }

        // Check if Player can win and stop it
        for(int i=1; i<10; i++)
        {
            if(field[i] == ' ')
            {
                field[i] = 'X';
                if(checkWin('X'))
                {
                    field[i] = 'O';
                    return;
                }
                else
                {
                    field[i] = ' ';
                }
            }
        }
        // Set to field in the middle with a chance when it is still free
        int middle = rand() % 4;
        if(field[5] == ' ' && middle != 1)
        {
            field[5] = 'O';
            return;
        }
        // Set random field
        while(true)
        {
            int i = rand() % 9 + 1;
            if(field[i] == ' ')
            {
                field[i] = 'O';
                return;
            }
        }
    }
    else {
        return;
    }
}

int main()
{
    menu();
    drawField();
    system("PAUSE");
    cout << "Hello world!" << endl;
    return 0;
}
