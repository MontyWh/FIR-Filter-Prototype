//
//  EffectExtra.h
//  Additional Plugin Code
//
//  This file is a workspace for developing new DSP objects or functions to use in your plugin.
//


class MyFilter
{
public:
	void set(float coeff)
	{
		// Initialise your filter variables here
		fCurrentACoeff = coeff;
		fPreviousBCoeff = 1 - fCurrentACoeff;
	}

	float getCutoff(float sampleRate)
	{
		float fOutput = acos(1 - (pow(fCurrentACoeff, 2.0f / (2.0f * fPreviousBCoeff))) * (sampleRate / (2.0f * M_PI))); // Calculate cutoff frequency based on fCurrentACoeff and fPreviousBCoeff
		printf("Cutoff: %f\n", fOutput);
		return fOutput;
	}

	float process(float input)
	{
		// Filter individual samples here - 𝑦0 = 𝑎𝑥0 + ((1 − 𝑎) * 𝑥0-1)
		// Y is the output, X is the input, a is the fCurrentACoeff, and x0-1 is the previous input sample
		float fOutput = (input * fCurrentACoeff) + ((1.0f - fCurrentACoeff) * fPreviousInput);
		fPreviousInput = input;  // Store for next sample
		return fOutput;
	}

private:
	// Declare your internal filter variables here

	float fCurrentACoeff;
	float fPreviousBCoeff = 0.0f;
	float fPreviousInput = 0.0f;   // Stores x-1
};