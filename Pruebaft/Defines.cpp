#pragma once
#include <memory>
#include <csignal>
#include <ctime>
#include <cstdint>
#define EXIST_VEHICLE false

#if EXIST_VEHICLE

#include <ft/ft.hpp>
using TxtType = ft::TXT;
using EncoderType = ft::Encoder;
using CounterType = ft::Counter;
#else
using TxtType = std::nullptr_t;
using EncoderType = int;
using CounterType = int;
#endif

#define ConnectExitSignalHandler std::signal(SIGINT, signal_handler);


static inline TxtType createTXT() {
        return TxtType{};
}

static inline constexpr std::shared_ptr<EncoderType> createEncoder_shared_ptr(auto& txt, int id) {
    if constexpr (EXIST_VEHICLE) {
        return std::shared_ptr<EncoderType>(txt.getEncoder(id));
    } else {
        return std::shared_ptr<EncoderType>(nullptr);
    }
}

static inline constexpr std::shared_ptr<CounterType> createCounter_shared_ptr(auto& txt, int id) {
    if constexpr (EXIST_VEHICLE) {
        return std::shared_ptr<CounterType>(txt.getCounter(id));
    } else {
        return std::shared_ptr<CounterType>(nullptr);
    }
}

static inline constexpr void updateTXT_config(auto& txt) {
    if constexpr (EXIST_VEHICLE) {
        txt.update_config();
    }
}


auto stop = false;
void signal_handler(int signal);
void signal_handler(int signal)
{
    stop = true;
}



inline uint64_t now_ms();
inline uint64_t now_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL;
}