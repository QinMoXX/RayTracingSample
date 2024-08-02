#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

#include "hittable.h"
#include "material.h"

class camera {
  public:
    
    double aspect_ratio = 1.0;  // 渲染图宽高比
    int    image_width  = 100;  // 渲染图像素宽度
    int    image_height;   // 渲染图高度
    int    samples_per_pixel = 10; //每采样点随机采样点数
    int    max_depth         = 10;   // 限制最大递归深度
    double vfov = 90; //垂直fov

    point3 lookfrom = point3(0,0,0);   
    point3 lookat   = point3(0,0,-1);  //相机朝向
    vec3   vup      = vec3(0,1,0);     //相机直立空间向上坐标


    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

  private:
    double pixel_samples_scale; //采样颜色比例因子
    point3 center;         // 相机坐标
    point3 pixel00_loc;    // 屏幕像素原点位置
    vec3   pixel_delta_u;  // 像素向右偏移量
    vec3   pixel_delta_v;  // 像素向下偏移量
    
    vec3   u, v, w; //相机空间基坐标

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = lookfrom;
        // 视窗尺寸计算
        auto focal_length = (lookfrom - lookat).length();
        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2 * h * focal_length;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        // 计算摄像机基坐标
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // 计算横跨水平视图和纵向视图边缘的向量。
        vec3 viewport_u = viewport_width * u;    
        vec3 viewport_v = viewport_height * -v;  

        // 计算从像素水平和垂直增量向量。
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // 计算左上像素的位置。
        auto viewport_upper_left = center - (focal_length * w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const {
        //构造一个摄像机光线，从原点出发，获取到像素位置 i，j 周围的随机射线。

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((i + offset.x()) * pixel_delta_u)
                          + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // 返回 [-.5,+.5] 之间的随机坐标
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

     color ray_color(const ray& r, int depth, const hittable& world) const {
        
        if (depth <= 0)
            return color(0,0,0);
        hit_record rec;

        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth-1, world);
            return color(0,0,0);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};

#endif