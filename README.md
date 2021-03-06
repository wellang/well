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

#NOTE:

Wellang is in an extremely early state, with pending syntax changes, and the development of the compiler. MAKE SURE you keep wellang up to date in these early stages.

# About
	
### This is a project originally started by Tristan Wellman(read CONTRIBUTING.md for contribution info). This is a high level compiled assembly language, you will have your low level assembly programming but with some features from high level languages. Wellang compiles directly to assembly(NASM), See below for compilation and simple documentation.

contact me at:

email: wellangcode@gmail.com

discord: ``__Oblivion__#3258``

wellang discord server: https://discord.gg/K4ufunGxJv

## Compile Wellang

git the wellang github repository

``$ git clone https://github.com/wellang/well.git``

move to the wellang directory in your terminal

``$ cd well``

compile and install wellang with make

``$ make base install``

## Compile Wellang on windows

[`windows installation`](windows/WINDOWS.md)

### Example program (using linux x86_x64 syscall table): helloworld.well (in /example/)

```
~var:main {

	string~ text = 'hello world!'
	length~ text_length, text

}

~func:main {

	move~ 1, rax
	move~ 1, rdi
	move~ text, rsi
	move~ text_length, rdx
	syscall

	return 0
}

```

## compile program
to compile your well program you can run ``wesm`` in your terminal:
```
[test@test example]$ wesm helloworld.well -o hello.o hello
done compiling program
[test@test example]$ ./hello
hello world!
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

6/18/22: You can now make use of macros in wellang!

6/9/22: added char type. Added halt, cif, bits, resb, and print to assembly instructions

6/6/22: log.c, and log.h additions

5/14/22: Added Function handling. You can now make use of more than just the main function in wellang!

5/10/22: Added support for vim syntax highlighting with wellang

## Stargazers over time

[![Stargazers over time](https://starchart.cc/wellang/well.svg)](https://starchart.cc/wellang/well)

