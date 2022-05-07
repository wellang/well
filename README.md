# Wellang

<div align="center">
  <br />
  <p>
    <a href="https://github.com/wellang/wellang.git"><img src="https://avatars.githubusercontent.com/u/102248284?s=400&u=3136606a100a8538df92d7158e7d2ca119c233b3&v=4" width="250" alt="wellang" /></a>
  </p>
  <br />
  <p>
    <br> <a href="https://discord.gg/3mdNFb8ZyE"><img src="https://img.shields.io/discord/957338481108074517?color=5865F2&logo=discord&logoColor=white" alt="Well discord server" /></a> </br>
  </p>
</div>

# About
	
### This is a small project made by yours truly (TristanWellman). This language includes your normal things like variables, mathamatics, loops, etc. It compiles directly to c++ (See below for compilation and simple documentation).

contact me at:

email: wellangcode@gmail.com

discord: ``__Oblivion__#3258``


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

r:func:main {

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

