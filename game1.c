#include <stdio.h>
#include <uchar.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <process.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP_FUNC(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_FUNC(ms) usleep(ms * 1000)
#endif
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include "map.h"
#include "canvas.h"
#include "canvas.c" // Why?
#include "input.h"
#include "player.h"

Colors Foreground, Background;
void moveCursor(int x, int y);
void setChar(Canvas* canvas, char16_t c, int x, int y);
void setBackground(Canvas* canvas, int color, int x, int y);
void setForeground(Canvas* canvas, int color, int x, int y);
Canvas createCanvas(int w, int h);
void flushCanvas(Canvas* canvas);

//Colors Background;
Map createMap(int w, int h);
Tile* getTile(Map* map, int x, int y);
//void moveCursor(int x, int y);
//void setChar(Canvas* canvas, char16_t c, int x, int y);
//void setBackground(Canvas* canvas, int color, int x, int y);

//Canvas createCanvas(int w, int h);
//void flushCanvas(Canvas* canvas);
void loadMaps();

void updatePlayer(Player* player, Map* map, Canvas* canvas);

MapPreset mapCorridor, mapBox, mapWindserf, mapCorridor2, mapRooms;

void draw(Map* map) {
    for (int y = 0; y < map->h; y++) {
        for (int x = 0; x < map->w; x++) {
            Tile* t = getTile(map, x, y);
            printf("%d", t->type);
        }
        printf("\n");
    }
}

Player player = { 0 };

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));
    loadMaps();
    int w = 16;// 56;
    int h = 13;// 27;
    Map map = createMap(w, h);
    map.food = 0;
    Canvas canvas = createCanvas(w, h);
    int x = 0, y = 0;
    setupKeyboard();
    player.x = map.w / 2;
    player.y = map.h / 2;
    player.maxSize = map.w * map.h;
    player.head = 0;
    player.size = 1;
    player.xs = calloc(map.w * map.h, sizeof(short));
    player.ys = calloc(map.w * map.h, sizeof(short));
    player.xs[0] = player.x;
    player.ys[0] = player.y;

    MapPreset preset = mapCorridor;
    for (int y = 0; y < map.h; y++) {
        for (int x = 0; x < map.w; x++) {
            char type = preset.walls[x + y * map.w];
            setForeground(&canvas, Foreground.white, x, y);
            if (type == '-') {
                setBackground(&canvas, preset.background, x, y);
                //getTile(&map, x, y)->food = 1;
                //map.food++;
                continue;
            }

            if (type == 'W') setBackground(&canvas, Background.bwhite, x, y);
            if (type == 'R') setBackground(&canvas, Background.bred, x, y);
            if (type == 'B') setBackground(&canvas, Background.black, x, y);
            getTile(&map, x, y)->solid = 1;
        }
    }
    map.background = preset.background;

    int ticks = 0;
    int tps = 5;
    while (1) {
        flushCanvas(&canvas);
        SLEEP_FUNC(1000 / tps);
        updatePlayer(&player, &map, &canvas);
        if (map.food == 0) {
            int freeTiles = player.maxSize - player.size;
            int rtile = rand() % (freeTiles);
            int index = 0;
            for (int y = 0; y < map.h; y++) {
                for (int x = 0; x < map.w; x++) {
                    Tile* t = getTile(&map, x, y);
                    if (t -> solid) continue;
                    index++;
                    if (index == rtile) {
                        t->food = 1;
                        map.food++;
                        setBackground(&canvas, Background.bblue, x, y);
                    }
                }
            }
        }
        moveCursor(0, map.h+1);
        printf("\x1b[0m\033[4;30m\033[1;37mSCORE\x1b[0m: %d", (player.size-1)*tps);
        ticks++;
    }
    return 0;
}