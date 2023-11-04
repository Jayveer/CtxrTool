
# CtxrTool


CtxrTool is a free open source tool to convert CTXR textures from Metal Gear Solid: Master Collection to DDS, BMP or TGA. It is also possible to convert DDS. BMP and TGA textures to CTXR but as there are still some unknown's it is a work in progress.

DDS files must be saved in the 8.8.8.8 ARGB format, I have only tested using the NVIDIA Texture Tools Exporter plugin and Photoshop.

TGA and BMP files can also be converted to CTXR, the tool will automatically generate mip maps but it is recommended to use DDS. you can use the -m no option to moit generating mip maps. They must be saved as 32 bits/pixel.

### Latest Changes
 - Added support for extracting as BMP
 - Added support for converting BMP and TGA to CTXR with mipmap generation.


### To Do
 - Find out purpose of unknown bytes for DDS to CTXR conversion.

##  Usage

Currently only a CLI version of the application exists. You can drag a CTXR file onto the tool and it will create a DDS file and param file in the same folder. Alternatively you can drag a DDS file on the tool and it will create a CTXR file (Experimental).

You can use the -f command along with 'bmp' or 'tga' when extracting a CTXR file to export it as a TGA or BMP instead of a DDS. This will not save mip map data, example below.

Upon exporting a ctxr file a 'param' file will also be created, this will be used when repacking the data if it exists.

Running the program without any arguments will display usage information.

```
CtxrTool.exe <example_file.ctxr>
```
The above command will convert a CTXR file to a DDS file.

```
CtxrTool.exe <example_file.ctxr> -f tga
```
The above command will convert a CTXR file to a TGA file. This will not export mipmap data.

```
CtxrTool.exe <example_file.ctxr> -f bmp
```
The above command will convert a CTXR file to a BMP file. This will not export mipmap data.

```
CtxrTool.exe <example_file.dds>
```
The above command will convert a DDS file to a CTXR file, if a file with same name and extension as param is in the same directory it will repack that data back into the ctxr file (Work in progress, still some unknowns)

```
CtxrTool.exe <example_file.tga>
```
The above command will convert a TGA file to a CTXR file, this will generate mip maps for you. It is recommeneded to use DDS and create your own, but this option is available for those that can't

```
CtxrTool.exe <example_file.tga> -m no
```
The above command will convert a TGA file to a CTXR file, this will not generate any mip maps.

```
CtxrTool.exe <example_file.bmp>
```
The above command will convert a BMP file to a CTXR file, this will generate mip maps for you. It is recommeneded to use DDS and create your own, but this option is available for those that can't

```
CtxrTool.exe <example_file.tga> -m no
```
The above command will convert a BMP file to a CTXR file, this will not generate any mip maps.

## License
[MIT](LICENSE.md)
This project falls under the MIT license.
