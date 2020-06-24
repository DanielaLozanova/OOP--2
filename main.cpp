#include"Header3.h"

using namespace std;

int main()
{
	CourierCompany company(4);
	char qyn[10];
	bool quit;
	do
	{
		char item[65];
		cout << "Choose between Shoes or Furniture? ";
		cin.getline(item,64);
		if (!strcmp("Shoes", item) || !strcmp("Furniture", item))
		{
			cout << "Enter box size: ";
			double x = 0, y = 0, z = 0;
			cin >> x >> y >> z;
			cin.get();
			cout << "Enter address: ";
			char address[65];
			cin.getline(address, 64);
			double cost = 0;
			cout << "Enter price for kilogram: ";
			cin >> cost;
			unsigned int capacity = 1;
			if (!strcmp("Shoes", item))
			{
				cin.get();
				cout << "Enter number of elements of the shoes: ";
				cin >> capacity;
				bool tryS;
				cout << "Can shoes be tried out immediately after shipment? ";
				char yn[10];
				cin.getline(yn, 9);
				if (!strcmp("Yes", yn))
				{
					tryS = true;
				}
				else
				{
					tryS = false;
				}
				cin.get();
				company.addItemToCC(new Shoes({ x,y,z }, address, cost, capacity, tryS));

			}
			else
			{
				cin.get();
				cout << "Enter number of elements of the Furniture: ";
				cin >> capacity;
				char marka[65];
				cout << "Enter the brand of the Furniture: ";
				cin.get();
				cin.getline(marka, 64);
				company.addItemToCC(new Furniture({ x,y,z }, address, cost, capacity, marka));
			}
		}
		cin.get();
		cout << "Do you want to quit? ";
		cin.getline(qyn, 9);
		if (!strcmp("Yes",qyn))
		{
			quit = true;
		}
		else
		{
			quit = false;
		}
	} while (!quit);
	cout << endl;
	cout << "PRINTCC" << endl;
	company.printCC();
	cout << endl;
	cout << "Ranking" << endl;
	company.ranking();
	cout << endl;
	cout << "income" << endl;
	cout<<company.income();
	
	cin.get();
	return 0;
}