#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "structure.h"


using namespace std;

class BMS_Receiver
{

	vector<Parameters> parameter_list;
	vector<Parameters> _parameter_list;
	Parameter_data stat;
	
		
public:

	vector<Parameters>& get_parameter_list();
	void get_data_from_console();
	void print_statistics();
	BMS_Receiver get_operation_instance();
	bool parse_data(string data, Parameters& parameter);
	void calculate_statistics();
	void calculate_min_max();
	void calculate_moving_average();
	void print_data();
	void perform_operation(vector<Parameters> parameter_list);
	Parameter_data get_statitics();

};
