#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../BMS_Receiver.h"
#include <cmath>



bool compare_float(float x, float y, float epsilon = 0.01f) {
	if (fabs(x - y) < epsilon)
		return true; 
	return false; 
}

string test_data[4] = {"{\"Temperature\":-22,\"SOC\" : 16}",
						"{\"Temperature\":-26,\"SOC\" : 56}", 
						"{\"Temperature\":-38,\"SOC\" : 31}",  
						"{\"Temperature\":-84,\"SOC\" : 63}"};


TEST_CASE("validate sender data")
{
	BMS_Receiver receiver;
	Parameters _parameter;
	
	for (int i = 0;i < 6;i++)
	{
		REQUIRE(receiver.parse_data(test_data[i], _parameter));
		auto& list = receiver.get_parameter_list();
		list.push_back(_parameter);		
	}

	REQUIRE(receiver.get_parameter_list().size() == 6);

	receiver.calculate_statistics();
	auto stat = receiver.get_operation_instance().get_statitics();

	//positive test cases 
	REQUIRE(compare_float(stat.min_SOC , 16.0));
	REQUIRE(compare_float(stat.max_SOC , 63.0));
	REQUIRE(compare_float(stat.min_Temperature , -52.0));


	//Negative test 
	REQUIRE(!receiver.parse_data("aa bb cc", _parameter));
	REQUIRE(!receiver.parse_data("{\"Temperature:-26,\"SOC\" : 56}", _parameter));
	REQUIRE(!receiver.parse_data("{\"Temperature:one,\"SOC\" : two}", _parameter));
}
