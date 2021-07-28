#ShaderSegment:vertex
#version 330 core
layout(location = 0) in vec3 a_Position;   // the position variable has attribute position 0
layout(location = 1) in vec3 a_Color;   // the position variable has attribute position 0

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

out vec3 out_Color;

void main()
{
    gl_Position = u_ProjectionView * u_Model * vec4(a_Position, 1.0);
    out_Color = a_Color;
}



#ShaderSegment:fragment
#version 330 core
out vec4 FragColor;
in vec3 out_Color;

uniform vec3 u_Color;
  
void main()
{
    // FragColor = vec4(u_Color, 1.0);
    // FragColor = vec4(out_Color, 1.0) * vec4(u_Color, 1.0f);
    FragColor = vec4(0.56471, 0.56471, 0.56471, 1.0) * vec4(u_Color, 1.0f);
}