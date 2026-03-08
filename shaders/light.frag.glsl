# version 330 core
// Do not use any version older than 330!

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Inputs to the fragment shader are the outputs of the same name of the vertex shader.
// Note that the default output, gl_Position, is inaccessible!
in vec3 mynormal; 
in vec4 myvertex; 

// You will certainly need this matrix for your lighting calculations
uniform mat4 modelview;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

uniform vec3 color;

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.
// I use ambient, diffuse, specular, shininess. 
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emission;
uniform float shininess;

vec4 light(vec4 pos, vec3 norm, vec4 diff, float shin, vec4 spec, vec4 lpos[numLights], vec4 lcolor[numLights]) {
    vec4 color = vec4(0, 0, 0, 0);
    vec3 posh = pos.xyz / pos.w;
    vec3 eye = vec3(0, 0, 0);
    vec3 eyedir = normalize(eye - posh);
    vec3 normal = normalize(norm);

    for(int i = 0; i < numused; i++) {
        vec3 lposh = lpos[i].xyz / lpos[i].w;
        vec3 ldir = normalize(lposh - posh);
        vec3 halfvec = normalize(ldir + eyedir);

        float nDotL = dot(normal, ldir);
        vec4 lambert = diff * lcolor[i] * max(nDotL, 0.0);

        float nDotH = dot(normal, halfvec);
        vec4 phong = spec * lcolor[i] * pow(max(nDotH, 0.0), shin);
        color += lambert + phong;
    }
    return color;
}

void main (void)
{
    if (enablelighting) {
        fragColor = ambient + emission + light(myvertex, mynormal, diffuse, shininess, specular, lightposn, lightcolor);
        //fragColor = vec4(1.0, 0.0, 0.0, 1.0);
    } else {
        fragColor = vec4(color, 1.0f);
    }
}
