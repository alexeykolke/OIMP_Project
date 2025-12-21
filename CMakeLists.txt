cmake_minimum_required(VERSION 3.10)

# Название проекта
project(TourAgency)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Список всех файлов проекта
set(SOURCES
    main.cpp
    Headers.h
    BaseTour.h
    BeachTour.h
    ExcursionTour.h
    SkiTour.h
    TourCatalog.h
    TravelAgency.h
)

add_executable(TourAgency ${SOURCES})

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Tours.txt")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Tours.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
endif()