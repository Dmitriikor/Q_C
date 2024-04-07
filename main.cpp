#include <iostream>
#include <chrono>
#include <windows.h>

void progressBar(float current_progress, float totalCounter) 
{
    float percentage = current_progress / totalCounter * 100;
    auto pos = (percentage / 100 * totalCounter);
    const std::string bar((size_t)pos, '=');
    const std::string blank((size_t)totalCounter - (size_t)pos, ' ');

    std::cout << '[' << bar << '>' << blank << "] " << int(percentage) << " %\r";
    std::cout.flush();
}

int main() {
    int width = 50;
    for (int i = 0; i <= width; ++i) 
    {
        progressBar((float)i, (float)width);
        Sleep(100);
    }



    std::cin >> width;
    return 0;
}
