#pragma

struct Vec3f {
    float x, y, z;
};

struct Vec4f {
    float x, y, z, w;
};

struct Pose {
    Vec4f orientation;
    Vec3f position;
};