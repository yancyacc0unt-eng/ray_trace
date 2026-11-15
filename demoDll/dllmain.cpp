#include "pch.h"
#include <Windows.h>

#include <cstdint>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <limits>

#undef max
#undef min

namespace Renderer
{
    constexpr double PI = 3.14159265358979323846;
    constexpr int MAX_BOUNCES = 16;
    constexpr double EPSILON = 0.0001;

    short FRAME_WIDTH = 256*2*2;
    short FRAME_HEIGHT = 144*2*2;

    using RGB = std::tuple<uint8_t, uint8_t, uint8_t>;
    using Frame = std::vector<RGB>;

    struct Vec3
    {
        double x, y, z;

        Vec3 operator+(const Vec3& v) const
        {
            return { x + v.x, y + v.y, z + v.z };
        }

        Vec3 operator-(const Vec3& v) const
        {
            return { x - v.x, y - v.y, z - v.z };
        }

        Vec3 operator*(double s) const
        {
            return { x * s, y * s, z * s };
        }

        Vec3 operator/(double s) const
        {
            return { x / s, y / s, z / s };
        }

        Vec3 operator-() const
        {
            return { -x, -y, -z };
        }

        double dot(const Vec3& v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        Vec3 cross(const Vec3& v) const
        {
            return {
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            };
        }

        double length() const
        {
            return std::sqrt(dot(*this));
        }

        Vec3 normalized() const
        {
            double l = length();

            if (l < EPSILON)
                return { 0, 0, 0 };

            return *this / l;
        }

        Vec3 reflect(const Vec3& normal) const
        {
            return *this - normal * (2.0 * dot(normal));
        }

        bool refract(
            const Vec3& normal,
            double eta,
            Vec3& result
        ) const
        {
            double cosI = std::clamp(
                -dot(normal), -1.0, 1.0
            );

            double sin2T = eta * eta *
                (1.0 - cosI * cosI);

            if (sin2T > 1.0)
                return false;

            double cosT = std::sqrt(1.0 - sin2T);

            result = *this * eta +
                normal * (eta * cosI - cosT);

            result = result.normalized();

            return true;
        }
    };

    struct Ray
    {
        Vec3 origin;
        Vec3 direction;

        Vec3 at(double t) const
        {
            return origin + direction * t;
        }
    };

    enum class MaterialType
    {
        Metal,
        Glass,
        Plastic,
        Concrete
    };

    struct Material
    {
        Vec3 color;
        MaterialType type;

        double reflectivity;
        double roughness;
        double refractiveIndex;
    };

    struct Hit
    {
        double distance = std::numeric_limits<double>::max();

        Vec3 position;
        Vec3 normal;

        Material material;
        bool frontFace = true;

        void setFaceNormal(
            const Ray& ray,
            const Vec3& outwardNormal
        )
        {
            frontFace = ray.direction.dot(outwardNormal) < 0;

            normal = frontFace
                ? outwardNormal
                : -outwardNormal;
        }
    };

    struct Sphere
    {
        Vec3 center;
        double radius;
        Material material;
    };

    struct Plane
    {
        double y;
        Material material;
    };

    struct Triangle
    {
        Vec3 a, b, c;
    };

    struct Mesh
    {
        std::vector<Triangle> triangles;
        Material material;
    };

    struct Cube
    {
        Vec3 center;
        double halfSize;
        Material material;
    };

    struct Scene
    {
        std::vector<Sphere> spheres;
        std::vector<Mesh> meshes;
        std::vector<Cube> cubes;
        Plane ground;
    };

    struct Camera
    {
        Vec3 position;
        Vec3 forward;
        Vec3 right;
        Vec3 up;

        double viewportHeight;
        double viewportWidth;

