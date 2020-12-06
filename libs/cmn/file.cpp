#include <experimental/iterator>
#include <file.h>
#include <fmt/format.h>
#include <sstream>
#include <string>
#include <tl/expected.hpp>
#include <vector>

namespace hh::aoc
{

File::File(const std::string &path) : d_stream{path}
{
    if (!d_stream.good())
    {
        throw std::runtime_error(fmt::format("Unable to open path {}", path));
    }
}
File::~File()
{
    d_stream.close();
}

std::vector<std::string> File::read_lines()
{
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(d_stream, line))
    {
        lines.emplace_back(std::move(line));
    }
    return lines;
}

std::string File::read_all()
{
    auto lines = read_lines();
    std::stringstream ss;
    std::move(lines.begin(), lines.end(), std::experimental::make_ostream_joiner(ss, "\n"));
    return ss.str();
}

tl::expected<std::string, std::string> File::read()
{
    std::string line;
    auto &result = std::getline(d_stream, line);
    if (!result)
    {
        return tl::make_unexpected("Unable to read from file.");
    }
    return line;
}
} // namespace hh::aoc
