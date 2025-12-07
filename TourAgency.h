#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <string>

enum class TourTypes {
	BeachTour,
	ExcursionTour, 
	SkiTour,
	Undefined
};

class BaseTour {
private:
	std::string tourName_;
	std::string tourPlace_;
	std::string tourStartTime_;
	double tourPrice_;
	double tourTime_;
public:
	BaseTour() = default;
	virtual ~BaseTour() = default;

	// Геттеры
	std::string getName() const noexcept { return tourName_; }
	std::string getPlace() const noexcept { return tourPlace_; }
	std::string getStartTime() const noexcept { return tourStartTime_; }
	double getPrice() const noexcept { return tourPrice_; }
	double getTime() const noexcept { return tourTime_; }

	// Сеттеры
	void setName(std::string tourName) { this->tourName_ = tourName; }
	void setPlace(std::string tourPlace) { this->tourPlace_ = tourPlace; }
	void setStartTime(std::string tourStartTime) { this->tourStartTime_ = tourStartTime; }
	void setPrice(double tourPrice) { this->tourPrice_ = tourPrice; }
	void setTime(double tourTime) { this->tourTime_ = tourTime; }

	virtual void read(std::istream& input);
	virtual void print(std::ostream& output) const noexcept;
};

inline std::istream& operator>>(std::istream& input, BaseTour* tour);
inline std::ostream& operator<<(std::ostream& output, const BaseTour* tour);