#version 120
#extension GL_ARB_texture_rectangle : enable

// This fill the billboard made on the Geometry Shader with a texture

uniform sampler2DRect sparkTex;
uniform sampler2DRect albumArt;
uniform vec4 color;

void main() {
    vec2 st = gl_TexCoord[0].st;
    gl_FragColor = texture2DRect(sparkTex, st);
    vec4 album_color = texture2DRect(albumArt, glFragCoord);
    vec4 col = color / 255.0;
    /*
    gl_FragColor[0] = gl_FragColor[0] * col[0];
    gl_FragColor[1] = gl_FragColor[1] * col[1];
    gl_FragColor[2] = gl_FragColor[2] * col[2];
    */
    gl_FragColor = album_color;
    gl_FragColor[3] = 1;
}
