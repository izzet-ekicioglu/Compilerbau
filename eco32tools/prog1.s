	.import	printi
	.import	printc
	.import	readi
	.import	readc
	.import	exit
	.import	time
	.import	clearAll
	.import	setPixel
	.import	drawLine
	.import	drawCircle
	.import	_indexError

	.code
	.align	4

	.export	main
main:
	sub	$29,$29,24		; allocate frame
	stw	$25,$29,12		; save old frame pointer
	add	$25,$29,24		; setup new frame pointer
	stw	$31,$25,-16		; save return register
	add	$8,$25,-4
	stw	$8,$29,0		; store argument #0
	jal	readi
	add	$8,$25,-8
	stw	$8,$29,0		; store argument #0
	jal	readi
	add	$8,$25,-4
	stw	$8,$29,0		; store argument #0
	add	$8,$25,-8
	stw	$8,$29,4		; store argument #1
	jal	add
	ldw	$31,$25,-16		; restore return register
	ldw	$25,$29,12		; restore old frame pointer
	add	$29,$29,24		; release frame
	jr	$31			; return

	.export	add
add:
	sub	$29,$29,16		; allocate frame
	stw	$25,$29,8		; save old frame pointer
	add	$25,$29,16		; setup new frame pointer
	stw	$31,$25,-12		; save return register
	add	$8,$25,0
	ldw	$8,$8,0
	ldw	$8,$8,0
	add	$9,$25,4
	ldw	$9,$9,0
	ldw	$9,$9,0
	add	$8,$8,$9
	add	$9,$25,-4
	stw	$8,$9,0
	add	$8,$25,-4
	ldw	$8,$8,0
	stw	$8,$29,0		; store argument #0
	jal	printi
	ldw	$31,$25,-12		; restore return register
	ldw	$25,$29,8		; restore old frame pointer
	add	$29,$29,16		; release frame
	jr	$31			; return
