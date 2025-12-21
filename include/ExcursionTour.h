#pragma once
#include "BaseTour.h"

class ExcursionTour : public BaseTour {
public:
	ExcursionTour() = default;
	~ExcursionTour() override = default;

	// Геттеры
	int getSitesCount() { return sitesCount_; }
	std::string getTransport() { return transport_; }

	// Сеттеры 
	void setSitesCount(int sitesCount) {
		if (sitesCount < 1) {
			throw std::invalid_argument("Excursion must include at least 1 site\n");
		}
		sitesCount_ = sitesCount;
	}

	void setTransport(std::string transport) {
		if (transport.empty()) {
			throw std::invalid_argument("Transport type mustn't be empty\n");
		}
		transport_ = transport;
	}

	// Функция read()
	void read(std::istream& input) override {
		BaseTour::read(input);
		
		int sites;
		std::string trans;
		if (!(input >> sites >> trans)) {
			input.clear(std::ios::failbit);
			throw std::runtime_error("Wrong order of reading ExcursionTour\n");
		}
		this->setSitesCount(sites);
		this->setTransport(trans);
	}

	// Функция print()
	void print(std::ostream& output) override {
		BaseTour::print(output);
		output << " | sites " << std::setw(5) << sitesCount_
			   << " | transport " << std::setw(10) << transport_;
	}

	// Реализация виртуальных функций
	TourType getType() override { return TourType::Excursion; }
	std::string toString() override { return "ExcursionTour"; }

private:
	int sitesCount_;       // количество достопримечательностей
	std::string transport_; // автобус, поезд, самолет и т.д.
};