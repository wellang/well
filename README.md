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

Wellang is in an extremely early state, with pending syntax changes, and the development of the compiler. MAKE SURE you keep wellang up to date in these early stages.

# About
	
### This is a project originally started by Tristan Wellman. This is a high level compiled assembly language, you will have your low level assembly programming but with some features from high level languages. Wellang compiles directly to NASM, See below for compilation and simple documentation.

NEED HELP?

``
email: wellangcode@gmail.com
``

``
wellang discord server: https://discord.gg/K4ufunGxJv
``
# Compile Wellang

Linux

```
$ git clone https://github.com/wellang/well.git
$ cd well``
$ make base install
```

FreeBSD

```
$ git clone https://github.com/wellang/well.git
$ cd well
$ gmake base install
```

Windows

[`windows installation`](windows/WINDOWS.md)

## Hello World program (using linux x86_x64 syscall table)

```
~var:main {

	string~ text = 'Hello World!'
	length~ text_length, text

}

~func:main {

	move~ 1, rax
	move~ 1, rdi
	move~ text, rsi
	move~ text_length, rdx
	syscall

	return~ 0
}

```

## compile program
to compile your well program you can run ``wesm`` in your terminal:
```
❯ wesm helloworld.well -o helloworld
20:14:46 INFO  src/asm_interp.c:393: Compile time:: 0.000451 seconds
❯ ./helloworld
Hello World

```

## Vim syntax highlighting
to install wellang syntax highlighting for vim all you have to do is
```
make vim
```

if it says you don't have ``~/.vim/syntax/`` or ``~/.vim/ftdetect/`` then you can do
```
cd ~/.vim
mkdir syntax && mkdir ftdetect
```

### Credits
![Contributors](https://contrib.rocks/image?repo=wellang/well)

# New Features!

8/21/22: wesm arg overhaul

6/18/22: You can now make use of macros in wellang!

6/9/22: added char type. Added halt, cif, bits, resb, and print to assembly instructions

5/10/22: Added support for vim syntax highlighting with wellang

## Stargazers over time

[![Stargazers over time](https://starchart.cc/wellang/well.svg)](https://starchart.cc/wellang/well)

