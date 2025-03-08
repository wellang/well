# Wellang

<div align="center">
  <br />
  <p>
    <a href="https://github.com/wellang/wellang.git"><img src="https://github.com/wellang/well/blob/main/wellang.png" width="800" alt="wellang" /></a>
  </p>
  <br />
  <p>
    <br> <a href="https://discord.gg/3mdNFb8ZyE"><img src="https://img.shields.io/discord/957338481108074517?color=5865F2&logo=discord&logoColor=white" alt="Well discord server" /></a> </br>
  </p>
</div>

# NOTE

* Wellang is currently under a complete rewrite, it is currently barely functional so please be patient. Thank you!

* Wellang is in an extremely early state with pending syntax changes and the development of the compiler. MAKE SURE you keep wellang up to date in these early stages.

# About
	
 This is a project by Tristan Wellman. Wellang is a high level compiled assembly language; you will have your low level assembly programming but with some features from high level language. See below for compilation and simple documentation.

### NEED HELP?

Email: wellangcode@gmail.com

Wellang discord server: https://discord.gg/K4ufunGxJv

# Compile Wellang

```
$ make
```

## Hello World program

```
~include <std.well>

~constants {
    ~string:text = 'Hello World!'
}

~int:main {
    move~ text, r1
    call~ printf
    return~ 0
}
```

## compile program
to compile your well program you can run ``well`` in your terminal:
```
$ well main.well -o out
```

## Vim syntax highlighting
```
make vim
```

### Credits
![Contributors](https://contrib.rocks/image?repo=wellang/well)

## Stargazers over time

[![Stargazers over time](https://starchart.cc/wellang/well.svg)](https://starchart.cc/wellang/well)

