#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>

class Notepad {
	/*здесь будет всё, что нужно для эмуляции блокнота (попытаюсь реализовать что-то типо консольного
	* блокнота, с анимацией пролистывания и содержимым прямо на листке, а так же что типа отдельного поля
	* специально для записи*/
};

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    const int animationFrames = 100;
    const float pi = 3.14457235;

    for (int frame = 1; frame < animationFrames; ++frame) {
        system("cls");

        // Отображение простой анимации
        gotoxy(frame * frame / 5, frame / 0.5);
        setColor(frame % 15 + 1);  // Цвет от 1 до 15
        std::cout << "FIRE IN THE HOLE";

        // Задержка между кадрами (в миллисекундах)
        Sleep(100);
    }
    return 0;
}