#include <file.h>

#include <fmt/format.h>
#include <range/v3/all.hpp>

#include <iostream>
#include <string_view>
#include <tuple>
#include <unordered_set>

using namespace hh::aoc;
using namespace ranges;

namespace hh::aoc::detail
{
std::pair<std::size_t, std::size_t> find_pos(std::size_t row_start, std::size_t row_end, std::size_t column_start, std::size_t column_end,
                                             std::string_view path)
{
    if (path.empty())
    {
        if (row_start != row_end || column_start != column_end)
        {
            throw std::runtime_error(
                fmt::format("Binary partitioning faled due to short string. RStart: {}, REnd: {}, CStart: {}, CEnd: {}.", row_start,
                            row_end, column_start, column_end));
        }
        return std::make_pair(row_start, column_start);
    }
    if (path.at(0) == 'F')
    {
        return find_pos(row_start, (row_start + row_end) / 2, column_start, column_end, path.substr(1));
    }
    if (path.at(0) == 'B')
    {
        return find_pos((row_start + row_end) / 2 + 1, row_end, column_start, column_end, path.substr(1));
    }
    if (path.at(0) == 'L')
    {
        return find_pos(row_start, row_end, column_start, (column_end + column_start) / 2, path.substr(1));
    }
    if (path.at(0) == 'R')
    {
        return find_pos(row_start, row_end, (column_start + column_end) / 2 + 1, column_end, path.substr(1));
    }
    throw std::runtime_error(fmt::format("Unrecognised path parameter {}", path.at(0)));
}
} // namespace hh::aoc::detail

template <std::size_t ROWS, std::size_t COLUMNS> std::pair<std::size_t, std::size_t> find_row(std::string_view path)
{
    return hh::aoc::detail::find_pos(0, ROWS - 1, 0, COLUMNS - 1, path);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Please provide 1 input file." << std::endl;
        return 1;
    }
    File file{argv[1]};
    auto contents = file.read_lines();
    auto result = contents | ranges::views::transform(find_row<128, 8>) |
                  ranges::views::transform([](auto &&result) -> std::size_t { return result.first * 8 + result.second; }) |
                  ranges::to_vector;
    result |= ranges::actions::sort;
    std::cout << fmt::format("Highest seat number was seat number {}", result.back()) << std::endl;
    for (std::size_t idx = 1; idx < result.size(); ++idx)
    {
        if (result[idx - 1] != result[idx] - 1)
        {
            std::cout << fmt::format("Looks like seat number {} might be yours!", result[idx] - 1) << std::endl;
        }
    }
}
