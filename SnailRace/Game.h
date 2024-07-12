#pragma once

#include "Player.h"
#include "Bet.h"

#include <vector>

using namespace std;

class Game
{
public:
	Game(int earnings);
	void start();
	void set_bet(Bet& bet, int player_count);

private:
	float earnings;
	Bet current_bet;

	void error();
	void display(int& user_option);
	void handle_race_finish(vector<Player> players);
	void configure_race_track(int& player_count);
	void start_race();
};

