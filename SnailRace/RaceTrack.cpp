#include "RaceTrack.h"

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

RaceTrack::RaceTrack(int player_count, int canvas_width) : player_count(player_count), canvas_width(canvas_width), canvas(vector<vector<string>>((player_count * 2) + 1, vector<string>(canvas_width, " "))) {

    vector<string> alphabet = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    for (int i = 0; i < player_count; i++)
    {
        Player new_player(alphabet[i], 0, i * 2 + 1);
        players.push_back(new_player);
        add_player_to_canvas(new_player);
    }
}

void RaceTrack::start() {
    add_track();
    render();

    while (get_winners().size() == 0)
    {
        update_players();
    }

    system("pause");

    callback(get_winners());
}

void RaceTrack::setCallback(Callback callback) {
    this->callback = callback;
}

void RaceTrack::add_track() {
    int lanes = player_count + 1;
    int height = lanes + player_count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < canvas_width; j++)
        {
            if ((i % 2) == 0 || j == 0)
            {
                canvas[i][j] = '#';
            }
        }
    }
}

void RaceTrack::add_player_to_canvas(Player player) {
    canvas[player.y_position][player.x_position] = player.identifier;
}

void RaceTrack::move_players() {
    random_device rd;

    for (int i = 0; i < players.size(); i++)
    {
        mt19937 gen(rd());
        uniform_int_distribution<> movement_threshold(1, 3);

        canvas[players[i].y_position][players[i].x_position] = ' ';

        int new_position = min(canvas_width - 1, players[i].x_position + movement_threshold(gen));

        players[i].x_position = new_position;

        add_player_to_canvas(players[i]);
    }
}

void RaceTrack::update_players() {
    this_thread::sleep_for(chrono::milliseconds(150));

    system("CLS");

    move_players();

    render();
}

void RaceTrack::render() {
    for (int i = 0; i < canvas.size(); i++)
    {
        for (int j = 0; j < canvas[i].size(); j++)
        {
            cout << canvas[i][j];
        }

        cout << endl;
    }
}

vector<Player> RaceTrack::get_winners() {
    vector<Player> winners;

    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].has_reached_end(canvas_width))
        {
            winners.push_back(players[i]);
        }
    }

    return winners;
}