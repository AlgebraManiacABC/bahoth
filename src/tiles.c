#include "tiles.h"

//	Door bits
//	If set in `doors` bitfield,
//	Then that direction has a door
#define DOOR_NORTH (0b1 << 3)
#define DOOR_SOUTH (0b1 << 2)
#define DOOR_EAST  (0b1 << 1)
#define DOOR_WEST  (0b1)

//	Tile rotation directions
//	Each tile has a default "Up," which I'm declaring "North."
//	When rotated, this "up" faces a new direction, given by these IDs.
#define TILE_NORTH (0)
#define TILE_SOUTH (1)
#define TILE_EAST  (2)
#define TILE_WEST  (3)

struct tile
{
	//	Tile's X position in the world
	int x;
	//	Tile's Z position in the world
	int z;
	//	Tile's rotation
	Uint8 r;
	//	The ID of the tile (associated with name, texture, etc)
	Uint8 which;
	//	Bitfield showing who visited this tile (only used for trait tiles from WW)
	Uint8 visited;
	//	Doors bitfield: `0000NSEW`
	//	Must be updated if rotated
	Uint8 doors;
	//	Links: `NSEW`
	//	Must be updated if new tile attached or removed or if rotated
	tile * links[4];
};

char * tileNames[] =
{
	"Abandoned Room",
	"Attic",
	"Balcony",
	"Ballroom",
	"Basement Landing",
	"Bedroom",
	"Bloody Room",
	"Catacombs",
	"Chapel",
	"Charred Room",
	"Chasm",
	"Coal Chute",
	"Collapsed Room",
	"Conservatory",
	"Creaky Hallway",
	"Crypt",
	"Dining Room",
	"Dusty Hallway",
	"Entrance Hall",
	"Foyer",
	"Furnace Room",
	"Gallery",
	"Game Room",
	"Gardens",
	"Grand Staircase",
	"Graveyard",
	"Gymnasium",
	"Junk Room",
	"Kitchen",
	"Larder",
	"Library",
	"Master Bedroom",
	"Mystic Elevator",
	"Operating Laboratory",
	"Organ Room",
	"Patio",
	"Pentagram Chamber",
	"Research Laboratory",
	"Servants Quarters",
	"Stairs From Basement",
	"Statuary Corridor",
	"Storeroom",
	"Tower",
	"Underground Lake",
	"Upper Landing",
	"Vault",
	"Wine Cellar",
	"Arsenal",
	"Bathroom",
	"Cave",
	"Drawing Room",
	"Dungeon",
	"Laundry",
	"Locked Room",
	"Menagerie",
	"Nursery",
	"Panic Room",
	"Roof Landing",
	"Rookery",
	"Sewing Room",
	"Solarium",
	"Spiral Staircase",
	"Storm Cellar",
	"Study",
	"Theater",
	"Tree House",
	"Widow's Walk"
};