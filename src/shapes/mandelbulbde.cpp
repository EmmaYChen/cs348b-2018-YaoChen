
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
#include "shapes/mandelbulbde.h"
#include "sampling.h"
#include "paramset.h"
#include "efloat.h"
#include "stats.h"

namespace pbrt {

// Sphere Method Definitions

Bounds3f MandelbulbDE::ObjectBound() const {
    return Bounds3f(Point3f(-radius, -radius, -radius),
                    Point3f(radius, radius, radius));
}

Float MandelbulbDE::Area() const { return Infinity; }

Float MandelbulbDE::Evaluate(const Point3f &p) const {
    const float bailout = 2.0f;
    const float Power = (float)mandelbulbPower;
    Point3f z = p;
    float dr = 1.0;
    float r = 0.0;
    for (int i = 0; i < fractalIters; i++) {
        r = (z-Point3f(0,0,0)).Length();
        if (r>bailout) break;

        // convert to polar coordinates
        float theta = acos(z.z/r);
        float phi = atan2(z.y,z.x);
        dr =  pow( r, Power-1.0)*Power*dr + 1.0;

        // scale and rotate the point
        float zr = pow( r,Power);
        theta = theta*Power;
        phi = phi*Power;

        // convert back to cartesian coordinates
        z = zr*Point3f(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
        z += p;
    }
    return 0.5*log(r)*r/dr;
}

std::shared_ptr<Shape> CreateMandelbulbDEShape(const Transform *o2w,
                                         const Transform *w2o,
                                         bool reverseOrientation,
                                         const ParamSet &params) {
                                        
    Float radius = params.FindOneFloat("radius", 1.f);
    int maxIters = params.FindOneFloat("maxiters", 1000);
    Float hitEpsilon = params.FindOneFloat("hitEpsilon", 0.00001);
    Float rayEpsilonMultiplier = params.FindOneFloat("rayEpsilonMultiplier", 10);
    Float normalEpsilon = params.FindOneFloat("normalEpsilon", 0.01);
    int fractalIters = params.FindOneFloat("fractalIters", 1000);
    int mandelbulbPower = params.FindOneFloat("mandelbulbPower", 8);
    return std::make_shared<MandelbulbDE>(o2w, w2o, reverseOrientation, radius, maxIters, hitEpsilon, 
                                        rayEpsilonMultiplier, normalEpsilon, fractalIters, mandelbulbPower);
}

}  // namespace pbrt
