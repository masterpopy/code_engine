.text
.thumb
.thumb_func
.align 1

.include "asm_defines.s"

special_EF_hook: @hook at 0x08163ACC, via r3
	ldrh r1, [r2]
	add r0, #0x26
	strb r1, [r0]
	ldrh r0, [r2]
	cmp r0, #0xA
	bls special_EF_switchjump
	cmp r0, #0xB
	beq special_EF_custom_tag_battle
special_EF_hook_end:
	ldr r0, =(0x08163E68 | 1)
	bx r0
	
special_EF_switchjump:
	ldr r1, =(0x08163ADA | 1)
	bx r1
	
special_EF_custom_tag_battle:
	bl custom_stevenliketag_battle
	b special_EF_hook_end
	
bbp07_correct_sprite: @hook at 0805B4F8, via r0
	ldr r5, =(battle_flags)
	ldr r0, [r5]
	mov r1, #BATTLE_LINK
	tst r1, r0
	bne bbp07_linkbattle
	bl get_player_backspriteID
	mov r4, r0
	ldr r1, [r5]
	mov r2, #BATTLE_PARTER
	tst r1, r2
	beq bbp07_no_partner
	mov r0, #0x20
	mov r9, r0
	bl does_partner_animate
	cmp r0, #0x0
	bne bbp07_load_animated
	mov r0, #0x5A
	mov r9, r0
	ldr r1, =(0x0805B5FA | 1)
	bx r1
bbp07_no_partner:
	ldr r0, =(0x0805B63C | 1)
	bx r0
bbp07_load_animated:
	ldr r0, =(0x0805B618 | 1)
	bx r0
bbp07_linkbattle:
	ldr r0, =(0x0805B504 | 1)
	bx r0

bbp07_correct_sprite2: @hook at 0x0805B664, via r0
	bl does_partner_animate
	cmp r0, #0x0
	bne bpp07_animates
	ldr r0, =(0x0805B670 | 1)
	bx r0
bpp07_animates:
	ldr r0, =(0x0805B794 | 1)
	bx r0
	
bbpp07_correct_sprite: @hook at 0x081BD384, via r0
	bl does_partner_animate
	ldr r2, =(partner_trainer)
	cmp r0, #0x0
	bne bbpp07_correct_sprite_animate
	ldr r0, =(0x081BD3A8 | 1)
	bx r0
bbpp07_correct_sprite_animate:
	ldr r4, =(partner_sprite)
	ldrh r4, [r4]
	cmp r4, #0
	beq bbpp07_steven_sprite_animate
	mov r4, r4
	mov r0, #0x5A
	mov r9, r0
	ldr r1, =(trainerhrow_positions)
	lsl r0, r4, #2
	add r1, r1, r0
	ldrb r1, [r1]
	mov r0, #8
	sub r0, r0, r1
	lsl r0, r0, #0x12
	ldr r1, =(0x500000)
	add r0, r0, r1
	lsr r7, r0, #0x10
	ldr r0, =(0x081BD3D6 | 1)
	bx r0
bbpp07_steven_sprite_animate:
    mov r4, #7
	mov r0, #0x5A
	mov r9, r0
	ldr r1, =(trainerhrow_positions)
	lsl r0, r4, #2
	add r1, r1, r0
	ldrb r1, [r1]
	mov r0, #8
	sub r0, r0, r1
	lsl r0, r0, #0x12
	ldr r1, =(0x500000)
	add r0, r0, r1
	lsr r7, r0, #0x10
	ldr r0, =(0x081BD3D6 | 1)
	bx r0
	
window_control_multibattle: @hook at 0x0803682C, via r1
	cmp r0, #0x0
	beq window_control_normal
	push {r2}
	bl does_partner_animate
	pop {r2}
	cmp r0, #0x1
	beq window_control_normal
	ldr r0, =(0x0803683A | 1)
	bx r0
window_control_normal:
	ldr r0, =(0x08036870 | 1)
	bx r0
	
prepare_intro_slide: @hook at 0x081181E8, via r0
	bl does_partner_animate
	cmp r0, #1
	beq prepare_intro_slide_normal
	ldr r0, =(0x08118D68 | 1)
	ldr r1, =(0x08118258 | 1)
	bx r1
prepare_intro_slide_normal:
	ldr r2, =(battle_flags)
	ldr r0, =(0x08118208 | 1)
	bx r0
	
bbpp2F_trainer_throw: @hook at 0x081BE1B0, via r1
	mov r4, r0
	bl does_partner_animate
	cmp r0, #0
	beq bbpp2F_trainer_throw_sprite
	ldr r0, =(trainerthrow_pals)
	ldr r1, =(partner_sprite)
	ldrh r1, [r1]
	cmp r1, #0
	beq bbpp2F_steven_throw_sprite
	mov r1, r1
	lsl r1, r1, #3
	ldr r0, [r0, r1]
	ldr r2, =(0x081BE1C2 | 1)
	bx r2
bbpp2F_trainer_throw_sprite:
	ldr r2, =(partner_trainer)
	ldrh r0, [r2]
	ldr r1, =(0x081BE1FC | 1)
	bx r1
bbpp2F_steven_throw_sprite:
    mov r1, #7
	lsl r1, r1, #3
	ldr r0, [r0, r1]
	ldr r2, =(0x081BE1C2 | 1)
	bx r2
bbp2F_trainer_throw: @hook at 0805CB28, via r0
	bl get_player_backsprite_pal
	ldr r1, =(0x0805CB36 | 1)
	bx r1
	
get_partner_frontier_spriteID: @hook at 0x08162AA0 via r1
	push {r4,r5,LR}
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	mov r1, #0x80
	lsl r1, r1, #7 @r1 = 0x4000
	tst r1, r4
	beq get_normal_spriteID
	mov r0, r4
	bl get_partner_spriteID
	ldr r1, =(0x08162BCA | 1)
	bx r1
get_normal_spriteID:
	mov r5, r4
	ldr r2, =(0x08165C40 | 1)
	bl r2_caller
	ldr r1, =(0x08162AAC | 1)
	bx r1
	
tag_wild_prepare_buffer_hook: @hook at 0x0803AEC0 via r0
	ldr r0, =(active_bank)
	ldrb r0, [r0]
	bl is_controlled_by_trainer_in_multi
	cmp r0, #0
	beq tag_wild_no_throw
	ldr r0, =(0x0803AF14 | 1)
	bx r0
tag_wild_no_throw:
	ldr r0, =(0x0803AF20 | 1)
	bx r0
	