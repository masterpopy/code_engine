.text
.thumb
.thumb_func
.align 1

hazards_hook:
	bl entry_hazards_hook
	cmp r0, #0
	beq return
	ldr r0, =(0x0804DD8E + 1)
	bx r0
	
return:
	ldr r0, =(0x0804DC30 + 1)
	bx r0
