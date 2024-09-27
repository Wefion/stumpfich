#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>

class Notepad {
	/*����� ����� ��, ��� ����� ��� �������� �������� (��������� ����������� ���-�� ���� �����������
	* ��������, � ��������� ������������� � ���������� ����� �� ������, � ��� �� ��� ���� ���������� ����
	* ���������� ��� ������*/
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

        // ����������� ������� ��������
        gotoxy(frame * frame / 5, frame / 0.5);
        setColor(frame % 15 + 1);  // ���� �� 1 �� 15
        std::cout << "FIRE IN THE HOLE";

        // �������� ����� ������� (� �������������)
        Sleep(100);
    }
    return 0;
}