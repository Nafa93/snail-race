#pragma once

#include <string>

using namespace std;

class Player
{
public:
    Player(string identifier, int x_position, int y_position);
    bool has_reached_end(int canvas_width);

    string identifier;
    int x_position;
    int y_position;
};