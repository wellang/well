if exists("b:current_syntax")
	finish
endif

syntax keyword welldatatypes string length int
syntax keyword wellpush push
syntax keyword wellmov move
syntax keyword welllea lea
syntax keyword wellcall call
syntax keyword welllib lib
syntax keyword wellasm asm
syntax keyword wellfunc func
syntax keyword wellvar var
syntax keyword wellextern extern
syntax keyword wellreturn return 
syntax keyword wellsyscall syscall

syn match welldirective "\.[A-Za-z][0-9A-Za-z-_]*"

syntax match wellnum "\-\?\<\d\+\>" display
syntax region wellstring start=/\v'/ skip=/\v\\./ end=/\v'/

highlight link welldatatypes Type
highlight link wellpush Keyword
highlight link wellmov Keyword
highlight link welllea Keyword
highlight link wellcall keywrord
highlight link wellasm keyword
highlight link welllib keyword
highlight link wellreturn Keyword
highlight link wellsyscall Keyword
highlight link wellextern keyword

highlight def link welldirective Statement

highlight link wellnum Number
highlight link wellstring String

highlight link wellfunc Function
highlight link wellvar Function

let b:current_syntax = "well"
