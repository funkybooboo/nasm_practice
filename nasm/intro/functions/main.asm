section .data

section .text
global main

addTwo:
    add eax, ebx
    ret ; return back to the locaion we where called from

main:
    mov eax, 4
    mov ebx, 1
    call addTwo
    mov ebx, eax
    mov eax, 1

    int 80h
