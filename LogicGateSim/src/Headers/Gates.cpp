#include "Gates.hpp"

void NotGate::logic()
{
	outputs[0] = !inputs[0];
	std::cout << "Not: " << outputs[0] << std::endl;
}

void AndGate::logic()
{
	outputs[0] = inputs[0] && inputs[1];
	std::cout << "And: " << outputs[0] << std::endl;
}
