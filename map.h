#pragma once

typedef struct Tile {

    int type;
    char food;
    char solid;
    char snake;

} Tile;


typedef struct Map {

    int w, h;
    Tile* tiles;

    Tile(*getTile) (int, int);

    char food;
    int background;

} Map;

typedef struct MapPreset {

    char* name;
    char* walls;
    int background;

} MapPreset;