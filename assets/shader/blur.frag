#version 120

uniform sampler2D source;
uniform vec2 blur_offset;

const float BLUR_WEIGHT[7] = float[7]
(
    924.0 / 4096.0,
    792.0 / 4096.0,
    495.0 / 4096.0,
    220.0 / 4096.0,
    66.0 / 4096.0,
    12.0 / 4096.0,
    1.0 / 4096.0
);

void main()
{
    vec4 pixel = texture2D(source, gl_TexCoord[0].xy) * BLUR_WEIGHT[0];
    for(int i = 1; i < 7; i++)
    {
        pixel += texture2D(source, gl_TexCoord[0].xy - i*blur_offset) * BLUR_WEIGHT[i];
        pixel += texture2D(source, gl_TexCoord[0].xy + i*blur_offset) * BLUR_WEIGHT[i];
    }

    gl_FragColor = pixel;
}
