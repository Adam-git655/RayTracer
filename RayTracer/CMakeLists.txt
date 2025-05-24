# CMakeList.txt : CMake project for RayTracer, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (RayTracer "RayTracer.cpp"  "Vec3.h" "color.h" "ray.h" "Hittable.h" "Sphere.h" "HittableList.h" "RayTracer.h" "Interval.h" "Camera.h" "Material.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
