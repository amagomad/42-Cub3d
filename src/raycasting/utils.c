#include "../../includes/cub3d.h"


float FixAng(float a)
{
	while (a < 0)
		a += 360;
	while (a >= 360)
		a -= 360;
	return a;
}

int is_wall(t_data *data, float x, float y)
{
	int mx = (int)x / 64;
	int my = (int)y / 64;
	if (mx < 0 || mx >= data->map_width || my < 0 || my >= data->map_height)
		return 1;
	return (data->map[my][mx] == 1);
}
