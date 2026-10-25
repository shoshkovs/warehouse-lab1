#pragma once

class Price {
public:
    explicit Price(int value);

    int getValue() const;
    void setValue(int value);

private:
    int value_;
};
