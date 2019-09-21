# steamfontsizer - Version 1.0

A simple CLI tool that adds a given number to all font-size entries in a steam.styles file.
So you can easily create one dirty ugly steam skin with huge fonts :-)

## Usage:
```
    steamfontsizer [OPTION(s)] [FILE]
```

## Options:
```
    -a NUMBER       add NUMBER to font size
                    (default value: 2)
    -h, --help      display this helpscreen
    -o FILE         specify output file
                    (default stdout)
    -v              verbose mode
```

## How to use example:
1. Download, build and "install" steamfontsizer
    ```
    git clone https://github.com/jansalleine/steamfontsizer.git
    cd steamfontsizer/src
    make
    sudo cp ../bin/steamfontsizer /usr/local/bin/
    ```
1. Create a directory for your skin:
    ```
    mkdir -p ~/.steam/steam/skins/myuglyskin/resource/styles
    ```
1. Use steamfontsizer to create a steam.styles file
    ```
    steamfontsizer ~/.steam/steam/resource/styles/steam.styles ~/.steam/steam/skins/myuglyskin/resource/styles/steam.styles
    ```
1. Change the skin in Steam settings to "myuglyskin"
