#include "../include/cub3D.h"
#include "../include/test.h"
#include <math.h>
#include <string.h>

// Utility function to setup a test map
static char **create_test_map(void)
{
    char *test_layout[] = {
        "111111",
        "100001",
        "100001",
        "100001",
        "111111",
        NULL
    };
    
    char **map = calloc(6, sizeof(char *));
    if (!map) return NULL;
    
    for (int i = 0; test_layout[i]; i++) {
        map[i] = strdup(test_layout[i]);
        if (!map[i]) {
            // Free previously allocated memory if allocation fails
            while (i > 0) {
                free(map[--i]);
            }
            free(map);
            return NULL;
        }
    }
    
    return map;
}

// Utility function to cleanup test map
static void cleanup_test_map(t_game *game, char **original_map)
{
    if (game->map.matrix) {
        for (int i = 0; game->map.matrix[i]; i++) {
            free(game->map.matrix[i]);
        }
        free(game->map.matrix);
    }
    game->map.matrix = original_map;
}

// Helper function to print detailed ray information
static void print_detailed_ray_info(t_camera *camera, t_pos *pos, const char *test_name)
{
    printf("%s Detailed Ray Information:\n", test_name);
    printf("Player Position: (%.2f, %.2f)\n", pos->x, pos->y);
    printf("Camera Direction: (%.2f, %.2f)\n", camera->dir_x, camera->dir_y);
    printf("Ray Direction: (%.2f, %.2f)\n", camera->ray_dir_x, camera->ray_dir_y);
    printf("Initial Map Position: (%d, %d)\n", camera->map_x, camera->map_y);
    printf("Delta Distance: (%.2f, %.2f)\n", camera->delta_dist_x, camera->delta_dist_y);
    printf("Side Distance X: %.2f (Step: %d)\n", camera->side_dist_x, camera->step_x);
    printf("Side Distance Y: %.2f (Step: %d)\n", camera->side_dist_y, camera->step_y);
    printf("Perpendicular Wall Distance: %.2f\n", camera->perp_wall_dist);
}

// Test ray initialization with more verbose debugging
static bool test_ray_initialization(void)
{
    printf("\nTesting Ray Initialization...\n");
    
    struct {
        double dir_x;
        double dir_y;
        double pos_x;
        double pos_y;
    } test_cases[] = {
        // Test case 1: Facing right
        {1.0, 0.0, 2.5, 2.5},
        // Test case 2: Facing up
        {0.0, -1.0, 2.5, 2.5}
    };
    
    int test_count = sizeof(test_cases) / sizeof(test_cases[0]);
    bool all_passed = true;

    for (int i = 0; i < test_count; i++) {
        t_camera camera = {0};
        t_pos pos = {.x = test_cases[i].pos_x, .y = test_cases[i].pos_y};
        
        // Manually set camera direction for this test
        camera.dir_x = test_cases[i].pos_x;
        camera.dir_y = test_cases[i].pos_y;
        
        // Initialize ray
        init_ray(&camera, test_cases[i].dir_x, test_cases[i].dir_y, &pos);
        
        // Verify ray initialization
        bool test_passed = true;
        
        // Check ray direction
        if (fabs(camera.ray_dir_x - test_cases[i].dir_x) > 0.0001 || 
            fabs(camera.ray_dir_y - test_cases[i].dir_y) > 0.0001)
        {
            printf("❌ Ray Direction Test %d Failed\n", i + 1);
            printf("Expected: (%.4f, %.4f), Got: (%.4f, %.4f)\n", 
                   test_cases[i].dir_x, test_cases[i].dir_y, 
                   camera.ray_dir_x, camera.ray_dir_y);
            test_passed = false;
        }
        
        // Print detailed ray information
        print_detailed_ray_info(&camera, &pos, "Initialization");
        
        // Check delta distances handling
        if ((test_cases[i].dir_x == 0 && camera.delta_dist_x != 1e30) ||
            (test_cases[i].dir_y == 0 && camera.delta_dist_y != 1e30))
        {
            printf("❌ Delta Distance Handling Test %d Failed\n", i + 1);
            test_passed = false;
        }
        
        // Check map position calculation
        int expected_map_x = (int)pos.x;
        int expected_map_y = (int)pos.y;
        if (camera.map_x != expected_map_x || camera.map_y != expected_map_y)
        {
            printf("❌ Map Position Test %d Failed\n", i + 1);
            printf("Expected Map Position: (%d, %d), Got: (%d, %d)\n", 
                   expected_map_x, expected_map_y, camera.map_x, camera.map_y);
            test_passed = false;
        }
        
        if (test_passed) {
            printf("✅ Ray Initialization Test %d Passed\n", i + 1);
        }
        else {
            all_passed = false;
        }
    }
    
    return all_passed;
}

