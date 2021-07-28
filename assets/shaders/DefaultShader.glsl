#ShaderSegment:vertex
#version 420 core
layout(location = 0) in vec3 a_Position;   // the position variable has attribute position 0
layout(location = 1) in vec2 a_UV;   // the position variable has attribute position 0

out vec2 f_UV;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_ProjectionView * u_Model * vec4(a_Position, 1.0);
    f_UV = a_UV;
}


#ShaderSegment:fragment
#version 420 core

in vec2 f_UV;

out vec4 FragColor;

uniform vec3 u_Color;
uniform sampler2D u_Texture;
  
void main()
{
    // FragColor = vec4(u_Color, 1.0);
    FragColor = texture(u_Texture, f_UV) * vec4(u_Color, 1.0);
}