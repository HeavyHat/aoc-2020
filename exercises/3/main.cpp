#include <file.h>
#include <fmt/format.h>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace hh::aoc;

template <std::size_t X, std::size_t Y> struct Move
{
    constexpr static auto x = X;
    constexpr static auto y = Y;
};

template <std::size_t X, std::size_t Y> std::size_t find_collisions(const std::vector<std::string> &terrain)
{
    std::size_t x = 0, y = 0;
    std::size_t tree_counter{0};
    auto move = Move<X, Y>{};
    while (y < terrain.size())
    {
        if (terrain.at(y).at(x) == '#')
        {
            ++tree_counter;
        }
        x += move.x;
        x %= terrain.at(0).size();
        y += move.y;
    }
    return tree_counter;
}

int main(int argc, const char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Please provide one argument with the file describing the terrain." << std::endl;
    }
    File file{argv[1]};
    auto lines = file.read_lines();
    auto collisions1 = find_collisions<1, 1>(lines);
    auto collisions2 = find_collisions<3, 1>(lines);
    auto collisions3 = find_collisions<5, 1>(lines);
    auto collisions4 = find_collisions<7, 1>(lines);
    auto collisions5 = find_collisions<1, 2>(lines);
    std::cout << fmt::format("Multiplied collisions={}", collisions1 * collisions2 * collisions3 * collisions4 * collisions5) << std::endl;
}
