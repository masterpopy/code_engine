.text
.thumb
.align 1

.include "asm_defines.s"

no_item_if_embargo: @hook at 0x081B14C6, via r0
	ldr r2, =(not_in_battle)
	bl r2_caller
	cmp r0, #0x1
	beq no_item_if_embargo_works
	ldr r2, =(pokemenu_get_selected_poke)
	bl r2_caller
	cmp r0, #0x0
	beq check_if_embargo_on
	cmp r0, #0x1
	beq check_embargo_second_poke
no_item_if_embargo_works:
	ldr r0, =(0x3006328)
	ldr r1, =(0x081B6794 | 1)
	ldr r2, [r0]
	mov r0, r5
	bl r2_caller
no_item_if_embargo_ret:
	ldr r0, =(0x081B159E | 1)
	bx r0
	
check_embargo_second_poke:
	mov r0, #0x2
check_if_embargo_on:
	ldr r2, =(get_bank_by_player_ai)
	bl r2_caller
	bl is_embargo_on
	cmp r0, #0x0
	beq no_item_if_embargo_works
	ldr r0, =(item_effectiveness)
	mov r1, #0x0
	strb r1, [r0]
	mov r0, #5
	ldr r2, =(play_sound)
	bl r2_caller
	ldr r2, =(0x081B1B5C | 1)
	ldr r0, =(embargo_text_onbagitem) @text ptr
	mov r1, #1
	bl r2_caller
	ldr r2, =(bgid_mark_for_sync)
	mov r0, #2
	bl r2_caller
	ldr r1, =(tasks)
	lsl r0, r5, #2
	add r0, r5
	lsl r0, r0, #3
	add r0, r0, r1
	ldr r1, =(0x081B6794 | 1)
	str r1, [r0]
	b no_item_if_embargo_ret
	
embargo_text_onbagitem:
.byte 0x02, 0x0D, 0x03, 0xE5, 0x10, 0xE3, 0x0C, 0xAD, 0x0D, 0xE6, 0x0D, 0xA4, 0x03, 0xAB, 0xFE, 0x0B, 0xF5, 0x0F, 0x71, 0x03, 0x07, 0x07, 0x8F, 0xAB, 0xFC, 0x9, 0xFF
