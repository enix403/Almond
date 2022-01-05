#include "almond/rendering/Shader.h"
#include "almond/core/Logging.h"

#include <glad/gl.h>

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

static bool ReadShaderSourcesFromFile(Almond::ShaderSources& outSources,
                                      const std::string& filepath);

namespace Almond
{

    static std::string ConvertShaderTypeToString(ShaderType type)
    {
        switch(type)
        {
        case ShaderType::Vertex:
            return "SHADER_VERTEX";
        case ShaderType::Fragment:
            return "SHADER_FRAGMENT";
        case ShaderType::Geometry:
            return "SHADER_GEOMETRY";
        }
    }

    Ref<Shader> Shader::Create(const std::string& name, const ShaderSources& sources)
    {
        int programId = glCreateProgram();

        std::vector<uint> children;

        for(auto& it : sources)
        {
            uint openglType;
            switch(it.first)
            {
            case ShaderType::Vertex: {
                openglType = GL_VERTEX_SHADER;
                break;
            }

            case ShaderType::Fragment: {
                openglType = GL_FRAGMENT_SHADER;
                break;
            }

            case ShaderType::Geometry: {
                openglType = GL_GEOMETRY_SHADER;
                break;
            }
            }

            const char* sourceStr = it.second.c_str();

            uint sid = glCreateShader(openglType);
            children.push_back(sid);
            glShaderSource(sid, 1, &sourceStr, NULL);
            glCompileShader(sid);

            int success;
            glGetShaderiv(sid, GL_COMPILE_STATUS, &success);

            if(success)
            {
                glAttachShader(programId, sid);
            }
            else
            {
                int len;
                glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &len);
                char* infoLog = (char*)alloca(len * sizeof(char));

                glGetShaderInfoLog(sid, len, NULL, infoLog);

                AD_CORE_LOG_ERROR("Shader compilation error (name={0}, type={1}): {2}",
                                  name,
                                  ConvertShaderTypeToString(it.first),
                                  infoLog);
            }
        }

        // ========================== Linking Stage ==========================

        glLinkProgram(programId);
        // glValidateProgram(programId);

        for(int sid : children)
        {
            glDeleteShader(sid);
        }

        int success;
        glGetProgramiv(programId, GL_LINK_STATUS, &success);

        if(success == GL_FALSE)
        {
            int len;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &len);
            char* infoLog = (char*)alloca(len * sizeof(char));

            glGetProgramInfoLog(programId, len, NULL, infoLog);

            AD_CORE_LOG_ERROR("Shader link error (name={0}): {1}", name, infoLog);

            return nullptr;
        }

        Ref<Shader> program = CreateRef<Shader>();
        program->m_ProgramID = programId;
        program->m_Name = name;
        return program;
    }

    void Shader::Bind() const
    {
        glUseProgram(m_ProgramID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    int Shader::GetUniformLocation(const std::string& uniformName) const
    {
        if(m_UniformLocationCache.find(uniformName) != m_UniformLocationCache.end())
        {
            return m_UniformLocationCache[uniformName];
        }

        int location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
        if(location == -1)
        {
            AD_CORE_LOG_WARN(
                "Shader(name={0}) Error: Uniform '{1}' not found", m_Name, uniformName);
        }

        m_UniformLocationCache[uniformName] = location;

        return location;
    }

    /* ========================= Uniform setters =========================*/

    void Shader::SetUniformInt(const std::string& name, int value)
    {
        int location = GetUniformLocation(name);
        glUniform1i(location, value);
    }

    void Shader::SetUniformIntArray(const std::string& name, int* values, uint32_t count)
    {
        int location = GetUniformLocation(name);
        glUniform1iv(location, count, values);
    }

    void Shader::SetUniformFloat(const std::string& name, float value)
    {
        int location = GetUniformLocation(name);
        glUniform1f(location, value);
    }

    void Shader::SetUniformFloat2(const std::string& name, const glm::vec2& value)
    {
        int location = GetUniformLocation(name);
        glUniform2f(location, value.x, value.y);
    }

    void Shader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        int location = GetUniformLocation(name);
        glUniform3f(location, value.x, value.y, value.z);
    }

    void Shader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        int location = GetUniformLocation(name);
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void Shader::SetUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        int location = GetUniformLocation(name);
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        int location = GetUniformLocation(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    /* ============================ ShaderLibrary ========================== */

    Ref<Shader> ShaderLibrary::LoadFromFile(const std::string& filepath)
    {
        const std::string& name = filepath; // TODO: set name to last segment (filename) of filepath
        return LoadFromFile(name, filepath);
    }

    Ref<Shader> ShaderLibrary::LoadFromFile(const std::string& name, const std::string& filepath)
    {
        if(Exists(name))
            return m_Shaders[name];

        ShaderSources sources;
        ReadShaderSourcesFromFile(sources, filepath);

        Ref<Shader> shader = Shader::Create(name, sources);
        m_Shaders[name] = shader;
        return shader;
    }

} // namespace Almond

bool ReadShaderSourcesFromFile(Almond::ShaderSources& outSources, const std::string& filepath)
{
    using namespace Almond;
    std::fstream fileStream(filepath);

    if(fileStream.fail())
    {
        AD_CORE_LOG_ERROR("Could not open shader file: {0}", filepath);
    }

    std::stringstream writer;
    bool writing = false;

    ShaderType currentType;

    std::string line;
    int lineNumber = 0;

    while(getline(fileStream, line))
    {
        lineNumber++;
        if(line.empty())
            continue;

        if(line.rfind("#ShaderSegment:", 0) == 0)
        {
            if(writing)
            {
                outSources[currentType] = writer.str();
                std::stringstream().swap(writer);
            }

            writing = true;

            if(line.find("vertex") != std::string::npos)
                currentType = ShaderType::Vertex;
            else if(line.find("fragment") != std::string::npos)
                currentType = ShaderType::Fragment;
            else if(line.find("geometry") != std::string::npos)
                currentType = ShaderType::Geometry;
            else
            {
                AD_CORE_LOG_WARN("Invalid shader segment at line {0}, Skipping segment",
                                 lineNumber);
                writing = false;
            }

            continue;
        }

        if(writing)
            writer << line << "\n";
    }

    if(writing)
    {
        outSources[currentType] = writer.str();
    }

    return true;
}
