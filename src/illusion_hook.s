.text
.thumb
.align 1

illusion_throw_different_ball: @r0 contains bank
	bl b_get_ball_to_throw
	mov r4, r0
	ldr r2, =(0x080754DA | 1)
.global r2_caller
r2_caller:
	bx r2
	
illusion_on_player_switch_in:
	push {r5}
	mov r5, r0 @party address
	mov r1, r6 @bank
	bl try_illusion_change
	cmp r0, #0x0
	beq illusion_on_player_switch_in_get_normal_species
	mov r0, r6 @bank
	bl get_transform_species
	mov r8, r0
illusion_on_player_switch_in_get_normal_species:
	mov r0, r5 @party address
	mov r1, #0xB
	bl get_attributes
	mov r8, r0
illusion_on_player_switch_in_return:
	pop {r5}
	ldr r0, =(0x0805B29C | 1)
	bx r0
	
illusion_pokenick_hpbox:
	mov r0, r7
	bl update_pokenick_in_healthbox
	ldr r0, =(0x08074278 | 1)
	bx  r0

anim_spritechange_pal:
	mov r0, r7 @bank
	mov r1, r6 @arg1
	bl update_transform_sprite_pal
	ldr r0, =(0x0805E726 | 1)
	bx r0
	
illusion_on_opponent_switch_in:
	push {r5}
	add r5, r0, r5 @poke ptr
	mov r0, r5
	mov r1, r6 @bank
	bl try_illusion_change
	cmp r0, #0x0
	beq illusion_on_opponent_switch_in_normal
	mov r0, r6 @bank
	bl get_transform_species
	mov r8, r0
	b illusion_on_opponent_switch_in_return
illusion_on_opponent_switch_in_normal:
	mov r0, r5
	mov r1, #0xB
	bl get_attributes
	mov r8, r0
illusion_on_opponent_switch_in_return:
	pop {r5}
	ldr r0, =(0x08061426 | 1)
	bx r0
	
illusion_playcorrectcry: @r7 = pokestruct, r5 = bank
	mov r0, r5
	bl get_transform_species
	cmp r0, #0x0
	beq illusion_playcorrectcry_nottransformed
	mov r9, r0
	b illusion_playcorrectcry_return
illusion_playcorrectcry_nottransformed:
	mov r0, r7
	mov r1, #0xB
	bl get_attributes
	mov r9, r0
illusion_playcorrectcry_return:
	ldr r1, =(0x08075DE4 | 1)
.global r1_caller
r1_caller:
	bx r1
	