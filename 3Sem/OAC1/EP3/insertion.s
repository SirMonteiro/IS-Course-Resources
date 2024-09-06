insertionSort:
        addiu   $sp,$sp,-32         # Allocate 32 bytes on the stack for local variables
        sw      $fp,28($sp)         # Save the old frame pointer
        move    $fp,$sp             # Set the frame pointer to the current stack pointer
        sw      $4,32($fp)          # Save the base address of the array (first argument)
        sw      $5,36($fp)          # Save the length of the array (second argument)
        li      $2,1                # Load immediate value 1 into register $2
        sw      $2,12($fp)          # Store 1 into the memory location at $fp + 12 (initialize i = 1)
        b       $L2                 # Branch to the label $L2
        nop                         # No operation (delay slot)

$L6:
        lw      $2,12($fp)          # Load i from the memory location at $fp + 12
        nop                         # No operation (delay slot)
        sll     $2,$2,2             # Shift left logical by 2 bits (i * 4, since each int is 4 bytes)
        lw      $3,32($fp)          # Load the base address of the array
        nop                         # No operation (delay slot)
        addu    $2,$3,$2            # Add the base address and the offset to get the address of array[i]
        lw      $2,0($2)            # Load array[i] into register $2
        nop                         # No operation (delay slot)
        sw      $2,16($fp)          # Store array[i] into the memory location at $fp + 16 (initialize key)
        lw      $2,12($fp)          # Load i from the memory location at $fp + 12
        nop                         # No operation (delay slot)
        addiu   $2,$2,-1            # Decrement i by 1 (i - 1)
        sw      $2,8($fp)           # Store the decremented value (i - 1) into the memory location at $fp + 8
        b       $L3                 # Branch to the label $L3
        nop                         # No operation (delay slot)

$L5:
        lw      $2,8($fp)           # Load j from the memory location at $fp + 8
        nop                         # No operation (delay slot)
        sll     $2,$2,2             # Shift left logical by 2 bits (j * 4)
        lw      $3,32($fp)          # Load the base address of the array
        nop                         # No operation (delay slot)
        addu    $3,$3,$2            # Add the base address and the offset to get the address of array[j]
        lw      $2,8($fp)           # Load j from the memory location at $fp + 8
        nop                         # No operation (delay slot)
        addiu   $2,$2,1             # Increment j by 1 (j + 1)
        sll     $2,$2,2             # Shift left logical by 2 bits ((j + 1) * 4)
        lw      $4,32($fp)          # Load the base address of the array
        nop                         # No operation (delay slot)
        addu    $2,$4,$2            # Add the base address and the offset to get the address of array[j + 1]
        lw      $3,0($3)            # Load array[j] into register $3
        nop                         # No operation (delay slot)
        sw      $3,0($2)            # Store array[j] into array[j + 1]
        lw      $2,8($fp)           # Load j from the memory location at $fp + 8
        nop                         # No operation (delay slot)
        addiu   $2,$2,-1            # Decrement j by 1 (j - 1)
        sw      $2,8($fp)           # Store the decremented value (j - 1) into the memory location at $fp + 8

$L3:
        lw      $2,8($fp)           # Load j from the memory location at $fp + 8
        nop                         # No operation (delay slot)
        bltz    $2,$L4              # Branch to $L4 if j < 0
        nop                         # No operation (delay slot)

        lw      $2,8($fp)           # Load j from the memory location at $fp + 8
        nop                         # No operation (delay slot)
        sll     $2,$2,2             # Shift left logical by 2 bits (j * 4)
        lw      $3,32($fp)          # Load the base address of the array
        nop                         # No operation (delay slot)
        addu    $2,$3,$2            # Add the base address and the offset to get the address of array[j]
        lw      $2,0($2)            # Load array[j] into register $2
        lw      $3,16($fp)          # Load key from the memory location at $fp + 16
        nop                         # No operation (delay slot)
        slt     $2,$3,$2            # Set $2 to 1 if key < array[j], else set $2 to 0
        bne     $2,$0,$L5           # Branch to $L5 if key < array[j]
        nop                         # No operation (delay slot)

$L4:
        lw      $2,8($fp)           # Load j from the memory location at $fp + 8
        nop                         # No operation (delay slot)
        addiu   $2,$2,1             # Increment j by 1 (j + 1)
        sll     $2,$2,2             # Shift left logical by 2 bits ((j + 1) * 4)
        lw      $3,32($fp)          # Load the base address of the array
        nop                         # No operation (delay slot)
        addu    $2,$3,$2            # Add the base address and the offset to get the address of array[j + 1]
        lw      $3,16($fp)          # Load key from the memory location at $fp + 16
        nop                         # No operation (delay slot)
        sw      $3,0($2)            # Store key into array[j + 1]
        lw      $2,12($fp)          # Load i from the memory location at $fp + 12
        nop                         # No operation (delay slot)
        addiu   $2,$2,1             # Increment i by 1 (i + 1)
        sw      $2,12($fp)          # Store the incremented value (i + 1) into the memory location at $fp + 12

$L2:
        lw      $3,12($fp)          # Load i from the memory location at $fp + 12
        lw      $2,36($fp)          # Load the length of the array
        nop                         # No operation (delay slot)
        slt     $2,$3,$2            # Set $2 to 1 if i < length, else set $2 to 0
        bne     $2,$0,$L6           # Branch to $L6 if i < length
        nop                         # No operation (delay slot)

        nop                         # No operation (delay slot)
        nop                         # No operation (delay slot)
        move    $sp,$fp             # Restore the stack pointer to the frame pointer
        lw      $fp,28($sp)         # Restore the old frame pointer
        addiu   $sp,$sp,32          # Deallocate the 32 bytes of stack space
        jr      $31                 # Return from the subroutine
        nop                         # No operation (delay slot)
