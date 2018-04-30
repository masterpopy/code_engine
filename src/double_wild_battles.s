.text
.thumb
.thumb_func
.align 1

wild_grass_hook: @at 0x080B5424, via r1
	bl wild_grass_battle
	ldr r1, =(0x080B5430 | 1)
	bx r1

ignore_action_for_second: @at 0x0803BFD0, via r0, r2 is bank, r3 is 0
	push {r2-r3}
	mov r0, r2
	bl ignore_second_poke_action
	pop {r2-r3}
	cmp r0, #0x0
	beq choose_action_for_poke
	ldr r0, =(0x0803BFF6 | 1)
	bx r0
choose_action_for_poke:
	ldr r0, =(0x0803C00C | 1)
	bx r0
	
can_run_from_double: @at 0x0803ED80, via r0, r1 is battle flags
	ldr r0, [r1]
	cmp r0, #5 @wild double
	beq check_further
	mov r1, #1
	and r0, r1
	cmp r0, #0
	beq check_further
	ldr r0, =(0x0803EE06 | 1)
	bx r0
check_further:
	ldr r0, =(0x0803ED8A | 1)
	bx r0
	
throw_at_correct_poke: @at 0x0805BC36, via r0, r5 is throwing bank
	ldrb r0, [r4]
	mov r1, r0
	ldr r2, =(bank_target)
	ldrb r2, [r2]
	ldr r3, =(0x0805BC48 | 1)
	bx r3
