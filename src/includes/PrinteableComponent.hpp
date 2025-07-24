#pragma once
#include <string>
#include <iostream>
#include <cstdint>


class PrinteableComponent {
public:

    explicit PrinteableComponent(const char& text = '0');
    explicit PrinteableComponent(char&& text);

    ~PrinteableComponent();                                // Destructor
    PrinteableComponent(const PrinteableComponent& other); // Constructor de copia
    PrinteableComponent(PrinteableComponent&& other) noexcept; // Constructor de movimiento
    PrinteableComponent& operator=(const PrinteableComponent& other); // Asignación copia
    PrinteableComponent& operator=(PrinteableComponent&& other) noexcept; // Asignación movimiento

    void print() const;

    friend std::ostream& operator<<(std::ostream& os, const PrinteableComponent& pc);

    void setText(const char& newText);
    void setText(char&& newText);

    const char& getText() const;

private:
    char text;
};