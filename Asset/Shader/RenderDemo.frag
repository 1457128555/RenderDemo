#version 300 es

precision mediump float;

in vec4 oTexCoord;

out vec4 FragColor;

uniform sampler2D uImageTex;
uniform sampler2D uBaseTableTex;

uniform float uLutIntensity;  // 添加 LUT 强度控制 (0.0-1.0)

vec4 lut3d(highp vec4 textureColor)
{
    mediump float blueColor = textureColor.b * 63.0;

    mediump vec2 quad1;
    quad1.y = min(8.0,max(0.0,floor(floor(blueColor) / 8.0)));
    quad1.x = min(8.0,max(0.0,floor(blueColor) - (quad1.y * 8.0)));

    mediump vec2 quad2;
    quad2.y = floor(ceil(blueColor) / 8.0);
    quad2.x = ceil(blueColor) - (quad2.y * 8.0);

    highp vec2 texPos1;
    texPos1.x = (quad1.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.r);
    texPos1.y = (quad1.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.g);

    highp vec2 texPos2;
    texPos2.x = (quad2.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.r);
    texPos2.y = (quad2.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.g);

    lowp vec4 newColor1 = texture(uBaseTableTex, texPos1);
    lowp vec4 newColor2 = texture(uBaseTableTex, texPos2);

    mediump vec4 newColor = mix(newColor1, newColor2, fract(blueColor));
    return newColor;
}

void main() 
{
    vec4 orgColor = texture(uImageTex, oTexCoord.xy);
    vec4 lutColor = lut3d(orgColor);

    FragColor = mix(orgColor, lutColor, uLutIntensity);
}