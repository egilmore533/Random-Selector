#ifndef __GAME_SELECTOR_H__
#define __GAME_SELECTOR_H__

#include <stdlib.h>
#include <stdio.h>

#include "cJSON.h"

/** @file	game_selector.h
 *	@brief	class that stores a game (a char pointer of the game name), populate a list of games and randomly choose a game from that list.
 */



/**
 *	@struct Game structure
 *	@brief	a char pointer for the name of a game, could be used to store the name of anything though
 */
typedef struct Game_t{
	int used;
	char *game_name;
}Game;

/**
 * @brief initializes the game list from a cJSON file, calls game_list_system_initialize passing the number of games to allocate space for the games
 * @param [in] json an opened json object to parse for the number and list of games
 */
void game_list_initialize(cJSON *json);

/**
 * @brief allocates and memsets space for the number of games specified by the parameter
 * @breif	maxGames	the number of games the gameList will be able to handle
 */
void game_list_system_initialize(int maxGames);

/**
 * @brief frees the gameList using game_free, and sets the gameMax to 0 and gameNum to 0
 */
void game_list_close_system();

/**
 * @brief frees a game from the gameList
 */
void game_free(Game **game);

/**
 * @brief randomly selects a game from the gameList based on its size and returns it
 * @return a pointer to the selected game
 */
Game *game_select();

#endif
