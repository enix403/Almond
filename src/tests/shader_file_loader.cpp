#include "almond/rendering/Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace Almond;
// using std::endl;

static std::string ConvertShaderTypeToString(ShaderType type) {
    switch (type) {
        case ShaderType::Vertex:    return "SHADER_VERTEX";
        case ShaderType::Fragment:  return "SHADER_FRAGMENT";
        case ShaderType::Geometry:  return "SHADER_GEOMETRY";
    }
}

void ReadShaderSourcesFromFile(ShaderSources& outSources, const std::string& filepath) 
{
    std::fstream fileStream(filepath);
    
    std::stringstream writer;
    bool writing = false;

    ShaderType currentType;

    std::string line;
    int lineNumber = 0;

    while (getline(fileStream, line)) {
        lineNumber++;
        if (line.empty()) continue;

        if (line.rfind("#ShaderSegment:", 0) == 0) {
            if (writing) {
                outSources[currentType] = writer.str();
                std::stringstream().swap(writer);
            }

            writing = true;

            if (line.find("vertex") != std::string::npos)
                currentType = ShaderType::Vertex;
            else if (line.find("fragment") != std::string::npos)
                currentType = ShaderType::Fragment;
            else if (line.find("geometry") != std::string::npos)
                currentType = ShaderType::Geometry;
            else {
                std::cout << "Error: invalid segment type at line " << lineNumber;
                writing = false;
            }

            continue;
        }

        if (writing)
            writer << line << "\n"; 
    }

    if (writing) {
        outSources[currentType] = writer.str();
    }

    for (auto& it: outSources) {
        std::cout << "<--------------------------------->\n";
        std::cout << "ShaderType: " << ConvertShaderTypeToString(it.first) << "\n";
        std::cout << "\n";
        std::cout << it.second;
    }
}

int main() {
    // std::cout << "Helo error\n";
    ShaderSources sources;
    ReadShaderSourcesFromFile(sources, "assets/shaders/DefaultShader.shader");
    return 0;
}