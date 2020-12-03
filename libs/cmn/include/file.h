#ifndef INCLUDED_AOC_2020_FILE_H
#define INCLUDED_AOC_2020_FILE_H

#include <fstream>
#include <string_view>
#include <vector>

#include <tl/expected.hpp>

namespace hh::aoc
{
class File
{
  private:
    std::fstream d_stream;

  public:
    File(const std::string &path);
    virtual ~File();
    std::vector<std::string> read_lines();
    tl::expected<std::string, std::string> read();
};
} // namespace hh::aoc

#endif
