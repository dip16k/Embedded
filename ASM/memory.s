	AREA APP2, CODE, READONLY
	ENTRY
START
	MOV R0,#1
	MOV R1,#2
	MOV R2,#3
	MOV R3,#4
	MOV R4,#100
	STR R4,[R0,R1]
STOP
	END