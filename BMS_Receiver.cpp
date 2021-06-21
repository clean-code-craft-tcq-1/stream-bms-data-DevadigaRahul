#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "BMS_Receiver.h"

using boost::property_tree::ptree;

void BMS_Receiver::get_sender_data(SENDER sender)
{
	switch (sender)
	{
	case CONSOLE:
		get_data_from_console();
		break;
	case CONTROLLER:
		//out of scope
		break;
	}
}

vector<Parameters>& BMS_Receiver::get_parameter_list()
{
	return parameter_list;
}

void BMS_Receiver::get_data_from_console()
{
	string sender_data;
	
	for (int i = 0; i < 15;i++)
	{
		Parameters parameter;
		std::getline(std::cin, sender_data);
		//sender_data = "{\"Temperature\":-29.90,\"SOC\":36.91}";

		if (parse_data(sender_data, parameter))
		{
			parameter_list.push_back(parameter);
			calculate_statistics();			
		}
	}	
}

void BMS_Receiver::print_statistics()
{
	operation.print_data();
}

void BMS_Receiver::calculate_statistics()
{
	operation.perform_operation(parameter_list);		
}

BMS_operation_manager BMS_Receiver::get_operation_instance()
{
	return operation;
}

bool BMS_Receiver::parse_data(string data, Parameters &parameter)
{
	std::stringstream ss;
	ss.str(data);

	try
	{
		ptree pt;
		boost::property_tree::read_json(ss, pt);

		parameter.json_string = data;
		parameter.Temperrature = pt.get<float>("Temperature");
		parameter.SOC = pt.get<float>("SOC");
	}
	catch (std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;
}
