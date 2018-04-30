.text
.thumb
.thumb_func
.align 1

can_open_poke_menu:
	push {r3}
	ldrb r0, [r5] @bank trying to open poke menu
	bl can_switch
	cmp r0, #0
	beq cant_switch
	cmp r0, #0xFF
	beq ability_cant_switch
	@can switch
	ldr r0, =(0x0803C3B0 + 1)
	b return_loc
	
cant_switch:
	ldr r0, =(0x0803C2B8 + 1)
	b return_loc
	
ability_cant_switch:
	ldr r0, =(another_active_bank)
	ldrb r1, [r0]
	ldr r0, =(0x0803C376 + 1)

return_loc:
	pop {r3}
	bx r0
	