#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h> // For Windows console control

void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScreen() {
    system("cls");
}

int main() {
    srand(time(NULL));
    int width = 80;
    int height = 25;
    int fireworkX = rand() % width;
    int fireworkY = height - 1;
    int explosionRadius = 5;

    // Simulate firework launch
    for (int y = height - 1; y >= 0; y--) {
        clearScreen();
        setCursorPosition(fireworkX, y);
        std::cout << "*";
        Sleep(100);
    }

    // Simulate explosion
    for (int frame = 0; frame < 10; frame++) {
        clearScreen();
        for (int i = 0; i < 20; i++) {
            int x = fireworkX + (rand() % (2 * explosionRadius + 1)) - explosionRadius;
            int y = 0 + (rand() % (2 * explosionRadius + 1)) - explosionRadius;
            if (x >= 0 && x < width && y >= 0 && y < height) {
                setCursorPosition(x, y);
                std::cout << "*";
            }
        }
        Sleep(200);
    }

    clearScreen();
    std::cout << "Happy New Year!" << std::endl;
    return 0;
}