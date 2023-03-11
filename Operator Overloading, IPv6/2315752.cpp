/*Oğuzhan Alpertürk -2315752
I read and accept the submission rules and the extra rules specified in each question. This is my own work that
is done by myself only
*/
#include "Address.h"


int main()
{
	Address a1, a2;
	cout << "CNG 242 Assignment 3\n";
	cout << "Oguzhan Alperturk - 2315752\n";
	cout << "Welcome to my solution for assignment 3\n";
	cout << "-------------------------------------------------------\n";
	cout << "For A1: \n";
	cin >> a1;
	cout << "-------------------------------------------------------\n";
	cout << "For A2: \n";
	cin >> a2;
	
	char selection[3];
	int a1ora2;
	while (1) {
		cout << "\n-------------------------------------------------------\n";
		cout << "a. Change first address (A1)\n";
		cout << "b. Change second address (A2)\n";
		cout << "1. Print result of classification\n";
		cout << "2. Print TLA ID\n";
		cout << "3. Print NLA ID\n";
		cout << "4. Print SLA ID\n";
		cout << "5. Bitwise disjunction\n";
		cout << "6. Bitwise conjuction\n";
		cout << "7. Bitwise NOR\n";
		cout << "8. Bitwise NAND\n";
		cout << "9. Bitwise XOR\n";
		cout << "10. Bitwsse XNOR\n";
		cout << "11.Copy contents of first address to another\n";
		cout << "12. Compare if A1 == A2\n";
		cout << "13. Compare if A1 != A2\n";
		cout << "14. Print Address\n";
		cout << "15.Enter an Address\n";
		cout << "0. Exit\n";
		cout << "Please Select: ";
		cin >> selection;
		cout << "\n";
		if (HelperStringComparer(selection,"a") == 0) {
			cout << "For A1: \n";
			cin >> a1;
		}
		else if (HelperStringComparer(selection, "b") == 0) {
			cout << "For A2: \n";
			cin >> a2;
		}
		else if (HelperStringComparer(selection, "1") == 0) {
			cout << "Please enter 1 for A1, 2 for A2: ";
			cin >> a1ora2;
			if (a1ora2 == 1) {
				cout << "Classification for A1 is: ";
				~a1;
			}
			else if (a1ora2 == 2) {
				cout << "Classification for A2 is: ";
				~a2;
			}
		}
		else if (HelperStringComparer(selection, "2") == 0) {
			cout << "Please enter 1 for A1, 2 for A2: ";
			cin >> a1ora2;
			if (a1ora2 == 1) {
				cout << "TLA ID of A1\n";
				!a1;
			}
			else if (a1ora2 == 2) {
				cout << "TLA ID of A2\n";
				!a2;
			}
		}
		else if (HelperStringComparer(selection, "3") == 0) {
			cout << "Please enter 1 for A1, 2 for A2: ";
			cin >> a1ora2;
			if (a1ora2 == 1) {
				cout << "NLA ID of A1\n";
				++a1;
			}
			else if (a1ora2 == 2) {
				cout << "NLA ID of A2\n";
				++a2;
			}
		}
		else if (HelperStringComparer(selection, "4") == 0) {
			cout << "Please enter 1 for A1, 2 for A2: ";
			cin >> a1ora2;
			if (a1ora2 == 1) {
				cout << "SLA ID of A1\n";
				&a1;
			}
			else if (a1ora2 == 2) {
				cout << "SLA ID of A2\n";
				&a2;
			}
		}
		else if (HelperStringComparer(selection, "5") == 0) {
			Address addr = a1 + a2;
			cout << "Result of A1 + A2;\n";
			cout << addr;
		}
		else if (HelperStringComparer(selection, "6") == 0) {
			Address addr = a1 * a2;
			cout << "Result of A1 * A2;\n";
			cout << addr;
		}
		else if (HelperStringComparer(selection, "7") == 0) {
			Address addr = a1 - a2;
			cout << "Result of A1 - A2;\n";
			cout << addr;
		}
		else if (HelperStringComparer(selection, "8") == 0) {
			Address addr = a1 / a2;
			cout << "Result of A1 / A2;\n";
			cout << addr;
		}
		else if (HelperStringComparer(selection, "9") == 0) {
			Address addr = a1 % a2;
			cout << "Result of A1 % A2;\n";
			cout << addr;
		}
		else if (HelperStringComparer(selection, "10") == 0) {
			Address addr = a1 ^ a2;
			cout << "Result of A1 ^ A2;\n";
			cout << addr;
		}
		else if (HelperStringComparer(selection, "11") == 0) {
			cout << "Creating a new object (A3)!\n";
			Address a3;
			cout << "A3 is created!\n\n";
			cout << "Contents of A3:\n";
			cout << a3;
			cout << "Contents of A1:\n";
			cout << a1;
			a3 = a1;
			cout << "After A3 = A1\nContents of A3:\n";
			cout << a3;
			cout << "Contents of A1: ";
			cout << a1;
		}
		else if (HelperStringComparer(selection, "12") == 0) {
			cout << "Result of A1 == A2: ";
			a1 == a2;
		}
		else if (HelperStringComparer(selection, "13") == 0) {
			cout << "Result of A1 != A2: ";
			a1 != a2;
		}
		else if (HelperStringComparer(selection, "14") == 0) {
			cout << "Please enter 1 for A1, 2 for A2: ";
			cin >> a1ora2;
			if (a1ora2 == 1) {
				cout << a1;
			}
			else if (a1ora2 == 2) {
				cout << a2;
			}
		}
		else if (HelperStringComparer(selection, "15") == 0) {
			cout << "Please enter 1 for A1, 2 for A2: ";
			cin >> a1ora2;
			if (a1ora2 == 1) {
				cin >> a1;
			}
			else if (a1ora2 == 2) {
				cin >> a2;
			}
		}
		else if (HelperStringComparer(selection, "0") == 0) {
			cout << "\nGoodbye!\n\n";
			break;
		}
		else {
			cout << "\nPlease enter valid command!\n\n";
		}
	}
	return 0;
}