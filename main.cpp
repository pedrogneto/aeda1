#include <iostream>
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

	/*experimenting adding/removing SharePoints/Clients*/

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

	return 0;
}
