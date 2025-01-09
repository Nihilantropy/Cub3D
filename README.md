Here's the modified README.md that aligns more closely with the subject requirements:

# 🎮 Cub3D - A Wolfenstein 3D-style Game Engine

## 🎯 Project Overview
Welcome to Cub3D, a project inspired by Wolfenstein 3D's rendering engine. Using raycasting, we transform a 2D map into an immersive 3D world, creating a dynamic view inside a maze.

## 🛠️ Technical Requirements 
The project must follow these specifications:
- Written in C according to the Norm
- Allowed functions:
  - Basic: open, close, read, write, printf, malloc, free, perror, strerror, exit
  - Math library (-lm)
  - MinilibX library
- Libft library is allowed

## 🗺️ Map and Scene Description
The scene is described in a .cub file containing:
- Wall textures for each direction:
  - NO ./texture/walls/north_wall_texture.xpm
  - SO ./texture/walls/south_wall_texture.xpm
  - WE ./texture/walls/west_wall_texture.xpm
  - EA ./texture/walls/east_wall_texture.xpm
- Floor and ceiling colors (RGB format)
- Map using these characters:
  - '0' for empty spaces
  - '1' for walls
  - 'N', 'S', 'E' or 'W' for player's starting position and direction

## 🎨 Raycasting Implementation

### 📐 Core Mechanics
1. For each screen column:
   - Calculate ray direction using camera plane
   - Determine wall intersections using DDA algorithm
   - Calculate wall height based on perpendicular distance

### 🎥 Display Requirements
1. Texture Display:
   - Different textures for each wall direction (N, S, E, W)
   - Floor and ceiling colors
   - Proper perspective correction

## 🎮 Controls

### 👾 Basic Controls
- Movement: W, A, S, D keys
- Camera rotation: Left/Right arrow keys
- Exit: ESC key or window close button

### 🏃‍♂️ Window Management
- Smooth window handling (minimize, switch)
- Clean exit on window close

## 🚀 Getting Started

### Building the Project
```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile everything
```

### Map Requirements
- Maps must be closed/surrounded by walls
- Only one player starting position
- Invalid maps should return "Error\n" with explicit message
- Spaces are valid in maps

## 🎨 Bonus Features
Optional enhancements:
- Wall collisions
- Minimap system
- Opening/closing doors
- Animated sprites
- Mouse-controlled camera rotation

## 🎯 Key Challenges & Solutions
Common issues to watch for:
- Texture alignment: Verify wall hit calculations
- Wall distortion: Ensure proper perpendicular distance calculation
- Map parsing: Handle all edge cases and spaces correctly

Remember: Focus on creating a stable 3D visualization with clean, norm-compliant code! 🎮✨