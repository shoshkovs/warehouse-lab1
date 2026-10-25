#pragma once

class Weight {
public:
    explicit Weight(double value);

    double getValue() const;
    void setValue(double value);

private:
    double value_;
};
