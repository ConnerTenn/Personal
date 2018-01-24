
#include "classes.h"


Element::Element(ElementType type) :
	Type(type)
{
}


Operator::Operator(Operations operation) :
	Element(OPERATOR), Operation(operation)
{
}


Measurement Sin(Measurement other)
{
	return Measurement(sin(other.Value), abs(sin(other.Value + other.Uncertainty) - sin(other.Value - other.Uncertainty)) / 2.0);
}

Measurement Cos(Measurement other)
{
	return Measurement(cos(other.Value), abs(cos(other.Value + other.Uncertainty) - cos(other.Value - other.Uncertainty)) / 2.0);
}

Measurement Sqrt(Measurement other)
{
	return Measurement(sqrt(other.Value), sqrt(other.Value) * 0.5 * (other.Uncertainty / other.Value));
	//pow(Value, other.Value) * abs(other.Value) * (Uncertainty / Value);
	//return Measurement(sqrt(other.Value), sqrt(other.Value + other.Uncertainty) - sqrt(other.Value - other.Uncertainty) / 2.0);
}

Coefficient Sin(Coefficient other)
{
	return Coefficient(sin(other.Value));
}

Coefficient Cos(Coefficient other)
{
	return Coefficient(cos(other.Value));
}

Coefficient Sqrt(Coefficient other)
{
	return Coefficient(sqrt(other.Value));
}


Measurement::Measurement(double value, double uncertainty) :
	Element(MEASUREMENT), Value(value), Uncertainty(uncertainty)
{
}

Measurement Measurement::operator+(Measurement other)
{
	return Measurement(Value + other.Value, Uncertainty + other.Uncertainty);
}

Measurement Measurement::operator-(Measurement other)
{
	return Measurement(Value - other.Value, Uncertainty + other.Uncertainty);
}

Measurement Measurement::operator*(Measurement other)
{
	return Measurement(Value * other.Value, Value * other.Value * (Uncertainty / Value + other.Uncertainty / other.Value));
}

Measurement Measurement::operator/(Measurement other)
{
	return Measurement(Value / other.Value, (Value / other.Value) * (Uncertainty / Value + other.Uncertainty / other.Value));
}

Measurement Measurement::operator+(Coefficient other)
{
	return Measurement(Value + other.Value, Uncertainty);
}

Measurement Measurement::operator-(Coefficient other)
{
	return Measurement(Value - other.Value, Uncertainty);
}

Measurement Measurement::operator*(Coefficient other)
{
	return Measurement(Value * other.Value, Uncertainty * other.Value);
}

Measurement Measurement::operator/(Coefficient other)
{
	return Measurement(Value / other.Value, Uncertainty * other.Value);
}

Measurement Measurement::Pow(Coefficient other)
{
	return Measurement(pow(Value, other.Value), pow(Value, other.Value) * abs(other.Value) * (Uncertainty / Value));
}

std::string Measurement::operator+(std::string following)
{
	return std::to_string(Value) + "+-" + std::to_string(Uncertainty) + following;
}

std::string Measurement::print()
{
	int valuePower = floor(log10(Value));
	double valueValue = Value / pow(10, valuePower);
	int uncertaintyPower = floor(log10(Uncertainty));
	double uncertaintyValue = Uncertainty / pow(10, uncertaintyPower);
	return std::to_string(valueValue) + "*10^" + std::to_string(valuePower) + " +- " + std::to_string(uncertaintyValue) + "*10^" + std::to_string(uncertaintyPower);
	//return std::to_string(Value) + "+-" + std::to_string(Uncertainty);
}


Coefficient::Coefficient(double value) :
	Element(COEFFICIENT), Value(value)
{
}

Coefficient Coefficient::operator+(Coefficient other)
{
	return Coefficient(Value + other.Value);
}

Coefficient Coefficient::operator-(Coefficient other)
{
	return Coefficient(Value - other.Value);
}

Coefficient Coefficient::operator*(Coefficient other)
{
	return Coefficient(Value * other.Value);
}

Coefficient Coefficient::operator/(Coefficient other)
{
	return Coefficient(Value / other.Value);
}

Measurement Coefficient::operator+(Measurement other)
{
	return Measurement(Value + other.Value, other.Uncertainty);
}

Measurement Coefficient::operator-(Measurement other)
{
	return Measurement(Value - other.Value, other.Uncertainty);
}

Measurement Coefficient::operator*(Measurement other)
{
	return Measurement(Value * other.Value, Value * other.Uncertainty);
}

Measurement Coefficient::operator/(Measurement other)
{
	//return Measurement(Value / other.Value, Value * other.Uncertainty);//fix: Uncertainty = Coefficient * pow(Measurement,-1)
	return Measurement(Value / other.Value, Value * other.Pow(-1).Uncertainty);
}

Coefficient Coefficient::Pow(Coefficient other)
{
	return Coefficient(pow(Value, other.Value));
}

std::string Coefficient::operator+(std::string following)
{
	return std::to_string(Value) + following;
}

std::string Coefficient::print()
{
	int valuePower = floor(log10(Value));
	double valueValue = Value / pow(10, valuePower);
	return std::to_string(valueValue) + "*10^" + std::to_string(valuePower);
	//return std::to_string(Value);
}

