#include <iostream>
#include <vector>
#include <string>

using std::string, std::cout, std::cin, std::endl;

class BankApp {
private:
	string name;
	long long int cardNumber = 0;
	unsigned balance;
	unsigned int pincode;
	
	unsigned howMuch;
	unsigned int choice;
	
	enum constants{MAXFORPIECE = 9999, MINFORPIECE = 1000, INVMAX = 9999, INVMIN = 1000};

	//strukturiruet nomer karti kak #### #### #### ####
	void structCard(){

		bool falseCondition = true;
		unsigned int piece1, piece2, piece3, piece4;

		do {
			cout << "Please, enter card numbers (via space): ";
			cin >> piece1 >> piece2 >> piece3 >> piece4;
			cardNumber = piece1 * 1'000'000'000'000ll + piece2 * 1'000'000'00ll + piece3 * 1'000'0ll + piece4;
			falseCondition = (piece1 > MAXFORPIECE || piece1 < MINFORPIECE || piece2 > MAXFORPIECE || piece2 <
				MINFORPIECE || piece3 > MAXFORPIECE || piece3 < MINFORPIECE || piece4 > MAXFORPIECE || piece4 < MINFORPIECE);
		} while (falseCondition);
	}

	void checkBalance() {cout <<"\nYour balance is: "<<balance<<" $\n";}

	/*mojno dobavit DB dlya obnolvleniya i hraneniya dannyh*/
	void transaction(int userChoice) {
		switch (userChoice) {
		case 2:
			structCard();
			cout << "How much would you like to transfer?";
			cin >> howMuch;
			cout << "\n";
			while (howMuch > balance) {
				cout << "The amount entered is too large, please enter a smaller amount: ";
				cin >> howMuch;
				cout << "\n";
			}
			cout << "You have successfully transferred " << howMuch << "$ to the card " << cardNumber;
			balance = balance - howMuch;
			break;
		case 3:
			//pust budet 8 znakov
			int invoice, invChoice, invBalance, invHowMuch;
			invBalance = 0;
			invoice = -1;
			do {
				if(invoice == -1){
					string userName;
					cout << "Please create an invoice - enter the invoice number and contractor name: \n";
					cin >> invoice >> userName;
					while (invoice < INVMIN || invoice > INVMAX) {
						cout << "Please enter your account number: \n";
						cin >> invoice;
					}
					while (userName != name) {
						cout << "\nPlease enter your name \n";
						cin >> userName;
					}
					cout << "[Invoice № "<<invoice<<" of user "<<name<<" was successfully created!]\n";
				}
				cout << "On уour balance is " << invBalance << "$\n";
				do{
					cout << "Please enter your account number: \n";
					cin >> invoice;

				} while (invoice < INVMIN || invoice > INVMAX);

				cout << "Select an operation on the account: \n";
				cout << "[1] - transfer funds to the card, [2] - top up the account from the card\n";
				cout << "Enter the number: ";
				cin >> invChoice;
				cout << "\n";
				if (invChoice == 1) {
					structCard();
					cout << "Сколько вы хотите перевести на карту? ";
					cin >> invHowMuch;
					while (invHowMuch > invBalance) {
						cout << "Введенная сумма больше, чем баланс счёта, пожалуйста, уменьшите сумму: \n";
						cin >> invHowMuch;
						cout << "\n";
					}
					cout << "Успешно пополнено!\n";
					balance += invHowMuch;
					invBalance -= invHowMuch;
					break;
				}
				else if (invChoice == 2) {
					structCard();
					cout << "На сколько вы хотите пополнить счёт?";
					cin >> invHowMuch;
					while (invHowMuch > balance) {
						cout << "Введенная сумма больше, чем баланс карты, пожалуйста, уменьшите сумму: \n";
						cin >> invHowMuch;
						cout << "\n";
					}
					cout << "\n";
					cout << "Успешно пополнено!\n";
					balance -= invHowMuch;
					invBalance += invHowMuch;
					break;

				}

			} while (invChoice != 1 && invChoice != 2);
			break;

		case 4:
			unsigned depositChoice;
			static int opens = 0;
			do {
				cout << "Открыть вклад или просмотреть существующий? [1] - открыть [2] - просмотреть: \n";
				cout << "Введите число: ";
				cin >> depositChoice;
				cout << "\n";
			} while ((depositChoice != 1) && (depositChoice != 2));
			if (depositChoice == 1) {
				opens++;
			}
			else if (depositChoice == 2) {
				if (opens < 1)cout << "Вклада не существует!\n";
				//просмотр существующего
				cout << "Имя держателя: " << name << endl;
				cout << "";
			}
			break;
		default:
			cout << "Неверная операция\n";
			break;
		}
	}

	void app() {

		unsigned int userChoice;
		cout << "\t\t\t1 - Проверить баланс. 2 - Перевод на карту. 3 - Перевод на счёт\n";
		cout << "\t\t\t4 - Открыть или просмотреть вклад\n";
		cout << "\t\t\t\t\t0 - Выйти из приложения.\n";
		
		do{
			cout << "\n\nЧто бы вы хотели сделать? Введите код операции, пожалуйста: ";
			cin >> userChoice;
			if (userChoice == 0) {
				break;
			}

			switch (userChoice) {
				
			case 1:
				checkBalance();
				break;
			case 2:
				transaction(userChoice);
				break;
			case 3:
				transaction(userChoice);
				break;
			case 4:
				transaction(userChoice);
				break;
			default:
				cout << "Неверный код, введите еще раз.\n";
				break;
			}

		} while(userChoice != 0);
	}

public:

	BankApp():howMuch(0){}
	BankApp(string name, unsigned cash) : name(name),balance(cash){}
	
	//пусть пинкод будет 1234 (в будующем кастомизируемый + смена пароля, мб многозначный(от 4 до 8))
	void openApp() {
		
		const int PASSWORD = 1234;
		unsigned int attempts = 3;
		
		cout << "Добрый день, " << name <<" !\n";
		cout << "Пожалуйста, введите свой пин-код:\n";
		cout << "[~Типа крутое окно для ввода чисел:] > ";
		cin >> pincode;
		cout << "\n";

		if (pincode == PASSWORD) {
			cout << "\n\n\nДобро пожаловать!\n";
			app();
		}
		else if (attempts > 0) {
			while(pincode != PASSWORD){
				cout << "Неверный пинкод! Попробуйте ещё раз (Осталось " << attempts-1 << " попыток.)\n";
				cout << "Пожалуйста, введите свой пин-код еще раз: ";
				cin >> pincode;
				attempts--;
			}
		}

		else if (attempts == 0) {
			cout << "К сожалению, вы ввели слишком много неверных попыток. Попробуйте еще раз через 24 часа\n";
			return;
		}
	}
};

int main() {

	setlocale(LC_ALL, "ru");
	
	string name;
	int balance;
	
	cout << "Введите своё имя: ";
	cin >> name;
	cout << "\n";

	cout << "Your balance: ";
	cin >> balance;
	cout << endl;
	
	BankApp client(name, balance);
	client.openApp();

	return 0;
}