#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "defines.h"
#include "BMS_operation_manager.h"

using namespace std;

class BMS_Receiver
{
	BMS_operation_manager operation;
	vector<Parameters> parameter_list;
		
public:
	vector<Parameters>& get_parameter_list();
	void get_data_from_console();
	void print_statistics();
	BMS_operation_manager get_operation_instance();
	bool parse_data(string data, Parameters& parameter);
	void calculate_statistics();
	void get_sender_data(SENDER sender);
};
