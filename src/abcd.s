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

    .global change_animation_bank_target
change_animation_bank_target:
    ldr r2,=animation_bank_attacker
    ldrb r0,[r2]
    strb r0,[r2,#1]
    bx lr

    .global change_animation_bank_attacker
change_animation_bank_attacker:
    ldr r2,=animation_bank_attacker
    ldrb r0,[r2,#1]
    strb r0,[r2]
    bx lr
	
trainer_battle_music: //0x806e4a8 r3  setvar 0x40fe
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
back0:
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

.global toxic_thread_task
toxic_thread_task:
    push {r0,r4-r5,lr}
    ldr r4,=toxic_thread_task_data
    ldrh r0,[r4]
    bl get_particle_pal
    ldrh r5,[r4,#2]
    strh r5,[r0,#8]
    ldrh r0,[r4]
    add r0, #1
    bl get_particle_pal
    strh r5,[r0,#8]
    ldr r0,[sp]
    bl move_anim_task_delete
    pop {r0,r4-r5,pc}

toxic_thread_task_data:
.hword 0x27C3, 0x7C1E



_080327A0_hook:
    and r0,r1
    cmp r0,#0
    beq _080327A0_hook_2
    ldr r3,=0x8032CC1
_080327A0_hook_2:
    ldr r3,=(0x08032824|1)
    bl back0
    bl after_hook
    ldr r3,=(0x080327B4|1)
    bx r3