        void initialize(
            Vec3 pos,
            Vec3 target,
            double aspect
        )
        {
            position = pos;

            forward = (target - pos).normalized();

            Vec3 worldUp = { 0, 1, 0 };

            right = forward.cross(worldUp).normalized();
            up = right.cross(forward).normalized();

            double fov = 60.0 * PI / 180.0;

            viewportHeight = 2.0 * std::tan(fov / 2.0);
            viewportWidth = viewportHeight * aspect;
        }

        Ray generateRay(double u, double v) const
        {
            Vec3 direction =
                forward +
                right * ((u - 0.5) * viewportWidth) +
                up * ((v - 0.5) * viewportHeight);

            return {
                position,
                direction.normalized()
            };
        }
    };

    const Vec3 LIGHT_DIRECTION =
        Vec3{ -1, -2, -1 }.normalized();

    const Vec3 LIGHT_COLOR = {
        1.0, 0.97, 0.90
    };

    const Vec3 SKY_COLOR = {
        0.35, 0.80, 0.95
    };

    Vec3 multiply(const Vec3& a, const Vec3& b)
    {
        return {
            a.x * b.x,
            a.y * b.y,
            a.z * b.z
        };
    }

    Vec3 clampColor(const Vec3& c)
    {
        return {
            std::clamp(c.x, 0.0, 1.0),
            std::clamp(c.y, 0.0, 1.0),
            std::clamp(c.z, 0.0, 1.0)
        };
    }

    RGB toRGB(const Vec3& color)
    {
        Vec3 c = clampColor(color);

        auto convert = [](double v) -> uint8_t
            {
                v = std::pow(v, 1.0 / 2.2);

                return static_cast<uint8_t>(
                    std::clamp(v * 255.0, 0.0, 255.0)
                    );
            };

        return {
            convert(c.x),
            convert(c.y),
            convert(c.z)
        };
    }

    bool intersectSphere(
        const Ray& ray,
        const Sphere& sphere,
        Hit& hit
    )
    {
        Vec3 oc = ray.origin - sphere.center;

        double a = ray.direction.dot(ray.direction);
        double halfB = oc.dot(ray.direction);
        double c = oc.dot(oc) -
            sphere.radius * sphere.radius;

        double discriminant =
            halfB * halfB - a * c;

        if (discriminant < 0)
            return false;

        double sqrtd = std::sqrt(discriminant);

        double t = (-halfB - sqrtd) / a;

        if (t < EPSILON || t >= hit.distance)
        {
            t = (-halfB + sqrtd) / a;

            if (t < EPSILON || t >= hit.distance)
                return false;
        }

        hit.distance = t;
        hit.position = ray.at(t);

        Vec3 outward =
            (hit.position - sphere.center) / sphere.radius;

        hit.setFaceNormal(ray, outward);
        hit.material = sphere.material;

        return true;
    }

    bool intersectPlane(
        const Ray& ray,
        const Plane& plane,
        Hit& hit
    )
    {
        if (std::abs(ray.direction.y) < EPSILON)
            return false;

        double t = (plane.y - ray.origin.y) /
            ray.direction.y;

        if (t < EPSILON || t >= hit.distance)
            return false;

        hit.distance = t;
        hit.position = ray.at(t);

        hit.setFaceNormal(
            ray,
            { 0, 1, 0 }
        );

        hit.material = plane.material;

        return true;
    }

    bool intersectTriangle(
        const Ray& ray,
        const Triangle& triangle,
        double& t,
        Vec3& normal
    )
    {
        Vec3 edge1 = triangle.b - triangle.a;
        Vec3 edge2 = triangle.c - triangle.a;

        Vec3 h = ray.direction.cross(edge2);

        double determinant = edge1.dot(h);

        if (std::abs(determinant) < EPSILON)
            return false;

        double invDet = 1.0 / determinant;

        Vec3 s = ray.origin - triangle.a;

        double u = invDet * s.dot(h);

        if (u < 0 || u > 1)
            return false;

        Vec3 q = s.cross(edge1);

        double v = invDet * ray.direction.dot(q);

        if (v < 0 || u + v > 1)
            return false;

        t = invDet * edge2.dot(q);

        if (t < EPSILON)
            return false;

        normal = edge1.cross(edge2).normalized();

        return true;
    }

