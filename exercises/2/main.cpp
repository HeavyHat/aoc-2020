#include <algorithm>
#include <ctre.hpp>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

std::vector<std::string> read_lines(const std::string &path)
{
    std::vector<std::string> lines;
    std::ifstream fstream{path};
    if (!fstream.good())
    {
        throw std::runtime_error("Unable to open file " + path);
    }
    std::string line;
    while (std::getline(fstream, line))
    {
        lines.emplace_back(std::move(line));
    }
    std::cout << "Loaded " << path << std::endl;
    return lines;
}

bool check_policy1(std::string_view password, char character, std::size_t minimum, std::size_t maximum)
{
    std::size_t count = std::count(password.begin(), password.end(), character);
    return minimum <= count && count <= maximum;
}

bool check_policy2(std::string_view password, char character, std::size_t minimum, std::size_t maximum)
{
    bool left = password.at(minimum - 1) == character;
    bool right = password.at(maximum - 1) == character;
    return (left || right) && !(left && right);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Please provide input policies file." << std::endl;
        return 1;
    }
    auto policies = read_lines(argv[1]);
    std::size_t valid_policy1_count = 0;
    std::size_t valid_policy2_count = 0;
    for (const auto &policy : policies)
    {
        auto match = ctre::match<"^([0-9]++).([0-9]++) ([A-z]): (.++)$">(policy);
        auto minimum = static_cast<std::size_t>(std::stoi(match.get<1>().to_string()));
        auto maximum = static_cast<std::size_t>(std::stoi(match.get<2>().to_string()));
        auto character = match.get<3>().to_view().at(0);
        auto password = match.get<4>().to_view();
        if (check_policy1(password, character, minimum, maximum))
            ++valid_policy1_count;
        if (check_policy2(password, character, minimum, maximum))
            ++valid_policy2_count;
    }
    std::cout << "Counted " << valid_policy1_count << " valid policies, according to policy 1." << std::endl;
    std::cout << "Counted " << valid_policy2_count << " valid policies, according to policy 2." << std::endl;
}
