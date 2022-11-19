// Queue in a Supermarket in C++ - Villanueva
#include<iostream>
#include<fstream>
#include<string>
#include <iomanip>
#include <sstream>

using namespace std;

double qTime;
struct Queue {
	int item;
	string prefPack;
	int numPack;
	string prefPay;
	string cashPay;
};

Queue getData(string line){
	size_t pos = 0;
	size_t npos = -1;
	string delimiter = " ";
	string data[5] = {""};
	int data_index = 0;
	
	while ((pos = line.find(delimiter)) != npos) {
	    data[data_index] = line.substr(0, pos);
	    line.erase(0, pos + delimiter.length());
	    data_index++;
	}
	
	data[data_index] = line;
	
	stringstream ss;
	
	Queue temp;
	
	for (int i = 0; i < 5; i++) {
		string d = *(data + i);
		if (i == 0 || i == 2) {
			ss << d;
			if (i == 0) {
				ss >> temp.item;
			} else if (i == 2) {
				ss >> temp.numPack;
			}
			ss.clear();
			ss.str("");
		} else if (i == 1) {
			temp.prefPack = d;
		} else if (i == 3) {
			temp.prefPay = d;
		} else if (i == 4) {
			temp.cashPay = d;
		}
	}
	
	return temp;
}

void Info(Queue n, int index){
	float deCart, scanTime, packTime, payTime, reciTime, custoTime, totalQ;
	int custoNum, idTime;

    custoNum = index + 1;

	cout << "Customer #" << custoNum <<": "<< endl;
	cout << "No. of Cart Items: " << n.item << endl;
	cout << "Preferred Packaging: " << n.prefPack << endl;
	cout << "Number of Box: " << n.numPack << endl;
	
	if(n.cashPay == "e"){
		cout << "Preferred Payment Method: " << n.prefPay << " (exact) " << endl;
	}
	else if(n.cashPay == "ne"){
		cout << "Preferred Payment Method: " << n.prefPay << " (not exact) " << endl;
	}
	else {
		cout << "Preferred Payment Method: " << n.prefPay << endl;
	}
	
	cout << "------------------------------------------------\n";
	
	//Total Decarting Time 
	deCart = n.item * 0.5;
	cout << "Total De-Carting Time: " << n.item << " * 0.5 = " << deCart << endl;
	
	//Total Scanning Time
	scanTime =  n.item * 0.5;
	cout << "Total Scanning Time: " << n.item << " * 0.5 = " << scanTime << endl;
	
	//Prefered Packaging and the Total Packing Time
	if(n.prefPack == "box"){
		packTime = (n.item * 0.50) + (n.numPack * 10);
		cout << "Total Packing Time: (" << n.item << " * 0.5) + (" << n.numPack << " * 10) = " << packTime << endl;
	} 
	else if (n.prefPack == "bag") {
		packTime = (n.item * 0.50) + (n.numPack * 5);
		cout << "Total Packing Time: (" << n.item<< " * 0.5) + (" << n.numPack << " * 5) = " << packTime << endl;
	}
	
	//Preferred Payment and Cash Type
	if(n.prefPay == "cash"){
		if(n.cashPay == "e"){
			payTime = 15;
			cout << "Total Paying Time: " << payTime << endl;
		}
		else if(n.cashPay == "ne"){
			payTime = 20;
			cout << "Total Paying Time: " << payTime << endl;
		}
	}
	if(n.prefPay == "digital"){
		payTime = 15;
		cout << "Total Paying Time: " << payTime << endl;
	}
	
	//Total Receipt Printing Time
	reciTime = (n.item * 0.3) + 2;
	cout << "Total Receipt Printing Time: (" << n.item << " * 0.5) + 2 = " << reciTime << endl;
	
	//Idle Time
	if(index == 0){
		idTime = 0;
		cout << "Idle Time: " <<  idTime << endl;
	} else if(index > 0){
		idTime = 3;
		cout << "Idle Time: " <<  idTime << endl;
	}
	
	//Total Customer Queue Time
	custoTime = deCart + scanTime + packTime + payTime + reciTime + idTime;
	cout << "Total Customer-Queue Time: " << custoTime << endl;
	
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    qTime += custoTime;
}

int main(){
	ifstream in_stream("file.txt");
	if(in_stream.fail())
    	{
        	cout<<"Input file opening failed.\n";
        	exit(1);
   		} 
   	
   	int custo;
	
	in_stream >> custo;
	
	cout << "No. of Customers:: " << custo << endl;
	cout << "================================================\n";
	
	Queue q[custo];
	
	Queue n;
		
	string line;
	
	int index = 0;
	
	while (getline(in_stream, line)) {
		if (line.length() > 0) {
			q[index] = getData(line);
			Info(q[index],index);
			index++;
		}
	}

    cout << "Total Lane Queue Time: " << qTime;
   	
	return 0;
}
