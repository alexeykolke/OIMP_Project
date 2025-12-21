#pragma once
#include "Headers.h"

class TravelAgency {
public:
	// Конструктор (задаем бюджет по умолчанию 5000)
	TravelAgency() : maxBudget(5000.0) {}

	// Деструктор
	~TravelAgency() {
		basket.clear(); 
	}

	// Установка лимита бюджета
	void setMaxBudget(double budget) {
		if (budget <= 0) throw std::invalid_argument("Budget must be positive\n");
		maxBudget = budget;
	}

	// Добавление тура в сборку (с проверкой бюджета)
	void addToBasket(BaseTour* tour) {
		if (tour == nullptr) return;

		double currentTotal = calculateTotal();
		if (currentTotal + tour->getPrice() > maxBudget) {
			throw std::runtime_error("Budget exceeded! Cannot add this tour.\n");
		}
		
		basket.push_back(tour);
	}

	// Расчет общей стоимости
	double calculateTotal() {
		double total = 0;
		for (auto tour : basket) {
			total += tour->getPrice();
		}
		return total;
	}

	// Сортировка по длительности
	void sortByDuration() {
		for (size_t i = 0; i < basket.size(); ++i) {
			for (size_t j = 0; j < basket.size() - 1; ++j) {
				if (basket[j]->getDuration() > basket[j + 1]->getDuration()) {
					std::swap(basket[j], basket[j + 1]);
				}
			}
		}
	}

	// Поиск внутри сборки по диапозону цен
	void findInPriceRange(double minPrice, double maxPrice) {
		bool found = false;
		for (auto tour : basket) {
			if (tour->getPrice() >= minPrice && tour->getPrice() <= maxPrice) {
				std::cout << tour << "\n";
				found = true;
			}
		}
		if (!found) std::cout << "No tours in this price range.\n";
	}

    // Функция расчета стоимости с учётом скидки(например скидка составляет 10%)
	double getDiscountPrice() {
		double total = calculateTotal();
		if (basket.size() >= 2) {
			return total * 0.9; // Скидка 10%
		}
		return total;
	}

	// Показать текущую сборку
	void printBasket() {
		std::cout << "--- Your Current Selection ---\n";
		if (basket.empty()) {
			std::cout << "Basket is empty.\n";
			return;
		}
		for (auto tour : basket) {
			std::cout << tour << "\n";
		}
		std::cout << "Total Price: " << calculateTotal() << "\n";
		std::cout << "Price with possible discount: " << getDiscountPrice() << "\n";
	}

private:
	std::vector<BaseTour*> basket; // Список выбранных туров
	double maxBudget;              // Максимальная сумма
};