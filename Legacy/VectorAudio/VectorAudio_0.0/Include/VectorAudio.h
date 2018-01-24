
class VectorAudio;

#ifndef _VECTOR_AUDIO_
#define _VECTOR_AUDIO_

#define V_STEPS 65536 //vertical resolution for the audio (±65536)
#define V_STEPS_TOTAL 131073 //vertical resolution for the audio (2*65536 + 1) (±65536 && 0)
#define H_STEPS 4410000 //horizontal resolution for 1 second (10*44100)

#include <iostream>
#include <string>
#include <portaudio.h>
#include "MathGlobals.h"
#include "PortAudio.h"
#include "VectorTypes.h"



class VectorAudio
{
public:
	VectorAudio()
	{

	}
};



#endif // !_VECTOR_AUDIO_

