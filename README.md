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

## Supported OSs
- ex:
    - [x] OS is supported(compiles and runs)
    - [ ] not supported/untested

- supports:
    - [x] Linux
    - [x] FreeBSD
    - [ ] Solaris - Untested
    - [ ] MacOS - untested
    - [ ] Windows - untested

## Compile Wellang

git the wellang github repository

``$ git clone https://github.com/wellang/well.git``

move to the wellang directory in your terminal

``$ cd well``

compile wellang with make

``$ make base``

install wellang

``$ make install``

## Example program: while.well (in /example/)

```
v:func:while_func() {
	stack program(4);
	int i = 0;

while:(i != 5) {
	program.push(34);
	program.push(35);
	program.plus();
	program.dump();
	i++;
}

}

r:func:main() {
	while_func();
}
```

## compile program
to compile your well program you can run ``well`` in your terminal:
```
[test@test example]$ well while.well -o test
done compiling program
test
[test@test example]$ ./test
69
69
69
69
69
```
