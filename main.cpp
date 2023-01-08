#include "finalProject.h"

int main()
{
    bool run = true;
    //setup inventory
	cout << "Welcome\n";

	int size = numReader("Enter inventory size (minimum 5): ", 100, 5);
	//create Inventory object on the heap
	Inventory* inventory = new Inventory(size);

	//create default objectts
	inventory->tester();

	//loop
	while (run)
	{
	    //print menu
		cout << "Menu:\n";
		cout << "1. Create a new stock item\n";
		cout << "2. Add stocks\n";
		cout << "3. Sell stock item\n";
		cout << "4. Stock report\n";
		cout << "5. Delete stock item\n";
		cout << "6. Display revenue\n";
		cout << "7. Quit\n\n";
		//input request
		int command = numReader("Enter command number: ", 7, 1);

		//try completing user request
		try
		{
		    //switch
			switch (command)
			{
			case 1:
			{
			    //check if inventory is full
				inventory->spaceFinder("");
				cout << "1. Jeans\n";
				cout << "2. Pants\n";
				cout << "3. Hoodie\n";
				cout << "4. T-Shirt\n\n";

                //obtain stock type and call fucntion
				int type = numReader("Enter stock type number: ", 4, 1);
				inventory->createStock(type);
				break;
			}
			case 2:
			{
                    //read stock ID, check if valid
					string id = stringReader("Enter stock ID: ", 4, 4);
					int index = inventory->itemSearch(id);
					//add stocks
					int quantity = numReader("Enter quantity to be added (0 - 100): ", 100, 0);
					inventory->addStocks(index, quantity);
					break;

			}
			case 3:
			{
			    //read stock ID, check if valid
				string id = stringReader("Enter stock ID: ", 4, 4);
				int index = inventory->itemSearch(id);

				//sell stocks
				int quantity = numReader("Enter quantity to be sold: ", 100, 0);
				inventory->sellStock(index, quantity);
				break;
			}
			case 4:
			    //call method
				inventory->stockReport();
				break;
			case 5:
			{
			    //read stock ID, check if valid, and delete that stock
				string id = stringReader("Enter stock ID: ", 4, 4);
				int index = inventory->itemSearch(id);
				inventory->deleteStock(index);
				break;
			}
			case 6:
			    //display revenue
				if (inventory->getRevenue() == 0)
					cout << "\nNo revenue has been made yet!\n";
				else
					cout << fixed << setprecision(2);
					cout << "\nThis shop has made $" << inventory->getRevenue() << " in revenue!\n";
				break;
			case 7:
			    //modify loop control variable
				run = false;
				break;
			}//end switch
		}//end try block

		//catch any unhandled exceptions while processing user requests, print error message
		catch (invalid_reference &e)
		{
			cout << "\nInvalid input: ";
			cout << e.what();
		}
		catch (exception &e)
		{
			cout << e.what();
		}

		cout << endl;

	}//end main loop

	//delete heap allocated memeory
	inventory->deleteStock(-1);
	delete inventory;
	cout << "\nThank you for using!\n";
}