    bool intersectMesh(
        const Ray& ray,
        const Mesh& mesh,
        Hit& hit
    )
    {
        bool found = false;

        for (const auto& triangle : mesh.triangles)
        {
            double t;
            Vec3 normal;

            if (intersectTriangle(ray, triangle, t, normal)
                && t < hit.distance)
            {
                hit.distance = t;
                hit.position = ray.at(t);

                hit.setFaceNormal(ray, normal);
                hit.material = mesh.material;

                found = true;
            }
        }

        return found;
    }

    bool intersectCube(
        const Ray& ray,
        const Cube& cube,
        Hit& hit
    )
    {
        Vec3 minimum = cube.center -
            Vec3{ cube.halfSize, cube.halfSize, cube.halfSize };

        Vec3 maximum = cube.center +
            Vec3{ cube.halfSize, cube.halfSize, cube.halfSize };

        double tMin = -std::numeric_limits<double>::max();
        double tMax = std::numeric_limits<double>::max();

        Vec3 entryNormal = { 0, 0, 0 };
        Vec3 exitNormal = { 0, 0, 0 };

        for (int axis = 0; axis < 3; ++axis)
        {
            double origin = axis == 0 ? ray.origin.x :
                axis == 1 ? ray.origin.y : ray.origin.z;

            double direction = axis == 0 ? ray.direction.x :
                axis == 1 ? ray.direction.y : ray.direction.z;

            double lo = axis == 0 ? minimum.x :
                axis == 1 ? minimum.y : minimum.z;

            double hi = axis == 0 ? maximum.x :
                axis == 1 ? maximum.y : maximum.z;

            if (std::abs(direction) < EPSILON)
            {
                if (origin < lo || origin > hi)
                    return false;

                continue;
            }

            double t1 = (lo - origin) / direction;
            double t2 = (hi - origin) / direction;

            double sign = -1.0;

            if (t1 > t2)
            {
                std::swap(t1, t2);
                sign = 1.0;
            }

            Vec3 normal = { 0, 0, 0 };

            if (axis == 0) normal.x = sign;
            if (axis == 1) normal.y = sign;
            if (axis == 2) normal.z = sign;

            if (t1 > tMin)
            {
                tMin = t1;
                entryNormal = normal;
            }

            if (t2 < tMax)
            {
                tMax = t2;
                exitNormal = -normal;
            }

            if (tMin > tMax)
                return false;
        }

        double t = tMin >= EPSILON ? tMin : tMax;

        if (t < EPSILON || t >= hit.distance)
            return false;

        Vec3 normal = t == tMin
            ? entryNormal
            : exitNormal;

        hit.distance = t;
        hit.position = ray.at(t);
        hit.setFaceNormal(ray, normal);
        hit.material = cube.material;

        return true;
    }

    bool traceScene(
        const Scene& scene,
        const Ray& ray,
        Hit& hit
    )
    {
        bool found = false;

        if (intersectPlane(ray, scene.ground, hit))
            found = true;

        for (const auto& sphere : scene.spheres)
        {
            if (intersectSphere(ray, sphere, hit))
                found = true;
        }

        for (const auto& cube : scene.cubes)
        {
            if (intersectCube(ray, cube, hit))
                found = true;
        }

        for (const auto& mesh : scene.meshes)
        {
            if (intersectMesh(ray, mesh, hit))
                found = true;
        }

        return found;
    }

    bool isInShadow(
        const Scene& scene,
        const Vec3& position,
        const Vec3& normal
    )
    {
        Ray shadowRay = {
            position + normal * EPSILON * 4.0,
            -LIGHT_DIRECTION
        };

        Hit shadowHit;

        return traceScene(scene, shadowRay, shadowHit);
    }

