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
#include <algorithm>
#include <map>

#pragma comment(lib, "winmm.lib")

using namespace std;

#define PI 3.14159265358979323
#define TAU (2.0 * PI)

//typedef unsigned short BitDepth;//	16bit audio
typedef unsigned char BitDepth;//	8bit audio
typedef unsigned long long QWORD;
struct WaveData
{
	//Channels
	vector<string> Channel;
	//Channel<stream<data>>
	vector<vector<vector<string>>> Data;
};

WaveData Data;
vector<BitDepth> Buffer;
std::string filename = "Audio";
const DWORD SampleRate = 44100;
map<string, string> NoteMap = 
{
	{ "---", "0"},
	{ "0000", "0" },
	{ "C1", "0032.7" }, { "C#1", "0034.6" }, { "D1", "0036.7" }, { "D#1", "0038.9" }, { "E1", "0041.2" }, { "F1", "0043.7" }, { "F#1", "0046.2" }, { "G1", "0049.0" }, { "G#1", "0051.9" }, { "A1", "0055.0" }, { "A#1", "0058.3" }, { "B1", "0061.7" } ,
	{ "C2", "0065.4" }, { "C#2", "0069.3" }, { "D2", "0073.4" }, { "D#2", "0077.8" }, { "E2", "0082.4" }, { "F2", "0087.3" }, { "F#2", "0092.5" }, { "G2", "0098.0" }, { "G#2", "0103.8" }, { "A2", "0110.0" }, { "A#2", "0116.5" }, { "B2", "0123.5" } ,
	{ "C3", "0130.8" }, { "C#3", "0138.6" }, { "D3", "0146.8" }, { "D#3", "0155.6" }, { "E3", "0164.8" }, { "F3", "0174.6" }, { "F#3", "0185.0" }, { "G3", "0196.0" }, { "G#3", "0207.7" }, { "A3", "0220.0" }, { "A#3", "0233.1" }, { "B3", "0246.9" } ,
	{ "C4", "0261.6" }, { "C#4", "0277.2" }, { "D4", "0293.7" }, { "D#4", "0311.1" }, { "E4", "0329.6" }, { "F4", "0349.2" }, { "F#4", "0370.0" }, { "G4", "0392.0" }, { "G#4", "0415.3" }, { "A4", "0440.0" }, { "A#4", "0466.2" }, { "B4", "0493.9" } ,
	{ "C5", "0523.3" }, { "C#5", "0554.4" }, { "D5", "0587.3" }, { "D#5", "0622.3" }, { "E5", "0659.3" }, { "F5", "0698.5" }, { "F#5", "0740.0" }, { "G5", "0784.0" }, { "G#5", "0830.6" }, { "A5", "0880.0" }, { "A#5", "0932.3" }, { "B5", "0987.8" } , 
	{ "C6", "1046.5" }, { "C#6", "1108.7" }, { "D6", "1174.7" }, { "D#6", "1244.5" }, { "E6", "1318.5" }, { "F6", "1396.9" }, { "F#6", "1480.0" }, { "G6", "1568.0" }, { "G#6", "1661.2" }, { "A6", "1760.0" }, { "A#6", "1864.7" }, { "B6", "1975.5" } ,
	{ "C7", "2093.0" }, { "C#7", "2217.5" }, { "D7", "2349.3" }, { "D#7", "2489.0" }, { "E7", "2637.0" }, { "F7", "2793.8" }, { "F#7", "2960.0" }, { "G7", "3136.0" }, { "G#7", "3322.4" }, { "A7", "3520.0" }, { "A#7", "3729.3" }, { "B7", "3951.1" } ,
};


//Settings
int SampleDurration = SampleRate / 8;
bool UseNotes = true;


template<typename _Ty> void write(std::ofstream& stream, const _Ty& ty)
{
	stream.write((const char*)&ty, sizeof(_Ty));
}


void writeWaveFile(const char* filename, vector<BitDepth> &Buffer)
{
	std::ofstream stream(filename, std::ios::binary);

	stream.write("RIFF", 4);
	::write<int>(stream, 36 + Buffer.size()*sizeof(BitDepth));
	stream.write("WAVEfmt ", 8);
	::write<int>(stream, 16);
	::write<short>(stream, 1);
	::write<unsigned short>(stream, 1);
	::write<int>(stream, SampleRate);
	::write<int>(stream, SampleRate*sizeof(BitDepth));
	::write<short>(stream, sizeof(BitDepth));
	::write<short>(stream, sizeof(BitDepth) * 8);
	stream.write("data", 4);
	::write<int>(stream, Buffer.size()*sizeof(BitDepth));
	stream.write((const char*)&Buffer[0], Buffer.size()*sizeof(BitDepth));
	stream.close();
}

/*
Style			
0:Letters		
1:Frequencies	

::
Frequency	Data
			Continuous

*/



