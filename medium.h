#ifndef MEDIUM_H
#define MEDIUM_H
#include <string>

class Medium {
public:
    Medium(const std::string title);
    virtual ~Medium() = default;

    virtual void displayDetails() const = 0;

protected:
    std::string title;
};

#endif // MEDIUM_H