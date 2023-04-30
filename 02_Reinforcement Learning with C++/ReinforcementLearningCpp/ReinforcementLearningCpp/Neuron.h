#pragma once

class Neuron
{
public:
	Neuron();

	Neuron(
		const double& Weight,
		const double& Bias);

	Neuron(
		const double& Weight,
		const double& Bias,
		const double& LearnRate);
	
	~Neuron();

	double GetWeight() const { return mWeight; }
	void SetWeight(const double& Weight) { mWeight = Weight; }

	double GetBias() const { return mBias; }
	void SetBias(const double& Bias) { mBias = Bias; }

	double GetInput() const { return mInput; }
	void SetInput(const double& Input) { mInput = Input; }

	double GetOutput() const { return mOutput; }
	void SetOutput(const double& Output) { mOutput = Output; }

	double GetLearnRate() const { return mLearnRate; }
	void SetLearnRate(const double& LearnRate) { mLearnRate = LearnRate; }

	double GetActFunc(const double& X);
	double GetActGrad(const double& X);

	double FeedForward(const double& Input);
	void PropBackward(const double& Target);

	void PrintFeedForward(const double& Input);

private:
	double mWeight;
	double mBias;

	double mInput;
	double mOutput;

	double mLearnRate;
};