# Wellang

<div align="center">
  <br />
  <p>
    <a href="https://github.com/cogmasters/concord.git"><img src="https://avatars.githubusercontent.com/u/102248284?s=400&u=3136606a100a8538df92d7158e7d2ca119c233b3&v=4" width="250" alt="Concord" /></a>
  </p>
  <br />
  <p>
    <br> <a href="https://discord.gg/3mdNFb8ZyE"><img src="https://img.shields.io/discord/928763123362578552?color=5865F2&logo=discord&logoColor=white" alt="Well discord server" /></a> </br>
  </p>
</div>

## Compile Wellang

git the wellang github repository

``$ git clone https://github.com/wellang/well.git``

move to the wellang directory in your terminal

``$ cd well``

compile wellang with make

``$ make base``

install wellang

``$ make install``

## Example program

```
func:test() { // function to run program
	stack program(4); //create program

	program.push(34); //push nums to stack
	program.push(35); 
	program.plus(); // add last two stack variables together
	program.dump(); // dump program
}

func:main() { // main function

	test();

}
```

## compile program
to compile your well program you can run ``well`` in your terminal:
```
[test@test example]$ well
:: Enter file name
test.well
done compiling program
[test@test example]$ ./a.o
69
```
