bits 32

global _fibonacci@4, _walk_list_map@8


section .text


_fibonacci@4:
;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;	This method takes a single parameter:
;	
;	Param 1: The fibonacci number to calculate (e.g., "5" would indicate
;	to calculate and return the 5th fibonacci number).
;
;	int __stdcall fibonacci(int n);	
;
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;
mov edi, [esp+4]		;only 1 arg, put it in edx

mov eax, 1				;starting value
xor ecx, ecx			;second value

.loop:
  xadd eax, ecx			;exchanges first and second operand, then loads sum of two into destination (eax replaces edx, eax + edx replaces eax)
  dec edi				;count down
  cmp edi, 1			;have you done the loop edx times yet?
  ja .loop				;if edx is greater than 1 (not done) repeat
  
ret 4					;return eax
;;;;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;


struc Node
	.Next	resd  1
	.Data	resd  1
endstruc


_walk_list_map@8:
;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;	This method takes two parameters:
;
;	Param 1: A pointer to the beginning of a linked list of nodes (structure
;	definition above)
;
;	Param 2: A function pointer
;
;	Your task:
;	1.) Walk the list of nodes
;	2.) For each node, call the function pointer provided
;	as parameter 2, giving it as input the Data from the node.
;
;	void __stdcall walk_list_map(Node* n, void(*)(size_t));
;
; BEGIN STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;
mov edi, [esp+4]			;first param
mov edx, [esp+8]			;second param

.loop:
  mov esi, [edi+Node.Data]	;set to current node
  mov eax, esi				;put data into eax

  push eax
  call edx					;get [esp+8]
  pop eax

  mov edi, [edi+Node.Next]	;load next node
  cmp edi, 0				;null term?
  je .end					;yes
  jmp .loop					;no

.end:

ret 8						;return eax
;;;;;;;;;;;;;;;;;;;;;;;;;;
; END STUDENT CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;