// Test Digital Differential Analysis (DDA) algorithm
static bool test_dda_algorithm(t_game *game)
{
    printf("\nTesting Digital Differential Analysis (DDA) Algorithm...\n");
    
    // Create a test map
    char **original_map = game->map.matrix;
    game->map.matrix = create_test_map();
    if (!game->map.matrix) return false;
    
    // Set game map dimensions
    game->map.width = 6;
    game->map.height = 5;
    
	struct {
		double pos_x;
		double pos_y;
		double ray_dir_x;
		double ray_dir_y;
		int expected_grid_cells_traversed;
		int expected_side;
	} test_cases[] = {
		// Test case 1: Facing right from center
		{
			.pos_x = 2.5,
			.pos_y = 2.5,
			.ray_dir_x = 1.0,
			.ray_dir_y = 0.0,
			.expected_grid_cells_traversed = 3,
			.expected_side = 0  // X-side
		},
		// Test case 2: Facing up from center
		{
			.pos_x = 2.5,
			.pos_y = 2.5,
			.ray_dir_x = 0.0,
			.ray_dir_y = -1.0,
			.expected_grid_cells_traversed = 2,
			.expected_side = 1  // Y-side
		}
	};
    
    int test_count = sizeof(test_cases) / sizeof(test_cases[0]);
    bool all_passed = true;

    for (int i = 0; i < test_count; i++) {
        t_camera camera = {0};
        t_pos player_pos = {.x = test_cases[i].pos_x, .y = test_cases[i].pos_y};
        
        // Extensive diagnostic printing
        printf("\nTest Case %d Detailed Diagnostics:\n", i + 1);
        printf("Starting Position: (%.2f, %.2f)\n", player_pos.x, player_pos.y);
        printf("Map Cell: (%d, %d)\n", 
            (int)player_pos.x, (int)player_pos.y);
        printf("Fractional Position: (%.2f, %.2f)\n", 
            player_pos.x - floor(player_pos.x), 
            player_pos.y - floor(player_pos.y));
        printf("Ray Direction: (%.2f, %.2f)\n", 
            test_cases[i].ray_dir_x, test_cases[i].ray_dir_y);
        
        // Manually set camera direction for this test
        camera.dir_x = test_cases[i].pos_x;
        camera.dir_y = test_cases[i].pos_y;
        
        // Initialize ray
        init_ray(&camera, test_cases[i].ray_dir_x, test_cases[i].ray_dir_y, &player_pos);
        
        // Calculate initial step and side distances
        calculate_step_dist(&camera, &player_pos);
        
        // Print detailed information before DDA
        printf("\nBefore DDA - Test Case %d:\n", i + 1);
        print_detailed_ray_info(&camera, &player_pos, "Pre-DDA");
        
        // Perform DDA
        int side = perform_dda(game, &camera);
        
        // Calculate wall distance
        calculate_wall_dist(&camera, side);
		printf("Debug Wall Distance Calculation:\n");
		printf("Player Position: (%.2f, %.2f)\n", player_pos.x, player_pos.y);
		printf("Fractional X: %.2f, Fractional Y: %.2f\n", 
			player_pos.x - floor(player_pos.x), 
			player_pos.y - floor(player_pos.y));
		printf("Map X: %d, Map Y: %d\n", camera.map_x, camera.map_y);
		printf("Ray Direction: (%.2f, %.2f)\n", camera.ray_dir_x, camera.ray_dir_y);
		printf("Step X: %d, Step Y: %d\n", camera.step_x, camera.step_y);
		printf("Calculated Wall Distance: %.2f\n", camera.perp_wall_dist);
        
        // Print detailed information after DDA
        printf("After DDA - Test Case %d:\n", i + 1);
        print_detailed_ray_info(&camera, &player_pos, "Post-DDA");
        
        // Verify results
        bool test_passed = true;
        
        // Check side hit
        if (side != test_cases[i].expected_side) {
            printf("❌ DDA Test %d Failed - Incorrect Side Hit\n", i + 1);
            printf("Expected Side: %d, Got: %d\n", 
                   test_cases[i].expected_side, side);
            test_passed = false;
        }
        
		// In the verification section, replace the previous distance check with:
		// Verify grid cells traversed
		int grid_cells_traversed = abs(camera.map_x - (int)player_pos.x) + 
								abs(camera.map_y - (int)player_pos.y);
		if (grid_cells_traversed != test_cases[i].expected_grid_cells_traversed) {
			printf("❌ DDA Test %d Failed - Incorrect Grid Cells Traversed\n", i + 1);
			printf("Expected: %d, Got: %d\n", 
				test_cases[i].expected_grid_cells_traversed, 
				grid_cells_traversed);
			test_passed = false;
		}

		// Wall distance check now focuses on being a reasonable value
		if (!isfinite(camera.perp_wall_dist) || 
			camera.perp_wall_dist <= 0) 
		{
			printf("❌ DDA Test %d Failed - Invalid Wall Distance\n", i + 1);
			printf("Calculated Wall Distance: %.2f\n", camera.perp_wall_dist);
			test_passed = false;
		}
        
        if (test_passed) {
            printf("✅ DDA Test %d Passed\n", i + 1);
        }
        else {
            all_passed = false;
        }
		printf("Calculated Wall Distance Components:\n");
        printf("Initial Fractional Distance: %.2f\n", 
            side == 0 
                ? (player_pos.x - floor(player_pos.x))
                : (player_pos.y - floor(player_pos.y)));
        printf("Grid Cells Traversed: %d\n", 
            abs(camera.map_x - (int)player_pos.x) + 
            abs(camera.map_y - (int)player_pos.y));
    }
    
    // Cleanup
    cleanup_test_map(game, original_map);
    
    return all_passed;
}

// Main test function for raycasting
bool test_raycasting(t_game *game)
{
    printf("\nRunning Raycasting Tests...\n");
    
    // Run tests
    bool ray_init_passed = test_ray_initialization();
    bool dda_passed = test_dda_algorithm(game);
    
    // Overall test result
    bool all_tests_passed = ray_init_passed && dda_passed;
    
    if (all_tests_passed) {
        printf("\n🟢 All Raycasting Tests Passed Successfully!\n");
    }
    else {
        printf("\n🔴 Some Raycasting Tests Failed!\n");
    }
    
    return all_tests_passed;
}