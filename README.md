
# CtxrTool


CtxrTool is a free open source tool to convert CTXR textures from Metal Gear Solid: Master Collection to DDS. It is also possible to convert DDS textures to CTXR but as there are still some unknown's it is a work in progress.

DDS files must be saved in the 8.8.8.8 ARGB format, I have only tested using the NVIDIA Texture Tools Exporter plugin and Photoshop.

### Latest Changes
 - Added support for extracting as TGA file
 - Addded param extraction


### To Do
 - Find out purpose of unknown bytes for DDS to CTXR conversion.

##  Usage

Currently only a CLI version of the application exists. You can drag a CTXR file onto the tool and it will create a DDS file and param file in the same folder. Alternatively you can drag a DDS file on the tool and it will create a CTXR file (Experimental).

You can add add 'tga' as a second argument when extracting a CTXR file to export it as a TGA instead of a DDS. This will not save mip map data, example below.

Upon exporting a ctxr file a 'param' file will also be created, this will be used when repacking the data if it exists.

Running the program without any arguments will display usage information.

```
CtxrTool.exe <example_file.ctxr>
```
The above command will convert a CTXR file to a DDS file.

```
CtxrTool.exe <example_file.ctxr> tga
```
The above command will convert a CTXR file to a TGA file. This will not export mipmap data.

```
CtxrTool.exe <example_file.dds>
```
The above command will convert a DDS file to a CTXR file, if a file with same name and extension as param is in the same directory it will repack that data back into the ctxr file (Work in progress, still some unknowns)

## License
[MIT](LICENSE.md)
This project falls under the MIT license.
