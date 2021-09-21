/*
 * lock.h
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */

#ifndef LOCK_H_
#define LOCK_H_

// zabranjuje prekide
//#define lock asm cli

// dozvoljava prekide
//#define unlock asm sti

// zabranjuje prekide -
// na ovaj nacin omoguceno je
// ugnezdavanje parova poziva lock-unlock
#define lock asm{\
 		pushf;\
 		cli;\
}

// dozvoljava prekide
#define unlock asm popf


#endif /* LOCK_H_ */
