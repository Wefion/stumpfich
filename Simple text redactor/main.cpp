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
		
		if (exception) cout << "�������� ��� ��� ���������� �����!\n";

		fstream ffile;
		ffile.open(path,ios::in);
		string line;

		if (!ffile.is_open()) {
			cerr << "������ �������� �����.";
		}else {
			while (getline(ffile, line)) {
				cout << line << endl;
			}
		}

		ffile.close();
	}
	void fileWriter(const string& path) {
		bool exception = ((path.length() < 4) || (path.substr(path.length() - 4, path.length() - 1) != ".txt"));
		if (exception) cout << "�������� ��� ��� ���������� �����!\n";
		
		//����� ��� �������� � ��������� ������ � ����
		fstream ffile;
		string line;
		
		ffile.open(path, ios::app);
		if (!ffile.is_open()) {
			cerr << "������ �������� �����.";
		}
		else {
			cout << "��� ����� ������ ������� '0'." << endl;
			cout << "������� ���������, ������� ����� �������� � ����: ";

			while (getline(cin, line)) {
				if (line == "0") break;
				ffile << line << endl;
			}
		}
		ffile.close();
	}
};

//launch-> mainWork -> ((1-> ������ � ������� ������) || (2-> ��������, � ����� ������ � ������) || (3-> �����)) -> ���������� ����
//������ ���� ����, ����� ���������� storage � ������� ����� ��������� ���������� ����� ��� ������, 
//����� ������� � ����� �������������� � ��������� ���������� �������

class Notepad: protected RAWOfFiles{
private:
	string storage = "storage.txt"; //�������� �����, � ������� ����� ������ ������ �����
	vector<string>fileStorage; //������, �������� �������� ������

	void mainWork() {
		int choise;
		cout << "������� �������������� �����, �����:\n"<<"������� ���� - 1, ������� ���� - 2, ����� �� ��������� - 3:\n";
		cin >> choise;

		if (choise != 1 && choise != 2 && choise != 3) {
			cout << "�������� ��������!\n";
			return;

		}
		else if (choise == 1) {
			fstream storageOpener(storage);
			int fileNum = 0;

			//��� ������������ ������ � storage
			if ((storageOpener.is_open() && storageOpener.peek() != ifstream::traits_type::eof())) {
				cerr << "��� ������������ ������!\n";
			}
			//����� ����, �� ����� �������, �����
			else {
				string line;
				while (getline(storageOpener,line)) {
					fileStorage.push_back(line);
				}
				cout << "�������� ����� �����: \n";
				for (size_t i = 0; i < fileStorage.size(); i++){
					cout << i << " " << fileStorage[i] << endl;
				}
			}

		}
		else if (choise == 2) {
			string name;
			cout << "���������� �������� �����: ";
			cin >> name;
			name += ".txt";


		}
		else if (choise == 3) return;
	}
	

	void displayMenu() {
		cout << "\n\n\n��� �� ������ ������� � ������\n?";
		cout << "[1] - ������� ����, [2] - ������� ����\n";
		cout << "[3] - ����� �� ���������\n\n\n";
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
		else cerr << "�������� ��������!\n";
	}


	void info() {
		//storage.open();
		fstream storageOpener(storage);

		if ((storageOpener.is_open() && storageOpener.peek() == ifstream::traits_type::eof())) {
			cout << "������ �� ���������� -\\_(@_@)_/-\n";
			return;
		}else {
			cout << "������������ �����: " << endl;
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
	cout << "������� ����� 'exit', ���� ������ ���������.\n";

	while (cin >> word && word != "exit") {
		list << word << endl;
	}
	
	list.close();*/



	return 0;
}