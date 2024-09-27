#include <iostream>
#include <vector>
using namespace std;


class Booster {
protected:
    //������ ��� ������
    int energizer(int num) {
        std::cout << "ROCK AND STONES ROCK AND STONE!!! [����������� �����������]" << std::endl;
        int boostIt = 2;

        return boostIt * num;
    }
};

class IronFurnace :protected Booster {
public:
    IronFurnace(int rocks) : raw(rocks) {}
    IronFurnace() { raw = 1; }

    //���������� ������������ ������
    int makeIron(int rocks) {
        int iron = rocks;
        return iron;
    }

    //���������� ��������� ���-�� ������
    int makeMoreIron(int rocks) {
        int doubledIron = energizer(rocks);
        return doubledIron;
    }

    //���������� ����������
    void showInfo(IronFurnace& obj) {
        std::cout << "����� ������: " << obj.raw << std::endl;
    }

private:
    int raw;
};

class IronFurnaceFactory {
public:
    static IronFurnace createIronFurnace(int rocks) {
        return IronFurnace(rocks);
    }

    static IronFurnace createMoreIronFurnace(int rocks) {
        IronFurnace temp(rocks);
        int doubledRocks = temp.makeMoreIron(rocks);
        return IronFurnace(doubledRocks);
    }
};


int main() {
    setlocale(LC_ALL, "ru");
    
    int rocks = 7;
    

    auto result1 = IronFurnaceFactory::createIronFurnace(rocks);
    result1.showInfo(result1);
    result1.makeIron(rocks);
    result1.showInfo(result1);

    auto result2 = IronFurnaceFactory::createMoreIronFurnace(rocks);
    result2.showInfo(result2);
    result2.makeMoreIron(rocks);
    result2.showInfo(result2);

    std::cout << sizeof(result1) << std::endl;
    std::cout << sizeof(result2) << std::endl;

    return 0;
}