void ParseFile(string path)
{
	std::ifstream File(path);
	if (File)
	{
		// get length of file:
		File.seekg(0, File.end);
		int length = File.tellg();
		File.seekg(0, File.beg);

		//Read from file
		string buffer;
		int state = 0;

		while (int(File.tellg()) != -1)
		{
			if (state == 0)
			{
				File >> buffer;
				transform(buffer.begin(), buffer.end(), buffer.begin(), toupper);
				if (buffer == "#HEADER")
				{
					state = 1;
				}
			}
			if (state == 1)
			{
				File >> buffer;
				transform(buffer.begin(), buffer.end(), buffer.begin(), toupper);
				if (buffer == "SQUARE")
				{
					Data.Channel.push_back("SQUARE");
					Data.Data.push_back({ });
				}
				else if (buffer == "TRIANGLE")
				{
					Data.Channel.push_back("TRIANGLE");
					Data.Data.push_back({ });
				}
				else if (buffer == "SAWTOOTH")
				{
					Data.Channel.push_back("SAWTOOTH");
					Data.Data.push_back({ });
				}
				else if (buffer == "SINE")
				{
					Data.Channel.push_back("SINE");
					Data.Data.push_back({});
				}
				else if (buffer == "OFF")
				{
					Data.Channel.push_back("OFF");
					Data.Data.push_back({});
				}
				else if (buffer == "SAMPLESPERSEC")
				{
					File >> buffer;
					SampleDurration = SampleRate / stoi(buffer);
				}
				else if (buffer == "USENOTES")
				{
					File >> buffer;
					UseNotes = stoi(buffer);
				}
				else if (buffer == "#DATA")
				{
					state = 2;
				}
				else
				{
					cout << "ERROR::File Parsing; Invalid Token\n";
				}
			}
			if (state == 2)
			{
				File >> buffer;
				transform(buffer.begin(), buffer.end(), buffer.begin(), toupper);
				string temp = buffer;
				File >> buffer;
				transform(buffer.begin(), buffer.end(), buffer.begin(), toupper);

				static int ChannelNum = 0;
				Data.Data[ChannelNum].push_back({ temp, buffer });
				ChannelNum++;
				if (ChannelNum >= Data.Channel.size())
				{
					ChannelNum = 0;
				}
			}
		}
		if (state != 2)
		{
			cout << "ERROR::No Data\n";
		}
	}
	else
	{
		cout << "ERROR::Cannot Open File\n";
	}
}


void GenData()
{
	BitDepth amplitude = (pow(2, 8 * sizeof(BitDepth)) - 1) * 0.5 * (1.0 / Data.Channel.size());
	for (int i = 0; i < Data.Data[0].size() * SampleDurration; i++)
	{
		Buffer.push_back(0);
	}

	for (int channelnum = 0; channelnum < Data.Channel.size(); channelnum++)
	{
		long count = 0;
		for (int sample = 0; sample < Data.Data[channelnum].size(); sample++)
		{
			//double Frequency = double(stoi(Data.Data[channelnum][sample][0]));
			double Frequency;
			if (!UseNotes) 
			{ 
				Frequency = Data.Data[channelnum][sample][0] != "---" ? double(stoi(Data.Data[channelnum][sample][0])) : 0; 
			}
			else
			{
				Frequency = stod(NoteMap.find(Data.Data[channelnum][sample][0])->second);
			}

			for (int i = 0; i < SampleDurration; i++, count++)
			{
				if (Data.Channel[channelnum] == "SQUARE")
				{
					double val = double(count) / (double(SampleRate) / Frequency);
					//Buffer[count] += (ceil(sin(val * TAU) / 2.0) * 2.0 - 1) * amplitude;
					//Buffer[count] += ceil(sin(val * TAU) / 2.0) * amplitude;
					//Buffer.push_back(ceil(sin(val*TAU) / 2.0)*amplitude);
					Buffer[count] += (ceil(sin(val * TAU) / 2.0) * amplitude) * 2.0;
				}
				else if (Data.Channel[channelnum] == "TRIANGLE")
				{
					double val = double(count) / (double(SampleRate) / Frequency);
					//Buffer[count] += (fmod((ceil(sin(val / (2.0 * amplitude) * TAU) / 2.0) * 2.0 - 1) * val, 2.0 * amplitude) - amplitude / 2.0) * amplitude;
					//Buffer[count] += 4.0 / TAU * asin(sin(val / (2.0*amplitude)*TAU));
					Buffer[count] += (4.0 / TAU) * asin(sin(val * TAU)) * amplitude + amplitude;
				}
				else if (Data.Channel[channelnum] == "SAWTOOTH")
				{
					double val = double(count) / (double(SampleRate) / Frequency);
					//Buffer[count] += fmod(val, amplitude) * amplitude;
					//Buffer[count] += (fmod(val, amplitude*2.0) - amplitude) * amplitude;
					Buffer[count] += fmod(val + 0.5, 1) * 2.0 * amplitude;
				}
				else if (Data.Channel[channelnum] == "SINE")
				{
					double val = double(count) / (double(SampleRate) / Frequency);
					//Buffer[count] += sin(val * TAU) * amplitude;
					//Buffer.push_back(ceil(sin(val*TAU) / 2.0)*amplitude);
					Buffer[count] += (sin(val * TAU) * amplitude) + amplitude;
				}
				else if (Data.Channel[channelnum] == "OFF")
				{
				}
				else
				{
					cout << "ERROR::Invalid Waveform\n";
				}
			}
		}
	}
}

int main(int argc, char** argv)
{
	SetConsoleTitleA("Music Maker");


	string path;
	//cout << "Enter File Path:";
	//getline(cin, path);

	path = "Music.txt";
	
	cout << "Parsing File\n";
	ParseFile(path);
	cout << "Generating Audio\n";
	GenData();
	cout << "Writing File\n";
	writeWaveFile("Audio.wav", Buffer);

	std::cout << "\nPress Enter To Continue:";
	string Out;
	getline(cin, Out);

	return 1;
}


