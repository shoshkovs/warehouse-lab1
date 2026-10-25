#pragma once

class Quantity {

public:

    explicit Quantity(int value);

    int getValue() const;

    void setValue(int value);

    void change(int delta);

private:

    int value_;

};
