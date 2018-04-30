.text
.thumb
.thumb_func
.align 1

target_self_ally:
	ldr r7, =(active_bank)
	ldrb r5, [r7]
	cmp r4, #0x12
	bne just_self
	mov r0, r5
	bl is_bank_present
	cmp r0, #0
	beq just_self
	mov r0, #2
	eor r0, r5
	bl is_bank_present
	cmp r0, #0
	bne choose_target_doubles
	
just_self:
	ldr r0, =(move_selection_chosen_target_pbs)
	strb r5, [r0]
	ldr r0, =(0x08057D62 + 1)
	bx r0
	
choose_target_doubles:
	ldr r0, =(0x08057D80 + 1)
	bx r0
	
get_move_target:
	push {lr}
	ldr r1, =(active_bank)
	ldrb r6, [r1]
	mov r2, #0x58
	mul r2, r6
	ldr r1, =(battle_participants)
	add r1, #0xC
	add r2, r2, r1
	ldr r1, =(move_selection_cursor_pbs)
	add r1, r6, r1
	ldrb r1, [r1]
	lsl r1, r1, #1
	add r2, r2, r1
	ldrh r1, [r2]
	ldr r2, =(move_table)
	mov r7, #0xC
	mul r1, r7
	add r2, r2, r1
	ldrb r2, [r2, #6]
	cmp r2, #0x12
	beq is_acupressure
	mov r0, #0
	pop {pc}
	
is_acupressure:
	mov r1, #1
	pop {pc}
	
choose_self_or_ally_left:
	push {r6-r7}
	bl get_move_target
	pop {r6-r7}
	cmp r1, #1
	bne not_acupressure
	cmp r0, #0
	beq can_target_left
	cmp r0, #2
	beq can_target_left
	ldr r0, =(0x08057A70 + 1)
	bx r0
	
not_acupressure:
	cmp r0, #0
	beq cant_target_left
	cmp r0, #1
	beq can_target_left
	cmp r0, #2
	beq cant_target_left

can_target_left:
	ldr r0, =(0x08057A6E + 1)
	bx r0
	
cant_target_left:
	ldr r0, =(0x08057A32 + 1)
	bx r0
	
choose_self_or_ally_right:
	push {r6-r7}
	bl get_move_target
	pop {r6-r7}
	cmp r1, #1
	bne not_acupressureright
	cmp r0, #0
	beq can_target_right
	cmp r0, #2
	beq can_target_right
	ldr r0, =(0x08057B94 + 1)
	bx r0
	
not_acupressureright:
	cmp r0, #0
	beq cant_target_right
	cmp r0, #1
	beq can_target_right
	cmp r0, #2
	beq cant_target_right

can_target_right:
	ldr r0, =(0x08057B92 + 1)
	bx r0
	
cant_target_right:
	ldr r0, =(0x08057B56 + 1)
	bx r0
