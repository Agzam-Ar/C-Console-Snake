#include <uchar.h>
#include "player.h"
#include "input.h"
#include "map.h"
#include "canvas.h"

static x, y;

Tile* getTile(Map* map, int x, int y);
void setChar(Canvas* canvas, char16_t c, int x, int y);
void setChars(Canvas* canvas, char16_t c1, char16_t c2, int x, int y);
void setBackground(Canvas* canvas, int color, int x, int y);
void setForeground(Canvas* canvas, int color, int x, int y);
Colors Background;
Colors Foreground;

// from to
const char16_t* snakeParts = {
	u"───╮───╯"
	u"╰─││─╯││"
	u"──╭───╰─"
	u"╭─││─╮││"
	u"─▷╲╱◁─╱╲"
	u"──╭╮──╰╯"
};

int abs(int i) {
	return i > 0 ? i : -1;
}

int calcAngle(int dx, int dy) {
	if (dx == 1) return 0;
	if (dy == 1) return 1;
	if (dx == -1) return 2;
	return 3;
}

void updatePlayer(Player* player, Map* map, Canvas* canvas) {
	int colors[] = { Background.red, Background.red, Background.bred, Background.white, Background.bred };
	int fcolors[] = { Foreground.red, Foreground.red, Foreground.bred, Foreground.white, Foreground.bred };
	int colorsCount = 5;
	


	x = player->x;
	y = player->y;

	x += Input.x;
	y += Input.y;

	x = ((x % map->w) + map->w) % map->w;
	y = ((y % map->h) + map->h) % map->h;

	Tile* t = getTile(map, x, y);

	if (t->solid) {
		return;
	}
	player->head++;

	t->solid = 1;
	t->snake = 1;
	if (t->food == 1) {
		t->food = 0;
		player->size++;
		map->food--;
		//setChar(&canvas, u'C', x, y);
	} else {
		int tailIndex = (player->head - player->size);
		int tx = player->xs[tailIndex];
		int ty = player->ys[tailIndex];
		setBackground(canvas, map->background, tx, ty);
		setChar(canvas, u' ', tx, ty);
		Tile* t = getTile(map, tx, ty);
		t->solid = 0;
		t->snake = 0;
	}


	player->xs[player->head] = x;
	player->ys[player->head] = y;
	//setBackground(canvas, (x+y) % 2 ? Background.bred : Background.white, x, y);

	char color = 0;// player->size% colorsCount;
	int tailIndex = player->head - player->size + 1;
	int headIndex = player->head;
	for (int i = tailIndex; i <= headIndex; i++) {
		int cx = player->xs[i];
		int cy = player->ys[i];
		int px = i == tailIndex ? cx : player->xs[i - 1];
		int py = i == tailIndex ? cy : player->ys[i - 1];
		int nx = i == headIndex ? cx : player->xs[i + 1];
		int ny = i == headIndex ? cy : player->ys[i + 1];


		int fa = calcAngle(cx - px, cy - py);
		int ta = calcAngle(nx - cx, ny - cy);

		if (cx == 0 && cx+1 < nx) ta = 2;
		if (cx == map->w-1 && cx-1 > nx) ta = 0;

		if (cx == 0 && cx + 1 < px) fa = 2;
		if (cx == map->w - 1 && cx - 1 > px) fa = 0;

		/*if (nx - cx > 1) {
			ta = (ta + 1) % 4;
		}*/

		if (i == headIndex) {
			ta = fa;
			fa = 4;
			if (cx == 0 && cx + 1 < px) ta = 0;
			if (cx == map->w - 1 && cx - 1 > px) ta = 2;
		} else if (i == tailIndex) {
			fa = 5;
		}

		//setBackground(canvas, colors[color], cx,cy);
		setForeground(canvas, fcolors[color], cx, cy);
		setBackground(canvas, map->background, cx, cy);
		int partIndex = (ta + fa * 4)*2;
		setChars(canvas, snakeParts[partIndex], snakeParts[partIndex+1], cx, cy);
		//setChar(canvas, u'C', player->xs[i], player->ys[i]);
		color = (color+1)% colorsCount;
	}
	//setBackground(canvas, (x + y) % 2 ? Background.bred : Background.white, x, y);

	player->x=x;
	player->y=y;

}