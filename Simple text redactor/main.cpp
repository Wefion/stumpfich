#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

class RAWOfFiles {
protected:
	void fileReader(const string& path) {
		
		bool exception = (path.length() < 4) || (path.substr(path.length() - 4, path.length() - 1) != ".txt");
		
		/*string bannedSymbols = "\\/:*?<>|""";
		if (bannedSymbols.find(path)) {
			cout << "???????";
		}*/
		
		if (exception) cout << "Неверное имя или расширение файла!\n";

		fstream ffile;
		ffile.open(path,ios::in);
		string line;

		if (!ffile.is_open()) {
			cerr << "Ошибка открытия файла.";
		}else {
			while (getline(ffile, line)) {
				cout << line << endl;
			}
		}

		ffile.close();
	}
	void fileWriter(const string& path) {
		bool exception = ((path.length() < 4) || (path.substr(path.length() - 4, path.length() - 1) != ".txt"));
		if (exception) cout << "Неверное имя или расширение файла!\n";
		
		//поток для открытия и дальнешей записи в файл
		fstream ffile;
		string line;
		
		ffile.open(path, ios::app);
		if (!ffile.is_open()) {
			cerr << "Ошибка открытия файла.";
		}
		else {
			cout << "Для конца записи введите '0'." << endl;
			cout << "Введите сообщение, которое будет записано в файл: ";

			while (getline(cin, line)) {
				if (line == "0") break;
				ffile << line << endl;
			}
		}
		ffile.close();
	}
};

//launch-> mainWork -> ((1-> работа с готовым файлом) || (2-> создание, а потом работа с файлом) || (3-> выход)) -> сохранение инфы
//должен быть файл, пусть называется storage в котором будут храниться допустимые имена для файлов, 
//через которые и будет взаимодействие с основными текстовыми файлами

class Notepad: protected RAWOfFiles{
private:
	string storage = "storage.txt"; //название файла, в котором будут лежать другие файлы
	vector<string>fileStorage; //массив, хранящий названия файлов

	void mainWork() {
		int choise;
		cout << "Введите соответсвующие цифры, чтобы:\n"<<"Выбрать файл - 1, Создать файл - 2, Выйти из программы - 3:\n";
		cin >> choise;

		if (choise != 1 && choise != 2 && choise != 3) {
			cout << "Неверная операция!\n";
			return;

		}
		else if (choise == 1) {
			fstream storageOpener(storage);
			int fileNum = 0;

			//нет существующих файлов в storage
			if ((storageOpener.is_open() && storageOpener.peek() != ifstream::traits_type::eof())) {
				cerr << "Нет существующих файлов!\n";
			}
			//файлы есть, но нужно выбрать, какой
			else {
				string line;
				while (getline(storageOpener,line)) {
					fileStorage.push_back(line);
				}
				cout << "Выберите номер файла: \n";
				for (size_t i = 0; i < fileStorage.size(); i++){
					cout << i << " " << fileStorage[i] << endl;
				}
			}

		}
		else if (choise == 2) {
			string name;
			cout << "Придумайте название файлу: ";
			cin >> name;
			name += ".txt";


		}
		else if (choise == 3) return;
	}
	

	void displayMenu() {
		cout << "\n\n\nЧто вы хотите сделать с файлом\n?";
		cout << "[1] - открыть файл, [2] - закрыть файл\n";
		cout << "[3] - выход из программы\n\n\n";
	}


	void fileWork(int ind = 0) {
		int choise;
		string localPath = fileStorage[ind];
		fstream thisFile;
		
		displayMenu();
		cin >> choise;

		if (choise == 1) {
			thisFile.open(localPath);
		}

		else if (choise == 2 && thisFile.is_open()) {
			thisFile.close();
			return;
		}
		else if (choise == 3) {
			return;
		}
		else cerr << "Неверная операция!\n";
	}


	void info() {
		//storage.open();
		fstream storageOpener(storage);

		if ((storageOpener.is_open() && storageOpener.peek() == ifstream::traits_type::eof())) {
			cout << "Файлов не существует -\\_(@_@)_/-\n";
			return;
		}else {
			cout << "Существующие файлы: " << endl;
			string line;
			while (getline(storageOpener, line)) {
				cout << line << endl;
			}
		}
	}
public:
	void launch() {
		mainWork();
	}

	void showInfo() {
		info();
	}
};

/*class ReadTest : protected RAWOfFiles {
public:
	void func() {
		string line = "test.txt";
		//.fileWriter(line);
		fileReader(line);
	}
};*/

int main() {
	setlocale(LC_ALL, "ru");
	
	Notepad np;
	np.showInfo();
	np.launch();

	/*string word;

	list.open("shoplist.txt",ofstream::app);
	cout << "Введите слово 'exit', если хотите закончить.\n";

	while (cin >> word && word != "exit") {
		list << word << endl;
	}
	
	list.close();*/



	return 0;
}