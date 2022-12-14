#include "Point.h"

EntertainmentPoint::EntertainmentPoint() 
	: Point(),
	  durationOfStop(0)
{}

EntertainmentPoint::EntertainmentPoint
(unsigned int _durationOfStop, Type _type, unsigned int _id, unsigned int _numberOfSlots, const std::vector<Road>& _connectedRoads)
	: Point(_type, _id, _numberOfSlots, _connectedRoads),
	  durationOfStop(_durationOfStop)
{}

EntertainmentPoint::EntertainmentPoint(const EntertainmentPoint& _point) 
	: Point(_point),
	  durationOfStop(_point.durationOfStop)
{}

unsigned int EntertainmentPoint::getDurationOfStop() const {
	return durationOfStop;
}

EntertainmentPoint& EntertainmentPoint::setDurationOfStop(unsigned int _durationOfStop) {
	durationOfStop = _durationOfStop;
	return *this;
}