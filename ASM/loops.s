	AREA AP1,CODE,READONLY
	ENTRY
START
		MOV R0 ,#1
		MOV R1 ,#4
		MOV R4,#0
LOOP
		CMP R1 ,R4
		BLE EXIT
		MUL R2,R1,R0
		MOV R0,R2
		SUB R1,R1,#1
		B LOOP
EXIT
		MOV R0,R1
		BX LR
STOP
		END
	