#include "Game.h"
#include "RaceTrack.h"
#include "Player.h"
#include "Bet.h"

#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include <vector>

using namespace std;

Game::Game(int earnings) : earnings(earnings) { }

void Game::start()
{
    int user_option;

    display(user_option);

    while (user_option != 1 && user_option != 2) {
        system("CLS");

        error();

        display(user_option);
    }

    system("CLS");

    if (user_option == 1) {
        start_race();
    }
    else {
        exit(0);
    }
}

void Game::start_race()
{
    int player_count;

    configure_race_track(player_count);

    Bet bet;

    set_bet(bet, player_count);

    current_bet = bet;

    system("CLS");

    RaceTrack race_track(player_count, 60);

    race_track.setCallback([this](vector<Player> players) {
        this->handle_race_finish(players);
    });

    race_track.start();
}

void Game::set_bet(Bet& bet, int player_count)
{
    cout << "Ahora debes apostar por uno de los jugadores: ";

    cin >> bet.player;

    while (0 > bet.player || bet.player > player_count) {
        error();

        cout << "Ahora debes apostar por uno de los jugadores: ";

        cin >> bet.player;
    }

    printf("Ahora debes elegir un monto entre 1 y %.2f para apostar: ", earnings);

    cin >> bet.amount;

    while (0 > bet.amount || bet.amount > earnings) {
        error();

        printf("Ahora debes elegir un monto entre 1 y %.2f para apostar: ", earnings);

        cin >> bet.amount;
    }

    earnings -= bet.amount;
}

void Game::configure_race_track(int& player_count)
{
    cout << "Primero ingrese la cantidad de jugadores que competiran (4 - 9): ";

    cin >> player_count;

    while (4 > player_count || player_count > 9) {
        system("CLS");

        error();

        cout << "Primero ingrese la cantidad de jugadores que competiran (4 - 9): ";

        cin >> player_count;
    }
}

void Game::error()
{
    wstring wide_string = L"Error: el número ingresado no es una opción válida";
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    string converted_string = converter.to_bytes(wide_string);

    cout << converted_string << endl;
}

void Game::display(int& user_option)
{
    cout << "Bienvenidos a carrera de caracoles!" << endl;

    cout << "1. Iniciar" << endl;

    cout << "2. Salir" << endl;

    cin >> user_option;
}

void Game::handle_race_finish(vector<Player> players) {
    system("CLS");

    bool player_won = false;

    string winners;

    if (players.size() == 1) {
        printf("El ganador es el jugador %s", players[0].identifier.c_str());

        cout << endl;
        
        if (stoi(players[0].identifier) == current_bet.player && !player_won) {
            player_won = true;
        }
    }
    else {

        for (int i = 0; i < players.size(); i++) {
            if (i == 0) {
                winners += players[i].identifier;
            }
            else {
                winners += " y " + players[i].identifier;
            }

            if (stoi(players[i].identifier) == current_bet.player && !player_won) {
                player_won = true;
            }
        }

        printf("Tenemos multiples ganadores. Los ganadores son los jugadores %s!", winners.c_str());

        cout << endl;
    }

    if (player_won) {
        float new_balance = earnings + (current_bet.amount + current_bet.amount / players.size());
        
        printf("Has ganado la apuesta, tu nuevo balance es: %.2f", new_balance);

        cout << endl;
        
        earnings = new_balance;
    }
    else {
        printf("Has perdido la apuesta, tu nuevo balance es: %.2f", earnings);

        cout << endl;
    }

    if (earnings > 0) {
        int user_option;

        cout << "Desea continuar?" << endl;

        cout << "1. Continuar" << endl;

        cout << "2. Salir" << endl;

        cin >> user_option;

        while (user_option != 1 && user_option != 2) {
            system("CLS");

            error();

            cout << "Desea continuar?";

            cout << "1. Continuar";

            cout << "2. Salir";
        }

        if (user_option == 1) {
            system("CLS");

            start_race();
        }
        else {
            exit(0);
        }
    }
}
