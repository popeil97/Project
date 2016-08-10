/* 
 * File:   NeuralNet.h
 * Author: fox2eagle1
 *
 * Created on June 19, 2016, 2:56 PM
 */d

#ifndef NEURALNET_H
#define	NEURALNET_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <cmath>

using namespace std;


class NeuralConnection {
    
public:
    double weight;
    double changeInWeight;
    
    double getWeight() {
        return weight;
    }
};

class Neuron;

typedef vector<Neuron> Layer; // allows layer to be a vector that holds neuron objects

class Neuron {
private:
    vector <NeuralConnection> connections;
    unsigned index;
    double output = 0.0;
    double gradient;
    double eta = 0.20; //determines how fast the net learns
    double alpha = 0.40;
    
    double randomWeightAssignment() {
        double random = (rand()/double(RAND_MAX));
        return random;
    }
    
    double transferFunc(double x) { //passing output to get results
        return tanh(x);
    }
    
    double transferFunctionDer(double x) {
        return (1-(x*x));
    }
    
    double sum(const Layer &nextLayer) {
        double sum = 0;
        
        for(unsigned i = 0; i < nextLayer.size()-1; i++) {
            sum += (nextLayer[i].gradient) * (connections[i].weight);
        }
        
        return sum;
    }
public:
    Neuron(unsigned outputNum, unsigned index) { //this method creates neurons
        
        for(unsigned connec = 0; connec < outputNum; connec++) {
            connections.push_back(NeuralConnection()); //gives every neuron a series of neural connections, with weights
            this->index = index;
            
        }
        
        for(unsigned i = 0; i < connections.size(); i++) {
            connections[i].weight = randomWeightAssignment(); //randomly assigns weights
        }
    }
    
    void setOutput(double output) {
        this->output = output;
    }
    
    double getOutput() {
        return output;
    }
    
    void feedForward(const Layer &lastLayer) { //feeds values forward to other neuron layers
        double sum = 0.0;
        
        for(unsigned i = 0; i < lastLayer.size(); i++) {
            sum += (lastLayer[i].output) * (lastLayer[i].connections[index].weight);
        }
        
        output = transferFunc(sum);
    }
    
    void updateWeights(Layer &lastLayer) { //updates the neural connection weights
        for(unsigned i = 0; i < lastLayer.size(); i++) {
            Neuron &neuron = lastLayer[i];
            double lastChangeInWeight = neuron.connections[index].changeInWeight;
            double newChangeInWeight = (neuron.getOutput() * eta * gradient) + (alpha * lastChangeInWeight);
            
            neuron.connections[index].changeInWeight = (neuron.getOutput() * eta * gradient) + (alpha * lastChangeInWeight);
            neuron.connections[index].weight += (neuron.getOutput() * eta * gradient) + (alpha * lastChangeInWeight);
        }
    }
    
    void calcOutputGradients(double targetVals) {
        gradient = (targetVals - output) * transferFunc(output); //used for calculations to update weights
    }
    
    void calcHiddenGradients(Layer &nextLayer) {
        gradient = sum(nextLayer) * transferFunctionDer(output);
    }
    
};

class Net {
private:
    vector <double> weights;
    vector <Layer> layers;
    double error;
    //double recentAverageError;
    double recentAverageSmoothingError;
public:
    Net(const vector<unsigned> &architecture) {
        
        unsigned lay = architecture.size();
        
        
        for(unsigned i = 0; i < lay; i++) {
            
            layers.push_back(Layer());
            unsigned numOfOutputs;
            
            if(i == architecture.size() - 1) {
                numOfOutputs = 0;
                
            }
            
            if(i != architecture.size() - 1) {
                numOfOutputs = architecture[i+1];
            }
            
            for(unsigned n = 0; n <= architecture[i]; n++) {
                
                layers.back().push_back(Neuron(numOfOutputs, n));
            }
            
            layers.back().back().setOutput(1); //assigns bias Neuron value of 1
        }
        
        layers.back().back().setOutput(1.0);
    }
    
    void feedForward(vector<double> &input) {
        
        unsigned size = input.size();
        
        for(unsigned i = 0; i < size; i++) {
            
            layers[0][i].setOutput(input[i]); //inputs values to first layer of neurons
            
        }
        
        for(unsigned i = 1; i < layers.size(); i++) { //takes from he last layer and feeds through
            Layer &lastLayer = layers[i - 1];
            
            for(unsigned j = 0; j < layers[i].size() - 1; j++) {
                layers[i][j].feedForward(lastLayer);
            }
            
            
            
        }
        
    }
    
    void backProp(const vector<double> &targetValues) {
        
        Layer &layerOutput = layers.back(); //relays target values cak through the net
        double changeIn;
        error = 0;
        
        for(unsigned i = 0; i < layerOutput.size() - 1; i++) {
            changeIn = (targetValues[i]) - (layerOutput[i].getOutput());
            error += (changeIn * changeIn);
        }
       
        error = sqrt((error) / (layerOutput.size()-1));
        
        
        for(unsigned i = 0; i < layerOutput.size() - 1; i++) {
            layerOutput[i].calcOutputGradients(targetValues[i]);
        }
        
        unsigned layerNum = layers.size() - 2;
        
        for(unsigned n = layerNum; n > 0; n--) {
            Layer &hidden = layers[n];
            Layer &next = layers[n + 1];
            
            //cout << "test4";
            for(unsigned i = 0; i < hidden.size(); i++) {
                hidden[i].calcHiddenGradients(next);
            }
            
        }
        
        unsigned newLayerNum = layers.size()-1;
        
        for(unsigned n = newLayerNum; n > 0; n--) {
            Layer &layer = layers[n];
            Layer &lastLayer = layers[n - 1];
            
            for(unsigned i = 0; i < layers.size()-2; i++) {
                layer[i].updateWeights(lastLayer); //updates connection weight
            }
            
        }
        
    }
    
    
    void getResults(vector <double> &resultVals) {
        resultVals.clear();
        
        unsigned n = 0;
        
        while(n < layers.back().size() - 1) {
            double result = layers.back()[n].getOutput();
            resultVals.push_back(result);
            
            n++;
        }
    }
    
};


#endif	/* NEURALNET_H */

