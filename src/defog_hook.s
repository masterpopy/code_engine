.text
.thumb
.thumb_func

.align 1
DEFOG_animation_hook:
	ldr r0, =(0x020241EA)
	ldrh r0, [r0]
	mov r2, #0xD8
	lsl r2, r2, #0x1
THUNDER_WAVE_animation_loader:
	ldr r0, =(0x08595840)

return_DEFOG_anim_hook:
	add r1, #0x20
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	mov r7, #0x22
	ldr r3, =(0x0810AA4D)
	bx r3
