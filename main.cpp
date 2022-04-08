#include <iostream>
#include <fstream>
#include <cmath>

#include "utils.h"
#include "color.h"
#include "hittable_list.h"
#include "camera.h"
#include "objects/sphere.h"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
    using namespace std;
#pragma region fileInfo
    ofstream FileStream;
    FileStream.open("./output.ppm");
    const auto aspect_ratio = 16.0/9.0;
    const int image_width = 1280;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    FileStream << "P3\n" << image_width << ' ' << image_height << "\n255\n";
#pragma endregion
#pragma region World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,0), 100));
#pragma endregion
#pragma region Camera
    camera cam;
#pragma endregion
#pragma region Render
    for(int y = image_height-1; y >= 0; --y){  //j
        cout << 100-round((double(y)/double(image_height))*100)  << '\n';
        for(int x = 0; x < image_width; ++x){  //i
            color pixel_color(0,0,0);
            for(int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = double(x + random_double()) / (image_width-1);
                auto v = double(y + random_double()) / (image_height-1);
                ray r = cam.getray(u,v);
                pixel_color += ray_color(r, world);
            }
            write_color(FileStream, pixel_color, samples_per_pixel);
        }
    }
#pragma endregion
#pragma region Disposal
    FileStream.close();
#pragma endregion
}
