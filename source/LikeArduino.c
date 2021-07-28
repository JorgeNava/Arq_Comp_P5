#include "LikeArduino.h"
#include <math.h>

void pinMode(unsigned char ubPort, unsigned char ubPin, unsigned char ubMode){
	unsigned int *pHelper, *pPCR, *pPDDR;
	unsigned int offset = (ubPort - 'A');
	unsigned int clock = FIRST_CLOCK_PORT;
	unsigned int bitHelper = 1;
	pHelper = SCGC5;
	// f(x) = 512 (2^offset)
	*pHelper = *pHelper | clock<<offset;//enciende el reloj del puerto
	//*pHelper = *pHelper | (FIRST_CLOCK_PORT*((int)pow(2.0, (double)offset)));
	pPCR = PCR + (0x1000 * offset) + (ubPin*4);// Se asigna la direccion de memoria inicial para los PCRs de los puertos
	*pPCR = GPIO;
	pPDDR = PDDR + (64 * offset);// Se le suma 64 por que la diferencia entre cada direccions de PDDr en hex es 40 = 64 en decimal
	bitHelper = bitHelper<<ubPin;// Hace la mascara para el OR con *pPDDR
	if(ubMode){
		*pPDDR = *pPDDR | bitHelper;
	}else{
		*pPDDR = *pPDDR & ~bitHelper;
	}
	return;
}
void digitalWrite(unsigned char ubPort, unsigned char ubPin, unsigned char ubValue){
	unsigned int offset = (ubPort - 'A');
	unsigned int *pPDOR;
	unsigned int bitHelper = 1;
	pPDOR =  PDOR + (64 * offset);// Se le suma 64 por que la diferencia entre cada direccions de PDOR en hex es 40 = 64 en decimal
	printf("%d",pPDOR);
	printf("%d",offset);
	bitHelper = bitHelper<<ubPin;// Hace la mascara para el OR con *pPDDR
		if(ubValue){
			*pPDOR = *pPDOR | bitHelper;
		}else{
			*pPDOR = *pPDOR & ~bitHelper;
		}
	return;
}


//int *p2SIMS;
//	int *p2PCRRed;
//	int *p2PCRBlue;
//	int *p2PCRGreen;
//	int *p2PDDRA;
//	int *p2PDDRB;
//	int *p2PDORA;
//	int *p2PDORB;
//	int *p2PDIRA;
//	int *p2PDIRB;
//
//	p2SIMS = 0x40048038;
//
//	*p2SIMS = 0x600; //activar el reloj del puerto A y B
//
//	p2PCRRed = 0x4004A048;
//	p2PCRBlue = 0x40049034;
//	p2PCRGreen = 0x4004A04C;
//
//	*p2PCRRed = 0x100;
//	*p2PCRBlue = 0x100;
//	*p2PCRGreen = 0x100;
//
//	p2PDDRA = 0x400FF014;
//	p2PDDRB = 0x400FF054;
//
//	*p2PDDRA = 0x2000;
//	*p2PDDRB = 0xC0000;
//
//	p2PDORA = 0x400FF000;
//	p2PDORB = 0x400FF040;
//
//	*p2PDORB = ~0x0;
//	*p2PDORA = ~0x0;
//
//	while(1){
//		*p2PDORB = ~0x0;
//		*p2PDORA = ~0x2000;
