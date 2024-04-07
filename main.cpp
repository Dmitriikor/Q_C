#include <iostream>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

void progressBar(float current_progress, float totalCounter) 
{
    float percentage = current_progress / totalCounter * 100;
    auto pos = (percentage / 100 * totalCounter);
    const std::string bar((size_t)pos, '=');
    const std::string blank((size_t)totalCounter - (size_t)pos, ' ');

    std::cout << '[' << bar << '>' << blank << "] " << int(percentage) << " %\r";
    std::cout.flush();
}

int main() 
{
    // {
    //     int width = 50;
    //     for (int i = 0; i <= width; ++i) 
    //     {
    //         //progressBar((float)i, (float)width);
    //         //Sleep(100);
    //     }
    // }

    json dataOpen;
    int cntr = 0;
    std::ifstream input_file("data.json");
    if (input_file.is_open()) 
    {
           input_file >> dataOpen; 
           auto& last_ticket = dataOpen.back();
           cntr = last_ticket["Counter"];
    }

    std::string stop = "stop\n";
    std::string Qinput;
    std::string Ainput1;
    std::string Ainput2;
    std::string Ainput3;
    std::string explanation;
    std::string ticket_N = "ticket_";

    json data;
    while(true)
    {
        Qinput.clear();
        Ainput1.clear();
        Ainput2.clear();
        Ainput3.clear();
        explanation.clear();
        std::string temp;

        std::cout << "inter Q: \n";
        while (std::getline(std::cin, temp) && !temp.empty()) 
        {
            Qinput += temp + '\n';
        }
        ++cntr;
        if(Qinput == stop)
        {
            break;
        }

        temp.clear();

        std::cout << "inter Ainput1: \n";
        while (std::getline(std::cin, temp) && !temp.empty()) 
        {
            Ainput1 += temp + '\n';
        }

        temp.clear();

        std::cout << "inter Ainput2: \n";
        while (std::getline(std::cin, temp) && !temp.empty()) 
        {
            Ainput2 += temp + '\n';
        }

        temp.clear();

        std::cout << "inter Ainput3: \n";
        while (std::getline(std::cin, temp) && !temp.empty()) 
        {
            Ainput3 += temp + '\n';
        }

        temp.clear();

        std::cout << "inter explanation: \n";
        while (std::getline(std::cin, temp) && !temp.empty()) 
        {
            explanation += temp + '\n';
        }

        json ticket = 
            {
                {"Q", Qinput},
                {"A1", Ainput1},
                {"A2", Ainput2},
                {"A3", Ainput3},
                {"explanation", explanation},
                {"Counter", cntr}
            };

        auto ticket_N_temp = ticket_N + (std::to_string(cntr));
        data[ticket_N_temp] = ticket;

    }
   
   
    if (input_file.is_open())
    {
        for (auto& ticket : data.items()) 
        {
            dataOpen[ticket.key()] = ticket.value();
        }

        input_file.close();

        std::ofstream file("data.json");
        file << dataOpen.dump(4);
        file.close();
        return 0;
    }
    else
    {
        std::ofstream file("data.json");
        file << data.dump(4);
        file.close();
    }

    
    return 0;
}
