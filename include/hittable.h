#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "interval.h"
class material;
class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    shared_ptr<material> mat;
    
    /*记录模型正反面
    * front_face 是根据射线检测获取正反面标识
    * 正反面的法线相反
    * 射线检测反面与外法线点乘将始终为正数
    * 射线检测正面与外法线点乘将始终为负数
    */
    void set_face_normal(const ray& r, const vec3& outward_normal) {

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }


};

class hittable {
  public:

    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
    
};

#endif