//
//  EffectExtra.h
//  Additional Plugin Code
//
//  This file is a workspace for developing new DSP objects or functions to use in your plugin.
//

const int iNUMBER_OF_TAPS = 128;

class MyFirFilter
{
public:
	void set(float coeff)
	{
		// Initialise your filter variables here
		if (coeff < 0.0f) coeff = 0.0f;
		if (coeff > 1.0f) coeff = 1.0f;

		fCurrentACoeff = coeff;

		float fRestCoeff = (1.0f - fCurrentACoeff) / iNUMBER_OF_TAPS;
		for (int i = 0; i < iNUMBER_OF_TAPS; i++) fPreviousBCoeff[i] = fRestCoeff;

		fPreviousBCoeff[0] += fCurrentACoeff;
	}

	float getCutoff(float sampleRate)
	{
		float fOutput = sampleRate * (0.45f * (1.0f - fCurrentACoeff)); // Calculate cutoff frequency based on fCurrentACoeff and fPreviousBCoeff
		printf("Cutoff: %f\n", fOutput);
		return fOutput;
	}

	float process(float input)
	{
		// Filter individual samples here - 𝑦0 = sum of all taps
		// Y is the output, X is the input, a is the fCurrentACoeff, b is the fPreviousBCoeff, and N is the iNUMBER_OF_TAPS
		for (int i = iNUMBER_OF_TAPS - 1; i > 0; i--) fDelayLine[i] = fDelayLine[i - 1];
		fDelayLine[0] = input;
		float fOutput = 0.0f; for (int i = 0; i < iNUMBER_OF_TAPS; i++) fOutput += fDelayLine[i] * fPreviousBCoeff[i];

		return fOutput;
	}

private:
	// Declare your internal filter variables here

	float fCurrentACoeff = 0.0f;
	float fPreviousBCoeff[iNUMBER_OF_TAPS] = { 0.0f };
	float fDelayLine[iNUMBER_OF_TAPS] = { 0.0f };
};
