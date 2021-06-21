#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

typedef struct
{
	string json_string;
	double SOC;
	double Temperrature;
}Parameters;

typedef struct
{
	double max_SOC;
	double min_SOC;
	double max_Temperature;
	double min_Temperature;
	double average_SOC;
	double average_Temperature;
}Parameter_statistics;

typedef enum
{
	CONSOLE,
	CONTROLLER
}SENDER;
