	AREA TRANSFER, CODE ,READONLY
	ENTRY
START
	LDR R0,=0X01
	LDR R1,=0X02
	LDR R2,=0X03
	LDR R3,=0X04
	LDR R4,=0X05
	
	MOV R5,#0X40000000
	STM R5,{R0-R4}
	
	MOV R6,#0X40000000
	LDM R6,{R5-R10}
	
HERE
	B HERE
	
STOP
	END