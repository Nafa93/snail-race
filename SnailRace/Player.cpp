#include "Player.h"

Player::Player(string identifier, int x_position, int y_position) : identifier(identifier), x_position(x_position), y_position(y_position) { }

bool Player::has_reached_end(int canvas_width) {
    return x_position == canvas_width - 1;
}