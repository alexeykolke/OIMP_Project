#include "Headers.h"

void BaseTour::setName(std::string tourName) {
	if (tourName.empty()) {
		throw std::invalid_argument("Name mustn't be empty!\n");
	}
	tourName_ = tourName;
}

void BaseTour::setPlace(std::string tourPlace) {
	if (tourPlace.empty()) {
		throw std::invalid_argument("Place mustn't be empty!\n");
	}
	tourPlace_ = tourPlace;
}

void BaseTour::setStartTime(std::string tourStartTime) {
	if (tourStartTime.empty()) {
		throw std::invalid_argument("Start time mustn't be empty!\n");
	}
	tourStartTime_ = tourStartTime;
}
void BaseTour::setPrice(double tourPrice) {
	if (tourPrice < 0) {
		throw std::invalid_argument("Price musnt't be negative!\n");
	}
	tourPrice_ = tourPrice;
}

void BaseTour::setTime(double tourTime) {
	if (tourTime < 0) {
		throw std::invalid_argument("Time mustn't be negative!\n");
	}
}