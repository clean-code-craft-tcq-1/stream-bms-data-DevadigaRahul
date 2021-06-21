#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "BMS_operation_manager.h"


void BMS_operation_manager::calculate_min_max()
{
	auto minmax = std::minmax_element(begin(_parameter_list), end(_parameter_list),
		[](Parameters const& s1, Parameters const& s2)
	{
		return s1.SOC < s2.SOC;
	});

	stat.min_SOC = minmax.first->SOC;
	stat.max_SOC = minmax.second->SOC;

	minmax = std::minmax_element(begin(_parameter_list), end(_parameter_list),
		[](Parameters const& s1, Parameters const& s2)
	{
		return s1.Temperrature < s2.Temperrature;
	});

	stat.min_Temperature = minmax.first->Temperrature;
	stat.max_Temperature = minmax.second->Temperrature;
}

void BMS_operation_manager::calculate_moving_average()
{
	float sum_soc = 0,sum_temperature = 0;
	
	int size = _parameter_list.size();
	int count = size;
	if (size > 5)
		count = 5;

	for (int index = size - 1;(index >= (size - count)); index--)
	{
		sum_soc += _parameter_list[index].SOC;
		sum_temperature += _parameter_list[index].Temperrature;
	}

	stat.average_SOC = sum_soc / count;
	stat.average_Temperature = sum_temperature / count;
}

void BMS_operation_manager::print_data()
{
	cout << "---Performance statistics---\n";
	cout << "----------------------------\n";
	cout << "Min Temperature: " << stat.min_Temperature << "\n";
	cout << "Max Temperature: " << stat.max_Temperature << "\n";
	cout << "Min SOC: " << stat.min_SOC << "\n";
	cout << "Max SOC: " << stat.max_SOC << "\n";
	cout << "Moving Average Temperature: " << stat.average_Temperature << "\n";
	cout << "Moving Average SOC: " << stat.average_SOC << "\n\n";

}

void BMS_operation_manager::perform_operation(vector<Parameters> parameter_list)
{
	_parameter_list.clear();
	_parameter_list = parameter_list;

	calculate_min_max();
	calculate_moving_average();

}

Parameter_statistics BMS_operation_manager::get_statitics()
{
	return stat;
}
