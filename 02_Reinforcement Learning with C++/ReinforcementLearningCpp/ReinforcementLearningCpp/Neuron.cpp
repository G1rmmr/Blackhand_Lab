#include <iostream>
#include <algorithm>
#include "Neuron.h"

Neuron::Neuron():
	mWeight(2.0),
	mBias(1.0),
	mLearnRate(0.1)
{}

Neuron::Neuron(
	const double& Weight,
	const double& Bias):
	mWeight(Weight),
	mBias(Bias)
{}

Neuron::Neuron(
	const double& Weight,
	const double& Bias,
	const double& LearnRate):
	mWeight(Weight),
	mBias(Bias),
	mLearnRate(LearnRate)
{}

Neuron::~Neuron()
{
	std::cout << "A Neuron sutdowned. . .\n";
}

double Neuron::GetActFunc(const double& X)
{
	return std::max(0.0, X);
}

double Neuron::FeedForward(const double& Input)
{
	SetInput(Input);
	const double Sigma = mWeight * GetInput() + mBias;

	SetOutput(GetActFunc(Sigma));
	return GetOutput();
}

double Neuron::GetActGrad(const double& X)
{
	return 1.0;
}

void Neuron::PropBackward(const double& Target)
{
	const double Grad
		= (GetOutput() - Target) * GetActGrad(GetOutput());

	double NewWeight = GetWeight() - GetLearnRate() * Grad * GetInput();
	SetWeight(NewWeight);

	double NewBias = GetBias() - GetLearnRate() * Grad * 1.0;
	SetBias(NewBias);
}

void Neuron::PrintFeedForward(const double& Input)
{
	std::cout << "Input = " << Input << " : "
		<< this->FeedForward(Input) << '\n';
}
