#include <iostream>
using namespace std;

#include "byteutil.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	string str = "sdfsdfw";
	string res = b64EncodeString(str);
	cout << res << endl;
	
	string res1 = b64DecodeString(res);
	cout << res1 << endl;
	return 0;
}
