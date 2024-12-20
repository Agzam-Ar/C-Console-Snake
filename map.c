#include <stdlib.h>
#include "map.h"
#include "canvas.h"

Colors Background;

MapPreset mapCorridor = { 0 }, mapBox = { 0 }, mapWindserf = { 0 }, mapRooms = { 0 }, mapCorridor2 = {0};

// https://www.youtube.com/watch?v=VT0L9ouW2Es

void loadMaps() {
    mapCorridor.name = "Corridor";
    mapCorridor.walls =
        "RWR----------WRW"
        "W--------------R"
        "R--------------W"
        "----------------"
        "----RWRWRWRW----"
        "----------------"
        "----------------"
        "----RWRWRWRW----"
        "----------------"
        "----------------"
        "R--------------W"
        "W--------------R"
        "RWR----------WRW";
    mapCorridor.background = Background.black;


    mapCorridor2.name = "Corridor 2";
    mapCorridor2.walls =
        "RWRWRWRWRWRWRWRW"
        "W--------------R"
        "R--------------W"
        "W----RWRWRW----R"
        "R--------------W"
        "----------------"
        "----------------"
        "----------------"
        "R--------------W"
        "W----RWRWRW----R"
        "R--------------W"
        "W--------------R"
        "RWRWRWRWRWRWRWRW";
    mapCorridor2.background = Background.black;


    mapBox.name = "Box",
        mapBox.walls =
        "BBBBBBBBBBBBBBBB"
        "B--------------B"
        "B--------------B"
        "B--------------B"
        "B--------------B"
        "B--------------B"
        "B--------------B"
        "B--------------B"
        "B--------------B"
        "B--------------B"
        "B--------------B"
        "B--------------B"
        "BBBBBBBBBBBBBBBB";
        mapBox.background = Background.yellow;


        mapWindserf.name = "Windserf",
            mapWindserf.walls =
            "----W-----------"
            "----W-----------"
            "----W----WWWWWWW"
            "----W-----------"
            "----W-----------"
            "----W----W------"
            "----W----W------"
            "----W----W------"
            "---------W------"
            "---------W------"
            "WWWWW----W------"
            "---------W------"
            "---------W------";
        mapWindserf.background = Background.green;


        mapRooms.name = "Rooms",
            mapRooms.walls =
            "WW--WWWWWWWWW---"
            "W-----W---------"
            "W-----W---------"
            "------W---------"
            "WWWWWWW--WWWWWWW"
            "----------------"
            "----------------"
            "WWWWWWWWWWWWWWWW"
            "---------W------"
            "---------W------"
            "---------W------"
            "---------W------"
            "---------W------";
        mapRooms.background = Background.green;

}

Tile* getTile(Map* map, int x, int y) {
    return &((map->tiles)[(x%map->w) + map->w * (y%map->h)]);
}

Map createMap(int w, int h) {
    Map map = { 0 };
    Tile* ts = malloc((w * h) * sizeof(Tile));
    if (!ts) return map;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Tile t = { 
                .type = x % 2 + y % 2,
                .food = 0,
            };
            ts[(x + y * w)] = t;
        }
    }
    map.w = w;
    map.h = h;
    map.tiles = ts;
    return map;
}
