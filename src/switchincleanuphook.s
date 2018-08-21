.text
.thumb
.thumb_func
.align 1

cleanstructhook:
	bl switchin_newstruct_update
	add sp, sp, #0x20
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7,pc}


