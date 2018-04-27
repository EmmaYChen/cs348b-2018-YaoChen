
/*
    pbrt source code is Copyright(c) 1998-2016
                        Matt Pharr, Greg Humphreys, and Wenzel Jakob.

    This file is part of pbrt.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */


// shapes/sphere.cpp*
#include "shapes/newde.h"
#include "sampling.h"
#include "paramset.h"
#include "efloat.h"
#include "stats.h"
#include <math.h>
namespace pbrt {

// Sphere Method Definitions

Bounds3f NewDE::ObjectBound() const {
    return Bounds3f(Point3f(-100, -100, -100),
                    Point3f(100, 100, 100));
}

//Float NewDE::Area() const { return  Infinity; }
Float NewDE::Area() const { return  4* Pi* Pi* center.x * center.y;}

Float max(float a,float b){
    if (a>=b) return a;
    else return b;
}

Float min(float a,float b){
    if (a>=b) return b;
    else return a;
}

Float NewDE::Evaluate(const Point3f &p) const {
   
    Point3f p1 = p;
    Vector2f p_xz = Vector2f(p1.x + 29,p1.z);
    Vector2f p2 = Vector2f((p_xz).Length() - center.x, p1.y);
    float d3 = p2.Length() - center.y;

    Point3f q = Abs(p1);
    float d1 = max(q.z-center.y, max((q.x*0.866025+q.y*0.5),q.y)-center.x);
    float d2 = 0.2 * sin(2*p.x)*sin(2*p.y)*sin(2*p.z);
    return min(d1+d2,d3+d2);
    
}


std::shared_ptr<Shape> CreateNewDEShape(const Transform *o2w,
                                         const Transform *w2o,
                                         bool reverseOrientation,
                                         const ParamSet &params) {
                                        
    Float cellSize = params.FindOneFloat("cellSize", 8.0);
    int maxIters = params.FindOneFloat("maxiters", 1000);
    Float hitEpsilon = params.FindOneFloat("hitEpsilon", 0.00001);
    Float rayEpsilonMultiplier = params.FindOneFloat("rayEpsilonMultiplier", 10);
    Float normalEpsilon = params.FindOneFloat("normalEpsilon", 0.00001);
    Float x = params.FindOneFloat("center_x", 10);
    Float y = params.FindOneFloat("center_y", 4);
    Vector2f center = Vector2f(x,y);
    return std::make_shared<NewDE>(o2w, w2o, reverseOrientation, cellSize, maxIters, hitEpsilon, 
                                        rayEpsilonMultiplier, normalEpsilon,center);
}

}  // namespace pbrt
