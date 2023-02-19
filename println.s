	.text
	.globl println
	
println:	# a0: line | a1: word
	mv t6, ra  		# save return address to leave the program

	li t4, 0 		# current position (pos)
	li t5, 0xffff8000    	# starting address of the graphics display
	
	
loop:
	li t0, 32
	bge t4, t0, exit  	# branch if pos >= 32
	
	li t0, 0x00000001
#	srl t0, t0, t4  	# mirrors along x-axis
	sll t0, t0, t4 
	and t0, t0, a1  	# checks bit at (pos) position

	beqz t0, skip		# skip the write if t0 == 0	
	jal write
skip:
	addi t4, t4, 1		# increment pos

	j loop
	
write:
	li t0, 4		# length of word
	mul t0, t0, t4		# pos * 4 		(address incrementer)
	add t1, t5, t0		# start addr + pos*4 	(address of word to write to)
	
	lw t2, (t1)			# load word to write to

	li t0, 0x80000000	# 0x80000000 = 0b1000...0
	srl t3, t0, a0		# shift 0b100...0 >> line(a0) -> bit mask
#	sll t3, t0, a0		# shift 0b000..1 << line(a0)  -> mirrors along y-axis

	or t2, t2, t3		# write bit from above to word
	sw t2, (t1)			# save word back to addr
	
	ret
	
exit:
	jr t6  			# return from program
