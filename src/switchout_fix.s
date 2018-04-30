.text
.thumb
.thumb_func
.align 1

explosion_like_switch_fix:
	push {r1-r3}
	lsl r0, r3, #2
	add r0, r0, r6
	ldr r0, [r0]
	and r1, r0
	cmp r1, #0
	bne dont_switch_yet
	mov r0, #0x0
	bl count_alive_mons
	cmp r0, #0x0
	beq switch_now
	mov r0, #0x1
	bl count_alive_mons
	cmp r0, #0x0
	beq switch_now
	ldr r0, =(no_of_all_banks)
	ldr r1, =(current_move_turn)
	ldrb r1, [r1]
	ldrb r0, [r0]
	cmp r1, r0
	bcc dont_switch_yet
switch_now:
	ldr r0, =(0x08041758 + 1)
	b switch_fix_end
dont_switch_yet:
	ldr r0, =(0x08041930 + 1)
switch_fix_end:
	pop {r1-r3}
	bx r0
