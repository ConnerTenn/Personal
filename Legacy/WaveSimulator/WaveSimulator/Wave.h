
#pragma once

#define PI 3.14159265358979323
#define TAU 2.0*PI

const int NumPoints = 800;

class Wave
{
private:
public:
	long double WaveData[NumPoints][2]; //Position, Vector
public:
	Wave()
	{

	}

	void Initilize()
	{
		for (int x = 0; x < NumPoints; x++)
		{
			//WaveData[x][0] += 30.0*pow(1.01, -pow(x - NumPoints / 2, 2.0)); //Bell
			//WaveData[x][0] += 100.0*pow(1.1, -pow(x - NumPoints / 2+100, 2.0)); //Bell
			////WaveData[x][0] += 100.0*pow(1.01, -pow(x - NumPoints / 2+250, 2.0)); //Bell
			//WaveData[x][0] += 50.0*pow(1.01, -pow((x - NumPoints / 2.0)/21.0, 2)); // Bell
			//WaveData[x][0] = 0.2*(-abs(x - NumPoints / 2.0) + NumPoints / 2.0);
			//WaveData[x][0] = sin(TAU / (0.25L/4.0L) / 800.0L*x)*70.0L;
			//if (x > 200 && x < 600) { WaveData[x][0] = 50; }
			////WaveData[x][0] += -100 * pow(1.018, -abs(NumPoints / 2 - x - 200));
			////WaveData[x][0] += -100 * pow(1.018, -abs(NumPoints / 2 - x + 200));
			//WaveData[x][0] = 0;

			//WaveData[x][1] += 40.0*pow(1.01, -pow(x - NumPoints / 2 + 1, 2.0))- 40.0*pow(1.01, -pow(x - NumPoints / 2 - 1, 2.0));
			WaveData[x][1] = 0;

		}
		//WaveData[0][0] = 30;
		//WaveData[0][1] = 0;
		//WaveData[1][1] = 10;
		//WaveData[2][1] = 5;
		//WaveData[NumPoints / 2][1] = 10;
		//WaveData[NumPoints / 2][0] = 50;
	}

	void UpdateV1()
	{
		long double WaveDataCPY[NumPoints][2];

		//WaveData[NumPoints / 2][0] = 250;
		//WaveData[NumPoints / 2][1] = 0;

		//WaveData[NumPoints / 2 - 100][0] = 250;
		//WaveData[NumPoints / 2 - 100][1] = 0;
		/*
		static int val = 0;
		WaveData[NumPoints / 2 - 300][0] = sin(TAU/100 * val) * 100;
		val++;
		WaveData[NumPoints / 2 - 300][1] = 0;
		*/

		for (int x = 0; x < NumPoints; x++) { for (int y = 0; y < 2; y++) { WaveDataCPY[x][y] = WaveData[x][y]; } }

		for (int point = 0; point < NumPoints; point++)
		{
			long double AverageMagnitude = WaveData[point][0];
			long double devisor = 1;
			//Calculate Movement Vector
			/*if (point != 0)
			{
				AverageMagnitude += WaveData[point - 1][0];
				devisor++;
			}
			else
			{
				WaveDataCPY[point][1] = WaveData[point + 1][1];
			}

			if (point != NumPoints - 1)
			{
				AverageMagnitude += WaveData[point + 1][0];
				devisor++;
			}
			else
			{
				WaveDataCPY[point][1] = WaveData[point - 1][1];
			}*/

			if (point != 0 && point != NumPoints - 1)
			{
				AverageMagnitude += WaveData[point - 1][0];
				AverageMagnitude += WaveData[point + 1][0];
				devisor = 3;
			}
			if (point == 0)
			{
				AverageMagnitude += WaveData[point + 1][0];
				devisor++;
				//devisor = 3; //(Semi)Fixed vs not ends
			}
			if (point == NumPoints - 1)
			{
				AverageMagnitude += WaveData[point - 1][0];
				devisor++;
				//devisor = 3; //(Semi)Fixed vs not ends
			}

			//devisor = 3.0; //(Semi)Fixed vs not ends
			AverageMagnitude /= devisor;

			WaveDataCPY[point][1] += AverageMagnitude - WaveData[point][0];

			/*
			if (point == 0)
			{
				WaveDataCPY[point][1] = WaveData[point + 1][1];
			}
			if (point == NumPoints - 1)
			{
				WaveDataCPY[point][1] = WaveData[point - 1][1];
			}
			/*/

			//WaveDataCPY[point][1] += -(pow(WaveData[point][0],2)/1000) * (WaveData[point][0] == 0? 0 : (WaveData[point][0] > 0? 1:-1));
			//WaveDataCPY[point][1] += -WaveData[point][0] / 1000; //Tension
			//WaveDataCPY[point][1] *= 0.9999; //Damping

			WaveDataCPY[point][0] += WaveDataCPY[point][1];
			WaveDataCPY[point][0];
		}

		//Update Position
		for (int x = 0; x < NumPoints; x++) { for (int y = 0; y < 2; y++) { WaveData[x][y] = WaveDataCPY[x][y]; } }
	}

