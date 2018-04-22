#include "Passenger.h"

std::istream  &operator>> (std::istream &is, Passenger &pass)
{
	is >> pass.requestTime >> pass.initialFloor >> pass.destination;
	if (!is) {
		pass = Passenger();
	}
	return is;
}