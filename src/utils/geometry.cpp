#include <cmath>

#include "geometry.hpp"

/**
 * @fn rotation
 * @desc Rotate a Vec2 by degree.
 */
void rotation(Vec2* v, float degree) {

    float vx = v->x;
    v->x = std::cos(degree) * v->x - std::sin(degree) * v->y;
    v->y = std::sin(degree) * vx + std::cos(degree) * v->y;

}

void rotationX(Vec3* v, float degree) {

    float vy = v->y;
    v->y = std::cos(degree) * v->y - std::sin(degree) * v->z;
    v->z = std::sin(degree) * vy + std::cos(degree) * v->z;

}

void rotationY(Vec3* v, float degree) {

    float vx = v->x;
    v->x = std::cos(degree) * v->x + std::sin(degree) * v->z;
    v->z = - std::sin(degree) * vx + std::cos(degree) * v->z;

}

void rotationZ(Vec3* v, float degree) {

    float vx = v->x;
    v->x = std::cos(degree) * v->x - std::sin(degree) * v->y;
    v->y = std::sin(degree) * vx + std::cos(degree) * v->y;

}

void initCamera(Image* i, Camera* c, float fov) {

    float size_x = 1/i->heigthUnit();
    float size_y = 1/i->weigthUnit();

    if (size_x > size_y) {

        c->fov_angle_x = (fov/2);
        c->fov_angle_y = (c->fov_angle_x * size_y) / size_x;

    } else {

        c->fov_angle_y = (fov/2);
        c->fov_angle_x = (c->fov_angle_y * size_x) / size_y;

    }

}

Vec2 translate2D(Vec3* v, Camera* c) {
    Vec2 result(-1., -1.);

    if (v->z <= 0) {
        return result;
    }

    float far_screen_y = c->fov_angle_y * v->z + 1;
    float far_screen_x = c->fov_angle_x * v->z + 1;

    result.x = v->x / far_screen_x;
    result.y = v->y / far_screen_y;

    return result;
}
