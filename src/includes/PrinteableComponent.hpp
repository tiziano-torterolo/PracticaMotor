#pragma once
#include <string>
#include <iostream>
#include <cstdint>


class PrintableComponent {
public:

    explicit PrintableComponent(const char& text = '0');
    explicit PrintableComponent(char&& text);

    ~PrintableComponent();                                // Destructor
    PrintableComponent(const PrintableComponent& other) noexcept; // Constructor de copia
    PrintableComponent(PrintableComponent&& other)  noexcept; // Constructor de movimiento
    PrintableComponent& operator=(const PrintableComponent& other) noexcept = default; // Asignación copia
    PrintableComponent& operator=(PrintableComponent&& other)  noexcept; // Asignación movimiento

    void print() const;

    friend std::ostream& operator<<(std::ostream& os, const PrintableComponent& pc);

    void setText(const char& newText);
    void setText(char&& newText);

    const char& getText() const;

private:
    char text;
};