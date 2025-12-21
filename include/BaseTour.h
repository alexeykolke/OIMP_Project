#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept> 

enum class TourType {
	Beach,
	Excursion,
	Ski,
	Undefined
};

class BaseTour {
public:
	BaseTour() = default;
	virtual ~BaseTour() = default;

	// Геттеры
	std::string getName() { return name_; }
	std::string getCountry() { return country_; }
	double getPrice() { return price_; }
	int getDuration() { return duration_; }

	// Сеттеры с проверкой
	void setName(std::string name) {
		if (name.empty()) throw std::invalid_argument("Error! Name mustn't be empty\n");
		name_ = name;
	}

	void setCountry(std::string country) {
		if (country.empty()) throw std::invalid_argument("Error! Country mustn't be empty!\n");
		country_ = country;
	}

	void setPrice(double price) {
		if (price <= 0) throw std::invalid_argument("Error! Price can't be negative or zero!\n");
		price_ = price;
	}

	void setDuration(int duration) {
		if (duration <= 0) throw std::invalid_argument("Error! Duration must be positive!\n");
		duration_ = duration;
	}

    // Функция read()
    virtual void read(std::istream& input) {
        std::string name, country;
        double price;
        int duration;

        if (!(input >> name >> country >> price >> duration)) {
            input.clear(std::ios::failbit);
            throw std::runtime_error("Wrong order of reading tour\n");
        }
        this->setName(name);
        this->setCountry(country);
        this->setPrice(price);
        this->setDuration(duration);
    }

    // Функция print()
    virtual void print(std::ostream& output) {
        output << std::left
            << "name " << std::setw(14) << name_
            << "| country " << std::setw(12) << country_
            << "| price " << std::setw(10) << price_
            << "| days " << std::setw(8) << duration_;
    }

    virtual TourType getType() = 0;
    virtual std::string toString() = 0;
    
private:
	std::string name_;
	std::string country_;
	double price_;
	int duration_;
};

// Перегрузка операторов ввода/вывода
inline std::istream& operator>>(std::istream& input, BaseTour* tour) {
	tour->read(input);
	return input;
}

inline std::ostream& operator<<(std::ostream& output, BaseTour* tour) {
	tour->print(output);
	return output;
}