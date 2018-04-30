.text
.thumb
.align 1

mega_trigger_hook:
	mov r6, #2		@B Button
	mov r0, r6
	and r0, r2
	cmp r0, #0x0
	bne b_is_pressed
	ldrb r0, [r1]
	cmp r0, #0x3B
	bls check_start_press

b_is_pressed:
	bl hide_trigger
	cmp r0, #0x0
	beq bx_move_menu_return
	ldr r0, =(0x8057E14|1)
	bx r0

check_start_press:
	mov r0, #0x8
	and r0, r2
	cmp r0, #0x0
	beq check_left
	ldr r0, =active_bank
	ldrb r0, [r0]
	bl set_mega_triggers_for_user_team
bx_move_menu_return:
	ldr r0, =(0x8057F9E|1)
	bx r0

check_left:
	ldr r0, =(0x8057E30|1)
	bx r0

reset_mega_trigger_hook:
	push {r4-r7, lr}
	ldr r4, =active_bank
	ldrb r0, [r4]
	bl clear_mega_triggers
	ldr r3, =battle_bufferA
	ldrb r0, [r4] 
	ldr r1, =(0x08057590|1)
	bx r1
