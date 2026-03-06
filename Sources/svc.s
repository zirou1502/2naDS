.arm
.balign 4

.macro SVC_BEGIN name
    .section .text.\name, "ax", %progbits
    .global \name
    .type \name, %function
    .align 2
    .cfi_startproc
\name:
.endm

.macro SVC_END
    .cfi_endproc
.endm

SVC_BEGIN svcSetWatchpoint
    svc 0xC0
    bx lr
SVC_END

SVC_BEGIN svcDisableWatchPoint
    svc 0xC1
    bx lr
SVC_END

SVC_BEGIN svcGetWatchpointInfo
    svc 0xC2
    bx lr
SVC_END