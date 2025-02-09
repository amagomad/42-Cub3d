#include "../../includes/cub3d.h"

static int convert_char_to_int(char c, t_player *player, int col, int row)
{
	if (isspace(c))
		return -1;
	if (c == '1')
		return 1;
	if (c == '0')
		return 0;
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (c == 'N')
			player->player_angle = 90;
		else if (c == 'S')
			player->player_angle = 270;
		else if (c == 'W')
			player->player_angle = 0;
		else if (c == 'E')
			player->player_angle = 180;
		player->player_pos_x = (col + 0.5) * MAP_S;
		player->player_pos_y = (row + 0.5) * MAP_S;
		player->player_dir_x = cos(degToRad(player->player_angle));
		player->player_dir_y = -sin(degToRad(player->player_angle));
		return 0;
	}
	return -1;
}

bool transform_map(t_data *data)
{
	int i, j;
	int width = data->parse->map_width;
	int height = data->parse->map_height;

	data->map = malloc(sizeof(int *) * height);
	if (!data->map)
		return false;
	for (i = 0; i < height; i++)
	{
		data->map[i] = malloc(sizeof(int) * width);
		if (!data->map[i])
			return false;
		for (j = 0; j < width; j++)
		{
			if (j >= (int)ft_strlen(data->parse->map[i]))
				data->map[i][j] = -1;
			else
				data->map[i][j] = convert_char_to_int(data->parse->map[i][j], data->player, j, i);
		}
	}
	data->map_width = width;
	data->map_height = height;
	return true;
}
