#pragma once
#include "BaseTour.h"

class BeachTour : public BaseTour { 
public:
	BeachTour() = default;
	~BeachTour() override = default;

	// Геттеры для полей класса
	std::string getHotelName() { return hotelName_; }
	bool isAllInclusive() { return allInclusive_; }
	int getStars() { return stars_; } 

	// Сеттеры
	void setHotelName(std::string hotelName) {
		if (hotelName.empty()) throw std::invalid_argument("Hotel name mustn't be empty\n");
		hotelName_ = hotelName;
	}

	void setAllInclusive(bool allInclusive) {
		allInclusive_ = allInclusive;
	}

	void setStars(int stars) {
		if (stars < 1 || stars > 5) {
            // учитываем, что количество звёзд варьируется от 1 до 5
			throw std::invalid_argument("Stars must be between 1 and 5\n");
		}
		stars_ = stars;
	}
    // Функция read()
	void read(std::istream& input) override {
		BaseTour::read(input);

		std::string hotel;
		int ai; // a - All, i - Inclusive
		int st; 
		if (!(input >> hotel >> ai >> st)) {
			input.clear(std::ios::failbit);
			throw std::runtime_error("Wrong order of reading BeachTour\n");
		}
		this->setHotelName(hotel);
		this->setAllInclusive(ai != 0);
		this->setStars(st);
	}

	// Функция print()
	void print(std::ostream& output) override {
		BaseTour::print(output);
		output << " | hotel " << std::setw(12) << hotelName_
			   << " | stars " << std::setw(2) << stars_
			   << " | all-inclusive " << (allInclusive_ ? "yes" : "no");
	}

	TourType getType() override { return TourType::Beach; }
	std::string toString() override { return "BeachTour"; }

private:
	std::string hotelName_;
	bool allInclusive_;
	int stars_; 
};