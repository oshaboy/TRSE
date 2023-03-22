	jp block1
Schip_n:
	db	0
Schip_x:
	db	0
Schip_y:
	db	0
Schip_c:
	db	0
	Schip_pram:
	 ds 8
	; NodeProcedureDecl -1
	
	
	; ***********  Defining procedure : Schip_ScrollDown4
	;    Procedure type : User-defined procedure
	
 ; Temp vars section
 ; Temp vars section ends
Schip_ScrollDown4_block2:
Schip_ScrollDown4:
	
	; Binary clause Simplified: LESS
	ld V0, #10
	LD V2, V0
	; Load Byte
	ld I,Schip_n
	ld V0,[I]
	subn V2,V0
	se VF, 0
	jp Schip_ScrollDown4_elsedoneblock6
Schip_ScrollDown4_ConditionalTrueBlock4: ;Main true block ;keep :
	
	; ****** Inline assembler section
		LD V0, Schip_n
		ADD V0, #C0
		LD I, schip_scd_insertion+1
		LD [I], V0
		schip_scd_insertion:
		SCD 0
		
	
	
Schip_ScrollDown4_elsedoneblock6:
	ret
end_procedure_Schip_ScrollDown4:
	; NodeProcedureDecl -1
	
	
	; ***********  Defining procedure : Schip_SavePRAM
	;    Procedure type : User-defined procedure
	
	Schip_SP_saved:
	 ds 8
Schip_SavePRAM_block9:
Schip_SavePRAM:
	
	; ****** Inline assembler section
	LD I, Schip_SP_saved
	LD [I], V7
	LD I, Schip_pram
	LD V7, [I]
	LD R, V7
	LD I, saved
	LD V7, [I]
	
	
	ret
end_procedure_Schip_SavePRAM:
	; NodeProcedureDecl -1
	
	
	; ***********  Defining procedure : Schip_LoadPRAM
	;    Procedure type : User-defined procedure
	
	Schip_LP_saved:
	 ds 8
Schip_LoadPRAM_block10:
Schip_LoadPRAM:
	
	; ****** Inline assembler section
	LD I, Schip_LP_saved
	LD [I], V7
	LD I, Schip_pram
	LD V7, R
	LD [I], V7
	LD I, saved
	LD V7, [I]
	
	
	ret
end_procedure_Schip_LoadPRAM:
	; NodeProcedureDecl -1
	
	
	; ***********  Defining procedure : Schip_PrintDigitTall
	;    Procedure type : User-defined procedure
	
	Schip_PDT_saved:
	 ds 3
Schip_PrintDigitTall_block11:
Schip_PrintDigitTall:
	
	; ****** Inline assembler section
        LD I, Schip_PDT_saved
        LD [I], V2
        LD I, Schip_x
        LD V2, [I]
        LD HF, V2
        DRW V0, V1, 10
        LD I, saved
        LD V2, [I]
    
	
	ret
end_procedure_Schip_PrintDigitTall:
block1:
	
main_block_begin_:
main_block_end_:
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
