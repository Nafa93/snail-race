#pragma once

#include "Player.h"

#include <vector>
#include <functional>
#include <string>

using namespace std;

class RaceTrack
{
public:
    using Callback = function<void(vector<Player>)>;
    RaceTrack(int player_count, int canvas_width);
    void start();
    void setCallback(Callback callback);

private:
    int player_count;
    int canvas_width;
    vector<vector<string>> canvas;
    vector<Player> players;
    Callback callback;

    void add_track();
    void add_player_to_canvas(Player player);
    void render();
    void move_players();
    void update_players();
    vector<Player> get_winners();
};