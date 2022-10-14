# math

```
move~ :32+{5*[49*3*(-4-9)]+56}:, rax 

	32+{5*[147*(-13)]+56}
	32+{5*[-1911]+56}
	-9467
```
### asm_out

```
mov rax, -9467
```


# macros

### well:

```
~macro:test[1] {
	move~ rax, %%1
}

~func:main {
	test~ blahvar
}
```

### asm_out:

```
main:
	jmp main._1_fname_test_
	._1_fname_test_:
	jmp main._2_fname_move_
	._2_fname_move_:
	mov rax, blahvar
	jmp main._2_fname_move_end_
	._2_fname_move_end_:
	jmp main._1_fname_test_end_
	._1_fname_test_end_:
```		
