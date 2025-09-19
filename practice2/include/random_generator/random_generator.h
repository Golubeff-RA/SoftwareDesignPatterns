#pragma once
#include <concepts>
#include <random>
#include <type_traits>

namespace my_math_lib {
template <typename T>
class RandomGenerator {
private:
    std::random_device rd;
    std::mt19937_64 gen;

public:
    RandomGenerator() : gen(rd()) {}

    template <typename U = T>
        requires std::integral<U>
    T Generate(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(gen);
    }

    template <typename U = T>
        requires std::floating_point<U>
    T Generate(T min = 0.0, T max = 1.0) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(gen);
    }

    template <typename U = T>
        requires std::same_as<U, bool>
    bool Generate() {
        std::bernoulli_distribution dist(0.5);
        return dist(gen);
    }
};

}  // namespace my_math_lib