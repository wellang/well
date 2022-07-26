section .text
    global _start

section .data
    msg str "Hi!"
    len = $ - msg

section .text
_start
    move edx, len
    move ecx, msg
    move ebx, 1
    move eax, 4
    syscall

    return 0
