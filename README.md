# Wellang

<div align="center">
  <br />
  <p>
    <a href="https://github.com/wellang/wellang.git"><img src="https://avatars.githubusercontent.com/u/102248284?s=400&u=5d92de95684e16d63035c33aadca8e07c11ccdf9&v=4" width="250" alt="wellang" /></a>
  </p>
  <br />
  <p>
    <br> <a href="https://discord.gg/3mdNFb8ZyE"><img src="https://img.shields.io/discord/957338481108074517?color=5865F2&logo=discord&logoColor=white" alt="Well discord server" /></a> </br>
  </p>
</div>

# About
	
### This is a small project made by yours truly (TristanWellman). This is a high level assembly language, you will have your low level assembly programming but with some features from high level languages. Wellang compiles directly to assembly(NASM), See below for compilation and simple documentation.

Website: https://wellang.github.io

contact me at:

email: wellangcode@gmail.com

discord: ``__Oblivion__#3258``

wellang discord server: https://discord.gg/K4ufunGxJv

## Compile Wellang

git the wellang github repository

``$ git clone https://github.com/wellang/well.git``

move to the wellang directory in your terminal

``$ cd well``

compile wellang with make

``$ make base``

install wellang

``$ make install``

## Example program: helloworld.well (in /example/)

```
var:main {

	string~ text = 'hello world!'
	length~ text_length, text

}

~func:main {

	move~ 1, rax
	move~ 1, rdi
	move~ text, rsi
	move~ text_length, rdx
	return

	move~ 60, rax
	move~ 0, rdi 
	return

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
cd {path/to/.vim}
mkdir syntax && mkdir ftdetect
```

# New Features!

5/14/22: Added Function handling. You can now make use of more than just the main function in wellang!

5/10/22: Added support for vim syntax highlighting with wellang
