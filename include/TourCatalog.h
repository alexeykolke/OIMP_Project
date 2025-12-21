#pragma once
#include "Headers.h"

class TourCatalog {
public:
	// Конструктор
	TourCatalog() = default;

	// Деструктор
	~TourCatalog() {
		for (auto tour : tours) {
			delete tour;
		}
		tours.clear();
	}

	// Добавить тур в каталог
	void addTour(BaseTour* tour) {
		if (tour == nullptr) return;
		tours.push_back(tour);
	}

	// Показать все доступные туры
	void printAll() {
		if (tours.empty()) {
			std::cout << "Catalog is empty.\n";
			return;
		}
		for (int i = 0; i < tours.size(); ++i) {
			std::cout << i << ". " << tours[i] << "\n";
		}
	}

	// Удалить тур из каталога при помощи индекса
	void removeTour(int index) {
		if (index < 0 || index >= tours.size()) {
			throw std::out_of_range("Invalid index\n");
		}
		delete tours[index]; // Удаляем тур из памяти
		tours.erase(tours.begin() + index); // Удаляем указатель на тур из списка
	}

	// Поиск по стране
	void findByCountry(std::string country) {
		bool found = false;
		for (auto tour : tours) {
			if (tour->getCountry() == country) {
				std::cout << tour << "\n";
				found = true;
			}
		}
		if (!found) {
			std::cout << "No tours found in " << country << "\n";
		}
	}

	// Геттер для получения всего списка
	std::vector<BaseTour*>& getTours() {
		return tours;
	}

private:
	std::vector<BaseTour*> tours; // основной список туров
};