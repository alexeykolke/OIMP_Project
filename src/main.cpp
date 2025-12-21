#include "Headers.h"
#include "TourCatalog.h"
// Функция для вывода меню
void showMenu() {
    std::cout << "\n========== ТУРАГЕНТСТВО ==========\n";
    std::cout << "1. CATALOG\n";
    std::cout << "  1. Show all\n";
    std::cout << "  2. Find tour according to coutry\n";
    std::cout << "  3. Delete tour from  catalog\n";
    std::cout << "2. CART\n";
    std::cout << "  4. Show my cart\n";
    std::cout << "  5. Add tour to cart (according to number)\n";
    std::cout << "  6. Sort cart (by duration)\n";
    std::cout << "  7. Find in cart according to price\n";
    std::cout << "3. FILES\n";
    std::cout << "  8. Load tour from file (input.txt)\n";
    std::cout << "  9. Save catalog in file\n";
    std::cout << "0. Exit\n";
    std::cout << "==================================\n";
    std::cout << "Your choice > ";
}

int main() {

    // Создаем главные объекты
    TourCatalog catalog;
    TravelAgency agency;
    
    // Установим бюджет клиенту (например, 3000 условных единиц)
    agency.setMaxBudget(3000.0);

    int choice;
    while (true) {
        showMenu();
        if (!(std::cin >> choice)) {
            // Защита от ввода букв вместо цифр
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            continue;
        }

        if (choice == 0) break;

        try {
            switch (choice) {
            // --- РАБОТА С КАТАЛОГОМ ---
            case 1: 
                catalog.printAll(); 
                break;
            
            case 2: {
                std::cout << "Введите название страны: ";
                std::string country;
                std::cin >> country;
                catalog.findByCountry(country);
                break;
            }

            case 3: {
                std::cout << "Введите индекс тура для удаления: ";
                int idx;
                std::cin >> idx;
                catalog.removeTour(idx);
                std::cout << "Тур удален.\n";
                break;
            }

            // --- РАБОТА С КОРЗИНОЙ ---
            case 4:
                agency.printBasket();
                break;

            case 5: {
                std::cout << "Введите индекс тура из каталога: ";
                int idx;
                std::cin >> idx;
                
                // Получаем доступ к списку туров
                auto& allTours = catalog.getTours();
                if (idx >= 0 && idx < allTours.size()) {
                    // Пытаемся добавить (здесь сработает проверка бюджета)
                    agency.addToBasket(allTours[idx]);
                    std::cout << "Тур успешно добавлен в корзину!\n";
                } else {
                    std::cout << "Неверный номер тура.\n";
                }
                break;
            }

            case 6:
                agency.sortByDuration();
                std::cout << "Корзина отсортирована по длительности.\n";
                break;

            case 7: {
                double minP, maxP;
                std::cout << "Введите мин. и макс. цену: ";
                std::cin >> minP >> maxP;
                agency.findInPriceRange(minP, maxP);
                break;
            }

            // --- РАБОТА С ФАЙЛАМИ ---
            case 8: {
                std::ifstream fin("Tours.txt");
                if (!fin.is_open()) {
                    std::cout << "Файл Tours.txt не найден! Создайте его.\n";
                    break;
                }

                int typeInt;
                int count = 0;
                // Это та самая логика "Фабрики" из твоего примера
                while (fin >> typeInt) {
                    TourType type = static_cast<TourType>(typeInt);
                    BaseTour* newTour = nullptr;

                    switch (type) {
                    case TourType::Beach:
                        newTour = new BeachTour();
                        break;
                    case TourType::Excursion:
                        newTour = new ExcursionTour();
                        break;
                    case TourType::Ski:
                        newTour = new SkiTour();
                        break;
                    default:
                        // Пропускаем неизвестные типы
                        break;
                    }

                    if (newTour != nullptr) {
                        try {
                            // Используем перегруженный оператор >>
                            fin >> newTour;
                            catalog.addTour(newTour);
                            count++;
                        }
                        catch (const std::exception& e) {
                            std::cout << "Ошибка чтения тура: " << e.what() << "\n";
                            delete newTour; // Не забываем чистить память при ошибке
                        }
                    }
                }
                fin.close();
                std::cout << "Загружено туров: " << count << "\n";
                break;
            }

            case 9: {
                std::ofstream fout("SavedCatalog.txt");
                // Сохраняем так, чтобы потом можно было считать (сначала тип, потом данные)
                for (auto tour : catalog.getTours()) {
                    fout << (int)tour->getType() << " "; 
                    fout << tour << "\n";
                }
                fout.close();
                std::cout << "Каталог сохранен в файл SavedCatalog.txt\n";
                break;
            }

            default:
                std::cout << "Неверный пункт меню.\n";
            }
        }
        catch (const std::exception& ex) {
            // Ловим все ошибки (бюджет, валидация и т.д.) в одном месте
            std::cerr << "ОШИБКА: " << ex.what() << "\n";
        }
    }

    return 0;
}