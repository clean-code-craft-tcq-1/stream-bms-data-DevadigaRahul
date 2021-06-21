#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "../bms-stream-receiver/bms-stream-receiver.h"
#include <vector>

TEST_CASE("Test Stream Parser : Extracted data ") {

	InputStreamParser parserObj;
	std::vector<float> paramVec;
	std::string line = "{ 'temp' : 1.1 , 'soc' : 2.2 }";
	parserObj.parseStreamInputLine(line);
	paramVec = parserObj.getParsedParamVec();
	REQUIRE(paramVec[0] == 1.1f);
	REQUIRE(paramVec[1] == 2.2f);
}

TEST_CASE("Test Stream Parser  : Test Line number ") {

	InputStreamParser parserObj;
	std::vector<float> paramVec;
	std::string line1 = "{ 'temp' : 1.1 , 'soc' : 2.2 } ";
	std::string line2 = "{ 'temp' : 3.3 , 'soc' : 4.4 } ";
	parserObj.parseStreamInputLine(line1);
	parserObj.parseStreamInputLine(line2);
	REQUIRE(parserObj.getLineNum() == 2);
}

TEST_CASE("Test Stream Processor  : Test value Min ") {

	BMSDataStreamReceiver bmsStreamRxObj;
	std::vector<float> outVec;
	std::string line1 = "{ 'temp' : 1.1 , 'soc' : 2.2 } ";
	std::string line2 = "{ 'temp' : 3.3 , 'soc' : 4.4 } ";
	bmsStreamRxObj.processInputDataStream(line1);
	bmsStreamRxObj.processInputDataStream(line2);
	outVec = bmsStreamRxObj.getStreamMinofParams();
	REQUIRE(outVec[0]== 1.1f);
	REQUIRE(outVec[1] == 2.2f);
}

TEST_CASE("Test Stream Processor  : Test value Max ") {

	BMSDataStreamReceiver bmsStreamRxObj;
	std::vector<float> outVec;
	std::string line1 = "{ 'temp' : 1.1 , 'soc' : 2.2 } ";
	std::string line2 = "{ 'temp' : 3.3 , 'soc' : 4.4 } ";
	bmsStreamRxObj.processInputDataStream(line1);
	bmsStreamRxObj.processInputDataStream(line2);
	outVec = bmsStreamRxObj.getStreamMaxofParams();
	REQUIRE(outVec[0] == 3.3f);
	REQUIRE(outVec[1] == 4.4f);
}

TEST_CASE("Test Stream Processor  : Test Running average of last 5 ") {

	BMSDataStreamReceiver bmsStreamRxObj;
	std::vector<float> outVec;
	std::vector<std::string> inputStreamVec{ "{ 'temp' : 1.0 , 'soc' : 10.0 } "  , "{ 'temp' : 2.0 , 'soc' : 11.0 } "  , "{ 'temp' : 3.0 , 'soc' : 12.0 } " , "{ 'temp' : 3.0 , 'soc' : 12.0 } ",
										"{ 'temp' : 2.0 , 'soc' : 11.0 } ","{ 'temp' : 1.0 , 'soc' : 10.0 } " };

	for (const auto &line : inputStreamVec)
	{
		bmsStreamRxObj.processInputDataStream(line);
	}
	

	outVec = bmsStreamRxObj.getRunningAvgofParam();
	REQUIRE(outVec[0] == 2.2f);
	REQUIRE(outVec[1] == 11.2f);
}
