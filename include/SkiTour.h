#pragma once
#include "BaseTour.h"

class SkiTour : public BaseTour {
public:
	SkiTour() = default;
	~SkiTour() override = default;

	// Геттеры
	std::string getDifficulty() { return difficulty_; }
	bool hasEquipmentRental() { return equipmentRental_; }

	// Сеттеры
	void setDifficulty(std::string difficulty) {
		if (difficulty.empty()) {
			throw std::invalid_argument("Difficulty level mustn't be empty\n");
		}
		difficulty_ = difficulty;
	}

	void setEquipmentRental(bool hasRental) {
		equipmentRental_ = hasRental;
	}

	// Функция read()
	void read(std::istream& input) override {
		BaseTour::read(input);
		
		std::string diff;
		int rental; // для удобства чтения потока
		if (!(input >> diff >> rental)) {
			input.clear(std::ios::failbit);
			throw std::runtime_error("Wrong order of reading SkiTour\n");
		}
		this->setDifficulty(diff);
		this->setEquipmentRental(rental != 0);
	}

	// Функция print()
	void print(std::ostream& output) override {
		BaseTour::print(output);
		output << " | difficulty " << std::setw(10) << difficulty_
			   << " | rental " << (equipmentRental_ ? "available" : "none");
	}

	// Реализация виртуальных функций
	TourType getType() override { return TourType::Ski; }
	std::string toString() override { return "SkiTour"; }

private:
	std::string difficulty_; // сложность участка
	bool equipmentRental_;   // можно ли взять экипировку в аренду