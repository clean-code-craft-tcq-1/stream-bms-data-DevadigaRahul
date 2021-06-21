#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "BMS_Receiver.h"

using boost::property_tree::ptree;



void BMS_Receiver::get_data_from_console()
{
	string sender_data;
	
	for (int i = 0; i < 15;i++)
	{
		Parameters parameter;
		std::getline(std::cin, sender_data);
		
		//cout<<sender_data<<endl;
		if (parse_data(sender_data, parameter))
		{
			parameter_list.push_back(parameter);
			calculate_statistics();			
		}
	}	
}

void BMS_Receiver::print_statistics()
{
	print_data();
}

void BMS_Receiver::calculate_statistics()
{
	perform_operation(parameter_list);		
}

BMS_Receiver BMS_Receiver::get_operation_instance()
{
	BMS_Receiver obj;
	return obj;
}
vector<Parameters>& BMS_Receiver::get_parameter_list()
{
	return parameter_list;
}
Parameter_data BMS_Receiver::get_statitics()
{
	return stat;
}

bool BMS_Receiver::parse_data(string data, Parameters &parameter)
{
	std::stringstream ss;
	ss.str(data);

	try
	{
		ptree pt;
		boost::property_tree::read_json(ss, pt);

		parameter.Temperature = pt.get<float>("Temperature");
		parameter.SOC = pt.get<float>("SOC");
	}
	catch (std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;
}


void BMS_Receiver::calculate_min_max()
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
		return s1.Temperature < s2.Temperature;
	});

	stat.min_Temperature = minmax.first->Temperature;
	stat.max_Temperature = minmax.second->Temperature;
	//cout<<"stat.min_Temperature="<<stat.min_Temperature<<endl;
	//cout<<"stat.max_Temperature="<<stat.max_Temperature<<endl;
}

void BMS_Receiver::calculate_moving_average()
{
	float sum_soc = 0,sum_temperature = 0;
	
	int size = _parameter_list.size();
	int count = size;
	if (size > 5)
		count = 5;

	for (int index = size - 1;(index >= (size - count)); index--)
	{
		sum_soc += _parameter_list[index].SOC;
		sum_temperature += _parameter_list[index].Temperature;
	}

	stat.average_SOC = sum_soc / count;
	stat.average_Temperature = sum_temperature / count;
	//cout<<"stat.average_SOC="<<stat.average_SOC<<endl;
	//cout<<"stat.average_Temperature="<<stat.average_Temperature<<endl;
}

void BMS_Receiver::print_data()
{

	cout << "Minimum Temperature: " << stat.min_Temperature << "\n";
	cout << "Maximum Temperature: " << stat.max_Temperature << "\n";
	cout << "Minimum SOC: " << stat.min_SOC << "\n";
	cout << "Maximum SOC: " << stat.max_SOC << "\n";
	cout << "Moving Average Temperature: " << stat.average_Temperature << "\n";
	cout << "Moving Average SOC: " << stat.average_SOC << "\n\n";

}

void BMS_Receiver::perform_operation(vector<Parameters> parameter_list)
{
	//cout<<"perform_operation"<<endl;
	_parameter_list.clear();
	_parameter_list = parameter_list;

	calculate_min_max();
	calculate_moving_average();

}

