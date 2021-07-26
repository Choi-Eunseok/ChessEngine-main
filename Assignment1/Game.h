#include <iostream>
#include <fstream>

namespace chess
{
    void Print27Spaces(std::ostream& os, std::string message, size_t message_size);

    void MainMenu(std::istream& is, std::ostream& os);

    void PrintInitialBoard(std::ostream& os);

    void LoadBoard(std::istream& is, std::ostream& os);

    void PrintGameInformation(std::istream& is, std::ostream& os);
}
