#include "adjust.h"

double float_adjust(double value) {
    std::uint64_t bits;
    std::memcpy(&bits, &value, sizeof(bits)); // Extract bit representation
    bits += 128; // Adjust bits (positive for up, negative for down)
    std::memcpy(&value, &bits, sizeof(bits)); // Convert back to double
    return value;
}

