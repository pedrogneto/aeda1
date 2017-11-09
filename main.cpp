#include <iostream>
#include <iomanip>
#include <fstream>
#include "bike.h"
#include "sharePoint.h"
#include "company.h"

using namespace std;

int main()
{

	/*GETTING SAVED INFORMATION FROM FILES*/

	Company bikesCompany;

	//reading SharePoints from file "SharePoints.txt"

	ifstream inFile;

	inFile.open("SharePoints.txt");

	if(inFile.fail())
	{
		cerr << "Error opening 'SharePoints.txt' file" << endl;
		exit(1);
	}

	bikesCompany.readSharePoints(inFile);

	inFile.close();

	//reading SharePoints from file "SharePoints.txt"

	inFile.open("Clients.txt");

	if(inFile.fail())
	{
		cerr << "Error opening 'Clients.txt' file" << endl;
		exit(1);
	}

	bikesCompany.readClients(inFile);

	inFile.close();

	/**MENU**/

	while(1)
	{
		//Menu
		cout << endl;
		cout << "::::::::::::MENU::::::::::::" << endl;
		cout << setw(5) << 1 << ". Client's Management " << endl;
		cout << setw(5) << 2 << ". SharePoint's Management " << endl;
		cout << setw(5) << 3 << ". Exit " << endl;
		cout << "::::::::::::::::::::::::::::" << endl << endl;

		int option;	//save option that user chooses from menu
		do
		{
			cout << "Choose an option (1 to 3) : "; cin >> option;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(9999, '\n');
				option = 0; //ignore error and set input to a not vaccepted input
			}

		} while (option < 1 || option > 3); //forces user to choose an option between 1 and 4
		cin.ignore(); //if we want to use getline later

		switch(option)
		{
		//*****Driver's Management*****//
		case 1:

			cout << endl;
			cout << setw(5) << 1 << ". Add Client " << endl;
			cout << setw(5) << 2 << ". Remove Client " << endl;
			cout << setw(5) << 3 << ". Change Client's Location " << endl;
			cout << setw(5) << 3 << ". Peek Bike " << endl;
			cout << setw(5) << 4 << ". Return Bike " << endl << endl;


			break;	//End of Driver's Management


		//*****SharePoint's Management*****/
		case 2:

			cout << endl;
			cout << setw(5) << 1 << ". Add SharePoint " << endl;
			cout << setw(5) << 2 << ". Remove SharePoint " << endl;
			cout << setw(5) << 3 << ". Add Bike " << endl << endl;

			int option2;	//option at SarePoint's Management
			do
			{
				cout << "Choose an option (1 to 3) : "; cin >> option2;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(9999, '\n');
					option = 0; //ignore error and set input to a not accepted input
				}

			} while (option2 < 1 || option2 > 3); //forces user to choose an option between 1 and 2
			cin.ignore(); //if we want to use getline later

			double x, y;	//used in Add and Remove

			switch(option2)
			{

			//Add SharePoint
			case 1:

				unsigned int capacity;

				cout << "x : "; cin >> x;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore(9999, '\n');
					cout << "x (double) : "; cin >> x;
				}

				cout << "y : "; cin >> y;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore(9999, '\n');
					cout << "y (double) : "; cin >> y;
				}

				cout << "capacity : "; cin >> capacity;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore(9999, '\n');
					cout << "capacity (unsigned int) : "; cin >> capacity;
				}

				try
				{
					bikesCompany.addSharePoint(new SharePoint(x,y,capacity));
				}

				catch(ExistentSharePoint & e)
				{
					cout << "Location Already Occupied : " << e.getInformation() << endl;
				}

				break;	//End of Add SharePoint

			//Remove SharePoint
			case 2:

				cout << "x : "; cin >> x;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore(9999, '\n');
					cout << "x (double) : "; cin >> x;
				}

				cout << "y : "; cin >> y;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore(9999, '\n');
					cout << "y (double) : "; cin >> y;
				}

				try
				{
					bikesCompany.removeSharePoint(x,y);
				}

				catch(NotExistentSharePoint & e)
				{
					cout << "Location doesn't have a SharePoint : " << e.getInformation() << endl;
				}

				break;	//End of Remove SharePoint

			//Add Bike
			case 3:

				string bikeType;

				cout << "Bike Type : "; getline(cin, bikeType);

				cout << "x : "; cin >> x;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore(9999, '\n');
					cout << "x (double) : "; cin >> x;
				}

				cout << "y : "; cin >> y;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore(9999, '\n');
					cout << "y (double) : "; cin >> y;
				}

				try
				{
					bikesCompany.addBike(x, y, bikeType);
				}

				catch(NotExistentSharePoint & e)
				{
					cout << "SharePoint does not exist : ( " << e.getInformation() << endl;
				}

				catch(NotExistentBikeType & e)
				{
					cout << "No such Bike Type : " << e.getType() << endl;
				}

				catch(FullSharePoint & e)
				{
					cout << "Full SharePoint : ( " << e.getX() << " , " << e.getY() << " ) " << endl;
				}

				break;

			}

			break;	//End of SharePoint's Management


			//*****End of Program*****//
			case 3:
				return 0;	//End of program

		}






		/*other tests: to remove later*/

		//bikesCompany.addBike(new Race(), 5);

		//adding SharePoints
		int num;
		cout << "How many tries to add SharePointers ? "; cin >> num;

		for(int i = 0; i < num; i++)
		{
			double x, y;
			int capacity;

			cout << "x : "; cin >> x; cout << "y : "; cin >> y; cout << "capacity : "; cin >> capacity;

			try
			{
				bikesCompany.addSharePoint(new SharePoint(x,y,capacity));
			}

			catch(ExistentSharePoint & e)
			{
				cout << "Location Already Occupied : " << e.getInformation() << endl;
			}
		}

		cout << "number of SharePoints : " << bikesCompany.getSharePoints().size() << endl;

		//removing SharePoints
		cout << "How many tries to remove SharePointers ? "; cin >> num;
		for(int i = 0; i < num; i++)
		{
			double x, y;

			cout << "x : "; cin >> x; cout << "y : "; cin >> y;

			try
			{
				bikesCompany.removeSharePoint(x,y);
			}

			catch(NotExistentSharePoint & e)
			{
				cout << "Location doesn't have a SharePoint : " << e.getInformation() << endl;
			}

		}

		cout << "number of SharePoints : " << bikesCompany.getSharePoints().size() << endl;

		//adding clients
		cout << "How many tries to add Clients ? "; cin >> num;
		for(int i = 0; i < num; i++)
		{
			string type, name;
			double x, y;

			cin.ignore();
			cout << "Type : "; getline(cin, type);
			cout << "Name : "; getline(cin, name);
			cout << "x : "; cin >> x; cout << "y : "; cin >> y;

			if(type == "Partner")
				bikesCompany.addClient(new Partner(name, x, y));
			else
				bikesCompany.addClient(new Regular(name, x, y));

		}

		cout << "number of Clients  : " << bikesCompany.getClients().size() << endl;

		//removing clients
		cout << "How many tries to remove Clients ? "; cin >> num;
		for(int i = 0; i < num; i++)
		{
			int clientID;

			cout << "Cient ID : "; cin >> clientID;

			try
			{
				bikesCompany.removeClient(clientID);
			}

			catch(NotExistentClient & e)
			{
				cout << "Ther isn't a client with ID : " << e.getID() << endl;
			}
		}

		cout << "number of Clients  : " << bikesCompany.getClients().size() << endl;

		//closest SharePoint
		int clientInd;
		cout << "Client index to find closest SharePoint to return bike: "; cin >>clientInd;

		try
		{
			SharePoint * p1 = bikesCompany.getClients().at(clientInd)->closestSHtoReturn(bikesCompany.getSharePoints());
			cout << "Closest SharePoint : "<< *p1 << endl;
		}

		catch(NotAvaibleSharePoints & e)
		{
			cout << "Not Avaible SharePoints" << endl;
		}

		string bikeType;
		cout << "Client index to find closest SharePoint to peek bike: "; cin >> clientInd;
		cout << "Bike Type : "; cin >> bikeType;

		try
		{
			SharePoint * p1 = bikesCompany.getClients().at(clientInd)->closestSHtoPeek(bikesCompany.getSharePoints(), bikeType);
			cout << "Closest SharePoint : "<< *p1 << endl;
		}

		catch(NotAvaibleSharePoints & e)
		{
			cout << "Not Avaible SharePoints with : " << e.getBykeType() <<  endl;
		}


		/*SAVING INFORMATION IN FILES*/

		//saving SharePoints in file "SharePoints.txt"

		ofstream outFile;

		outFile.open("SharePoints.txt");

		if(outFile.fail())
		{
			cerr << "Error opening 'SharePoints' file" << endl;
			exit(1);
		}

		bikesCompany.saveSharePoints(outFile);

		outFile.close();

		//saving Clients in file "Clients.txt"

		outFile.open("Clients.txt");

		if(outFile.fail())
		{
			cerr << "Error opening 'SharePoints' file" << endl;
			exit(1);
		}

		bikesCompany.saveClients(outFile);

		outFile.close();

	}
}
