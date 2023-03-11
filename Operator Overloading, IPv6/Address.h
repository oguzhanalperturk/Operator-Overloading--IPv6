#pragma once
#include <iostream> 
#include <cstring>
using std::ostream;
using std::istream;
using std::cin;
using std::cout;

int Nor(int, int);
int Nand(int, int);
int XNor(int, int);
char* HelperCleanDots(char*);
int Power(int, int);
int BinarytoDecimalfourDigits(int*);
int HelperStringComparer(char*, char*);


class Bin
{
public:
	int data[128];
	int size;
	Bin() {
		data[0] = 0;
		size = 0;
	}
	Bin(int* num, int s) {
		for (int i = 0;i < s;i++) {
			data[i] = num[i];
		}
		this->size = s;
	}
	void printbin() {
		int j = 1, i;
		int remainder = size % 4;
		for (i = 0;i < remainder;i++) {
			cout << data[i];
		}
		if (i != 0) {
			cout << " ";
		}
		for (;i < size;i++) {
			cout << data[i];
			if (j % 4 == 0) {
				cout << " ";
			}
			j++;
		}
	}
};

class Hex {
public:
	char value[50];
	int size;
	Hex() {
		strcpy(value, "0");
		size = 0;
	}
	Hex(char* hexnum) {
		strcpy(value, hexnum);
		size = strlen(hexnum);
	}
};


Hex BinarytoHex(Bin);
Bin HextoBinary(Hex);


class Address
{
private:
	Hex hdata;
	Bin bdata;
public:

	Address() {
		strcpy(hdata.value, "00000000000000000000000000000000");
		for (int i = 0;i < 128;i++) {
			bdata.data[i] = 0;
		}
		bdata.size = 128;
	}

	Address(Hex hex, Bin bin) {
		strcpy(hdata.value, hex.value);
		for (int i = 0;i < 128;i++) {
			bdata.data[i] = bin.data[i];
		}
		bdata.size = 128;
	}

	int IsValidAddress(char* addr) { // 1->No, 0->Yes
		char arr[18];
		strcpy(arr,"0123456789ABCDEF:");
		int test = 0;
		int length = strlen(addr);
		if (length != 39) {
			cout << "\nInvalid input! Length of input must be 39 characters!\n";
			cout << "Please re-enter:\n";
			return 1;
		}

		for (int i = 0; i < length;i++) {
			for (int j = 0;j < 17;j++) {
				if (addr[i] == arr[j]) {
					test++;
				}
			}
			if (test == 0) {
				cout << "\nInvalid input! Please only use :,0-9,A-F charactes!\n";
				cout << "Please re-enter\n";
				return 1;
			}
			else {
				test = 0;
			}
		}
		return 0;
	}
	
	/*             Operator Overloading Functions:
	------------------------------------------------------------------*/

	friend void operator ~(const Address& a) {
		int test[4];
		int decvalue;
		test[0] = 0;
		test[1] = a.bdata.data[0];
		test[2] = a.bdata.data[1];
		test[3] = a.bdata.data[2];
		decvalue = BinarytoDecimalfourDigits(test);
		if (decvalue == 0) {
			cout << "Anycast\n";
		}
		else if (decvalue == 1) {
			cout << "Unicast\n";
		}
		else if (1 < decvalue && decvalue <= 4) {
			cout << "Anycast\n";
		}
		else if (decvalue > 4) {
			cout << "Multicast\n";
		}
	}

	friend void operator !(const Address& a) {
		Bin bnum;
		bnum.size = 13;
		int j = 0;
		for (int i = 3;i < 16;i++) {
			bnum.data[j] = a.bdata.data[i];
			j++;
		}

		cout << "Hexadecimal: ";
		cout << BinarytoHex(bnum).value << "\n";
		cout << "Binary: ";
		bnum.printbin();
		cout << "\n";
	}

