
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <math.h>


enum ParseState
{
	ParseNull,
	ParseMeasurement,
	ParseMeasurementWhitespace,
	ParseUncertainty,
	ParseUncertaintyWhitespace,
	ParseUncertaintyPercent,
	ParseOperator,
	ParseOperatorWhitespace,
};

enum ElementType
{
	OPERATOR,
	MEASUREMENT,
	COEFFICIENT,
};

enum Operations
{
	NOP,
	ADD,
	SUB,
	MUL,
	DIV,
	OBR,//open bracket
	CBR,//close bracket
	POW,
};


class Operator;
class Measurement;
class Coefficient;

class Element
{
public:

	ElementType Type;

	Element(ElementType type);
};

class Operator : Element
{
public:

	Operations Operation;

	Operator(Operations operation);
};


Measurement Sin(Measurement other);

Measurement Cos(Measurement other);

Measurement Sqrt(Measurement other);

Coefficient Sin(Coefficient other);

Coefficient Cos(Coefficient other);

Coefficient Sqrt(Coefficient other);

class Measurement : Element
{
public:

	double Value = 0;
	double Uncertainty = 0;

	Measurement(double value, double uncertainty);

	Measurement operator+(Measurement other);

	Measurement operator-(Measurement other);

	Measurement operator*(Measurement other);

	Measurement operator/(Measurement other);

	Measurement operator+(Coefficient other);

	Measurement operator-(Coefficient other);

	Measurement operator*(Coefficient other);

	Measurement operator/(Coefficient other);

	Measurement Pow(Coefficient other);

	std::string operator+(std::string following);

	std::string print();
};

class Coefficient : Element
{
public:

	double Value = 0;

	Coefficient(double value);

	Coefficient operator+(Coefficient other);

	Coefficient operator-(Coefficient other);

	Coefficient operator*(Coefficient other);

	Coefficient operator/(Coefficient other);

	Measurement operator+(Measurement other);

	Measurement operator-(Measurement other);

	Measurement operator*(Measurement other);

	Measurement operator/(Measurement other);
	
	Coefficient Pow(Coefficient other);

	std::string operator+(std::string following);

	std::string print();
};


