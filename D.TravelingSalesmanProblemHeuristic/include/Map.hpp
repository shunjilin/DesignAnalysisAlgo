#ifndef MAP_HPP
#define MAP_HPP


#include <vector>
#include <math.h>
#include <algorithm>


namespace map {
    struct Coordinate {
	double x;
	double y;
	Coordinate(double x, double y) : x(x), y(y) {}
    };


    double euclideanDistanceSquared(Coordinate a, Coordinate b) {
	return pow((a.x - b.x),2) + pow(a.y - b.y,2);
    }
    
    

    class Map {
	std::vector<Coordinate> coordinates;
    public:
	Map(const std::vector<Coordinate>  coordinates) : coordinates(coordinates) {}

	double distanceSquared(int u, int v) const {
	    return euclideanDistanceSquared(coordinates[u], coordinates[v]);
	}

	std::size_t size() const {
	    return coordinates.size();
	}
        


    };
}


#endif
