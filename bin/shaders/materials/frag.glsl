in vec4 outCol;
in vec3 outPos;
in vec2 outTexCoord;
in vec3 outNorm;

layout(binding = 0) uniform sampler2D Tex0;
layout(location = 0) out vec4 OutPosId;
layout(location = 1) out vec4 OutNormalIsShade;
layout(location = 2) out vec4 OutKa;
layout(location = 3) out vec4 OutKd;
layout(location = 4) out vec4 OutKsPh;
layout(location = 5) out vec4 OutColor;

uniform vec4 MtlKa4;
uniform vec4 MtlKdTrans;
uniform vec4 MtlKsPh;
uniform vec3 CamLoc;
uniform vec4 IsTexture0123;

void main( void )
{
  vec4 color;
  if (IsTexture0123.x != 0)
  {
    vec4 tc = texture(Tex0, outTexCoord);
    color = vec4(tc.rgb, 1);
  }
  else
  {
    color = MtlKa4;
  }
  OutColor = color;
  OutPosId = vec4(outPos, 1);
  OutNormalIsShade = vec4(outNorm, 1);
  OutKa = MtlKa4;
  OutKd = MtlKdTrans;
  OutKsPh = MtlKsPh;
}