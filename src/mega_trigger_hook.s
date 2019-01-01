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
.global bx_move_menu_return
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
	bl clear_triggers
	ldr r3, =battle_bufferA
	ldrb r0, [r4] 
	ldr r1, =(0x08057590|1)
	bx r1

	.global is_z_seted
is_z_seted:
    ldr     r1,=0x2024218
    ldr     r1,[r1]
    add     r1,#0xD8
    ldrb    r0,[r1]
    ldr r1,  =active_bank
    ldrb r1, [r1]
    lsr r0,r0,r1
    mov r1,#3
    and     r0,r1
    bx lr


check_z_seted:
    bl is_z_seted
    cmp     r0,#0x1
    beq     case1
    push {r0-r4}
    bl position_trigger
    pop {r0-r4}
    ldr     r1,=0x3005D90
    ldr     r1,[r1]
    ldrb    r1,[r1,#0x13]
    cmp     r1,#0x2
    beq     case2
    ldr     r0,=0x8057C45
    bx       r0
case1:
    ldr     r0,=0x8057F9F
    bx r0
case2://end
    ldr     r0,=0x8057C29
    bx      r0
