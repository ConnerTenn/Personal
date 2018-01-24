// MusicMaker_00.cpp : Defines the entry point for the console application.
//
// Sound_01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
//#include <cmath>
//#include <limits>
#include <fstream>
#include <string>
#include <playsoundapi.h>
#include <mmsystem.h>
#include <vector>

#pragma comment(lib, "winmm.lib")

using namespace std;

#define PI 3.14159265358979323
#define TAU 2.0 * PI

//typedef signed short BitDepth;//	16bit audio
typedef signed char BitDepth;//	8bit audio
typedef unsigned long long QWORD;

const double pi = 3.141592653589;
const DWORD samplerate = 44100;
//const WORD channels = 1;
//const unsigned short SOUND_DURATION = 2;//	1 second for example.
//const QWORD NUM_SAMPLES = SOUND_DURATION * samplerate * channels;
//const QWORD NUM_SAMPLES = samplerate / 16;

/*void sineWave(BitDepth buffer[], double freq)
{
	//BitDepth amplitude = 32767 * 0.5;
	BitDepth amplitude = BitDepth(pow(2, 8 * sizeof(BitDepth)) * 0.5);
	QWORD c = 0;
	double d = (samplerate / freq);
	for (QWORD i = 0; i<NUM_SAMPLES; i += channels)
	{
		double deg = 360.0 / d;
		buffer[i] = buffer[i + (1 * (channels - 1))] = sin((c++*deg)*pi / 180)*amplitude;
	}
}*/

template<typename _Ty> void write(std::ofstream& stream, const _Ty& ty)
{
	stream.write((const char*)&ty, sizeof(_Ty));
}

/*void writeWaveFile(const char* filename, BitDepth* buffer)
{
	std::ofstream stream(filename, std::ios::binary);

	stream.write("RIFF", 4);
	::write<int>(stream, 36 + (NUM_SAMPLES*sizeof(BitDepth)));
	stream.write("WAVEfmt ", 8);
	::write<int>(stream, 16);
	::write<short>(stream, 1);
	::write<unsigned short>(stream, channels);
	::write<int>(stream, samplerate);
	::write<int>(stream, samplerate*channels*sizeof(BitDepth));
	::write<short>(stream, channels*sizeof(BitDepth));
	::write<short>(stream, sizeof(BitDepth) * 8);
	stream.write("data", 4);
	::write<int>(stream, NUM_SAMPLES*sizeof(BitDepth));
	stream.write((const char*)&buffer[0], NUM_SAMPLES*sizeof(BitDepth));
	stream.close();
}*/

void writeWaveFile(const char* filename, vector<BitDepth> &Buffer)
{
	std::ofstream stream(filename, std::ios::binary);

	stream.write("RIFF", 4);
	::write<int>(stream, 36 + Buffer.size()*sizeof(BitDepth));
	stream.write("WAVEfmt ", 8);
	::write<int>(stream, 16);
	::write<short>(stream, 1);
	::write<unsigned short>(stream, 1);
	::write<int>(stream, samplerate);
	::write<int>(stream, samplerate*sizeof(BitDepth));
	::write<short>(stream, sizeof(BitDepth));
	::write<short>(stream, sizeof(BitDepth) * 8);
	stream.write("data", 4);
	::write<int>(stream, Buffer.size()*sizeof(BitDepth));
	stream.write((const char*)&Buffer[0], Buffer.size()*sizeof(BitDepth));
	stream.close();
}

/*

Type		BeginFrequecy	EndFrequency	BeginAmplitude	EndAmplitude	Duration	
*			****			****			**				**				*****
0:Square	Hz				Hz												Cycle
1:Triangle
2:Sawtooth

*/

vector<BitDepth> Buffer;
vector<char> a;
std::string filename = "Audio";
const DWORD SampleRate = 44100;

struct Sample
{
	int Type;
	DWORD BeginFrequency;
	DWORD EndFrequency;
	int BeginAmplitude;
	int EndAmplitude;
	DWORD Duration;
};

int GenData(vector<BitDepth> &Buffer, Sample WaveData)
{
	BitDepth amplitude = pow(2, 8 * sizeof(BitDepth)) * 0.5;
	for (int i = 0; i < WaveData.Duration; i++)
	{
		if (WaveData.Type == 0x0)
		{
			//Buffer.push_back(ceil(sin(((double)i / ((double)SampleRate/WaveData.BeginFrequency))*TAU) / 2.0) * amplitude);
			double Frequency = ((double(WaveData.EndFrequency) - double(WaveData.BeginFrequency)) / double(WaveData.Duration)) * i + WaveData.BeginFrequency;
			double Val = double(i) / (double(SampleRate) / Frequency);
			Buffer.push_back(ceil(sin(Val*TAU) / 2.0) * amplitude);
		}
		if (WaveData.Type == 0x2)
		{
			double Frequency = ((double(WaveData.EndFrequency) - double(WaveData.BeginFrequency)) / double(WaveData.Duration)) * i + WaveData.BeginFrequency;
			double Val = double(i) / (double(SampleRate) / Frequency);
			Buffer.push_back( fmod(Val,amplitude) * amplitude);
		}
	}
	return 1;
}

int main(int argc, char** argv)
{
	SetConsoleTitleA("Music Maker");

	string path;
	//cout << "Enter File Path:";
	//getline(cin, path);
	path = "Music.txt";
	std::ifstream File(path);
	if (File)
	{
		// get length of file:
		File.seekg(0, File.end);
		int length = File.tellg();
		File.seekg(0, File.beg);

		string buffer;

		Sample WaveData;
		while (File >> buffer)
		{
			WaveData.Type = stoi(buffer, 0, 16);
			File >> buffer;
			WaveData.BeginFrequency = stoi(buffer, 0, 16);
			File >> buffer;
			WaveData.EndFrequency = stoi(buffer, 0, 16);
			File >> buffer;
			WaveData.BeginAmplitude = stoi(buffer, 0, 16);
			File >> buffer;
			WaveData.EndAmplitude = stoi(buffer, 0, 16);
			File >> buffer;
			WaveData.Duration = stoi(buffer, 0, 16);

			GenData(Buffer, WaveData);
		}
		writeWaveFile("Audio.wav", Buffer);
	}
	else
	{
		cout << "ERROR::Cannot Open File\n";
	}



	//BitDepth* buffer = new BitDepth[NUM_SAMPLES];
	//memset(buffer, 0, NUM_SAMPLES*sizeof(BitDepth));

	//sineWave(buffer, 440.0);


	//writeWaveFile(std::string(filename + std::string(".wav")).c_str(), buffer);
	//delete[] buffer;

	//PlaySound(TEXT("..\\Sound_01\\Audio.wav"), NULL, SND_FILENAME | SND_SYNC);

	//sineWave(buffer, 220.0);
	//writeWaveFile(std::string(filename + std::string(".wav")).c_str(), buffer);
	//delete[] buffer;
	//PlaySound(TEXT("..\\Sound_01\\Audio.wav"), NULL, SND_FILENAME | SND_SYNC);

	//delete[] buffer;
	std::cout << "\nPress Enter To Continue:";
	string Out;
	//getline(cin, Out);

	return 0;
}


