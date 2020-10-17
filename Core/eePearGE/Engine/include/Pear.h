#ifndef _PEAR_H_
#define _PEAR_H_

#include <utility>
namespace eePearGE
{
	class Pear
	{
		typedef short int Coord;
		typedef std::pair<Coord, Coord> Position;
	public:
		//Basic Interface Me...
		virtual void Update() = 0;
		Position& GetPosition() { return position; }
		void SetXPosition(Coord x) { position.first = x; }
		void SetYPosition(Coord y) { position.second = y; }

	private:
		std::pair<Coord, Coord> position;
	};
}

#endif