    Vec3 directLighting(
        const Scene& scene,
        const Hit& hit
    )
    {
        Vec3 ambient = hit.material.color * 0.12;

        if (isInShadow(scene, hit.position, hit.normal))
            return ambient;

        double diffuse = std::max(
            0.0,
            hit.normal.dot(-LIGHT_DIRECTION)
        );

        Vec3 lighting = ambient +
            LIGHT_COLOR * diffuse * 0.88;

        return multiply(hit.material.color, lighting);
    }

    Vec3 skybox(const Vec3& direction)
    {
        double t = std::clamp(
            direction.y * 0.5 + 0.5,
            0.0, 1.0
        );

        Vec3 horizon = { 0.70, 0.90, 0.98 };
        Vec3 zenith = { 0.20, 0.65, 0.90 };

        return horizon * (1.0 - t) + zenith * t;
    }

    double fresnel(
        double cosine,
        double refractiveIndex
    )
    {
        double r0 = (1.0 - refractiveIndex) /
            (1.0 + refractiveIndex);

        r0 *= r0;

        return r0 + (1.0 - r0) *
            std::pow(1.0 - cosine, 5.0);
    }

    Vec3 traceRay(
        const Scene& scene,
        Ray ray,
        int depth
    )
    {
        Vec3 throughput = { 1, 1, 1 };
        Vec3 result = { 0, 0, 0 };

        for (int bounce = 0; bounce <= depth; ++bounce)
        {
            Hit hit;

            if (!traceScene(scene, ray, hit))
            {
                result = result +
                    multiply(throughput, skybox(ray.direction));

                break;
            }

            const Material& material = hit.material;

            Vec3 surfaceColor =
                directLighting(scene, hit);

            if (material.type == MaterialType::Glass)
            {
                double eta = hit.frontFace
                    ? 1.0 / material.refractiveIndex
                    : material.refractiveIndex;

                Vec3 normal = hit.normal;

                double cosine = std::min(
                    -ray.direction.dot(normal), 1.0
                );

                double reflectance =
                    fresnel(cosine, material.refractiveIndex);

                Vec3 refracted;

                bool canRefract =
                    ray.direction.refract(normal, eta, refracted);

                if (!canRefract)
                    reflectance = 1.0;

                result = result +
                    multiply(throughput, surfaceColor) * 0.08;

                if (bounce == depth)
                    break;

                if (!canRefract || reflectance > 0.5)
                {
                    throughput = multiply(
                        throughput,
                        Vec3{ reflectance, reflectance, reflectance }
                    );

                    ray = {
                        hit.position + normal * EPSILON * 4.0,
                        ray.direction.reflect(normal).normalized()
                    };
                }
                else
                {
                    throughput = multiply(
                        throughput,
                        material.color
                    );

                    ray = {
                        hit.position - normal * EPSILON * 4.0,
                        refracted
                    };
                }
            }
            else
            {
                result = result +
                    multiply(throughput, surfaceColor);

                if (bounce == depth)
                    break;

                if (material.type == MaterialType::Metal)
                {
                    throughput = multiply(
                        throughput,
                        material.color * material.reflectivity
                    );

                    Vec3 reflected =
                        ray.direction.reflect(hit.normal).normalized();

                    ray = {
                        hit.position + hit.normal * EPSILON * 4.0,
                        reflected
                    };
                }
                else if (material.type == MaterialType::Plastic)
                {
                    if (material.reflectivity < 0.01)
                        break;

                    throughput = throughput *
                        material.reflectivity;

                    ray = {
                        hit.position + hit.normal * EPSILON * 4.0,
                        ray.direction.reflect(hit.normal).normalized()
                    };
                }
                else
                {
                    break;
                }
            }

            if (throughput.length() < 0.001)
                break;
        }

        return result;
    }

