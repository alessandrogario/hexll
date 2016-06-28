# Simple tool that dumps binary data in HexII format.

![hexll screenshot](https://raw.githubusercontent.com/alessandrogario/hexll/master/screenshots/hexll.png)

You can tweak how the output is printed using the following environment variables:

* Offset digits: HEXLL_OFFSETDIGITCOUNT
* Column count: HEXLL_COLUMNCOUNT
* Text color: HEXLL_COLORESCAPESEQUENCE

## Usage
**hexll** /path/to/input_file

cat /path/to/input_file | **hexll**

## About
The HexII notation has been invented by Ange Albertini (https://github.com/corkami)

