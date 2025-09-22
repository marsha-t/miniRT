# miniRT Usage Guide

This guide covers everything you need to know about using miniRT, from scene file syntax to interactive controls.

## Quick Start

```bash
# Build the project
make

# Run with a scene file
./miniRT maps/mandatory.rt
```

## Scene File Format

Scene files use the `.rt` extension and define the 3D world using a simple text format.

### Basic Elements

#### Ambient Light
```
A <ratio> <R,G,B>
```
- `ratio`: Ambient lighting ratio (0.0 to 1.0)
- `R,G,B`: Color values (0-255)

Example:
```
A 0.3 255,255,255
```

#### Camera
```
C <x,y,z> <orientation_x,y,z> <FOV>
```
- `x,y,z`: Camera position coordinates
- `orientation_x,y,z`: Normalized orientation vector
- `FOV`: Field of view in degrees

Example:
```
C 60,10,-50 0,0,1 30
```

#### Point Light
```
L <x,y,z> <brightness> <R,G,B>
```
- `x,y,z`: Light position coordinates
- `brightness`: Light intensity (0.0 to 1.0)
- `R,G,B`: Light color values (0-255)

Example:
```
L 70,100,20 0.8 255,250,250
```

#### Spotlight (Bonus)
```
SL <x,y,z> <direction_x,y,z> <brightness> <R,G,B>
```
- `x,y,z`: Spotlight position coordinates
- `direction_x,y,z`: Normalized direction vector
- `brightness`: Light intensity (0.0 to 1.0)
- `R,G,B`: Light color values (0-255)

Example:
```
SL 75,100,100 0,-1,0 0.7 255,255,0
```

### Objects

#### Sphere
```
sp <x,y,z> <diameter> <R,G,B> [checker <row,col>] [bump <texture.xpm>]
```
- `x,y,z`: Center coordinates
- `diameter`: Sphere diameter
- `R,G,B`: Color values (0-255)
- `checker`: Optional checkerboard pattern with square sizes
- `bump`: Optional bump mapping texture file

Examples:
```
sp 50,0,100 10 255,0,0
sp 40,0,100 12 255,120,0 checker 5,5
sp 65,10,100 7 0,255,255 bump bumpmaps/earthbump1k.xpm
```

#### Plane
```
pl <x,y,z> <normal_x,y,z> <R,G,B> [checker <row,col>] [bump <texture.xpm>]
```
- `x,y,z`: Point on the plane
- `normal_x,y,z`: Normalized normal vector
- `R,G,B`: Color values (0-255)
- `checker`: Optional checkerboard pattern
- `bump`: Optional bump mapping texture

Examples:
```
pl 0,-10,0 0,-1,0 120,20,60
pl 0,0,200 0,0,-1 25,0,100 checker 10,10
```

#### Cylinder
```
cy <x,y,z> <axis_x,y,z> <diameter> <height> <R,G,B> [checker <row,col>] [bump <texture.xpm>]
```
- `x,y,z`: Center coordinates
- `axis_x,y,z`: Normalized axis vector
- `diameter`: Cylinder diameter
- `height`: Cylinder height
- `R,G,B`: Color values (0-255)
- `checker`: Optional checkerboard pattern
- `bump`: Optional bump mapping texture

Examples:
```
cy 80,0,100 0,1,0 4.2 21.42 0,255,255
cy 90,0,100 0,1,0 4.2 21.42 0,255,255 checker 2,5
```

#### Cone (Bonus)
```
cn <x,y,z> <axis_x,y,z> <angle> <height> <R,G,B> [checker <row,col>]
```
- `x,y,z`: Tip coordinates
- `axis_x,y,z`: Normalized axis vector
- `angle`: Half-angle of the cone in degrees
- `height`: Cone height
- `R,G,B`: Color values (0-255)
- `checker`: Optional checkerboard pattern

Examples:
```
cn 70,0,100 0,1,0 10 35 0,0,255
cn 30,0,50 1,0,0 15 20 255,100,0 checker 3,3
```

## Interactive Controls

### Object Selection
- **NUMPAD_5**: To select object
  - **KEY_1**: Spheres
  - 2: Planes  
  - 3: Cylinders
  - 4: Cones
  - 5: Point lights
  - 6: Spotlights
  - 7: Camera
- Click **KEY_1** - **KEY_6** to cycle through different objects of a given type
- For example, **NUMPAD_5** + **KEY_1** + **KEY_1** will select the second 

### Movement
- **W**: Move forward/up
- **A**: Move left
- **S**: Move backward/down
- **D**: Move right
- **E**: Move up (Y+)
- **R**: Move down (Y-)

### Rotation
- **U/J**: Rotate around X axis
- **I/K**: Rotate around Y axis
- **O/L**: Rotate around Z axis

### Quality Settings
- **W**: Low quality
- **S**: High quality

### Other Controls
- **ESC**: Exit program
- **Arrow Keys**: Camera movement

## Troubleshooting

### Common Issues

#### "No such file or directory" error
- Verify the scene file path is correct
- Ensure the file has `.rt` extension
- Check that the file exists in the specified location

#### Black screen on render
- Verify camera position and orientation are valid
- Check that objects are within camera field of view
- Ensure proper lighting setup (at least ambient + one light source)
- Confirm light sources have appropriate brightness values

#### Performance issues
- Use lower quality settings (Numpad 0 for fastest rendering)
- Reduce image resolution by modifying `WINDOW_WIDTH` and `WINDOW_HEIGHT` in `miniRT.h`
- Simplify scene complexity (fewer objects, lights)
- Disable bump mapping and checkerboard patterns for faster rendering
