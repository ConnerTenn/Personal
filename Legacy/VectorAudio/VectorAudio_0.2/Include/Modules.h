
/*
Note
Input:
Vector Lines
Output:
Waveform per Vector Line

Envolope
Input:
Waveform
Vector Lines
Output:
Waveform Per Vector Line



utilize frequency and volume and volume for synthesis
utilize oscillator module to generate waveform
waveform can be used to mix with other samples

*/

class Pipeline;
class ModuleBase;

#ifndef _MODULES_
#define _MODULES_

#include <vector>
#include "Math.h"
#include "VectorTypes.h"
#include <algorithm>

struct Samples
{
	std::vector<Int2> data;
	int Begin;
	int End;
};


class Pipeline//switch from pointers to ids?
{
private:
	std::vector<ModuleBase *> ModuleList;
	std::vector<ModuleBase *> ProcessQueue;
	//std::vector<ModuleBase *> RootElementList;

public:
	void Process(ModuleBase *module);

	void AddModule(ModuleBase *module);

	void RemoveModule(ModuleBase *module);

	void ProcessToHere(ModuleBase *module);
};

class SubPipeline : public Pipeline//not necessary
{

};


class ModuleBase
{
protected:
	std::vector<ModuleBase *> InputModules;
	std::vector<ModuleBase *> OutputModules;

	

public:
	Int2 Position;
	std::string Name;

	std::vector<Samples> SampleData;

	void AddInput(ModuleBase *module);
	void RemoveInput(ModuleBase *module);
	void AddOutput(ModuleBase *module);
	void RemoveOutput(ModuleBase *module);
	virtual void DrawModule();
	virtual void Process();

};


class AudioOut : public ModuleBase
{

};

/*
Graphis handled in Elements?
Pipe (to link elements together)?

Constant:

Waveform:
Outputs(1)
Waveform

SubElement:
contains a sub net

Note:
Inputs(1)
Waveform
Outputs(n)
sample data per note

Envalope:
Inputs(s)
sampledata
Output(s)
computed sampledata

Phase:
Input(s, 1)
sampledata
offset
Output(s)
sampledata shifted by time

Scale:
Input(s,1)
sampledata
scalle

Buffer:


BandPassFilter:


FrequencyReporter:


AmplitudeReporter:


Collapser:
collapses all sampledata into 1 sampledata
*/


//pass waveform data around using an array of ints

#endif



