#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect prevPosData;  // recive the previus position texture
uniform sampler2DRect velData;      // recive the velocity texture

uniform float timestep;
uniform float pulse;

void main(void){
    vec2 st = gl_TexCoord[0].st;    // gets the position of the pixel that it´s dealing with...
    
    vec3 pos = texture2DRect( prevPosData, st ).xyz;
    vec3 vel = texture2DRect( velData, st ).xyz;     // Fetch both the pos and vel.
    
    pos += (1 - 12 * pulse) * vel * timestep; // Updates the position
    
    gl_FragColor.rgba = vec4(pos.x,pos.y, pos.z,1.0);  // And finaly it store it on the position FBO
}
