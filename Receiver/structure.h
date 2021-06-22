#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

typedef struct
{
	double SOC;
	double Temperature;
}Parameters;

typedef struct
{
	double max_SOC;
	double min_SOC;
	double max_Temperature;
	double min_Temperature;
	double average_SOC;
	double average_Temperature;
}Parameter_data;

