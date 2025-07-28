#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	cout << setw(29) << "CSG Gadget Shop"<< endl;
	cout << setw(33) << "LOT 1851-A, Jalan KPB 6," << endl;
	cout << setw(36) << "KAWASAN PERINDUSTRIAN BELAKONG" << endl;
	cout << setw(36) << "43300 SERI KEMBANGAN, SELANGOR" << endl;
	cout << setw(33) << "(MID VALLEY SHOPPING MALL)" << endl;
	cout << setw(25) << "-INCOICE-" << endl;
	cout << "+                                         +\n";
	cout << setfill('*') << setw(30) << endl;
	cout << "---------Welcome to CSG Gadget Shop--------\n";
	cout << setfill('*') << setw(30) << endl;
	cout << setw(8) << "-Welcome to CSG Menu-" << setw(8) << endl;

	cout << left << "A ORDER ENTRY" << endl;
	cout << left << "B REPORTING" << endl;
	cout << left << "C EXIT" << endl;

	return 0;
}
