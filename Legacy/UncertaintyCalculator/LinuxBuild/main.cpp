
#include "classes.h"

#define PI 3.14159265358979323
#define TAU (2.0*PI)


std::vector<Element> Equation;


int main()
{
	std::cout << "Add: " << (Measurement(1.0, 0.1) + Measurement(0.7, 0.3)).print() << "\n";
	std::cout << "Mul: " << (Measurement(1.0, 0.1) * Measurement(0.7, 0.3)).print() << "\n";
	return 0;

	bool Run = true;
	
	while (Run)
	{
		std::cout << ">";
		std::string input;
		std::getline(std::cin, input);
		input += ' ';

		//std::cout << (Measurement((Coefficient(4) * Coefficient(PI).Pow(Coefficient(2))).Value, 0) / (Measurement(0.034, 0.004))).print() << "\n";
		//std::cout << ((Coefficient(4) * Coefficient(PI).Pow(Coefficient(2))) / (Measurement(0.034, 0.004))).print() << "\n";
		//std::cout << (Coefficient(4.0/3.0) * Coefficient(PI) * Measurement(6.2, 0.05).Pow(Coefficient(3))).print() << "\n";
		//std::cout << (Measurement(12.02,0.08).Pow(Coefficient(2)) + Measurement(3.5, 0.1 * 3.5) * Measurement(2.7, 0.05)).print() << "\n";
		/*Measurement result = (
				Sqrt(
					(Measurement(0.035, 0.001).Pow(Coefficient(2)) * Measurement(0.0002, 0.0001) * Coefficient(9.81) * Sin(Measurement(0.4537856, 0.008726646)/Coefficient(2))) /
					((Coefficient(9.0)*(Coefficient(10).Pow(Coefficient(9)))) * Cos(Measurement(0.4537856, 0.008726646) / Coefficient(2)))
				)
			);*/
		std::cout << "sqrt= " << (
				(Measurement(2.59, 0.2)).Pow(Coefficient(0.5))
			).print() << "\n\n";
		std::cout << "sqrt= " << (
			Sqrt(Measurement(2.59, 0.2))
			).print() << "\n\n";
		std::cout << (
				Sqrt(
					(Measurement(0.035, 0.001).Pow(Coefficient(2)) * Measurement(0.0002, 0.0001) * Coefficient(9.81) * Sin(Measurement(0.453785605519, 0.01745329252) / Coefficient(2))) /
					((Coefficient(9.0)*(Coefficient(10).Pow(Coefficient(9)))) * Cos(Measurement(0.453785605519, 0.01745329252) / Coefficient(2)))
				)
			).print() << "\n";

		if (input == "exit")
		{
			Run = false;
		}
		else
		{
			/*double measurement = 0;
			double uncertainty = 0;
			Operations operation = NOP;
			std::string parse;
			ParseState parseState = PARSENUL;
			bool error = false;

			//for (int i = 0; i < input.length() && !error; i++)
			int i = 0;
			while (i < input.length() && !error)
			{
				char in = input[i];
				
				if (parseState == PARSENUL || parseState == PARSEWHITESPACE)
				{
					if (in == ' ')
					{
						parseState = PARSEWHITESPACE; i++;
					}
					else if (in >= '0' && in <= '9')
					{
						parseState = PARSEMEASUREMENT;
					}
					else if (in == '*' || in == '/' || in == '(' || in == ')' || in == '^')
					{
						parseState = PARSEOPERATOR;
					}
					else
					{
						error = true;
					}
				}
				else if (parseState == PARSEMEASUREMENT)
				{
					if (in >= '0' && in <= '9')
					{
						parse = parse + in;
					}
					else
					{
						std::cout << "[" << parse << "] ";
						parse = "";
						parseState = PARSENUL;
					}
					i++;
				}
			}

			if (error)
			{
				std::cout << "PARSE ERROR\n";
			}*/

			double measurement = 0;
			double uncertainty = 0;
			Operations operation = NOP;
			std::string parse;
			ParseState parseState = ParseNull;
			bool error = false;

			int i = 0;
			while (i < input.length() && !error)
			{
				if (parseState == ParseNull)
				{

				}
				else if (ParseMeasurement)
				{

				}
				else if (ParseMeasurementWhitespace)
				{

				}
				else if (ParseUncertainty)
				{

				}
				else if (ParseUncertaintyWhitespace)
				{

				}
				else if (ParseUncertaintyPercent)
				{

				}
				else if (ParseOperator)
				{

				}
				else if (ParseOperatorWhitespace)
				{

				}
			}

			Measurement coefficient(2, 3);
			std::cout << "[" << coefficient.print() << "]\n";
		}
	}

	return 0;
}

