#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include <ctre.hpp>
#include <file.h>
#include <fmt/format.h>

using namespace std::literals;
using namespace hh::aoc;

std::vector<std::string> split(std::vector<std::string> lines)
{
    std::vector<std::string> items;
    std::stringstream ss;
    for (auto line : std::move(lines))
    {
        if (line.empty() || line.size() == 1)
        {
            items.emplace_back(ss.str());
            ss.str("");
            continue;
        }
        ss << " " << std::move(line);
    }
    items.emplace_back(ss.str());
    return items;
}

bool regex_match(const std::string &str, const std::regex &re, const std::string &regex_str)
{
    auto result = std::regex_search(str, re);
    if (!result)
    {
        std::cout << fmt::format("Failed validation for '{}', for input string '{}'", regex_str, str);
    }
    return result;
}

template <typename... VIEW> auto make_validator(VIEW &&... regexes_str)
{
    return [regexes = std::make_tuple(std::make_pair(std::regex(regexes_str), regexes_str)...)](const std::string &passport) -> bool {
        return std::apply([&passport](auto &&... regexs) -> bool { return (regex_match(passport, regexs.first, regexs.second) && ...); },
                          regexes);
    };
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Please provide a single input file!" << std::endl;
        return 1;
    }
    File file{argv[1]};
    auto contents = file.read_lines();
    auto passports = split(std::move(contents));
    std::cout << fmt::format("Loaded {} passports.", passports.size()) << std::endl;
    auto valid_passport = make_validator(
        R"((^|\s)byr:(19[2-9][0-9]|200[0-2])(\s|$))", R"((^|\s)iyr:(20(1[0-9]|20))(\s|$))", R"((^|\s)eyr:(20(2[0-9]|30))(\s|$))",
        R"((^|\s)hgt:(((1([5-8][0-9]|9[0-3])cm))|((59|6[0-9]|7[0-3])in))(\s|$))", R"((^|\s)hcl:#([a-f0-9]+)(\s|$))",
        R"((^|\s)ecl:(amb|gry|hzl|grn|oth|brn|blu)(\s|$))", R"((^|\s)pid:[0-9]{9}(\s|$))");
    std::cout << fmt::format("Counted a total of {} valid passports.",
                             std::count_if(passports.begin(), passports.end(),
                                           [&valid_passport](auto str) {
                                               auto r = valid_passport(str);
                                               if (!r)
                                               {
                                                   std::cout << fmt::format("'{}' detected as invalid!", str) << std::endl;
                                               }
                                               return r;
                                           }))
              << std::endl;
}
