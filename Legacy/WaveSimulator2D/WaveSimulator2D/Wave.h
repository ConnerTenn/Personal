
#pragma once

#define PI 3.14159265358979323
#define TAU 2.0*PI

const int Dimensions = 100;

class Wave
{
private:
public:
	long double WaveData[Dimensions][Dimensions][2]; //Position, Vector
	long double WaveDataCPY[Dimensions][Dimensions][2];
public:
	Wave()
	{

	}

	void Initilize()
	{
		for (int x = 0; x < Dimensions; x++)
		{
			for (int y = 0; y < Dimensions; y++)
			{
				//WaveData[x][y][0] = ((x+y)/2-Dimensions/2)*10;
				//WaveData[x][y][0] += 1000.0l* pow(0.1l, (pow(x-Dimensions/2, 2.0l) + pow(y - Dimensions / 2, 2.0l)) / (2 * 100));
				//WaveData[x][y][0] += 1000.0l* pow(0.1l, (pow(x - Dimensions / 2 + 25, 2.0l) + pow(y - Dimensions / 2, 2.0l)) / (2 * 100));
				//z = 100 * 0.1 ^ ((x ^ 2 + y ^ 2) / (2 * 100))
				//WaveData[x][y][0] = 255 * 2;
				WaveData[x][y][0] += 100.0*pow(1.01, -pow(x - Dimensions / 2, 2.0));
				//WaveData[x][y][0] = 0;

				WaveData[x][y][1] = 0;
			}
		}
	}

	void Update()
	{

		for (int x = 0; x < Dimensions; x++) { for (int y = 0; y < Dimensions; y++) { for (int sel = 0; sel < 2; sel++) { WaveDataCPY[x][y][sel] = WaveData[x][y][sel]; } } }

		for (int x = 0; x < Dimensions; x++)
		{
			for (int y = 0; y < Dimensions; y++)
			{
				long double AverageMagnitude = WaveData[x][y][0];
				long double devisor = 1;

				
				for (int offsetx = -1; offsetx <= 1; offsetx++)
				{
					for (int offsety = -1; offsety <= 1; offsety++)
					{
						if ( x > 0 && x < Dimensions - 1 && y > 0 && y < Dimensions - 1)
						{
							AverageMagnitude += WaveData[x + offsetx][y + offsety][0] * sqrt(pow(offsetx, 2) + pow(offsety, 2));
							devisor++;
						}
					}
				}
				
				/*if (x > 0 && x < Dimensions - 1 && y > 0 && y < Dimensions - 1)
				{
					AverageMagnitude += WaveData[x][y][0];
					AverageMagnitude += WaveData[x + 1][y + 0][0];
					AverageMagnitude += WaveData[x - 1][y + 0][0];
					AverageMagnitude += WaveData[x + 0][y + 1][0];
					AverageMagnitude += WaveData[x + 0][y - 1][0];
					devisor++;
				}*/

				//devisor = 11.0; //(Semi)Fixed vs not ends
				AverageMagnitude /= devisor;

				WaveDataCPY[x][y][1] += AverageMagnitude - WaveData[x][y][0];

				//WaveDataCPY[x][y][1] += -WaveData[x][y][0] / 100; //Tension
				//WaveDataCPY[x][y][1] *= 0.99;// 0.9999; //Damping

				WaveDataCPY[x][y][0] += WaveDataCPY[x][y][1];
			}
		}

		for (int x = 0; x < Dimensions; x++) { for (int y = 0; y < Dimensions; y++) { for (int sel = 0; sel < 2; sel++) { WaveData[x][y][sel] = WaveDataCPY[x][y][sel]; } } }
	}
};



