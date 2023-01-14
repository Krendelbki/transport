#include "TransportManager.h"

#include <string>
#include <array>

std::string generateRandomCarNumber() {
	std::string number;

	number += char(rand() % 90 - 65) + char(rand() % 90 - 65);
	number += std::to_string(rand() % 10000);
	number += char(rand() % 90 - 65) + char(rand() % 90 - 65);

	return number;
}

std::string generateRandomBicycleNumber() {
	std::string number;

	number += char(rand() % 90 - 65);
	number += char(rand() % 90 - 65);
	number += char(rand() % 90 - 65);
	number += std::to_string(rand() % 100);
	
	return number;
}

void TransportManager::setUpRandomVehicleStats() {
	const unsigned int numTrucks = (int)(numberOfVehicles * 0.1);
	const unsigned int numBusses = (int)(numberOfVehicles * 0.2);
	const unsigned int numBicycles = (int)(numberOfVehicles * 0.1);

	const unsigned int numVehicles = numberOfVehicles - (numTrucks + numBusses + numBicycles);

	allVehicles.vehicles.resize(numVehicles);
	allVehicles.trucks.resize(numTrucks);
	allVehicles.busses.resize(numBusses);
	allVehicles.bicycles.resize(numBicycles);

	std::vector<unsigned int> randomIndexVehicles((int)(numVehicles * 0.7), rand() % numVehicles);
	std::vector<unsigned int> randomIndexTrucks((int)(numTrucks * 0.7), rand() % numTrucks);
	std::vector<unsigned int> randomIndexBusses((int)(numTrucks * 0.7), rand() % numBusses);
	std::vector<unsigned int> randomIndexBicycles((int)(numTrucks * 0.7), rand() % numBicycles);

	unsigned int index = 0;
	for (auto& vehicle : allVehicles.vehicles) {
		vehicle->setNumber(generateRandomCarNumber());

		for (const auto& randomVehicle : randomIndexVehicles) {
			if (index == randomVehicle) {
				vehicle->setSpeed(rand() % 31 + 50);
				vehicle->setGasLevel((float)(rand() % 81 + 20) / 100);
				vehicle->setGasCapacity(rand() % 11 + 10);
			}
		}
		index++;
	}

	index = 0;
	for (auto& truck : allVehicles.trucks) {
		truck->setNumber(generateRandomCarNumber());

		for (const auto& randomTruck : randomIndexTrucks) {
			if (index == randomTruck) {
				truck->setSpeed(rand() % 31 + 30);
				truck->setGasLevel((float)(rand() % 81 + 20) / 100);
				truck->setGasCapacity(rand() % 11 + 10);

				truck->setMaxMassOfCargo((float)(rand() % 16 + 5));
				float currMassCoef = (rand() % 101) / 100;
				truck->setCurrMassOfCargo(truck->getMaxMassOfCargo() * currMassCoef);
			}
		}
		index++;
	}

	index = 0;
	for (auto& bus : allVehicles.busses) {
		bus->setNumber(generateRandomCarNumber());

		for (const auto& randomBus : randomIndexBusses) {
			if (index == randomBus) {
				bus->setSpeed(rand() % 31 + 30);
				bus->setGasLevel((float)(rand() % 81 + 20) / 100);
				bus->setGasCapacity(rand() % 11 + 10);

				bus->setMaxNumberOfPassengers(rand() % 20 + 20);
				float currPassNumberCoef = (rand() % 101) / 100;
				bus->setCurrNumberOfPassengers(bus->getMaxNumberOfPassengers() * currPassNumberCoef);
			}
		}
		index++;
	}

	index = 0;
	for (auto& bicycle : allVehicles.bicycles) {
		bicycle->setNumber(generateRandomBicycleNumber());

		for (const auto& randomBicycle : randomIndexBicycles) {
			if (index == randomBicycle) {
				bicycle->setSpeed(rand() % 11 + 10);

				bicycle->setChanceOfGoingOffRoad((float)((rand() % 81) / 100));
			}
		}
		index++;
	}
}

