#version 330 core

in vec4 positionAttribute;

uniform mat4 uniformView;
uniform mat4 uniformProjection;
uniform mat4 uniformModel;


void main()
{
  gl_Position = uniformProjection * uniformView * uniformModel* positionAttribute;
}