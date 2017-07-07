uniform vec2 center;
uniform float radius;
uniform vec4 color;

void main()
{
    float r = distance(gl_FragCoord.xy, center);
    gl_FragColor = color * vec4(vec3(1.0),1.0-(r/radius));

    // gl_FragColor = color * vec4(0.5+0.5*step(r,radius)); // DEBUG
}
