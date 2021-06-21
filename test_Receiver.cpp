#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../test/catch.hpp"
#include "BMS_Receiver.h"
#include <cmath>

string dummy_data[6] = {"{\"Temperature\":-32,\"SOC\" : 36}",
						"{\"Temperature\":-36,\"SOC\" : 66}", 
						"{\"Temperature\":-28,\"SOC\" : 51}", 
						"{\"Temperature\":-46,\"SOC\" : 26}", 
						"{\"Temperature\":-52,\"SOC\" : 29}", 
						"{\"Temperature\":-24,\"SOC\" : 33}"};

bool compare_float(float x, float y, float epsilon = 0.01f) {
	if (fabs(x - y) < epsilon)
		return true; 
	return false; 
}
TEST_CASE("validate sender data")
{
	BMS_Receiver receiver;
	Parameters _parameter;
	
	for (int i = 0;i < 6;i++)
	{
		REQUIRE(receiver.parse_data(dummy_data[i], _parameter));
		auto& list = receiver.get_parameter_list();
		list.push_back(_parameter);		
	}

	//validate list size
	REQUIRE(receiver.get_parameter_list().size() == 6);

	receiver.calculate_statistics();
	auto stat = receiver.get_operation_instance().get_statitics();

	//positive test cases - validate paramters with expected output after calculation
	REQUIRE(compare_float(stat.min_SOC , 26.0));
	REQUIRE(compare_float(stat.max_SOC , 66.0));
	REQUIRE(compare_float(stat.min_Temperature , -52.0));
	REQUIRE(compare_float(stat.max_Temperature , -24.0));
	REQUIRE(compare_float(stat.average_SOC , 41.0));
	REQUIRE(compare_float(stat.average_Temperature, -37.2));

	//Negative test by injecting inappropriate json format
	REQUIRE(!receiver.parse_data("aa bb cc", _parameter));
	REQUIRE(!receiver.parse_data("{\"Temperature:-32,\"SOC\" : 36}", _parameter));
	REQUIRE(!receiver.parse_data("{\"Temperature:one,\"SOC\" : two}", _parameter));
}
