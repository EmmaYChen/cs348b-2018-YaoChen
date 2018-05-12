
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
#include "shapes/distanceestimator.h"
#include "sampling.h"
#include "paramset.h"
#include "efloat.h"
#include "stats.h"

namespace pbrt {

// // Sphere Method Definitions
// Float DistanceEstimator::Evaluate(const Point3f& p)const{
//     // f(x) = sqrt(x^2+y^2+z^2) - radius 
//     Float distance = std::sqrt(p.x * p.x + p.y * p.y + p.z * p.z) - radius;
//     return distance;
// }

bool DistanceEstimator::Intersect(const Ray &r, Float *tHit, SurfaceInteraction *isect,
                       bool testAlphaTexture) const {
   
    float d = 0.0;
    float t = 0.0;

    Ray ray = (*WorldToObject)(r);

    Point3f pHit;

    int i =0;
    while (t < ray.tMax && i < maxIters){
        d =  Evaluate(ray(t));
        if (d < hitEpsilon && d>0){
            pHit = ray(t);
            if (tHit != nullptr)
                *tHit = (Float)t;

            // calculate isect 
            Vector3f pError = Abs(Vector3f(rayEpsilonMultiplier * hitEpsilon, 
                                       rayEpsilonMultiplier * hitEpsilon,
                                       rayEpsilonMultiplier * hitEpsilon));

            Normal3f dndu = Normal3f(0,0,0);
            Normal3f dndv = Normal3f(0,0,0);
            // Compute error bounds for sphere intersection

            Vector3f normal = CalculateNormal(pHit, normalEpsilon, -ray.d);

            Vector3f dPdu, dPdv;

            CoordinateSystem(normal, &dPdu, &dPdv);

            //Vector3d testNormal = Normalize(Cross(dPdu, dPdv));

            //CHECK_DOUBLE_EQ(Dot(testNormal, normal), 1.0);

            if (isect != nullptr)
                *isect = (*ObjectToWorld)(SurfaceInteraction(pHit, pError, Point2f(0.0, 0.0), -ray.d, dPdu, dPdv, dndu, dndv, ray.time, this));
            return true;

            }
        t += d/(ray.d).Length();
        i++;
    }
    return false;
}

// Bounds3f DistanceEstimator::ObjectBound() const {
//     return Bounds3f(Point3f(-radius, -radius, -radius),
//                     Point3f(radius, radius, radius));
// }

//Float DistanceEstimator::Area() const { return 2* Pi * radius * (radius - (-radius)); }

Interaction DistanceEstimator::Sample(const Point2f &u, Float *pdf) const {
    LOG(FATAL) << "Cone::Sample not implemented.";
    return Interaction();
}

Vector3f DistanceEstimator::CalculateNormal(const Point3f& pos, float eps, 
        const Vector3f& defaultNormal) const {
        const Vector3f v1 = Vector3f( 1.0,-1.0,-1.0);
        const Vector3f v2 = Vector3f(-1.0,-1.0, 1.0);
        const Vector3f v3 = Vector3f(-1.0, 1.0,-1.0);
        const Vector3f v4 = Vector3f( 1.0, 1.0, 1.0);

        const Vector3f normal = v1 * Evaluate( pos + v1*eps ) +
                    v2 * Evaluate( pos + v2*eps ) +
                    v3 * Evaluate( pos + v3*eps ) +
                    v4 * Evaluate( pos + v4*eps );
        const Float length = normal.Length();

        return length > 0 ? (normal/length) : defaultNormal;
}

// std::shared_ptr<Shape> CreateDistanceEstimatorShape(const Transform *o2w,
//                                          const Transform *w2o,
//                                          bool reverseOrientation,
//                                          const ParamSet &params) {
                                    
//     Float radius = params.FindOneFloat("radius", 1.f);
//     int maxIters = params.FindOneFloat("maxIters", 1000);
//     Float hitEpsilon = params.FindOneFloat("hitEpsilon", 0.001);
//     Float rayEpsilonMultiplier = params.FindOneFloat("rayEpsilonMultiplier", 10);
//     Float normalEpsilon = params.FindOneFloat("normalEpsilon", 0.01);

//     return std::make_shared<DistanceEstimator>(o2w, w2o, reverseOrientation, radius, maxIters, hitEpsilon,
//                                                 rayEpsilonMultiplier, normalEpsilon);
// }

}  // namespace pbrt
