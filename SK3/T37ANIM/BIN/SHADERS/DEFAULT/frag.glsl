#version 430

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec3 DrawNormal;
in vec3 DrawPos;

uniform float Time;
uniform vec3 CamLoc;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ph;
uniform float Trans;

mat4 MatrRotateY( float AngleInDegree )
{
  float A = AngleInDegree * 3.14159265358979323846 / 180, si = sin(A), co = cos(A);
  mat4 m;

  m[0] = vec4(co, 0, si, 0);
  m[1] = vec4(0, 1, 0, 0);
  m[2] = vec4(-si, 0, co, 0);
  m[3] = vec4(0, 0, 0, 1);
  
  return m;
}

vec3 Shade( vec3 P, vec3 N, vec3 L, vec3 LC )
{
  vec3 color;
  vec3 V = normalize(P - CamLoc);
  vec3 R = reflect(V, N);
  
  ;// ambient
  color = Ka;

  ;// diffuse
  color += Ka * LC * max(dot(N, L), 0.01);

  ;// specular
  color += Ks * pow(max(dot(R, L), 0.01), Ph) * LC;

  return color;  
}
          	
void main( void )
{
  OutColor = vec4(Shade(DrawPos, normalize(DrawNormal), mat3(MatrRotateY(Time * 100)) * normalize(vec3(4, -2, 4)), vec3(0.8, 0, 0)) +
                  Shade(DrawPos, normalize(DrawNormal), normalize(vec3(-3, -1, 6)), vec3(0, 0.5, 0.8)  * (1 - sin(1.3 * Time))) + 
		  Shade(DrawPos, normalize(DrawNormal), normalize(vec3(7, 7, 0)), vec3(0.5, 0.48, 0.4)), 1);
}