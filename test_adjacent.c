#include "inc/cub3d.h"

static int	check_adjacent(char **map, int y, int x, int height, int width)
{
    // Verificar as 4 direções adjacentes
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int i;
    int new_y;
    int new_x;

    i = 0;
    while (i < 4)
    {
        new_y = y + directions[i][0];
        new_x = x + directions[i][1];
        
        // Verificar se a posição adjacente está dentro dos limites
        if (new_y >= 0 && new_y < height && new_x >= 0 && new_x < width)
        {
            // Se encontrar algo que não seja '#' ou '1', mapa é inválido
            if (map[new_y][new_x] != '#' && map[new_y][new_x] != '1')
                return (FAILURE);
        }
        i++;
    }
    return (SUCCESS);
}

static int	validate_walls(t_map *map)
{
    char	**map_copy;
    int		y;
    int		x;
    int		new_height;
    int		new_width;

    map_copy = copy_map(map);
    if (!map_copy)
        return (FAILURE);

    new_height = map->height + 2;
    new_width = map->width + 2;

    // Verificar posição do jogador
    if (map->player_x < 0 || map->player_x >= map->width
        || map->player_y < 0 || map->player_y >= map->height)
    {
        int i = 0;
        while (map_copy[i])
            free(map_copy[i++]);
        free(map_copy);
        return (FAILURE);
    }

    // Verificar adjacentes de cada '#'
    y = 0;
    while (y < new_height)
    {
        x = 0;
        while (x < new_width && map_copy[y][x])
        {
            if (map_copy[y][x] == '#')
            {
                if (check_adjacent(map_copy, y, x, new_height, new_width) == FAILURE)
                {
                    int i = 0;
                    while (map_copy[i])
                        free(map_copy[i++]);
                    free(map_copy);
                    return (FAILURE);
                }
            }
            x++;
        }
        y++;
    }

    // Liberar memória
    int i = 0;
    while (map_copy[i])
        free(map_copy[i++]);
    free(map_copy);
    
    return (SUCCESS);
}
