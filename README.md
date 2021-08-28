# ldline
A program for GNU/Linux to get, or erase, the last duplicated line of a file.

## Installation

How to install

```
$ git clone https://github.com/Araya2001/ldline.git
$ cd ldline
$ cmake .
$ make
$ make install
```

*Note: You'll need `cmake` 3.20 or later*

## Usage

How to get the last duplicated line of some sorted lines in a file

```
$ ldline -s /path/to/file
```

How to exclude the last duplicated line of some sorted lines in a file

```
$ ldline -e /path/to/file
```

How to compare from a specific character position, and from that specific position, compare a certain amount of characters

*From position 1, compare 5 characters*

```
$ ldline -s -f 1 -c 5 /path/to/file
```

*This example will compare the substring of the buffered lines and if the first 5 characters of the buffered line doesn't match with the current line, it will print the buffered line*

