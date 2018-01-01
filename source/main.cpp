#include <iostream>//input output
#include <ctime> //�ɶ��禡�w

using namespace std;//�Ŷ��R�W�A�᭱�i�H���Υ�std::

class slotMachine {//����struct
private://�u��ۤvclass����ק鷺�e
	int wheelA;
	int wheelB;
	int wheelC;
	double pullTimes;
	double payOut;
	double moneyInMachine;
	double moneyInPeople;
	double gameCost;
	double moneyPaid;
public://�j�a���i�H��
	slotMachine();
	bool displayMenu(void);
	bool pullHandle(void);
	void spinWheel(int &);
	double calculatePayout();
	void insertCoin(double);
	void displaySpinResults();
	int Random(int, int);
	void displayStatus();
};

int main(void) {
	slotMachine mySlot;//�w�qmySlot�����A�OslotMachine
	cout << "Hellow!" << endl;
	cout << "Welcome to our Slot Machine Game." << endl;
	cout << "Now your status:" << endl;
	cout << endl << "Money in Peoele $" << 150 << endl;
	cout << "Money in Machine $" << 100 << endl;
	cout << "Pulls Left: " << 0 << endl << endl;
	//�W���Ϊk��printf�O�@�˪��Aendl����\n���Ϊk
	bool ok = true;
	while (ok)
	{
		ok = mySlot.displayMenu();
	}
	system("pause");
	return 0;
}

slotMachine::slotMachine()//����W���w�q��private���ȳ]�w�n
{
	srand((int)time(0));//��ɶ����ü�
	moneyInMachine = 100;
	moneyInPeople = 150;
	moneyPaid = 0;
	pullTimes = 0;
	payOut = 0;
	wheelA = 0;
	wheelB = 0;
	wheelC = 0;
	gameCost = 2;
}

bool slotMachine::displayMenu(void)//�ؿ�
{
	char choice = 'Z';
	bool continueGame = true;
	if (moneyInMachine == 0)//���P�_���x�̭����S����
	{
		cout << "Congratulations. You hit the jackpot" << endl;
		cout << "That start NEW games!" << endl;
		moneyInMachine = rand() % 200 + 100;
		cout << "We put $" << moneyInMachine << " into the machine" << endl;
		cout << "Good Luck To You" << endl;
	}
	if (moneyInPeople < 2 && pullTimes == 0)//�P�_���S���}��
	{
		displayStatus();
		cout << "Now you are Bankruptcy" << endl;
		cout << "Get out of my store" << endl << endl;
		continueGame = false;
		return continueGame;
	}
	else//�S���}���h�}�l��ܰʧ@
	{
		cout << "---------------------------------------------------" << endl;
		cout << "\n(E)nd, (P)ull, P(A)Y, (S)tatus :";
		cin >> choice;//��J�A�n��ܪ�
		switch (choice) {
		case 'e':
		case 'E'://����
			continueGame = false;
			break;
		case 'a':
		case 'A'://��J���B
			int money;
			cout << "\nHow much would you want to put in?\n";
			cin >> money;
			if (money <= moneyInPeople)//��J���B�@�w�n�p�󵥩�ۨ��֦������B
			{
				if (money % 2 == 0)//�ڭ̬O 2$ 1�� �ҥH�u���2������ 
				{
					cout << "Put $" << money << " into the machine" << endl;
					moneyPaid = money;
					pullTimes += (moneyPaid / gameCost);
					cout << "Now you have " << pullTimes << " Pull times\n" << endl;
					insertCoin(money);
				}
				else
				{
					cout << "Please put even money" << endl;
				}
			}
			else
			{
				cout << "You have no enough money" << endl << endl;
			}
			break;
		case 'p':
		case 'P'://�ϥΩ��Q
			if (pullHandle())
			{
				cout << endl;
				pullTimes -= 1;
				displaySpinResults();
				cout << "Payout: $" << calculatePayout() << endl << endl;
			}
			else
			{
				cout << "\nYou have no money in Machine" << endl;
				cout << "Please choice (A) to put money in" << endl << endl;
			}
			break;
		case 'S':
		case 's'://�d�ݥثe�����A
			displayStatus();
			break;
		}
		return continueGame;
	}
}

double slotMachine::calculatePayout()//�p�G���Ψ�3�Ӥ@�˪��Ʀr�A�|�o����B
{
	if (wheelA == wheelB  && wheelA == wheelC)
	{
		switch (wheelA)
		{
		case 1:
		case 3:
		case 5://3��1 or 3��3 or 3��5 �A�|�o����x�̭������B*0.2 
			payOut = ((moneyInMachine + 1) * 0.2);
			moneyInMachine -= payOut;
			moneyInPeople += payOut;
			cout << "You win!" << endl;
			cout << "Pulls Left: " << pullTimes << endl;
			return payOut;
			break;
		case 2:
		case 4:
		case 6://3��2 or 3��4 or 3��6 �A�|�o����x�̭������B*0.4 
			payOut = (moneyInMachine * 0.4);
			moneyInMachine -= payOut;
			moneyInPeople += payOut;
			cout << "You win!" << endl;
			cout << "Pulls Left: " << pullTimes << endl;
			return payOut;
			break;
		case 7://3��7 ���j�� ���x�̭���������
			payOut = (moneyInMachine);
			pullTimes = 0;
			moneyInMachine = 0;
			moneyInPeople += payOut;
			cout << "You win!" << endl;
			cout << "Pulls Left: " << pullTimes << endl;
			return payOut;
			break;
		default:
			return 0;
			break;
		}
	}
	else//���S��3�Ӥ@�˪�
	{
		cout << "Pulls Left: " << pullTimes << endl;
		cout << "No payout. Try again?\n" << endl;
		return 0;
	}
}