#pragma once

struct PhysicalProperties
{

    explicit PhysicalProperties(
    const double mass
    ) : mass_(mass)
    {
    }

    [[nodiscard]] auto mass() const -> double
    {
        return mass_;
    }

private:
    double mass_;
};