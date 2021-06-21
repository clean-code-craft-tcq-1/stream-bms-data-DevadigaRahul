#include "bms-stream-receiver.h"

 void InputStreamParser::parseStreamInputLine(std::string line)
{
    const std::string fl_digits = "0123456789.";

    std::vector<std::string> strCommaDelimit;

    std::stringstream ss(line);

    /*Increase lilne number*/
    m_lineNum++;

    /* splits the string based on comma as delimiter */
    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        strCommaDelimit.push_back(substr);
    }

    /* Extracts the float numbers from each sub-string*/
    float tempNum = 0.0;
    for (size_t i = 0; i < strCommaDelimit.size(); i++)
    {
        unsigned ipos = strCommaDelimit[i].find_first_of(fl_digits);
        if (ipos != std::string::npos)
        {
            std::stringstream(strCommaDelimit[i].substr(ipos)) >> tempNum;
            streamParamVec[i] = tempNum;
        }
        else std::cout << "No number found\n";
    }

}

 std::vector<float>  InputStreamParser::getParsedParamVec()
 {
     return streamParamVec;
 }

int InputStreamParser::getLineNum()
{
    return m_lineNum;
}

void BMSDataStreamReceiver::findMinOfRxStream(float* currentMinVal, float* newCompareVal)
{
    if (*currentMinVal > * newCompareVal)
    {
        *currentMinVal = *newCompareVal;
    }
}

void BMSDataStreamReceiver::findMaxOfRxStream(float* currentMaxVal, float* newCompareVal)
{
    if (*currentMaxVal < *newCompareVal)
    {
        *currentMaxVal = *newCompareVal;
    }
}

std::vector<float> BMSDataStreamReceiver::getStreamMinofParams()
{
    return batteryParamMinVec;
}

std::vector<float> BMSDataStreamReceiver::getStreamMaxofParams()
{
    return batteryParamMaxVec;
}

std::vector<float> BMSDataStreamReceiver::getRunningAvgofParam()
{
    return runningAvg;
}

void BMSDataStreamReceiver::calcRunningAvg()
{
    /* Iterate over the battery param type and calculate average of the imput readings. 
    Limit the average calculation to the latest 5 readings. */

    for (int paramIndex = 0; paramIndex != END_OF_LIST; paramIndex++)
    {
        runningLastFiveInputMap[static_cast<batteryParamType>(paramIndex)].push_back(inputParamVec[paramIndex]);
        if (parserObj.getLineNum() > 5)
        {
            runningLastFiveInputMap[static_cast<batteryParamType>(paramIndex)].erase(runningLastFiveInputMap[static_cast<batteryParamType>(paramIndex)].begin());
        }

        runningAvg[static_cast<batteryParamType>(paramIndex)] = std::accumulate(runningLastFiveInputMap[static_cast<batteryParamType>(paramIndex)].begin(), runningLastFiveInputMap[static_cast<batteryParamType>(paramIndex)].end(), 0.00) / runningLastFiveInputMap[static_cast<batteryParamType>(paramIndex)].size();
    }
}

void BMSDataStreamReceiver::processInputDataStream(std::string line)
{

    parserObj.parseStreamInputLine(line);
    inputParamVec = parserObj.getParsedParamVec();


    /* Find Min and Max of input stream*/
    if (parserObj.getLineNum() == 1)
    {
        batteryParamMinVec = inputParamVec;
        batteryParamMaxVec = inputParamVec;
    }
    else
    {
        for (int paramIndex = 0; paramIndex < NUM_OF_BATTERY_PARAMS; ++paramIndex)
        {
            this->findMinOfRxStream(&batteryParamMinVec[paramIndex], &inputParamVec[paramIndex]);
            this->findMaxOfRxStream(&batteryParamMaxVec[paramIndex], &inputParamVec[paramIndex]);
        }
    }

    std::cout << "====>Receiver Output :: Temp_Min = " << batteryParamMinVec[TEMP] << " : Temp_Max = " << batteryParamMaxVec[TEMP] << std::endl;
    std::cout << "====>Receiver Output :: SOC_Min  = " << batteryParamMinVec[SOC] << " : SOC_Max  = " << batteryParamMaxVec[SOC] << std::endl;

    this->calcRunningAvg();

    std::cout << "====>Receiver Output :: Latest " << runningLastFiveInputMap[TEMP].size() << " readings Running Average :  Temperature = " << runningAvg[TEMP] << " SOC = " << runningAvg[SOC] << std::endl;
}

