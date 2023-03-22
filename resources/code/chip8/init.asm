Inject_ptr: dw 0
Inject_save_p2: db 0,0,0
Inject_LoadPointer:
	LD I, Inject_ptr
	LD V1, [I]
	LD I, Inject_save_p2
	LD [I], V2
	LD V2, #10
	SUBN V2, V0
	SE VF, 0
	RET
	LD I, Inject_save_p2
	LD V2, [I]
	ADD V0, #A0
	LD I, Inject_load_inst
	LD [I], V1
Inject_load_inst:
	LD I, 0
	RET