	friend void operator ++(const Address& a) {
		Bin bnum;
		bnum.size = 24;
		int j = 0;
		for (int i = 24;i < 48;i++) {
			bnum.data[j] = a.bdata.data[i];
			j++;
		}

		cout << "Hexadecimal: ";
		cout << BinarytoHex(bnum).value << "\n";
		cout << "Binary: ";
		bnum.printbin();
		cout << "\n";
	}

	friend void operator &(const Address& a) {
		Bin bnum;
		bnum.size = 16;
		int j = 0;
		for (int i = 48;i < 64;i++) {
			bnum.data[j] = a.bdata.data[i];
			j++;
		}

		cout << "Hexadecimal: ";
		cout << BinarytoHex(bnum).value << "\n";
		cout << "Binary: ";
		bnum.printbin();
		cout << "\n";
	}

	friend Address operator +(const Address& a,const Address& b) {
		Address addr;
		addr.bdata.size = 128;
		for (int i = 0;i < 64;i++) {
			addr.bdata.data[i] = a.bdata.data[i];
		}
		for (int i = 64;i < 128;i++) {
			addr.bdata.data[i] = a.bdata.data[i] | b.bdata.data[i];
		}
		strcpy(addr.hdata.value, BinarytoHex(addr.bdata).value);
		return addr;
	}

	friend Address operator *(const Address& a, const Address& b) {
		Address addr;
		addr.bdata.size = 128;
		for (int i = 0;i < 64;i++) {
			addr.bdata.data[i] = a.bdata.data[i];
		}
		for (int i = 64;i < 128;i++) {
			addr.bdata.data[i] = a.bdata.data[i] & b.bdata.data[i];
		}
		strcpy(addr.hdata.value, BinarytoHex(addr.bdata).value);
		return addr;
	}

	friend Address operator -(const Address& a, const Address& b) {
		Address addr;
		addr.bdata.size = 128;
		for (int i = 0;i < 64;i++) {
			addr.bdata.data[i] = a.bdata.data[i];
		}
		for (int i = 64;i < 128;i++) {
			addr.bdata.data[i] = Nor(a.bdata.data[i],b.bdata.data[i]);
		}
		strcpy(addr.hdata.value, BinarytoHex(addr.bdata).value);
		return addr;
	}

	friend Address operator /(const Address& a, const Address& b) {
		Address addr;
		addr.bdata.size = 128;
		for (int i = 0;i < 64;i++) {
			addr.bdata.data[i] = a.bdata.data[i];
		}
		for (int i = 64;i < 128;i++) {
			addr.bdata.data[i] = Nand(a.bdata.data[i], b.bdata.data[i]);
		}
		strcpy(addr.hdata.value, BinarytoHex(addr.bdata).value);
		return addr;
	}

	friend Address operator %(const Address& a, const Address& b) {
		Address addr;
		addr.bdata.size = 128;
		for (int i = 0;i < 64;i++) {
			addr.bdata.data[i] = a.bdata.data[i];
		}
		for (int i = 64;i < 128;i++) {
			addr.bdata.data[i] = a.bdata.data[i] ^ b.bdata.data[i];
		}
		strcpy(addr.hdata.value, BinarytoHex(addr.bdata).value);
		return addr;
	}

	friend Address operator ^(const Address& a, const Address& b) {
		Address addr;
		addr.bdata.size = 128;
		for (int i = 0;i < 64;i++) {
			addr.bdata.data[i] = a.bdata.data[i];
		}
		for (int i = 64;i < 128;i++) {
			addr.bdata.data[i] = XNor(a.bdata.data[i],b.bdata.data[i]);
		}
		strcpy(addr.hdata.value, BinarytoHex(addr.bdata).value);
		return addr;
	}
	
	Address& operator =(const Address& a) {
		hdata.size = a.hdata.size;
		strcpy(hdata.value, a.hdata.value);
		bdata.size = a.bdata.size;
		for (int i = 0;i < a.bdata.size;i++) {
			bdata.data[i] = a.bdata.data[i];
		}
		return *this;
	}

