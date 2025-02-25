/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:27:19 by amagomad          #+#    #+#             */
/*   Updated: 2025/02/23 18:16:27 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <sys/stat.h>
# include "../.MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"

# define WIDTH 1920
# define HEIGHT 1080

# define PLANE_SIZE 0.66

# define T_SIZE 30

# define WALK_SPEED 1.5
# define ROTATION_SPEED 0.018

# define PLAYER_RADIUS 5
# define MAP_OFFSET_X 20
# define MAP_OFFSET_Y 20

# define MLX_TOTAL_KEYS 349

typedef struct s_parsing
{
	int		file_fd;
	char	**desc;
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*floor_color;
	char	*ceiling_color;
	char	*line;
}	t_parsing;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	angle;
	float	move_speed;
	float	plane_x;
	float	plane_y;
}	t_player;

typedef struct s_color
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	abgr;
}	t_color;

typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	double			camera_x;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				x;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	double			perp_wall_dist;
	uint32_t		*pixel_buffer;
	mlx_texture_t	*texture;
}	t_ray;

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
	mlx_texture_t	*door_texture;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	mlx_image_t		*img;
	int				**map;
	int				map_width;
	int				map_height;
	char			player_dir;
	int				player_x;
	int				player_y;
	bool			keys[MLX_TOTAL_KEYS];
}	t_data;

// ================== PARSING ==================
bool		parsing(char *file, t_data *data);
void		stock_map(t_data *data);
bool		stock_desc(t_parsing *parse);
void		return_error(char *str, t_data *data, bool free_parse);
bool		validity_desc(t_parsing *parse);
void		validity_map(t_data *data);
bool		open_file(char *file, t_parsing *parse);
bool		file_validity(char *file);
void		valid_color(t_parsing *parsing, t_data *data);
void		transform_map(t_data *data);
void		validity_map_wall(t_data *data);
void		display_map(t_data *data);
void		set_player_starting_direction(t_data *data);
void		load_texture(t_data *data);

// ================== MOUVEMENT ==================
void		handle_keypress(mlx_key_data_t keydata, void *param);
void		move_player(t_data *data, float move_x, float move_y);

// ================== UTILS ==================
void		free_data(t_data *data);
void		render_frame(void *param);
void		my_put_pixel(t_data *data, int x, int y, uint32_t color);

// ================== RAYCASTING ==================
void		raycasting(t_data *data);
void		draw_rect(t_data *data, int x, int y, uint32_t color);
void		draw_wall(t_ray *ray);
void		calcul_texture(t_ray *ray, t_data *data);
void		calcul_wall_x(t_ray *ray, t_data *data);

void		free_all(t_data *data);
void		ft_free_str_tab(char **tab_str);

void		process_keys(t_data *data);
void		rotate_right(t_data *data, double rotation_speed);
void		rotate_left(t_data *data, double rotation_speed);
void		movement_key(t_data *data);
void		init(t_data *data, char **av);

void		free_parsing(t_data *data);
#endif