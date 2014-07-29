#version 120
#extension GL_ARB_texture_rectangle : enable
#define KERNEL_SIZE 9

uniform sampler2DRect backbuffer;   // recive the previus velocity texture
uniform sampler2DRect posData;      // recive the position texture
uniform sampler2DRect restingPosData;

uniform vec2  screen;

uniform float timestep;

uniform vec3 gravity_position;
uniform float gravity_strength;
uniform vec3 gravity_position2;
uniform float gravity_strength2;
uniform float pulse;

void main(void){
  vec2 st = gl_TexCoord[0].st;    // gets the position of the pixel that it´s dealing with...

  vec3 pos = texture2DRect( posData, st).xyz;      // ... for gettinh the position data 
  vec3 resting_pos = texture2DRect( restingPosData, st).xyz;      // ... for gettinh the position data 
  vec3 vel = texture2DRect( backbuffer, st ).xyz;  // and the velocity

  // Calculates what´s going to be the next position without updating it.
  // Just to see if it collide with the borders of the FBO texture
  //
  vec3 nextPos = pos;
  nextPos += vel * timestep;

  // Gravity 1
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

  // Gravity 2
  vec3 grav_delta2 = gravity_position2 - pos;
  float dist2 = length(grav_delta2);
  float strength2 = 0.0;
  // Attractive force.
  if (st.x < 300) {
    strength2 = gravity_strength2 / (5000.0 + dist2 / 2000.0);
  }
  else {
    strength2 = gravity_strength2 / (5000.0 + dist2 * sqrt(dist2) / 2000.0);
  }

  // Repulsive force.
  if (st.x < 300) {
    strength2 -= gravity_strength2 / (2 + 45 * dist2);
  }
  else {
    strength2 -= gravity_strength2 / (5.0 + 5 * dist2 * sqrt(dist2));
  }

  vel += strength2 * normalize(grav_delta2);

  // Pull back force.
  vec3 pull_delta = resting_pos - pos;
  vel += pull_delta / 1000.0;

  vel *= 0.985;

  gl_FragColor = vec4(vel.x,vel.y,vel.z,1.0);   // Then save the vel data into the velocity FBO
}