	bool operator ==(const Address& a) {
		int flag = 0,control = 0,fp = 0,tla=0,res=0,nla=0,sla=0,interf=0;
		for (int i = 0;i < 128;i++) {
			if (bdata.data[i] != a.bdata.data[i]) {
				flag += 1;
			}
			if (i == 2) {
				if (flag == 0) {
					fp++;
				}
				control = flag;
			}
			else if (i == 15) {
				if (flag == control) {
					tla++;
				}
				control = flag;
			}
			else if (i == 23) {
				if (flag == control) {
					res++;
				}
				control = flag;
			}
			else if (i == 47) {
				if (flag == control) {
					nla++;
				}
				control = flag;
			}
			else if (i == 63) {
				if (flag == control) {
					sla++;
				}
				control = flag;
			}
			else if (i == 127) {
				if (flag == control) {
					interf++;
				}
				control = flag;
			}
		}
		if (flag == 0) {
			cout << "true\n";
		}
		else {
			cout << "false\n";
		}
		cout << "Same sections:\n";
		if (fp != 0) {
			cout << "FP\n";
		}
		if (tla != 0) {
			cout << "TLA\n";
		}
		if (res != 0) {
			cout << "Res\n";
		}
		if (nla != 0) {
			cout << "NLA\n";
		}
		if (sla != 0) {
			cout << "SLA\n";
		}
		if (interf != 0) {
			cout << "Interface\n";
		}

		return (flag == 0);
	}

	bool operator !=(const Address& a) {
		int flag = 0, control = 0, fp = 0, tla = 0, res = 0, nla = 0, sla = 0, interf = 0;
		for (int i = 0;i < 128;i++) {
			if (bdata.data[i] != a.bdata.data[i]) {
				flag += 1;
			}
			if (i == 2) {
				if (flag == 0) {
					fp++;
				}
				control = flag;
			}
			else if (i == 15) {
				if (flag == control) {
					tla++;
				}
				control = flag;
			}
			else if (i == 23) {
				if (flag == control) {
					res++;
				}
				control = flag;
			}
			else if (i == 47) {
				if (flag == control) {
					nla++;
				}
				control = flag;
			}
			else if (i == 63) {
				if (flag == control) {
					sla++;
				}
				control = flag;
			}
			else if (i == 127) {
				if (flag == control) {
					interf++;
				}
				control = flag;
			}
		}
		if (flag == 0) {
			cout << "false\n";
		}
		else {
			cout << "true\n";
		}
		cout << "Different sections:\n";
		if (fp == 0) {
			cout << "FP\n";
		}
		if (tla == 0) {
			cout << "TLA\n";
		}
		if (res == 0) {
			cout << "Res\n";
		}
		if (nla == 0) {
			cout << "NLA\n";
		}
		if (sla == 0) {
			cout << "SLA\n";
		}
		if (interf == 0) {
			cout << "Interface\n";
		}

		if (flag == 0) {
			return false;
		}
		else {
			return true;
		}
	}

	friend ostream& operator <<(ostream& o, const Address& a) {
		o << "\nHexadecimal\n";
		int j = 1;
		for (int i = 0;;i++) {
			if (a.hdata.value[i] == '\0') {
				break;
			}
			o << a.hdata.value[i];
			if (j % 4 == 0 && j != 32) {
				o << ":";
			}
			j++;
		}
		o << "\n\n";
		o << "Binary\nFP,TLA,Res,NLA,SLA\n";
		j = 1;
		int i;
		int remainder = a.bdata.size % 4;
		for (i = 0;i < remainder;i++) {
			o << a.bdata.data[i];
		}
		if (i != 0) {
			o << " ";
		}
		for (;i < a.bdata.size;i++) {
			o << a.bdata.data[i];
			if (j % 4 == 0) {
				if (j == 16 || j == 32 || j == 48 || j == 80 || j == 96 || j == 112) {
					o << ":";
				}
				else if (j == 64) {
					o << "\nInterface Identifier\n";
				}
				else {
					o << " ";
				}
			}
			j++;
		}
		o << "\n\n";
		return o;
	}