void TransportManager::setUpPoints() {

	for (const auto& row : map.getMap()) {
		for (const auto& element : row) {
			std::vector<Road> connectedRoads(0);
			Point* point = new Point(NoType, element.getPointId(), rand() % 11, connectedRoads);

			EntertainmentPoint entertainment = EntertainmentPoint(*point);
			GasStationPoint gasStation		 = GasStationPoint(*point);
			BusStopPoint busStop			 = BusStopPoint(*point);
			ParkingPoint parking			 = ParkingPoint(*point);
			WarehousePoint warehouse		 = WarehousePoint(*point);

			switch (element.getPoint()) {
				case NoType:
					break;
				case Entertainment:
					entertainment.setType(Entertainment);

					allPoints.entertainments.push_back(&entertainment);
					break;
				case GasStation:
					gasStation.setType(GasStation);

					allPoints.gasStations.push_back(&gasStation);
					break;
				case BusStop:
					busStop.setType(BusStop);

					allPoints.busStops.push_back(&busStop);
					break;
				case Parking:
					parking.setType(Parking);

					allPoints.parkings.push_back(&parking);
					break;
				case Warehouse:
					warehouse.setType(Warehouse);

					allPoints.warehouses.push_back(&warehouse);
					break;
			}
		}
	}
}

void TransportManager::setUpRoads() {

	/*for (const auto& row : map.getMap()) {
		for (const auto& element : row) {
			unsigned int index = 0;
			if (element.getPoint() != NoType) {
				Road* road = &Road(rand() % 401 + 100, rand() % 51 + 50, rand() % 25);
				roads.push_back(road);

				roadStartEndPoints.insert(road, std::make_pair<element.getPointId(), element.getConnectedPointIds().at(index)>);
			}
		}
	}*/

}

void TransportManager::setUpSimulation() {
	setUpRandomVehicleStats();
	setUpPoints();
	setUpRoads();
};

void TransportManager::inputData() {
	std::cout << "Number of vehicles > ";
	std::cin >> numberOfVehicles;

	char ans;
	std::cout << "Enter the map? (Y/n) > ";
	std::cin >> ans;

	if (ans == 'Y') {
		unsigned int size;
		std::cout << "Size of your map (matrix) > ";
		std::cin >> size;

		Cell temp;
		std::vector<std::vector<Cell>> temp_map(size, std::vector<Cell>(size, Cell()));
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				std::cout << "[" << i << "][" << j << "]\n";
				std::cin >> temp;
				temp_map[i][j] = temp;
			}
		}

		map.setMap(temp_map);
	}
	else if (ans == 'n') {
		return;
	}
	else {
		std::cout << "The entered symbols was not 'Y' or 'n'! Try again!" << std::endl;
		inputData();
	}
}	

void TransportManager::printStats() const {
	for (const auto& vehicle : allVehicles.vehicles) {
		//std::cout << "********************************" << std::endl;
		std::cout << "Vehicle:    " << vehicle->getNumber() << std::endl;
		//std::cout << "Next point: " << vehicle->getAppointment() << std::endl;
		std::cout << "Gas level:  " << vehicle->getGasLevel() << std::endl;
	}
};


// Getters
unsigned int TransportManager::getNumberOfVehicles() const {
	return numberOfVehicles;
};

std::vector<std::vector<Cell>> TransportManager::getMap() const {
	return map.getMap();
};

Vehicles TransportManager::getVehicles() const {
	return allVehicles;
};

std::vector<Road*> TransportManager::getRoads() const {
	return roads;
}

Points TransportManager::getPoints() const {
	return allPoints;
}


// Setters
void TransportManager::setNumberOfVehicles(unsigned int _numberOfVehicles) {
	numberOfVehicles = _numberOfVehicles;
};

void TransportManager::setMap(const Map& _map) {
	map = _map;
}

void TransportManager::addVehicle(Vehicle* _vehicle) {
	allVehicles.vehicles.push_back(_vehicle);
	numberOfVehicles++;
};

void TransportManager::addBus(Bus* _bus) {
	allVehicles.busses.push_back(_bus);
	numberOfVehicles++;
}

void TransportManager::addTruck(Truck* _truck) {
	allVehicles.trucks.push_back(_truck);
	numberOfVehicles++;
}

void TransportManager::addBicycle(Bicycle* _bicycle) {
	allVehicles.bicycles.push_back(_bicycle);
	numberOfVehicles++;
}

void TransportManager::addRoad(Road* _road) {
	roads.push_back(_road);
}

void TransportManager::addEntertainment(EntertainmentPoint* _point) {
	allPoints.entertainments.push_back(_point);
}

void TransportManager::addGasStation(GasStationPoint* _point) {
	allPoints.gasStations.push_back(_point);
}

void TransportManager::addBusStop(BusStopPoint* _point) {
	allPoints.busStops.push_back(_point);
}

void TransportManager::addParking(ParkingPoint* _point) {
	allPoints.parkings.push_back(_point);
}

void TransportManager::addWarehouse(WarehousePoint* _point) {
	allPoints.warehouses.push_back(_point);
}