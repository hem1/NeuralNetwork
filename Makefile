all:	    neuron.o network.o mnist.o main.o

neuron.o:		Neuron.hpp Neuron.cpp
		g++ -std=c++11 -c -o neuron.o Neuron.cpp

network.o:    	Neuron.hpp Network.cpp
		g++ -std=c++11 -c -o network.o Network.cpp

mnist.o:	    	MNIST_data.hpp MNIST_data.cpp
	    	g++ -std=c++11 -c -o mnist.o MNIST_data.cpp

main.o:	    	MNIST_data.hpp Network.hpp Neuron.hpp main.cpp
		g++ -std=c++11 mnist.o neuron.o network.o -o main.o main.cpp

clean:
	   	rm neuron.o network.o mnist.o main.o
