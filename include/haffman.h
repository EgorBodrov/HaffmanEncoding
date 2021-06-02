#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

struct Node 
{
    char symbol;
    int frequency;
    std::string code;
    Node* left;
    Node* right;
};

std::string ReadData(char* filename);
Node* CreateNode(char symb, int freq, Node* left, Node* right);
std::vector<Node*> CalculateFrequency(std::string str);
bool CompareNodes(const Node* a, const Node* b);
void PrintProbabilityDistribution(const std::vector<Node*>& v, int length);
void Encode(Node* root, const std::vector<Node*>& nodes, std::string str);
void PrintCode(const std::vector<Node*>& nodes);
void Start(std::string str);

