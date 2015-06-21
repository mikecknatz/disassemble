
.data
main1String: .asciiz  "Inside main, after call to zap1, returned value = "
zap1String:  .asciiz  "Inside function zap1, quadrupled value = "
newline:     .asciiz  "\n"

.text

main:

        # Function prologue -- even main has one
        addiu $sp, $sp, -24   # allocate stack space -- default of 24 here
        sw    $fp, 0($sp)     # save caller's frame pointer
        sw    $ra, 4($sp)     # save return address
        addiu $fp, $sp, 20    # setup main's frame pointer

        # body of main

        # call function zap1 with 15
        addi  $a0, $zero, 15
        jal   zap1

        add   $t0, $v0, $zero # save return value in $t0

        la    $a0, main1String
        addi  $v0, $zero, 4
        syscall
        add   $a0, $t0, $zero
        addi  $v0, $zero, 1
        syscall
        la    $a0, newline
        addi  $v0, $zero, 4
        syscall

        # call function zap1 with 42
        addi  $a0, $zero, 42
        jal   zap1

        add   $t0, $v0, $zero # save return value in $t0

        la    $a0, main1String
        addi  $v0, $zero, 4
        syscall
        add   $a0, $t0, $zero
        addi  $v0, $zero, 1
        syscall
        la    $a0, newline
        addi  $v0, $zero, 4
        syscall

done:   # Epilogue for main -- restore stack & frame pointers and return
        lw    $ra, 4($sp)     # get return address from stack
        lw    $fp, 0($sp)     # restore the caller's frame pointer
        addiu $sp, $sp, 24    # restore the caller's stack pointer
        jr    $ra             # return to caller's code

zap1:
        # Function prologue
        addiu $sp, $sp, -24   # allocate stack space -- default of 24 here
        sw    $fp, 0($sp)     # save caller's frame pointer
        sw    $ra, 4($sp)     # save return address
        sw    $a0, 8($sp)     # save parameter value
        addiu $fp, $sp, 20    # setup zap1's frame pointer

        # something for zap to do
        add   $t0, $a0, $a0   # double the parameter
        add   $t0, $t0, $t0   # quadruple the parameter

        # print results
        la    $a0, zap1String # print the string
        addi  $v0, $zero, 4
        syscall
        add   $a0, $t0, $zero # print the quadruple'd value
        addi  $v0, $zero, 1
        syscall
        la    $a0, newline
        addi  $v0, $zero, 4
        syscall

        # put result of function in $v0
        # Note: could not do this before printing!
        add   $v0, $t0, $zero

        # Function epilogue -- restore stack & frame pointers and return
        lw    $ra, 4($sp)     # get return address from stack
        lw    $fp, 0($sp)     # restore the caller's frame pointer
        addiu $sp, $sp, 24    # restore the caller's stack pointer
        jr    $ra             # return to caller's code
