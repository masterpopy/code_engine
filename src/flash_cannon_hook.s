.text
.thumb
.thumb_func
.align 1

FLASH_CANNON_animation_hook:
	ldr r0, =(0x020241EA)
	ldrh r0, [r0]
	mov r2, #0xD7
	lsl r2, r2, #0x1
	cmp r0, r2
	bne CHARGE_animation_loader

FLASH_CANNON_animation_loader:
	ldr r0, =(FLASH_CANNON_animation_part_5)
	b return_flash_cannon_anim_hook

CHARGE_animation_loader:
	ldr r0, =(0x085958A8)

return_flash_cannon_anim_hook:
	mov r3, #0x24
	ldsh r1, [r5, r3]
	mov r3, #0x26
	ldsh r2, [r5, r3]
	ldr r3, =(0x0810ABB3)
	bx r3

.align 2
FLASH_CANNON_animation_part_5:
.byte 0xE3, 0x27, 0x71, 0x27, 0x04, 0x49, 0x52, 0x08, 0xA0, 0x58, 0x59, 0x08, 0x00, 0x00, 0x00, 0x00 
.byte 0xA8, 0xC6, 0x2E, 0x08, 0x29, 0x74, 0x00, 0x08
