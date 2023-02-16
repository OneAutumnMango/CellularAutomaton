	.text
	.globl println
	
println:	# a0: line | a1: word
	li s0, 0 		# current position (pos)
	li s1, 0xffff8000    	# starting address of the graphics display
	li s2, 0x80000000	# 0x80000000 = 0b1000...0
	
loop:
	li t0, 32
	bge s0, t0, end  	# branch if pos >= 32
	
	srl t0, s2, s0  
	and t0, t0, a1  	# checks bit at (pos) position

	beqz t0, skip		# skip the write if t0 == 0	
	jal write
skip:
	addi s0, s0, 1		# increment pos

	j loop
	
write:
	li t1, 4		# length of word
	mul t1, t1, s0		# pos * 4 		(address incrementer)
	add t2, s1, t1		# start addr + pos*4 	(address of word to write to)
	
	lw t3, (t2)			# load word to write to
	srl t4, s2, a0		# shift 0b100...0 >> line(a0) 
	or t3, t3, t4		# write bit from above to word
	sw t3, (t2)			# save word back to addr
	
	# # ---------------
	# li t6, 0xffff000c 	# print current pos to debug
	# sw s0, (t6)
	# # ---------------
	
	ret
	
end:
	li a7, 10
	ecall