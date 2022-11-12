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

Wellang is in an extremely early state with pending syntax changes and the development of the compiler. MAKE SURE you keep wellang up to date in these early stages.

# About
	
### This is a project originally started by Tristan Wellman. This is a high level compiled assembly language; you will have your low level assembly programming but with some features from high level languages. Wellang compiles directly to NASM. See below for compilation and simple documentation.

NEED HELP?

email: wellangcode@gmail.com

wellang discord server: https://discord.gg/K4ufunGxJv

# Compile Wellang

Linux

```
$ git clone https://github.com/wellang/well.git
$ cd well
$ make && make install
or
$ make base install
```

FreeBSD

```
$ git clone https://github.com/wellang/well.git
$ cd well
$ gmake base install
or
$ gmake && gmake install
```

Windows

[`windows installation`](windows/WINDOWS.md)

## Hello World program (using linux x86_x64 syscall table)

```
~include <std.well>
~var:main {
	string~ text = 'Hello World!'
}
~func:main {
	move~ 1, rax
	move~ 1, rdi
	move~ text, rsi
	move~ text.len, rdx
	syscall
	return~ 0
}
```

## compile program
to compile your well program you can run ``wesm`` in your terminal:
```
 ╰─λ wesm helloworld.well
16:48:37 INFO  src/asm_interp.c:572: Compile time:: 0.010380 seconds
 ╰─λ ./helloworld
Hello World!
```

## Vim syntax highlighting
```
make vim
```

### Credits
![Contributors](https://contrib.rocks/image?repo=wellang/well)

## Stargazers over time

[![Stargazers over time](https://starchart.cc/wellang/well.svg)](https://starchart.cc/wellang/well)

