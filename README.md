# Raytracer
A simple raytracer - project for graphics course.
<img src="./mirrorOnABoard.png">  

## Installation
Change to Project_3 folder, make a build directory, run cmake and make:
```
mkdir build  
cd build   
cmake ..  
make -j4  
```
To create custom scenes, make a ray file in `Media/SampleScenes`.  
*For examples look at other `.ray` files.*

## Running
While in build directory, execute:
```
./Project_3/Project_3 <ray filename> n
```
For example, `./Project_3/Project_3 SampleScenes/twoMirrorsOnAnotherMirror.ray n` will produce:

<img src="./twoMirrorsOnAnotherMirror.png">  
Option `n` enables display output  
Rendered scene is saved to 'final_output.png' in `raytracer/Project_3`
