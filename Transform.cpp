// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    auto x = axis.x;
    auto y = axis.y;
    auto z = axis.z;
    auto r = glm::radians(degrees);
    auto c = glm::cos(r);
    auto s = glm::sin(r);
    // column-major
	return mat3(
      c + x*x*(1-c),  z*s + x*y*(1-c), -y*s + x*z*(1-c),
      x*y*(1-c) - z*s, c + y*y*(1-c), x*s + y*z*(1-c),
      y*s + x*z*(1-c), -x*s + y*z*(1-c), c + z*z*(1-c)
    );
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    auto r = rotate(degrees, up);
    eye = r*eye;
    up = r*up;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    auto left = glm::normalize(glm::cross(eye, up));
    auto r = rotate(degrees, left);
    eye = r*eye;
    up = r*up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    auto w = glm::normalize(eye);
    auto u = glm::normalize(glm::cross(up, w));
    auto v = glm::cross(w, u);
    auto e = eye;
	return mat4(
        u.x, v.x, w.x, 0, // col 1
        u.y, v.y, w.y, 0,
        u.z, v.z, w.z, 0,
        -u.x*e.x-u.y*e.y-u.z*e.z, -v.x*e.x-v.y*e.y-v.z*e.z, -w.x*e.x-w.y*e.y-w.z*e.z, 1
    );
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    auto d = 1.0f / glm::tan(fovy / 2.0f);
    auto n = zNear;
    auto f = zFar;
    auto a = aspect;
	return mat4(
        d/a, 0, 0, 0, // col 1
        0, d, 0, 0,
        0, 0, -(f+n)/(f-n), -1,
        0, 0, -(2*f*n)/(f-n), 0
    );
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
	return mat4(
        sx, 0, 0, 0, // col 1
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
    );
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
	return mat4(
        1, 0, 0, 0, // col 1
        0, 1, 0, 0,
        0, 0, 1, 0,
        tx, ty, tz, 1
    );
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
