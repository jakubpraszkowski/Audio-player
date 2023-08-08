#include "../include/Audio-player/UserInterface.hpp"
#include "../include/Audio-player/Tag.hpp"

//int main() {
//
//    UserInterface ui;
//    ui.mainMenu();
//    return 0;
//}

int main() {
    // Pobranie aktualnego czasu w formie liczby sekund od epoki
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Konwersja na strukturę tm (czas lokalny)
    std::tm local_time = *std::localtime(&now_time);

    // Wypisanie dzisiejszej daty w formacie DD-MM-YYYY
    std::cout << "Dzisiejsza data: " << (local_time.tm_mday < 10 ? "0" : "") << local_time.tm_mday << "-"
              << (local_time.tm_mon + 1 < 10 ? "0" : "") << local_time.tm_mon + 1 << "-"
              << local_time.tm_year + 1900 << std::endl;

    return 0;
}
