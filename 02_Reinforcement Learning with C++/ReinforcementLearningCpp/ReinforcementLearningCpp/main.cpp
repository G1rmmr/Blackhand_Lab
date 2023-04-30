#include <iostream>
#include "Neuron.h"

int main()
{
	Neuron MyNeuron(2.0, 1.0, 0.4);

	for (std::size_t i = 0; i < 10; ++i)
	{
		std::cout << "Training repeat : " << i << '\n';

		MyNeuron.PrintFeedForward(1.0);
		MyNeuron.PropBackward(4.0);

		std::cout << '\n';

		std::cout << "Now Weight = " << MyNeuron.GetWeight() << '\n';
		std::cout << "Now Bias = " << MyNeuron.GetBias() << '\n';

		std::cout << '\n';
	}
	return 0;
}