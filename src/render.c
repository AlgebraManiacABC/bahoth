#include "render.h"
#include "game.h"

void renderAll()
{
	renderTable();
	renderUI();
}

void renderTable()
{
	renderTiles();
	renderPlayerInventories();
	renderTableExtras();
}
//============================//
void renderTiles()
{
	//	Experimental state of this function!
	//	Expect most or all of this to be replaced.
	renderTile();
}

void renderTile()
{
	//	Experimental state of this function!
	//	Expect most or all of this to be replaced.

	//	Let's say we want to render the foyer, ignoring the texture and other connected tiles.
	//	I'm going to get a camera set up first.
	//	We take the tile position, and add or subtract tileWidth/2 to x or z to get the borders of the tile.
	//	We can simply create two triangles with these newfound vertices and use them to render.
	//	Here's the most basic example:
	tile t;
	t.x = 0;
	t.z = 0;
	float tileVertices[] =	//	xyz of each vertex
	{
		t.x + (tileWidth/2.0), 0.0f, t.z + (tileWidth/2.0),
		t.x + (tileWidth/2.0), 0.0f, t.z - (tileWidth/2.0),
		t.x - (tileWidth/2.0), 0.0f, t.z + (tileWidth/2.0),
		t.x - (tileWidth/2.0), 0.0f, t.z - (tileWidth/2.0)
	};
	(void)tileVertices;
}

void renderPlayerInventories()
{
	return;
}

void renderTableExtras()
{
	return;
}
//============================//

void renderUI()
{
	return;
}