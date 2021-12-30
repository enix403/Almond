/* ================================================================================================================================= */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/* ================================================================================================================================= */

#ShaderSegment:vertex
#version 420 core

layout (location = 0) in vec3 v_Pos;
layout (location = 1) in vec3 v_Normal;
layout (location = 2) in vec2 v_TexCoords;
layout (location = 3) in int v_EntityID;

uniform mat4 u_PVM; // projection * view * model 
uniform mat4 u_Model;

out VS_OUT {
    vec3 fragNormal;
    vec2 texCoords;
    flat int entityID;
} vs_out;

void main()
{   
    gl_Position = u_PVM * vec4(v_Pos, 1.0);

    // FIXME: will not work if u_Model contains non-uniform scaling
    vec3 worldNormal = normalize(mat3(u_Model) * v_Normal);
    vs_out.fragNormal = worldNormal;
    vs_out.texCoords = v_TexCoords;

    vs_out.entityID = v_EntityID;
}

/* ================================================================================================================================= */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/* ================================================================================================================================= */

#ShaderSegment:fragment
#version 420 core

const float AMBIENT_LIGHT = 0.55;

uniform vec3 u_Color;
uniform vec3 u_DirectionToLight;

uniform sampler2D u_Texture;

in VS_OUT {
    vec3 fragNormal;
    vec2 texCoords;
    flat int entityID;
} fs_in;

layout (location = 0) out vec4 fragColor;
layout (location = 1) out int entityID;

void main()
{   
    float lightIntensity = AMBIENT_LIGHT + abs(dot(normalize(fs_in.fragNormal), u_DirectionToLight)) * 0.5;
    vec3 fragSampleColor = texture(u_Texture, fs_in.texCoords).xyz * u_Color;
        
    fragColor = vec4(fragSampleColor * lightIntensity, 1.0);
    entityID = fs_in.entityID;
}

/* ================================================================================================================================= */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/* ================================================================================================================================= */
