#include <file.h>

#include <fmt/format.h>
#include <range/v3/all.hpp>

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace hh::aoc;

std::vector<std::vector<std::string>> get_groups(std::vector<std::string> input)
{
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> current_group;
    for (auto line : std::move(input))
    {
        if (line.empty())
        {
            result.emplace_back(std::move(current_group));
            current_group.clear(); // Should be empty enyway but just to be sure.
            continue;
        }
        current_group.emplace_back(std::move(line));
    }
    result.emplace_back(std::move(current_group));
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Please provide one input file!" << std::endl;
        return 1;
    }
    File file{argv[1]};
    auto contents = file.read_lines();
    auto groups = get_groups(std::move(contents));
    std::size_t yes_count = 0;
    std::size_t unanimous_count = 0;
    for (auto group : std::move(groups))
    {
        std::unordered_map<char, std::size_t> group_unique_responses;
        std::unordered_map<char, std::size_t> group_unanimous_responses;
        for (auto response : group)
        {
            for (auto answer : std::move(response))
            {
                ++group_unique_responses[answer];
            }
        }
        yes_count += group_unique_responses.size();
        for (auto [key, value] : group_unique_responses)
        {
            if (value == group.size())
            {
                ++group_unanimous_responses[key];
            }
        }
        unanimous_count += group_unanimous_responses.size();
    }
    std::cout << fmt::format("Ended up with {} answers.", yes_count) << std::endl;
    std::cout << fmt::format("Ended up with {} unanimous answers.", unanimous_count) << std::endl;
}
