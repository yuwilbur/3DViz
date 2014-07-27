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


  // If it´s going to collide change the velocity course
  //
  if ( nextPos.x < 0.0)
    vel.x = abs(vel.x);

  if ( nextPos.x > 1.0)
    vel.x = -abs(vel.x);

  if (nextPos.y < 0.0)
    vel.y = abs(vel.y);

  if ( nextPos.y > 1.0)
    vel.y = -abs(vel.y);
  
  if ( nextPos.z > 100.0)
    vel.z = -abs(vel.z);

  if ( nextPos.z < -100.0)
    vel.z = abs(vel.z);

  vec3 grav_delta = gravity_position - pos;
  float strength = gravity_strength / (1.0 + length(grav_delta));
  vel += strength * normalize(grav_delta);

  gl_FragColor = vec4(vel.x,vel.y,vel.z,1.0);   // Then save the vel data into the velocity FBO
}
