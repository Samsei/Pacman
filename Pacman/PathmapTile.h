#ifndef PATHMAPTILE_H
#define PATHMAPTILE_H

class PathmapTile
{
public:
	PathmapTile(int, int, bool);
	~PathmapTile(void);

	int x = 0;
	int y = 0;

	bool is_blocking = false;
	bool is_visited = false;
};

#endif // PATHMAPTILE_H