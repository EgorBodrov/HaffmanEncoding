#include "haffman.h"

std::string ReadData(char* filename)
{
    std::ifstream in(filename);
    std::string str = "";
    std::string tmp = "";

    if (!in.is_open())
    {
        std::cout << "Error in open file\n";
    }
    
    while (std::getline(in, tmp)) {
        str += tmp;
    }

    return str;
}

Node* CreateNode(char symb, int freq, Node* left, Node* right)
{
    Node* tmp = new Node();
    tmp->code = "";
    tmp->symbol = symb;
    tmp->frequency = freq;
    tmp->left = left;
    tmp->right = right;

    return tmp;
}

std::vector<Node*> CalculateFrequency(std::string str)
{
    std::vector <Node*> nodes;
    std::vector <char> unique;
    for (char symb : str)
    {
        if (std::find(unique.begin(), unique.end(), symb) != unique.end())
            continue;
        else
            unique.push_back(symb);
    }

    for (char symb : unique)
    {
        Node* tmp = new Node();
        tmp->symbol = symb;
        tmp->frequency = std::count(str.begin(), str.end(), symb);
        tmp->left = nullptr;
        tmp->right = nullptr;
        tmp->code = "";

        nodes.push_back(tmp);
    }

    return nodes;
}

bool CompareNodes(const Node* a, const Node* b)
{
    return a->frequency > b->frequency;
}

void PrintProbabilityDistribution(const std::vector<Node*>& v, int length)
{
    std::cout << "PROBABILITY DISTRIBUTION\n"
        << "--------------------------------\n";
    std::cout << "Symbol  Frequency  Probability\n";
    for (Node* tmp : v)
    {
        std::cout << "  " << tmp->symbol << "\t    " << tmp->frequency <<
            "\t      " << tmp->frequency << "/" << length << std::endl;
    }
    std::cout << "--------------------------------\n\n";
}

void PrintCode(const std::vector<Node*>& nodes)
{
    std::cout << "CODE RESULTS\n"
        << "--------------------------------\n";
    std::cout << "Symbol  Code\n";
    for (Node* nd : nodes)
    {
        std::cout << "   " << nd->symbol << "\t " << nd->code << std::endl;
    }
    std::cout << "--------------------------------\n\n";
}

void Encode(Node* root, const std::vector<Node*>& nodes, std::string str)
{
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr)
    {
        for (Node* nd : nodes)
            if (nd->symbol == root->symbol && nd->frequency == root->frequency)
            {
                nd->code = str;
                break;
            }
    }

    Encode(root->left, nodes, str + "0");
    Encode(root->right, nodes, str + "1");
}

void PrintInfo(const std::vector<Node*>& nodes, std::string str)
{
    std::cout << "RESULTS\n"
        << "--------------------------------\n";
    std::cout << "Default string: " << str << std::endl;
    std::cout << "Encoded string: ";
    for (char symb : str)
        for (Node* nd : nodes)
            if (nd->symbol == symb)
            {
                std::cout << nd->code;
                break;
            }
    std::cout << std::endl;

    int len {0};
    double entropy {0.0};
    double efficiency {0.0};
    for (Node* nd : nodes)
    {
        double prob = static_cast<double>(nd->frequency) / static_cast<double>(str.size());
        len += nd->frequency * nd->code.size();
        entropy += prob * log2(prob);
    }
    entropy *= -1;
    efficiency = static_cast<double>(8 * str.size()) / static_cast<double>(len);
         
    std::cout << "Average length: " <<  static_cast<double>(len) / str.size() << std::endl;
    std::cout << "Entropy: " << entropy << std::endl;
    std::cout << "Efficiency: " << efficiency << std::endl;

    std::cout << "--------------------------------\n\n";
}

void Start(std::string str)
{
    std::vector <Node*> nodes = CalculateFrequency(str);
    std::sort(nodes.begin(), nodes.end(), CompareNodes);

    PrintProbabilityDistribution(nodes, str.size());

    std::vector <Node*> priority {nodes};
    while (priority.size() > 1)
    {
        std::sort(priority.begin(), priority.end(), CompareNodes);
        std::reverse(priority.begin(), priority.end());

        Node* tmp = CreateNode('\0', priority[0]->frequency + priority[1]->frequency,
            priority[0], priority[1]);

        priority.erase(priority.begin(), std::next(priority.begin(), 2));
        std::reverse(priority.begin(), priority.end());
        priority.push_back(tmp);
    }

    Encode(priority[0], nodes, "");

    PrintCode(nodes);

    PrintInfo(nodes, str);
}
