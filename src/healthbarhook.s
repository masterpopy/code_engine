.text
.thumb
.align 1

load_graphics_hook:
	push {r0}
	mov r0, r5
	bl healthbar_load_graphics
	pop {r0}	
	pop {r4-r6}
	pop {r1}
	bx r1

position_trigger_hook:
	bl position_trigger
	mov r1, #0x0
	mov r8, r1
	ldr r3, =active_bank
	ldrb r0, [r3]
	lsl r0, r0, #0x9
	ldr r1, =(0x8057C0C|1)
	bx r1

@At 0x57d6c via r1
slide_out_on_pressing_A_hook1:
	ldrb r0, [r0]
	lsl r0, r0, #0x8
	orr r2, r0
	push {r2}
	bl hide_trigger_on_pressing_A
	pop {r2}
	ldr r1, =(0x8057E1C|1)
	bx r1

@At 0x578D8 via r1
slide_out_on_pressing_A_hook2:
	push {r0,r2}
	bl hide_trigger_on_pressing_A
	pop {r0,r2}
	lsl r0, r0, #0x8
	orr r2, r0
	mov r0, #0x1
	mov r1, #0xA
	ldr r3, =(0x80578E0|1)
	bx r3

