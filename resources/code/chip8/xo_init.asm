	LD I, Inject_ptr
	LD V1, [I]
	LD I, XO_CHIP_load_inst
	LD [I], V1
	dw #f000
XO_CHIP_load_inst:
	dw 0
	RET