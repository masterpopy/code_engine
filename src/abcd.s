.text
.thumb
.thumb_func



.align 1
.global sub_0x8108ac0_task
sub_0x8108ac0_task:
	strh r0,[r6, #0xC]
	bl sub_0x8108ad4
	mov r2, #0xe
	ldsh r1,[r6,r2]
	mov r3, #0x10
	ldsh r2,[r6,r3]
	ldr r3, =(0x8108ae0|1)
	bx r3
	
trainer_battle_music: @0x806e4a8 r3
	push {r0-r2}
	ldr r0,=0x40fe
	ldr r1,=(0x0809D648|1)
	bl r1_caller
	mov r2, r0
	ldrh r0,[r2,#0]
	cmp r0, #0
	bne trainer_battle_music_return
	pop {r0-r2}
	lsl r0,r1,#2
	add r0,r0,r1
	lsl r0,r0,#3
	add r0,r0,r2
	ldr r3,=(0x806e4b0|1)
	bx r3
trainer_battle_music_return:
	mov r1,#0
	strh r1,[r2,#0]
	pop {r1-r3,pc}
	
	
get_active_poke_ability:
	bl get_poke_ability_active_bank
	ldr r1, = (0x804c99e|1)
	bx r1
	
get_active_poke_ability2:
	bl get_poke_ability_active_bank
	ldr r1, = (0x803ad6c|1)
	bx r1

wildbattle_clear_battleflags:
    ldr r4, =battle_flags
    ldr r0, [r4]
    lsl r0,  #31
    lsr r0,  #31
    str r0, [r4]
    bx  lr

