#include <iostream>
#include "BMS_Receiver.h"
using namespace std;

int main()
{
	BMS_Receiver receiver;	
	receiver.get_data_from_console();
	receiver.print_data();

	return 0;
}


