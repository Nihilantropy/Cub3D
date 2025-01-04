#ifndef ERROR_H
# define ERROR_H

/* checks err msg */
# define ERR_ARG "Error\nInvalid argument\n"
# define P_USAGE "[Usage]\n./cub3D map/map*.cub\n"
# define ERR_EMPY_FILE "Error\nMap file is empty\n"
# define ERR_WRONG_CHAR "Error\nWrong CHAR in map matrix\n"
# define ERR_WRONG_INFO_CHAR "Error\nWrong CHAR in map infos\n"
# define ERR_WRONG_INFO_NBR "Error\nWrong number of infos in map file\n"
# define ERR_TEXTURE_LOAD "Error\nTexture loading failed\n"
# define ERR_LOAD_FLOOR_RGB "Error\nCould not load floor rgb texture\n"
# define ERR_LOAD_CEILING_RGB "Error\nCould not load ceiling rgb texture\n"
# define ERR_MAP_ORDER "Error\nMap should start with the infos\n"
# define ERR_NO_MAP "Error\nNo Map matrix found in map file\n"
# define ERR_INV_MAP "Error\nMap provided is not valid\n"
# define ERR_NO_INFOS "Error\nMap infos are incomplete\n"
# define ERR_MATRIX_LEN "Error\nMap matrix length is too small\n"
# define ERR_MAP_MATRIX "Error\nMap matrix format is incorrect\n"
# define ERR_MAP_ISLAND "Error\nMap matrix contain an island\n"
# define ERR_MAP_BORDERS "Error\nMap matrix borders are open or there's a hole in the map\n"
# define ERR_NBR_PLAYER "Error\nWrong number of player\n"

/* generic err msg*/
# define ERR_DISPLAY_OPEN "Error\nCould not open display. Exiting...\n"

/* allocation err msg */
# define ERR_ALLOC_MATRIX "Error\nMatrix alloc failed\n"
# define ERR_ALLOC_MATRIX_DUP "Error\nMatrix duplicate alloc failed\n"
# define ERR_ALLOC_INFO "Error\nInfo list alloc failed\n"
# define ERR_ALLOC_NEW_MATRIX_ROW "Error\nNew matrix row alloc failed\n"
# define ERR_ALLOC_NEW_MATRIX_COL "Error\nNew matrix column alloc failed\n"
# define ERR_ALLOC_BOOL_MATRIX "Error\nBool matrix column alloc failed\n"
# define ERR_ALLOC_RENDER_STATE "Error\nRender state alloc failed\n"

/* raycast error msg */
# define ERR_INVALID_RAY_CAST_ACCESS "Error\nInvalid acces on raycast\nClosing game...\n"

/* player out of bound error msg */
# define ERR_OUT_OF_BOUND "Error\nYou exceeded map limts. No wall collision implemented\n"

#endif