	friend istream& operator >>(istream& i, Address& a) {
		cout << "Please enter the Address in Hexadecimal,\nseperated with ':' every 4 digits: \n";
		i >> a.hdata.value;
		while (1) {
			if (a.IsValidAddress(a.hdata.value) == 1) {
				i >> a.hdata.value;
			}
			else {
				break;
			}
		}
		char* newaddr = HelperCleanDots(a.hdata.value);
		strcpy(a.hdata.value, newaddr);
		delete[] newaddr;
		a.bdata = HextoBinary(a.hdata);
		cout << "\nSuccessfully created!\n";
		cout << "-------------------------------------------------------\n\n";

		return i;
	}
};



/*----------------------------------Helper Functions-----------------------------------------*/

int Nor(int val1, int val2) {
	int result = val1 | val2;
	if (result == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int Nand(int val1, int val2) {
	int result = val1 & val2;
	if (result == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int XNor(int val1, int val2) {
	int result = val1 ^ val2;
	if (result == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

char* HelperCleanDots(char* addr) {
	char* newaddr = new char[50];
	int j = 0;
	for (int i = 0;;i++) {
		if (addr[i] == '\0') {
			break;
		}
		if (addr[i] != ':') {
			newaddr[j] = addr[i];
			j++;
		}
	}
	newaddr[j] = '\0';

	return newaddr;
}

int Power(int a, int b) {
	int val = 1;
	for (int i = 0;i < b;i++) {
		val *= a;
	}
	return val;
}

int BinarytoDecimalfourDigits(int* arr) {
	int val = 0;
	val = (arr[0] * Power(2, 3)) + (arr[1] * Power(2, 2)) + (arr[2] * Power(2, 1)) + (arr[3] * 1);

	return val;
}

Hex BinarytoHex(Bin b) {
	int i = 0, j = 0, flag = 0;;
	int decimal;
	Hex hexnum;
	int adjust[4] = { 0,0,0,0 };
	if ((b.size % 4) != 0) {
		flag = 1;
		if ((b.size % 4) == 1) {
			adjust[0] = 0;
			adjust[1] = 0;
			adjust[2] = 0;
			adjust[3] = b.data[0];
			i = 1;
		}
		else if ((b.size % 4) == 2) {
			adjust[0] = 0;
			adjust[1] = 0;
			adjust[2] = b.data[0];
			adjust[3] = b.data[1];
			i = 2;
		}
		else if ((b.size % 4) == 3) {
			adjust[0] = 0;
			adjust[1] = b.data[0];
			adjust[2] = b.data[1];
			adjust[3] = b.data[2];
			i = 3;
		}
	}

	while (i < b.size) {

		if (flag == 0) {
			adjust[0] = b.data[i];
			adjust[1] = b.data[i + 1];
			adjust[2] = b.data[i + 2];
			adjust[3] = b.data[i + 3];
			i += 4;
		}
		else {
			flag = 0;
		}

		decimal = BinarytoDecimalfourDigits(adjust);

		if (decimal == 0) {
			hexnum.value[j] = '0';
		}
		else if (decimal == 1) {
			hexnum.value[j] = '1';
		}
		else if (decimal == 2) {
			hexnum.value[j] = '2';
		}
		else if (decimal == 3) {
			hexnum.value[j] = '3';
		}
		else if (decimal == 4) {
			hexnum.value[j] = '4';
		}
		else if (decimal == 5) {
			hexnum.value[j] = '5';
		}
		else if (decimal == 6) {
			hexnum.value[j] = '6';
		}
		else if (decimal == 7) {
			hexnum.value[j] = '7';
		}
		else if (decimal == 8) {
			hexnum.value[j] = '8';
		}
		else if (decimal == 9) {
			hexnum.value[j] = '9';
		}
		else if (decimal == 10) {
			hexnum.value[j] = 'A';
		}
		else if (decimal == 11) {
			hexnum.value[j] = 'B';
		}
		else if (decimal == 12) {
			hexnum.value[j] = 'C';
		}
		else if (decimal == 13) {
			hexnum.value[j] = 'D';
		}
		else if (decimal == 14) {
			hexnum.value[j] = 'E';
		}
		else if (decimal == 15) {
			hexnum.value[j] = 'F';
		}
		j++;
	}
	hexnum.value[j] = '\0';

	return hexnum;
}

Bin HextoBinary(Hex h) {
	Bin num;
	int length = strlen(h.value);
	int i, j = 0;
	for (i = 0;i < length;i++) {
		if (h.value[i] == '\0') {
			break;
		}
		else if (h.value[i] == '0') {
			num.data[j] = 0;
			num.data[j + 1] = 0;
			num.data[j + 2] = 0;
			num.data[j + 3] = 0;
		}
		else if (h.value[i] == '1') {
			num.data[j] = 0;
			num.data[j + 1] = 0;
			num.data[j + 2] = 0;
			num.data[j + 3] = 1;
		}
		else if (h.value[i] == '2') {
			num.data[j] = 0;
			num.data[j + 1] = 0;
			num.data[j + 2] = 1;
			num.data[j + 3] = 0;
		}
		else if (h.value[i] == '3') {
			num.data[j] = 0;
			num.data[j + 1] = 0;
			num.data[j + 2] = 1;
			num.data[j + 3] = 1;
		}
		else if (h.value[i] == '4') {
			num.data[j] = 0;
			num.data[j + 1] = 1;
			num.data[j + 2] = 0;
			num.data[j + 3] = 0;
		}
		else if (h.value[i] == '5') {
			num.data[j] = 0;
			num.data[j + 1] = 1;
			num.data[j + 2] = 0;
			num.data[j + 3] = 1;
		}
		else if (h.value[i] == '6') {
			num.data[j] = 0;
			num.data[j + 1] = 1;
			num.data[j + 2] = 1;
			num.data[j + 3] = 0;
		}
		else if (h.value[i] == '7') {
			num.data[j] = 0;
			num.data[j + 1] = 1;
			num.data[j + 2] = 1;
			num.data[j + 3] = 1;
		}
		else if (h.value[i] == '8') {
			num.data[j] = 1;
			num.data[j + 1] = 0;
			num.data[j + 2] = 0;
			num.data[j + 3] = 0;
		}
		else if (h.value[i] == '9') {
			num.data[j] = 1;
			num.data[j + 1] = 0;
			num.data[j + 2] = 0;
			num.data[j + 3] = 1;
		}
		else if (h.value[i] == 'A') {
			num.data[j] = 1;
			num.data[j + 1] = 0;
			num.data[j + 2] = 1;
			num.data[j + 3] = 0;
		}
		else if (h.value[i] == 'B') {
			num.data[j] = 1;
			num.data[j + 1] = 0;
			num.data[j + 2] = 1;
			num.data[j + 3] = 1;
		}
		else if (h.value[i] == 'C') {
			num.data[j] = 1;
			num.data[j + 1] = 1;
			num.data[j + 2] = 0;
			num.data[j + 3] = 0;
		}
		else if (h.value[i] == 'D') {
			num.data[j] = 1;
			num.data[j + 1] = 1;
			num.data[j + 2] = 0;
			num.data[j + 3] = 1;
		}
		else if (h.value[i] == 'E') {
			num.data[j] = 1;
			num.data[j + 1] = 1;
			num.data[j + 2] = 1;
			num.data[j + 3] = 0;
		}
		else if (h.value[i] == 'F') {
			num.data[j] = 1;
			num.data[j + 1] = 1;
			num.data[j + 2] = 1;
			num.data[j + 3] = 1;
		}
		j += 4;
		num.size += 4;
	}
	return num;
}

int HelperStringComparer(char* str1, char* str2) { // 0-> Equal, 1-> Not Equal
	if (strlen(str1) != strlen(str2)) {
		return 1;
	}
	int flag = 0;
	for (int i = 0;;i++) {
		if (str1[i] == '\0' || str2[i] == '\0') {
			break;
		}
		else {
			if (str1[i] != str2[i]) {
				flag = 1;
			}
		}
	}
	if (flag == 0) {
		return 0;
	}
	else {
		return 1;
	}
}