    Mesh createTetrahedron(
        Vec3 center,
        double size,
        Material material
    )
    {
        Mesh mesh;
        mesh.material = material;

        double s = size;

        Vec3 vertices[4] = {
            center + Vec3{ s, s, s },
            center + Vec3{ -s, -s, s },
            center + Vec3{ -s, s, -s },
            center + Vec3{ s, -s, -s }
        };

        const int faces[4][3] = {
            { 0, 1, 2 },
            { 0, 3, 1 },
            { 0, 2, 3 },
            { 1, 3, 2 }
        };

        for (const auto& face : faces)
        {
            mesh.triangles.push_back({
                vertices[face[0]],
                vertices[face[1]],
                vertices[face[2]]
                });
        }

        return mesh;
    }

    Scene createScene()
    {
        Scene scene;

        Material redMetal = {
            { 0.90, 0.08, 0.06 },
            MaterialType::Metal,
            0.85, 0.05, 1.0
        };

        Material blueGlass = {
            { 0.25, 0.70, 0.95 },
            MaterialType::Glass,
            0.95, 0.0, 1.5
        };

        Material greenPlastic = {
            { 0.08, 0.85, 0.15 },
            MaterialType::Plastic,
            0.15, 0.3, 1.0
        };

        Material concrete = {
            { 0.65, 0.65, 0.65 },
            MaterialType::Concrete,
            0.0, 1.0, 1.0
        };

        scene.meshes.push_back(
            createTetrahedron(
                { 14, 21, 46 },
                12.0,
                redMetal
            )
        );

        scene.cubes.push_back({
            { -52, 14, 67 },
            14.0,
            blueGlass
            });

        scene.spheres.push_back({
            { 31, 16, -43 },
            16.0,
            greenPlastic
            });

        scene.ground = {
            0.0,
            concrete
        };

        return scene;
    }

    Vec3 sampleGroundColor(const Vec3& position)
    {
        constexpr double TILE_SIZE = 8.0;

        int x = static_cast<int>(
            std::floor(position.x / TILE_SIZE)
            );

        int z = static_cast<int>(
            std::floor(position.z / TILE_SIZE)
            );

        bool checker = ((x + z) & 1) == 0;

        return checker
            ? Vec3{ 0.55, 0.55, 0.55 }
        : Vec3{ 0.12, 0.12, 0.12 };
    }

    Vec3 renderPixel(
        const Scene& scene,
        const Camera& camera,
        double u,
        double v
    )
    {
        Ray ray = camera.generateRay(u, v);

        Hit hit;

        if (!traceScene(scene, ray, hit))
            return skybox(ray.direction);

        if (hit.material.type == MaterialType::Concrete)
        {
            Material groundMaterial = hit.material;
            groundMaterial.color =
                sampleGroundColor(hit.position);

            Scene localScene = scene;

            localScene.ground.material = groundMaterial;

            return traceRay(localScene, ray, MAX_BOUNCES);
        }

        return traceRay(scene, ray, MAX_BOUNCES);
    }

    Frame render()
    {
        Frame frame;

        frame.reserve(
            static_cast<size_t>(FRAME_WIDTH) *
            static_cast<size_t>(FRAME_HEIGHT)
        );

        Scene scene = createScene();

        Camera camera;

        camera.initialize(
            { 78, 24, 78 },
            { 0, 0, 0 },
            static_cast<double>(FRAME_WIDTH) /
            static_cast<double>(FRAME_HEIGHT)
        );

        for (short y = 0; y < FRAME_HEIGHT; ++y)
        {
            for (short x = 0; x < FRAME_WIDTH; ++x)
            {
                double u =
                    (static_cast<double>(x) + 0.5) /
                    FRAME_WIDTH;

                double v =
                    1.0 - (
                        (static_cast<double>(y) + 0.5) /
                        FRAME_HEIGHT
                        );

                Vec3 color = renderPixel(
                    scene,
                    camera,
                    u,
                    v
                );

                frame.push_back(toRGB(color));
            }
        }

        return frame;
    }
}

__declspec(dllexport)
Renderer::Frame __cdecl getFrame()
{
    return Renderer::render();
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD reason,
    LPVOID reserved
)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        break;

    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}
