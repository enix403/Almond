#pragma once

#include <string>
#include <unordered_map>

#include <Almond/Core/Base.h>
#include <Almond/Utilities/typedefs.h>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Almond
{

    enum class ShaderType
    {
        Vertex,
        Fragment,
        Geometry
    };
    using ShaderSources = std::unordered_map<ShaderType, std::string>;

    class Shader
    {
    public:
        Shader() = default;

        static Ref<Shader> Create(const std::string& name, const ShaderSources& sources);

        inline uint32_t GetID() const
        {
            return m_ProgramID;
        }

        void Bind() const;
        void Unbind() const;

        inline const std::string& GetName() const
        {
            return m_Name;
        }

        // ------ Uniforms

        void SetUniformIntArray(const std::string& name, int* values, uint32_t count);
        void SetUniformInt(const std::string& name, int value);
        void SetUniformFloat(const std::string& name, float values);

        void SetUniformFloat2(const std::string& name, const glm::vec2& value);
        void SetUniformFloat3(const std::string& name, const glm::vec3& value);
        void SetUniformFloat4(const std::string& name, const glm::vec4& value);

        void SetUniformMat3(const std::string& name, const glm::mat3& value);
        void SetUniformMat4(const std::string& name, const glm::mat4& value);

    private:
        int GetUniformLocation(const std::string& uniformName) const;

    private:
        mutable std::unordered_map<std::string, int> m_UniformLocationCache;
        uint32_t m_ProgramID;
        std::string m_Name;
    };

    /* ======================== ShaderLibrary ======================== */

    class ShaderLibrary
    {
    public:
        ShaderLibrary() = default;

        inline bool Exists(const std::string& name)
        {
            return m_Shaders.find(name) != m_Shaders.end();
        }

        Ref<Shader> LoadFromFile(const std::string& filepath);
        Ref<Shader> LoadFromFile(const std::string& name, const std::string& filepath);

        // void Add(const std::string& name, const Ref<Shader>& shader);
        // void Add(const Ref<Shader>& shader);

        inline Ref<Shader> Get(const std::string& name)
        {
            return m_Shaders[name];
        }

    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };

} // namespace Almond