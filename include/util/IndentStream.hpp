#pragma once
#include <ostream>

class Indent {
public:
    explicit Indent(const std::size_t level) : level_(level) {}

    friend auto operator<<(std::ostream& stream, const Indent& ind) -> std::ostream& {
        for (std::size_t i = 0; i < ind.level_; ++i) {
            stream << "\t";
        }
        return stream;
    }

private:
    std::size_t level_;
};