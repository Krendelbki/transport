#include "Point.h"

ParkingPoint::ParkingPoint() 
	: Point(),
	  chanceOfStaying(0.0f)
{}

ParkingPoint::ParkingPoint
(float _chanceOfStaying, Type _type, unsigned int _id, unsigned int _numberOfSlots, const std::vector<Road>& _connectedRoads)
	: Point(_type, _id, _numberOfSlots, _connectedRoads),
	  chanceOfStaying(_chanceOfStaying)
{}

ParkingPoint::ParkingPoint(const ParkingPoint& _point) 
	: Point(_point),
	  chanceOfStaying(_point.chanceOfStaying)
{}

float ParkingPoint::getChanceOfStaying() const {
	return chanceOfStaying;
}

ParkingPoint& ParkingPoint::setChanceOfStaying(float _chanceOfStaying) {
	chanceOfStaying = _chanceOfStaying;
	return *this;
}