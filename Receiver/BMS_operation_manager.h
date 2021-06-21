#pragma once
#include <functional>
#include "defines.h"

using namespace std;

class BMS_operation_manager
{
	vector<Parameters> _parameter_list;
	Parameter_statistics stat;

public:
	void calculate_min_max();
	void calculate_moving_average();
	void print_data();
	void perform_operation(vector<Parameters> parameter_list);
	Parameter_statistics get_statitics();
};

