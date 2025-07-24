#include "./includes/PrinteableComponent.hpp"


PrinteableComponent::PrinteableComponent(const char& text)
    : text(text) {}

PrinteableComponent::PrinteableComponent(char&& text)
    : text(std::move(text)) {}

PrinteableComponent::~PrinteableComponent() {}

PrinteableComponent::PrinteableComponent(const PrinteableComponent& other)
    : text(other.text) {}

PrinteableComponent::PrinteableComponent(PrinteableComponent&& other) noexcept
    : text(std::move(other.text)) {}

PrinteableComponent& PrinteableComponent::operator=(PrinteableComponent&& other) noexcept {
    if (this != &other) {
        text = std::move(other.text);
    }
    return *this;
}
    
void PrinteableComponent::print() const {
    std::cout << this << std::endl;
}

void PrinteableComponent::setText(const char& newText) {
    text = newText;
}

void PrinteableComponent::setText(char &&newText) {
    text = std::move(newText);
}

const char& PrinteableComponent::getText() const {
    return text;
}

std::ostream& operator<<(std::ostream& os, const PrinteableComponent& pc) {
    os << pc.text;
    return os;
}