/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashxo <nashxo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:27:19 by amagomad          #+#    #+#             */
/*   Updated: 2025/02/09 21:15:12 by nashxo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <ctype.h>
# include <string.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../lib/includes/libft.h"

# define WIDTH 1024
# define HEIGHT 510
# define MAP_S 64

	// STRUCTURES

typedef struct s_player
{
	float	player_pos_x;
	float	player_pos_y;
	float	player_dir_x;
	float	player_dir_y;
	float	player_angle;
	float	move_speed;
	float	velocity;
}	t_player;

typedef enum e_state
{
	STATE_MENU,
	STATE_GAME,
	STATE_PAUSE
}	t_state;

typedef struct s_parsing
{
	int		file_fd;
	char	**description;
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*floor_color;
	char	*ceiling_color;
	int		map_width;
	int		map_height;
}	t_parsing;

typedef struct s_intersect
{
	float	rx;
	float	ry;
	float	dist;
}	t_intersect;

typedef struct s_data
{
	t_player		*player;
	t_parsing		*parse;
	mlx_t			*mlx;
	mlx_texture_t	*icon;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	mlx_image_t		*img;
	int				**map;
	int				map_width;
	int				map_height;
	bool			show_minimap;
	bool			debug_mode;
	int				minimap_tile_size;
	char			player_dir;
	int				player_x;
	int				player_y;
	t_state			state;
	int				selected_option;
}	t_data;


	//	FONCTIONS

float		degToRad(float a);
float		FixAng(float a);
void		return_error(char *str);
int			is_wall(t_data *data, float x, float y);
void		draw_rect(mlx_image_t *img, int x, int y, int width, int height, uint32_t color);
void		draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color);
void		drawMap2D(mlx_image_t *img, t_data *data);
void		drawPlayer2D(mlx_image_t *img, t_player *p);
void		clear_image(mlx_image_t *img, uint32_t color);
void		render(void *param);
t_intersect	get_vertical_intersection(t_player *p, t_data *data, float ra);
t_intersect	get_horizontal_intersection(t_player *p, t_data *data, float ra);
void		drawRays2D(mlx_image_t *img, t_player *p, t_data *data);
bool		transform_map(t_data *data);
void		key_hook(mlx_key_data_t keydata, void *param);
void		ft_free(t_data *data);

#endif
