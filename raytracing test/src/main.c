#include "../includes/raycasting.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y <= 0)
		return ;
	index = y * game->line_size + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	for (i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for (i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for (i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for (i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		y;
	int		x;

	map = game->map;
	color = 0x0000FF;
	for (y = 0; map[y]; y++)
		for (x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

char	**get_map(void)
{
	char	**map;

	map = (char **)malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000100000001";
    map[5] = "100000100000001";
    map[6] = "100000100000001";
    map[7] = "100000100000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "test");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->line_size, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
}

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = &game->player;
	move_player(player);
	clear_image(game);
	draw_square(player->x, player->y, 10, 0x00FF00, game);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	//draw_square(WIDTH / 2, HEIGHT / 2, 10, 0x00FF00, &game);
	mlx_loop(game.mlx);
	return (0);
}
