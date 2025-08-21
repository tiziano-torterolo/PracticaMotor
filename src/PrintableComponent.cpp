#include "./includes/PrinteableComponent.hpp"


PrintableComponent::PrintableComponent(const char& text)
    : text(text) {}

PrintableComponent::PrintableComponent(char&& text)
    : text(std::move(text)) {}

PrintableComponent::~PrintableComponent() {}

PrintableComponent::PrintableComponent(const PrintableComponent& other) noexcept
    : text(other.text) {}

PrintableComponent::PrintableComponent(PrintableComponent&& other) noexcept
    : text(std::move(other.text)) {}

PrintableComponent& PrintableComponent::operator=(PrintableComponent&& other)  noexcept {
    if (this != &other) {
        text = std::move(other.text);
    }
    return *this;
}
    
void PrintableComponent::print() const {
    std::cout << this << std::endl;
}

void PrintableComponent::setText(const char& newText) {
    text = newText;
}

void PrintableComponent::setText(char &&newText) {
    text = std::move(newText);
}

const char& PrintableComponent::getText() const {
    return text;
}

std::ostream& operator<<(std::ostream& os, const PrintableComponent& pc) {
    os << pc.text;
    return os;
}