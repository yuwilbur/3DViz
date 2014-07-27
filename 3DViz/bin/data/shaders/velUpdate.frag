#version 120
#extension GL_ARB_texture_rectangle : enable
#define KERNEL_SIZE 9

uniform sampler2DRect backbuffer;   // recive the previus velocity texture
uniform sampler2DRect posData;      // recive the position texture

uniform vec2  screen;

uniform float timestep;

uniform vec3 gravity_position;
uniform float gravity_strength;

void main(void){
  vec2 st = gl_TexCoord[0].st;    // gets the position of the pixel that it´s dealing with...

  vec3 pos = texture2DRect( posData, st).xyz;      // ... for gettinh the position data 
  vec3 vel = texture2DRect( backbuffer, st ).xyz;  // and the velocity

  // Calculates what´s going to be the next position without updating it.
  // Just to see if it collide with the borders of the FBO texture
  //
  vec3 nextPos = pos;
  nextPos += vel * timestep;

  vec3 grav_delta = gravity_position - pos;
  float dist = length(grav_delta);
  float strength = 0.0;
  // Attractive force.
  if (st.x < 300) {
    strength = gravity_strength / (5000.0 + dist / 2000.0);
  }
  else {
    strength = gravity_strength / (5000.0 + dist * sqrt(dist) / 2000.0);
  }

  // Repulsive force.
  if (st.x < 300) {
    strength -= gravity_strength / (2 + 45 * dist);
  }
  else {
    strength -= gravity_strength / (5.0 + 5 * dist * sqrt(dist));
  }

  vel += strength * normalize(grav_delta);
  vel *= 0.96;

  gl_FragColor = vec4(vel.x,vel.y,vel.z,1.0);   // Then save the vel data into the velocity FBO
}
