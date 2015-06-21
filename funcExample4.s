# funcExample4.s

# Takes a set of strings that are (sort of) email addresses.
# Prints the original string
# Calls convertCase procedure, which makes a copy of the string and converts
# upper-case letters to lower-case letters.  The procedure prints the
# modified string.


.data
mainNumNames:
         .word    5
mainNames:
         .word    mainName1
         .word    mainName2
         .word    mainName3
         .word    mainName4
         .word    mainName5

#                    123456789012345678901234567890123456789012
mainName1: .asciiz  "Patrick.Homer@mac.com"
mainName2: .asciiz  "PatrickH@email.Arizona.Edu"
mainName3: .asciiz  "patRICK@CS.Arizona.Edu"
mainName4: .asciiz  "someOneElse@someWhere.World.Com"
mainName5: .asciiz  "yetAnotherPersonHere@AnotherPlace.Email.tv"

mainString1:
         .asciiz  "The original string:  "
mainNewLine:
         .asciiz  "\n"
.text
main:
         # Prologue: set up stack and frame pointers for main
         addiu   $sp, $sp, -24    # allocate stack space -- default of 24
         sw      $fp, 0($sp)      # save frame pointer of caller
         sw      $ra, 4($sp)      # save return address
         addi    $fp, $sp, 20     # setup frame pointer for main
         
         # for (i = 0; i < mainNumNames; i++)
         #    get contents of mainNames[i]
         #    print string that starts at address in mainNames[i]
         #    jal convertCase
         
         addi    $t0, $zero, 0    # $t0 = i = 0
         la      $t1, mainNumNames
         lw      $t1, 0($t1)      # $t1 = mainNumNames
         la      $t2, mainNames   # $t2 = addr of mainNames[0]
mainLoopBegin:
         slt     $t3, $t0, $t1    # $t3 = i < mainNumNames
         beq     $t3, $zero, mainLoopEnd
         
         la      $a0, mainString1
         addi    $v0, $zero, 4
         syscall
         # get address of mainNames[i]
         sll     $t4, $t0, 2      # $t4 = i * 4
         add     $t5, $t4, $t2    # $t5 = addr of mainNames[i]
         
         # get the address of the start of the string
         lw      $t5, 0($t5)
         
         # print the original string
         addi    $a0, $t5, 0
         addi    $v0, $zero, 4
         syscall
         
         la      $a0, mainNewLine
         addi    $v0, $zero, 4
         syscall
         
         # call convertCase
         # save $t0, $t1, $t2 on the stack of main
         addiu   $sp, $sp, -16    # use 16 to keep $sp double-word aligned
         sw      $t2, 12($sp)
         sw      $t1,  8($sp)
         sw      $t0,  4($sp)
         # put addr of mainNames[i] in $a0
         addi    $a0, $t5, 0
         jal     convertCase
         
         # restore $t0, $t1, $t2
         lw      $t2, 12($sp)
         lw      $t1,  8($sp)
         lw      $t0,  4($sp)
         addiu   $sp, $sp, 16
         
         addi    $t0, $t0, 1     # i++
         j       mainLoopBegin
         
         
mainLoopEnd:         

mainDone:
         # Epilogue for main -- restore stack & frame pointers and return
         lw      $ra, 4($sp)      # get return address from stack
         lw      $fp, 0($sp)      # restore frame pointer for caller
         addiu   $sp, $sp, 24     # restore stack pointer for caller
         jr      $ra              # return to caller


# ConvertCase procedure:
# Will copy the string to the local stack.
# Will convert upper-case letters in the string to lower-case
# Will print the converted string

.data
convertCaseString:
         .asciiz "The converted string: "
convertCaseNewLine:
         .asciiz "\n"
.text
convertCase:
         # Prologue: set up stack and frame pointers for convertCase
         addiu   $sp, $sp, -24    # allocate stack space -- default of 24
         sw      $fp, 0($sp)      # save frame pointer of caller
         sw      $ra, 4($sp)      # save return address
         addi    $fp, $sp, 20     # setup frame pointer for convertCase
         # We need additional space, 43 bytes, to hold the characters of 
         # the string. Since the stack has to be double-word aligned, we
         # add 48 bytes to the size of the stack.
         addiu   $sp, $sp, -48

         # Copy the characters of the string onto our stack
         # while ( character != nul )
         #    copy charcter to our stack
         # put a nul character at the end
         addi    $t1, $sp, 0      # $t1 is where the next character goes
convertCaseCopyLoopBegin:
         lb      $t0, 0($a0)
         beq     $t0, $zero, convertCaseCopyLoopEnd
         sb      $t0, 0($t1)
         addi    $t1, $t1, 1      # $t1++
         addi    $a0, $a0, 1      # $a0++
         j       convertCaseCopyLoopBegin

convertCaseCopyLoopEnd:
         # put a nul character at the end
         sb      $zero, 0($t1)

         # Convert the upper-case letters to lower case
         # while ( character != nul )
         #    if ( 'A' <= character && character <= 'Z' )
         #       convert by masking with 32, which is 0x20
         addi    $t1, $sp, 0      # $t1 is where we get the next character
convertCaseConvertLoopBegin:
         lb      $t0, 0($t1)      # get the character
         beq     $t0, $zero, convertCaseConvertLoopEnd
         
         addi    $t2, $zero, 'A'  # put 'A' into $t2
         addi    $t2, $t2, -1     # ascii character before 'A'
         slt     $t3, $t2, $t0    # $t3 = ('A' <= character)
         beq     $t3, $zero, convertCaseNoConvert
         
         addi    $t2, $zero, 'Z'  # put 'Z' into $t2
         addi    $t2, $t2, 1      # ascii character after 'Z'
         slt     $t3, $t0, $t2    # $t3 = (character <= 'Z')
         beq     $t3, $zero, convertCaseNoConvert
         
         # convert the case by adding a bit in position 2^5
         ori     $t0, $t0, 0x20
         sb      $t0, 0($t1)
         
convertCaseNoConvert:
         addi    $t1, $t1, 1      # $t1++, so we can get the next character
         j       convertCaseConvertLoopBegin
         
convertCaseConvertLoopEnd:
         # Print the converted string
         la      $a0, convertCaseString
         addi    $v0, $zero, 4
         syscall
         
         addi    $a0, $sp, 0
         addi    $v0, $zero, 4
         syscall
         
         la      $a0, convertCaseNewLine
         addi    $v0, $zero, 4
         syscall

convertCaseDone:
         # Epilogue for convertCase -- restore stack & frame pointers and return
         # Remove the extra bytes used by the string
         addiu   $sp, $sp, 48

         # Now, clean up the rest of the stack
         lw      $ra, 4($sp)      # get return address from stack
         lw      $fp, 0($sp)      # restore frame pointer for caller
         addiu   $sp, $sp, 24     # restore stack pointer for caller
         jr      $ra              # return to caller
