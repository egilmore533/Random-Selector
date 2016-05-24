#include <string.h>

#include "game_selector.h"

static Game *gameList = NULL;
static int gameNum = 0;
static int gameMax = 0;

void game_list_system_initialize(int maxGames)
{
	int i;
	if(maxGames == 0)
	{
		printf("maxGames == 0\n");
		return;
	}
	gameList = (Game *) malloc (sizeof (Game) * maxGames);
	if(!gameList)
	{
		printf("failed to initialize gameList\n");
		return;
	}
	memset(gameList, 0, sizeof (Game) * maxGames);
	
	gameNum = 0;
	gameMax = maxGames;
	atexit(game_list_close_system);
}

void game_list_close_system()
{
	int i;
	Game *game;
	if(!gameList)
	{
		printf("gameList not initialized\n");
		return;
	}
	for(i = 0; i < gameMax; i++)
	{
		if(!gameList[i].used)
		{
			continue;
		}
		game = &gameList[i];
		game_free(&game);
	}
	gameNum = 0;
	free(gameList);
	gameList = NULL;
}

void game_free(Game **game)
{
	Game *self;
	if(!game)
	{
		return;
	}
	else if(!*game) 
	{
		return;
	}
	self = *game;
	self->used--;

	gameNum--;
	*game = NULL;
}

Game *game_new(char *game_name)
{
	int i;
	/*makesure we have the room for a new sprite*/
	if(gameNum + 1 > gameMax)
	{
		printf("Maximum Games Reached\n");
		exit(1);
	}
	for(i = 0; i < gameMax; i++)
	{
		if(gameList[i].used)
		{
			continue;
		}

		//found the first entity in the list that is free to use, 
		// clear memory, fill out config data, increment entityNum, and return the new entity
		memset(&gameList[i],0,sizeof(Game));

		gameList[i].used = 1;
		gameList[i].game_name = game_name;
		gameNum++;

		return &gameList[i];
	}
	return NULL;
}

void game_list_initialize(cJSON *json)
{
	//config file stuff
	cJSON *root;

	//system loading stuff
	int maxGames;
	int i;
	char game_num_string[10];

	root = cJSON_GetObjectItem(json,"game_list");
	if(!root)
	{
		printf("error parseing the file, file not the game_list\n");
		return;
	}
	maxGames = cJSON_GetObjectItem(root, "gameNumber")->valueint;
	game_list_system_initialize(maxGames);
	for(i = 0; i < maxGames; i++)
	{
		sprintf(game_num_string, "game %d", i);
		game_new(cJSON_GetObjectItem(root, game_num_string)->valuestring);
	}
}

Game *game_select()
{
	int random_num;
	int i;
	int count = 0;

	if(!gameList)
	{
		printf("game list not initialized\n");
	}
	if(gameNum == 0)
	{
		printf("no games\n");
	}
	else if(gameNum == 1)
	{
		random_num = 1;
	}
	else
	{
		random_num = rand() % gameNum;
	}
	for(i = 0; i < gameMax; i++)
	{
		if(gameList[i].used)
		{
			if(count >= random_num)
			{
				return &gameList[i];
			}
			count++;
		}
	}
	return NULL;
}
