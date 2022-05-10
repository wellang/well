if exists("b:current_syntax")
	finish
endif

syntax keyword welldatatypes string length int
syntax keyword wellpush push
syntax keyword wellmov move
syntax keyword wellfunc func
syntax keyword wellvar var
syntax keyword wellreturn return 

syntax match wellnum "\-\?\<\d\+\>" display
syntax region wellstring start=/\v'/ skip=/\v\\./ end=/\v'/

highlight link welldatatypes Type
highlight link wellpush Keyword
highlight link wellmov Keyword
highlight link wellreturn Keyword

highlight link wellnum Number
highlight link wellstring String

highlight link wellfunc Function
highlight link wellvar Function

let b:current_syntax = "well"
