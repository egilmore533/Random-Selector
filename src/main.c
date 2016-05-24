#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "cJSON.h"
#include "game_selector.h"

cJSON *cJSON_file_opener(char *def_file_path);

int main(int argc, char *argv[])
{
	int count = 1;
	cJSON *json = cJSON_file_opener("game_list.txt");
	Game *selected_game = NULL;
	srand ( time(NULL) );

	game_list_initialize(json);

	do
	{

	selected_game = game_select();

	if(selected_game)
	{
		printf("%s \n", selected_game->game_name);
	}	
	count--;

	}while(count);

	//loop so we can read the results
	while(1){}

	exit(0);
	return 0;
}

/**
 * @brief opens the given file and creates a cJSON object from it and returns that cJSON object
 * @param [in] filepath		the path to the file to create a cJSON object from
 * @return a cJSON object created from the given file_path
 */
cJSON *cJSON_file_opener(char *file_path)
{
	cJSON *json;
	FILE *config_file;
	long length;
	char *data;
	
	config_file = fopen(file_path,"r");
	if(!config_file)
	{
		printf("No file found: %s\n", file_path);
		return NULL;
	}

	//get the length of the file
	fseek(config_file, 0, SEEK_END);
	length = ftell(config_file);
	//reset position to start of the file and allocate data to be the length of the file + 1
	fseek(config_file, 0, SEEK_SET);
	data = (char*) malloc(length + 1);
	//store the contents of the file in data, and close the file
	fread(data, 1, length, config_file);
	fclose(config_file);

	json = cJSON_Parse(data);
	return json;
}
