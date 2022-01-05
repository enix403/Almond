#pragma once

#include <imgui/imgui.h>
#include <sstream>
#include <string>

// Outputs a comma separated list of rgb colors given in the range [0, 255]
#define COMMA_RGB_INT(r, g, b) (r) / 255.0f, (g) / 255.0f, (b) / 255.0f
#define IRGB_TO_FRGB(r, g, b) { (r) / 255.0f, (g) / 255.0f, (b) / 255.0f }


// namespace Almond {
//     struct Color {
//         float r, g, b, a;
//     };
// }

inline ImVec4 ImGuiColorFromHexString(const std::string& hexStr)
{
    unsigned int hexValue;
    std::stringstream ss;
    ss << std::hex << hexStr.c_str() + 1; // ignore the first "#" char
    ss >> hexValue;

    ImVec4 rgbColor;
    rgbColor.x = ((hexValue >> 16) & 0xFF) / 255.0f; // Extract the RR byte
    rgbColor.y = ((hexValue >> 8) & 0xFF) / 255.0f; // Extract the GG byte
    rgbColor.z = ((hexValue)&0xFF) / 255.0f; // Extract the BB byte
    rgbColor.w = 1.0f;
    return rgbColor;
}
