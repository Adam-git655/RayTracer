## Intro


This is my implementation of a RayTracer in C++.

Made by following the book **Ray Tracing in One Weekend** by Peter Shirley.
https://raytracing.github.io/books/RayTracingInOneWeekend.html

## Steps to build

1)Install CMake

2)Run the following commands in PowerShell/terminal

```
mkdir build
cd build
cmake ../
```
To Run, open a terminal in the folder where RayTracer.exe is located and run
`.\RayTracer.exe > image.ppm`

*For now, all the outputs are in .ppm formats. They can be viewed using any online PPM viewer and converted to JPG.


## Images of the various iterations of the RayTracer

### First Image Output
![image](https://github.com/user-attachments/assets/b21d48c9-aee2-451c-8a1f-88ffae46bc38)

### A Red Sphere
![image](https://github.com/user-attachments/assets/855c1ebe-afde-43f4-ad6b-202945448d7e)

### Coloured Normal map and a Ground
![image](https://github.com/user-attachments/assets/e02a3107-8919-47fc-9815-4cf8d0ce65af)

### AntiAliasing
![image](https://github.com/user-attachments/assets/b176f716-c644-4943-9926-f4631c4d30e6)

### Gamma Corrected Diffuse Sphere
![image](https://github.com/user-attachments/assets/4a6a78b8-4941-4d02-bacc-d86dabcf1999)

### Diffuse And Metal Spheres(With Fuzz)
![image](https://github.com/user-attachments/assets/8a1e06a1-fcf1-48e7-a787-660abe588ad1)

### Dielectrics (Glass)
![image](https://github.com/user-attachments/assets/abe30950-f905-46b2-813f-54cccb729841)

### Adjustable Camera Position and FOV
![image](https://github.com/user-attachments/assets/da95dd48-4ecb-4772-b257-c2cf13d04b2f)

### A Final Render (With Defocus Blur)
![image](https://github.com/user-attachments/assets/455089b0-4e3b-472d-930b-cc77afaa3d95)


