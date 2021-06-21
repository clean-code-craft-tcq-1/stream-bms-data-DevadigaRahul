#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <numeric>

#define NUM_OF_BATTERY_PARAMS 2

typedef enum {
	TEMP,
	SOC,
	END_OF_LIST
}batteryParamType;


class InputStreamParser
{
private : 
	int m_lineNum = 0; 
	std::vector<float> streamParamVec = {0.0,0.0};
public:
	int getLineNum();
	void parseStreamInputLine(std::string);
	std::vector<float> getParsedParamVec();
};

class BMSDataStreamReceiver
{
private:
	InputStreamParser parserObj;
	std::vector<float> inputParamVec;
	std::vector<float> batteryParamMinVec{0.0,0.0}, batteryParamMaxVec{0.0,0.0}, runningAvg{0.0,0.0};
	std::map<batteryParamType, std::vector<float>> runningLastFiveInputMap =
	{
		{TEMP , {}},
		{SOC , {}}
	};
public:
	void processInputDataStream(std::string);
	void findMaxOfRxStream(float*, float*);
	void findMinOfRxStream(float*, float*);
	void calcRunningAvg();
	std::vector<float> getStreamMinofParams();
	std::vector<float> getStreamMaxofParams();
	std::vector<float> getRunningAvgofParam();
};