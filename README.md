# Image Multiplexer
#### Mix and match channels of input images into new a image
<img align="center" src="https://raw.githubusercontent.com/BenCKB/ImageMultiplexer/images/Example1.png" alt="Image1"/>

***
This project started out of a necessity to reduce the amount of textures being loaded into my rendering engine, by using those channels that were not used by textures, for example combining the roughness and metalness texture into one. 

***
## Build:
You can either build the project yourself using cmake or download a precompiled version.
### Cmake:
    >> git clone https://github.com/BenCKB/ImageMultiplexer
    >> cd ImageMultiplexer
    >> cmake .

### Download:
You can find a precompiled version [here](https://github.com/BenCKB/ImageMultiplexer/releases).

## Instructions:
The general command format is as follows:

    >> imgmltplx [pattern] [image list]

* #### Pattern:
    The pattern determines which channel of the corresponding input image will be chosen. Optionally the alpha channel can also be chosen. The pattern is ordered.
    ##### Example 1: 

        >> imgmltplx RGB Image1 Image2 Image3
    This would ouput an image with new channels as follows:

    | RED        | GREEN           | BLUE  |
    |:-------------:|:-------------:| :-----:|
    |`Image1.R `     | `Image2.G `|` Image3.B` |

    ##### Example 2: 

        >> imgmltplx ABAR Image1 Image2 Image3 Image4
    This would ouput an image with new channels as follows:

    | RED        | GREEN           | BLUE  | ALPHA |
    |:-------------:|:-------------:| :-----:| :-----:|
    | `Image1.A`      | `Image2.B` | `Image3.A` | `Image4.R`|

* #### Images: 
    The output image will be in PNG format (due to alpha).
    
    #### Tested input formats:
    - .png
    - .jpg
    - .tga

## License:
### ImageMultiplexer is licensed under the MIT license.

## Third Party:
* [stb](https://github.com/nothings/) (MIT/Public Domain) 