# ImageProcessing

A Java console program for loading, transforming, and saving BMP images, working with raw RGB pixel arrays.

**Course project — HW2**

## What it does

The program loads a `.bmp` file into a 3D `int` array (`[height][width][RGB]`) and supports several operations, selected via command-line flags:

- `-display <file> <x> <y>` — print the RGB value of the pixel at position `(x, y)`
- `-hflip <file>` — horizontal flip, saved as `hflip-<file>`
- `-vflip <file>` — vertical flip, saved as `vflip-<file>`
- `-rrotate <file>` — rotate 90° clockwise, saved as `rrotate-<file>`
- `-lrotate <file>` — rotate 90° counter-clockwise, saved as `lrotate-<file>`
- `-grayscale <file1> <file2> ...` — convert one or more images to grayscale using the luminosity formula (`0.299R + 0.587G + 0.114B`) and save each as `gray-<filename>`

## Status

All operations are implemented: `loadBMP`, `saveBMP`, `saveGrayscaleBMP`, `display`, `grayscale`, `hflip`, `vflip`, `rrotate`, and `lrotate`. Each flip/rotate flag loads the given `.bmp`, transforms it, and saves the result with a prefixed filename (e.g. `hflip-photo.bmp`).

## Dependencies

The Eclipse classpath references Princeton's `stdlib.jar` (used for `StdIn` in the `-grayscale` case) at a local path. If you're setting this up fresh, grab `stdlib.jar` from [Princeton's introcs library](https://introcs.cs.princeton.edu/java/stdlib/) and update the classpath entry to point to wherever you keep it.

## How to run

This started as an Eclipse project (the `.project`/`.classpath`/`.settings` files are kept for that). To run from the command line once complete:

```bash
cd src
javac -cp .:stdlib.jar ImageProcessing.java
java -cp .:stdlib.jar ImageProcessing -display myphoto.bmp 10 20
```

(On Windows PowerShell, use `;` instead of `:` in the classpath.)
