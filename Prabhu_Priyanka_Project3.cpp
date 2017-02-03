#include<iostream>
#include<string>
#include"QueueTypeNoTemplate.h"
using namespace std;

void getLicenseNo(QueueType& queue, string garageName);
bool searchLicenseNo(QueueType& queue, string departLicenseNo, string garageName);
int calculateParking(int length, int size, string departLicenseNo);
void moveCars(QueueType& queue, QueueType& streetQueue, string garageName);
int totalParkingFee=0;

int main() {

	QueueType fenwayGarage(3);
	QueueType gardenGarage(1);
	QueueType streetPark(1);
	fenwayGarage.Clear();
	gardenGarage.Clear();
	streetPark.Clear();
	char input;
	string arriveLicenseNo, departLicenseNo, tempLicenseNo;
	int parkingFee = 0;
	cout << "Enter 'A' for arrival or 'D' for departure (enter 'Q' to quit) :";
	cin >> input;
	while (tolower(input) != 'q') {

		if (tolower(input) == 'a') {
			if (!(fenwayGarage.IsFull())) {
				getLicenseNo(fenwayGarage, "Fenway Garage");
			}
			else if (!(gardenGarage.IsFull())) {
				getLicenseNo(gardenGarage, "Garden Garage");
			}
			else if (!(streetPark.IsFull())) {
				getLicenseNo(streetPark, "Street Parking");
			}
			else
			{
				cout << "No Parking space...Go to New York!!" << endl;
			}
		}
		else if(tolower(input) == 'd')
		{
			cout << "Please enter your license no. for departure:";
			cin >> departLicenseNo;
			if (!(searchLicenseNo(fenwayGarage, departLicenseNo,"Fenway Garage")))
			{
				if (!(searchLicenseNo(gardenGarage, departLicenseNo, "Garden Garage")))
				{
					if (!(searchLicenseNo(streetPark, departLicenseNo, "Street Parking"))) {
						cout << "Your car is stolen" << endl;
					}
				}
			}
			if (!(streetPark.IsEmpty())) {
				if (!(fenwayGarage.IsFull())) {
					moveCars(fenwayGarage, streetPark, "Fenway Garage");
				}
				else if (!(gardenGarage.IsFull())) {
					moveCars(gardenGarage, streetPark, "Garden Garage");
				}
			}
		}
		else
		{
			cout << "Invalid input" << endl;
		}
		cout << "Enter 'A' for arrival or 'D' for departure (enter 'Q' to quit) :";
		cin >> input;
	}
	cout << "No. of cars in Fenway Garage :" << fenwayGarage.GetLength()<<endl;
	cout << "No. of cars in Garden Garage :" << gardenGarage.GetLength() << endl;
	cout << "No. of cars on Street parking :" << streetPark.GetLength() << endl;
	cout << "Total parking fees collected : $" << totalParkingFee << endl;
}

void getLicenseNo(QueueType& queue, string garageName) {

	string inputLicenseNo;
	cout << "Please enter your license no. :";
	cin >> inputLicenseNo;
	queue.Insert(inputLicenseNo);	
	cout << "Car parked :" << garageName << endl;
}

bool searchLicenseNo(QueueType& queue, string departLicenseNo, string garageName) {

	string tempLicenseNo;	
	QueueType tempQueue(6);
	tempQueue.Clear();
	int queueLengthBeforeSearch, queueLength, i, count=0, parkingFee;
	bool isLicensePresent = true, flag = false;	
	queueLengthBeforeSearch = queue.GetLength();
	queueLength = queue.GetLength();
	for (i = 0; i < queueLength; i++) {
		tempLicenseNo = queue.Delete();
		if (departLicenseNo != tempLicenseNo || flag)
		{
			tempQueue.Insert(tempLicenseNo);
			count++;
		}
		else
		{
			if (garageName != "Street Parking")
			{
				cout << "License no. =" << departLicenseNo << endl;
				cout << "Departing from garage = " << garageName << endl;
				parkingFee = calculateParking(queue.GetLength(), queueLength, departLicenseNo);
				totalParkingFee += parkingFee;
			}
			else
			{
				cout << "License no. = " << departLicenseNo << endl;
				cout << "Departing from street parking" << endl;
			}
			flag = true;
		}
	}
	queueLength = count;
	for (i = 0;i < count;i++) {
		queue.Insert(tempQueue.Delete());
	}
	if (queueLengthBeforeSearch == queueLength) {
		isLicensePresent = false;
	}
	return isLicensePresent;
}

int calculateParking(int length, int size, string departLicenseNo) {

	int parkingFee;
	parkingFee = ((size - length)*5) + 5;
	cout << "Parking fee = $" << parkingFee << endl;
	return parkingFee;
}

void moveCars(QueueType& queue, QueueType& streetQueue, string garageName) {
	
	string moveCar;
	while (!(streetQueue.IsEmpty()) && !(queue.IsFull())) {
		moveCar = streetQueue.Delete();
		queue.Insert(moveCar);
		cout << "License no. = " << moveCar << endl;
		cout << "Departing from street parking to garage = " << garageName<< endl;
	}
}