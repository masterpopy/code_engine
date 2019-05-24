.thumb
.align 1

sav_to_flash_copy:
	mov r0, r12
	ldr r0, [r0]
	mov r1, r10
	mov r2, r3
	bl copy_sav_to_buffer
	ldr r0, =(0x08152B34|1)
	bx r0


ov_showcontest:
    push {lr}
    bl new3_to_flash
    ldr r1,=0x80F840C|1
    bl r1_caller
    ldr r1,=0x8098F30|1
    bl r1_caller
    bl wait_flash_to_new3
    pop {pc}