	void Update()
	{
		long double WaveDataCPY[NumPoints][2];

		//WaveData[NumPoints / 2][0] = 250;
		//WaveData[NumPoints / 2][1] = 0;

		//WaveData[NumPoints / 2 - 100][0] = 250;
		//WaveData[NumPoints / 2 - 100][1] = 0;
		/*
		static int val = 0;
		WaveData[NumPoints / 2 - 300][0] = sin(TAU/100 * val) * 20;
		val++;
		WaveData[NumPoints / 2 - 300][1] = 0;
		*/
		///*
		static int val1 = 0, direction1 = 0;
		//WaveData[NumPoints / 2 - val1/8 - 200][0] = -100;
		direction1 == 1 ? val1++ : val1--;
		val1 > 200 * 8 || val1 < -200 * 8 ? direction1 = 1 - direction1 : 0;
		//WaveData[NumPoints / 2 - val1/8 - 200][1] = 0;
		//*/
		///*
		static int val2 = 0, direction2 = 1;
		//WaveData[NumPoints / 2 - val2 / 4 + 200][0] = -100;
		direction2 == 1 ? val2++ : val2--;
		val2 > 200 * 4 || val2 < -200 * 4 ? direction2 = 1 - direction2 : 0;
		//WaveData[NumPoints / 2 - val2 / 4 + 200][1] = 0;
		//*/

		for (int x = 0; x < NumPoints; x++) { for (int y = 0; y < 2; y++) { WaveDataCPY[x][y] = WaveData[x][y]; } }

		for (int point = 0; point < NumPoints; point++)
		{
			long double AverageMagnitude = WaveData[point][0]*1;
			long double devisor = 1*1;

			//Calculate Movement Vector
			if (point != 0 && point != NumPoints - 1)
			{
				AverageMagnitude += WaveData[point - 1][0];
				AverageMagnitude += WaveData[point + 1][0];
				devisor += 2;
			}
			if (point == 0)
			{
				AverageMagnitude += WaveData[point + 1][0];
				devisor++;
				//devisor = 3; //(Semi)Fixed vs not ends
			}
			if (point == NumPoints - 1)
			{
				AverageMagnitude += WaveData[point - 1][0];
				devisor++;
				//devisor = 3; //(Semi)Fixed vs not ends
			}

			//devisor = 3.0; //(Semi)Fixed vs not ends
			AverageMagnitude /= devisor;

			WaveDataCPY[point][1] += AverageMagnitude - WaveData[point][0];

			///*
			if (point == 0)
			{
				WaveDataCPY[point][0] = 0;// WaveData[point + 1][0];
				static long double prev = WaveData[point - 1][1];
				WaveDataCPY[point][1] = prev;
				prev = WaveData[point + 1][1];
				WaveDataCPY[point][1] = 0;// WaveData[point + 1][1];
			}
			if (point == NumPoints - 1)
			{
				WaveDataCPY[point][0] = 0;// WaveData[point - 1][0];
				static long double prev = WaveData[point - 1][1];
				WaveDataCPY[point][1] = prev;
				prev = WaveData[point - 1][1];
				WaveDataCPY[point][1] = 0;// WaveData[point - 1][1];
			}
			//*/

			//WaveDataCPY[point][1] += -(pow(WaveData[point][0],2)/1000) * (WaveData[point][0] == 0? 0 : (WaveData[point][0] > 0? 1:-1));
			//WaveDataCPY[point][1] += -WaveData[point][0] / 10000; //Tension
			//WaveDataCPY[point][1] *= 0.99;// 0.9999; //Damping

			WaveDataCPY[point][0] += WaveDataCPY[point][1];
		}

		//Update Position
		for (int x = 0; x < NumPoints; x++) { for (int y = 0; y < 2; y++) { WaveData[x][y] = WaveDataCPY[x][y]; } }
	}
};
