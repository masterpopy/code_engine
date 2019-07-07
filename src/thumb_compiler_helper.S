	.text
	.align 1
	.force_thumb
	
	.syntax unified
	.global __gnu_thumb1_case_uqi
	.thumb_func
	.type __gnu_thumb1_case_uqi,function
__gnu_thumb1_case_uqi:
	push	{r1}
	mov	r1, lr
	lsrs	r1, r1, #1
	lsls	r1, r1, #1
	ldrb	r1, [r1, r0]
	lsls	r1, r1, #1
	add	lr, lr, r1
	pop	{r1}
	bx	lr
	.size __gnu_thumb1_case_uqi, . - __gnu_thumb1_case_uqi
	
	.syntax unified
	.global __gnu_thumb1_case_uhi
	.thumb_func
	.type __gnu_thumb1_case_uhi,function
__gnu_thumb1_case_uhi:
	push	{r0, r1}
	mov	r1, lr
	lsrs	r1, r1, #1
	lsls	r0, r0, #1
	lsls	r1, r1, #1
	ldrh	r1, [r1, r0]
	lsls	r1, r1, #1
	add	lr, lr, r1
	pop	{r0, r1}
	bx	lr
	.size __gnu_thumb1_case_uhi, . - __gnu_thumb1_case_uhi

    .syntax unified
    .global __gnu_thumb1_case_sqi
    .thumb_func
    .type __gnu_thumb1_case_sqi,function
__gnu_thumb1_case_sqi:
	 push    {r1}
	 mov r1, lr
	 lsrs    r1, r1, #1
	 lsls    r1, r1, #1
	 ldrsb   r1, [r1, r0]
	 lsls    r1, r1, #1
	 add lr, r1
	 pop {r1}
	 bx  lr
    .size __gnu_thumb1_case_sqi, . - __gnu_thumb1_case_sqi
	
	.syntax unified
    .global __gnu_thumb1_case_shi
    .thumb_func
    .type __gnu_thumb1_case_shi,function
__gnu_thumb1_case_shi:
	push    {r0, r1}
	mov     r1, lr
	lsrs    r1, r1, #1
	lsls    r0, r0, #1
	lsls    r1, r1, #1
	ldrsh   r1, [r1, r0]
	lsls    r1, r1, #1
	add     lr, lr, r1
	pop     {r0, r1}
	bx      lr
    .size __gnu_thumb1_case_shi, . - __gnu_thumb1_case_shi


    .syntax unified
    .global __aeabi_uidiv
    .thumb_func
    .type __aeabi_uidiv,function
__aeabi_uidiv:
	ldr r3, =(__udivsi3)
	bx r3
	.size __aeabi_uidiv, . - __aeabi_uidiv

    .syntax unified
    .global __aeabi_idiv
    .thumb_func
    .type __aeabi_idiv,function
__aeabi_idiv:
	ldr r3, =(__divsi3)
	bx r3
	.size __aeabi_idiv, . - __aeabi_idiv


    .syntax unified
    .global memcpy
    .thumb_func
    .type memcpy,function
memcpy:
	ldr r3, =(memcpy_)
	bx r3
	.size memcpy, . - memcpy
	
    .syntax unified
    .global memset
    .thumb_func
    .type memset,function
memset:
	ldr r3, =(memset_)
	bx r3
	.size memset, . - memset
	
    .syntax unified
    .global malloc
    .thumb_func
    .type malloc,function
malloc:
	ldr r3, =(malloc_)
	bx r3
	.size malloc, . - malloc
	
    .syntax unified
    .global free
    .thumb_func
    .type free,function
free:
	ldr r1, =(free_)
	bx r1
	.size free, . - free

	.global read_word
read_word:
	movs r2, r0
	ldrb r0, [r2, #3]
	lsls r0, r0, #0x18
	ldrb r1, [r2, #2]
	lsls r1, r1, #0x10
	orrs r0, r1
	ldrb r1, [r2, #1]
	lsls r1, r1, #8
	orrs r0, r1
	ldrb r1, [r2]
	orrs r0, r1
	bx lr
	
	.global rng
rng:
	ldr r2, =(rand_seed)
	ldr r1, [r2]
	ldr r0, =(0x41C64E6D)
	muls r0, r1
	ldr r1, =(0x6073)
	adds r0, r0, r1
	str r0, [r2]
	lsrs r0, r0, #0x10
	bx lr

	.global __umodsi3
__umodsi3:
    ldr r3, = (__umodsi3__)
    bx r3

    .global LZ77UnCompWram
LZ77UnCompWram:
    swi 0x11
    bx lr

    .global LZ77UnCompVram
LZ77UnCompVram:
    swi 0x12
    bx lr

    .global CpuSet
CpuSet:
    swi 0xB
    bx lr

    .global get_attributes
get_attributes:
    ldr r3, =(__get_attributes)
    bx r3

    .global set_attributes
set_attributes:
    ldr r3, =(__set_attributes)
    bx r3

    .global set_callback2
set_callback2:
    ldr r1,=(__set_callback2)
    bx r1

    .global move_anim_task_delete
move_anim_task_delete:
    ldr r3, =(move_anim_task_del)
    bx r3

	.global random_value
random_value:
    push {r0,lr}
    bl rng
    ldr r1, [sp]
    bl __umodsi3
    pop {r1,pc}

    .global get_bank_side
get_bank_side:
    ldr r3, =get_bank_side0
    bx r3

    .global get_bank_identity
get_bank_identity:
     ldr r3, =get_bank_identity0
     bx r3
