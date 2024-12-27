#include "../include/cub3D.h"

static void setup_test_player(t_player *player, double pos_x, double pos_y, 
    double dir_x, double dir_y);
static void    print_ray_info(t_camera *ray, t_player *player);
static char    **create_test_map(void);
static void    cleanup_test_map(t_game *game, char **original_map);

static void setup_test_player(t_player *player, double pos_x, double pos_y, 
    double dir_x, double dir_y)
{
    player->pos.x = pos_x;
    player->pos.y = pos_y;
    player->camera.dir_x = dir_x;
    player->camera.dir_y = dir_y;
    player->camera.plane_x = -dir_y * 0.66;
    player->camera.plane_y = dir_x * 0.66;
}

bool    test_ray_init(t_game *game)
{
    t_player    player;
    t_camera    camera;
    double      ray_dir_x;
    double      ray_dir_y;

    (void)game;
    setup_test_player(&player, 2.0, 2.0, 1.0, 0.0);
    ray_dir_x = player.camera.dir_x + player.camera.plane_x * 0;
    ray_dir_y = player.camera.dir_y + player.camera.plane_y * 0;

    init_ray(&camera, ray_dir_x, ray_dir_y);

    if (fabs(camera.ray_dir_x - ray_dir_x) > 0.0001
        || fabs(camera.ray_dir_y - ray_dir_y) > 0.0001)
    {
        printf("Expected ray dir: (%.4f, %.4f)\n", ray_dir_x, ray_dir_y);
        printf("Actual ray dir: (%.4f, %.4f)\n", camera.ray_dir_x, 
            camera.ray_dir_y);
        return (false);
    }
    return (true);
}

static char    **create_test_map(void)
{
    char    **map;
    int        i;
    char    *test_layout[] = {
        "111111",
        "100001",
        "100001",
        "100001",
        "111111",
        NULL
    };

    map = (char **)malloc(sizeof(char *) * 6);
    if (!map)
        return (NULL);
    i = 0;
    while (test_layout[i])
    {
        map[i] = ft_strdup(test_layout[i]);
        if (!map[i])
        {
            while (i > 0)
                free(map[--i]);
            free(map);
            return (NULL);
        }
        i++;
    }
    map[i] = NULL;
    return (map);
}

bool    test_wall_detection(t_game *game)
{
    t_ray_test    test_cases[] = {
        {.player = {.pos = {2.5, 2.5}, .camera = {.dir_x = 1.0, .dir_y = 0.0}},
            1.5, true, 0},
        {.player = {.pos = {2.5, 2.5}, .camera = {.dir_x = 0.0, .dir_y = 1.0}},
            1.5, true, 1},
        {.player = {.pos = {2.5, 2.5}, .camera = {.dir_x = -1.0, .dir_y = 0.0}},
            1.5, true, 0}
    };
    int         i;
    bool        success;
    char        **original_map;

    original_map = game->map.matrix;
    game->map.matrix = create_test_map();
    if (!game->map.matrix)
        return (false);

    success = true;
    i = 0;
    while (i < 3 && success)
    {
        t_camera ray;
        double ray_dir_x = test_cases[i].player.camera.dir_x;
        double ray_dir_y = test_cases[i].player.camera.dir_y;

        init_ray(&ray, ray_dir_x, ray_dir_y);
        calculate_step_dist(&ray, &test_cases[i].player.pos);

        printf("\nTest case %d:\n", i + 1);
        print_ray_info(&ray, &test_cases[i].player);

        int side = perform_dda(game, &ray);
        calculate_wall_dist(&ray, side);

        printf("Results:\n");
        print_ray_results(&ray, side, test_cases[i].expected_dist,
            test_cases[i].expected_side);

        if (!verify_ray_results(&ray, side, &test_cases[i]))
        {
            printf("❌ Test case %d failed!\n", i + 1);
            success = false;
        }
        i++;
    }
    cleanup_test_map(game, original_map);
    return (success);
}

static void    print_ray_info(t_camera *ray, t_player *player)
{
    printf("Player position: (%.2f, %.2f)\n", player->pos.x, player->pos.y);
    printf("Ray direction: (%.2f, %.2f)\n", ray->ray_dir_x, ray->ray_dir_y);
    printf("Initial map position: (%d, %d)\n", ray->map_x, ray->map_y);
    printf("Step direction: (%d, %d)\n", ray->step_x, ray->step_y);
    printf("Delta distance: (%.2f, %.2f)\n", ray->delta_dist_x, ray->delta_dist_y);
    printf("Side distance: (%.2f, %.2f)\n", ray->side_dist_x, ray->side_dist_y);
}

static void    cleanup_test_map(t_game *game, char **original_map)
{
    int    i;

    i = 0;
    while (game->map.matrix[i])
        free(game->map.matrix[i++]);
    free(game->map.matrix);
    game->map.matrix = original_map;
}

bool    test_raycasting(t_game *game)
{
    bool    all_passed;

    all_passed = true;
    printf("\nRunning raycasting tests...\n");

    if (!test_ray_init(game))
    {
        printf("❌ Ray initialization test failed\n");
        all_passed = false;
    }
    else
        printf("✅ Ray initialization test passed\n");

    if (!test_wall_detection(game))
    {
        printf("❌ Wall detection test failed\n");
        all_passed = false;
    }
    else
        printf("✅ Wall detection test passed\n");

    return (all_passed);
}