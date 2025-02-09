#include "../../includes/cub3d.h"

float degToRad(float a)
{
	return a * (M_PI / 180.0);
}

float FixAng(float a)
{
	while (a < 0)
		a += 360;
	while (a >= 360)
		a -= 360;
	return a;
}

void return_error(char *str)
{
	fprintf(stderr, "Error: %s\n", str);
	exit(1);
}


int is_wall(t_data *data, float x, float y)
{
	int mx = (int)x / MAP_S;
	int my = (int)y / MAP_S;
	if (mx < 0 || mx >= data->map_width || my < 0 || my >= data->map_height)
		return 1;
	return (data->map[my][mx] == 1);
}
