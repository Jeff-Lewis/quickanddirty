.cseg
;***** Subroutine Register Variables

.def	drem8u	=r15		;remainder
.def	dres8u	=r16		;result
.def	dd8u	=r16		;dividend
.def	dv8u	=r17		;divisor
.def	dcnt8u	=r18		;loop counter

;***** Code

div8u:
	sub		drem8u,drem8u	; clear remainder and carry
	ldi		dcnt8u,9		; init loop counter
d8u_1:	
	rol		dd8u			; shift left dividend
	dec		dcnt8u			; decrement counter
	brne	d8u_2			; if done
	ret						; return
d8u_2:	
	rol		drem8u			; shift dividend into remainder
	sub		drem8u,dv8u		; remainder = remainder - divisor
	brcc	d8u_3			; if result negative
	add		drem8u,dv8u		; restore remainder
	clc						; clear carry to be shifted into result
	rjmp	d8u_1			; else
d8u_3:	
	sec						; set carry to be shifted into result
	rjmp	d8u_1
