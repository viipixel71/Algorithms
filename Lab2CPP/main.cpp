#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <functional>
#include <unordered_map>
#include "beule.h"

bool is_number(const std::string& s)
{
    if (s.empty()) return false;
    size_t i = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    if (i == 1 && s.length() == 1) return false;
    for (; i < s.length(); ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    return true;
}

void process_stream(std::istream& in)
{
    Stack* stack = stack_create();
    std::string token;

    static const std::unordered_map<std::string, std::function<Data(Data, Data)>> ops = {
        {"+", [](Data a, Data b) { return a + b; }},
        {"-", [](Data a, Data b) { return a - b; }},
        {"*", [](Data a, Data b) { return a * b; }},
        {"/", [](Data a, Data b) { return b != 0 ? a / b : 0; }},
        {"%", [](Data a, Data b) { return b != 0 ? a % b : 0; }}
    };

    while (in >> token)
    {
        if (is_number(token))
        {
            stack_push(stack, std::stoi(token));
        }
        else if (auto it = ops.find(token); it != ops.end())
        {
            Data b = stack_pop(stack);
            Data a = stack_pop(stack);
            stack_push(stack, it->second(a, b));
        }
        else if (token == "dup") { stack_dup(stack); }
        else if (token == "drop") { stack_drop(stack); }
        else if (token == "swap") { stack_swap(stack); }
        else if (token == "over") { stack_over(stack); }
        else if (token == "rot") { stack_rot(stack); }
        else if (token == "." && !stack_is_empty(stack))
        {
            std::cout << stack_pop(stack) << "\n";
        }
    }

    stack_delete(stack);
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        if (std::ifstream file(argv[1]); file.is_open())
        {
            process_stream(file);
            return 0;
        }
    }
    process_stream(std::cin);
    return 0;
}