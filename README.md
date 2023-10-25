
# CtxrTool


CtxrTool is a free open source tool to convert CTXR textures from Metal Gear Solid: Master Collection to DDS. It is also possible to convert DDS textures to CTXR but as there are still some unknown's it is a work in progress.

### To Do
 - Find out purpose of unknown bytes for DDS to CTXR conversion.

##  Usage

Currently only a CLI version of the application exists. You can drag a CTXR file onto the tool and it will create a DDS file in the same folder. Alternatively you can drag a DDS file on the tool and it will create a CTXR file (Experimental) .

Running the program without any arguments will display usage information.

```
CtxrTool.exe <example_file.ctxr>
```
The above command will convert a CTXR file to a DDS file.

```
CtxrTool.exe <example_file.dds>
```
The above command will convert a DDS file to a CTXR file (Work in progress, still some unknowns)

## License
[MIT](LICENSE.md)
This project falls under the MIT license.