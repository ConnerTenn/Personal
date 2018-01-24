
struct PortAudioData;
class PortAudio;

#ifndef _PORT_AUDIO_
#define _PORT_AUDIO_

#include <portaudio.h>
#include <string>

struct PortAudioData
{
	int Index;
	float *Buffer;
	int Size;
};

class PortAudio
{
private:
	int SampleRate = 44100;
	PaStream *Stream;
	PortAudioData CallbackData;
	std::string ErrorMessage;

public:
	PortAudio()
	{

	}

private:
	static int Callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
	{
		/* Cast data passed through stream to our structure. */
		PortAudioData *data = (PortAudioData*)userData;
		float *out = (float*)outputBuffer;

		for (int i = 0; (unsigned long)i < framesPerBuffer; i++)
		{
			if (data->Index < data->Size)
			{
				out[i] = data->Buffer[data->Index];
			}
			else
			{
				out[i] = 0;
			}
			data->Index++;
		}

		return 0;
	}

public:
	std::string GetError()
	{
		std::string error = ErrorMessage;
		ErrorMessage.clear();
		return error;
	}

	bool Initialize()
	{
		PaError errorMessage;
		bool error = false;

		errorMessage = Pa_Initialize();
		ErrorMessage = ErrorMessage + Pa_GetErrorText(errorMessage) + "\n";
		if (errorMessage) { error = true; }

		/* Open an audio I/O stream. */
		errorMessage = Pa_OpenDefaultStream(&Stream,
			0,          /* no input channels */
			1,          /* mono output */
			paFloat32,  /* 32 bit floating point output */
			SampleRate,
			256,        /* frames per buffer, i.e. the number of sample frames that PortAudio will
						request from the callback. Many apps may want to use
						paFramesPerBufferUnspecified, which tells PortAudio to pick the best,
						possibly changing, buffer size.*/
			Callback, /* this is your callback function */
			&CallbackData); /*This is a pointer that will be passed to your callback*/
		ErrorMessage = ErrorMessage + Pa_GetErrorText(errorMessage) + "\n";
		if (errorMessage) { error = true; }

		return !error;
	}

	bool Terminate()
	{
		PaError errorMessage;
		bool error = false;

		errorMessage = Pa_StopStream(Stream);
		ErrorMessage = ErrorMessage + Pa_GetErrorText(errorMessage) + "\n";
		if (errorMessage) { error = true; }

		errorMessage = Pa_Terminate();
		ErrorMessage = ErrorMessage + Pa_GetErrorText(errorMessage) + "\n";
		if (errorMessage) { error = true; }

		return !error;
	}

	bool Play(float *data, int size)
	{
		PaError errorMessage;
		bool error = false;

		CallbackData.Index = 0;
		CallbackData.Buffer = data;
		CallbackData.Size = size;

		errorMessage = Pa_StartStream(Stream);
		ErrorMessage = ErrorMessage + Pa_GetErrorText(errorMessage) + "\n";
		if (errorMessage) { error = true; }

		return !error;
	}
};


#endif // !_PORT_AUDIO_

