/*****************************************************************************/
/*
/*		tbecc_f2x.c
/*  
/*      This file is part of TinyBECC.
/*
/*      TinyBECC is free software: you can redistribute it and/or modify
/*      it under the terms of the GNU General Public License as published by
/*      the Free Software Foundation, either version 3 of the License, or
/*      (at your option) any later version.
/*
/*      TinyBECC is distributed in the hope that it will be useful,
/*      but WITHOUT ANY WARRANTY; without even the implied warranty of
/*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/*      GNU General Public License for more details.
/*
/*      You should have received a copy of the GNU General Public License
/*      along with TinyBECC.  If not, see <http://www.gnu.org/licenses/>.
/*
/*      $Author$
/*      $Date$
/*      $Revision$
/*      $Id$
/*
/*****************************************************************************/
#include <memory.h>
#include "tinyBECC.h"
#include "tbecc_f2x.h"

uint	BIT[32] =
{		0x01,	  0x02,	    0x04, 	  0x08,	    0x10,	   0x20,	  0x40,	     0x80,
		0x100,	  0x200,	0x400,	  0x800,	0x1000,	   0x2000,    0x4000,    0x8000,
		0x10000,  0x20000,  0x40000,  0x80000,  0x100000,  0x200000,  0x400000,  0x800000,
		0x1000000,0x2000000,0x4000000,0x8000000,0x10000000,0x20000000,0x40000000,0x80000000
};
/*****************************************************************************/
/*
/*	tbecc_is_val_ui()		checks to see if an array is = a single int val, 
/*
/*  Return Values	FALSE		on false 
/*
/*                  TRUE		on true
/*
/*****************************************************************************/
uint		tbecc_is_val_ui(uint sz, uint *op, uint ui)
{
	uint    i;
	if(op[0]!=ui)	return FALSE;
	for(i=sz-1;i>0;i--){	if(op[i])	return FALSE;	}
	return TRUE;
}
/****************************************************************************/
/*
/*	tbecc_get_bitlength()	returns the bit length floor(log_2(op))
/*
/* Return Values   floor(log_2(op))
/*
/*****************************************************************************/
uint	tbecc_get_bitlength(uint sz, uint *op)
{
	sint	i, d;
	uint	n;
	if(sz == 0)		return 0;
	d = sz-1;
	while(op[d]==0){	--d;	}
	if(d<0)			return 0;	
	n = op[d];
	i = 0;
	while(n){	n>>=1;	++i;	}
	return (d*(LIMB_BIT_SIZE)) + i;
}/****************************************************************************/
/*
/*	tbecc_f2x_add()		This function adds two polynomials of the same length 
/*                      in F_2[x], rop = op1 + op2 in F_2[x]
/*
/*****************************************************************************/
void	tbecc_f2x_add(uint sz, uint *rop, uint *op1, uint *op2)
{
	sint i;
	i = -(int)(sz);		rop -= i;	op1 -= i;	op2 -= i;
	do{
		rop[i] = op1[i]^op2[i];
	}while(++i!=0);
}/****************************************************************************/
/*
/*	tbecc_shift_left()	This shifts the value to the left by amt many bits, or
/*						in terms of binary finite field this function performs 
/*						polynomial multiplication of op(x) in F_{2}[x] by x^amt  
/*
/*							rop(x) =  x^{amt}*op(x).
/*
/*	RESTRICTIONS:	rop must be properly allocated.
/*
/*****************************************************************************/
void	tbecc_shift_left(uint amt, uint sz, uint *rop, uint *op)
{
	unsigned int	big, r, l, size, n, t;

	size = sz + (amt/LIMB_BIT_SIZE);
	big = size - sz;
	l = amt - big*LIMB_BIT_SIZE;
	if(l==0){	
		memcpy(rop+big, op, sizeof(uint)*sz);	
		--big;
		while(big!=-1){	rop[big--] = 0;	}
		return;
	}
	r = LIMB_BIT_SIZE - l;
	sz = sz-1;
	n = 0;
	rop[sz+big+1] = 0;
	while(sz!=-1){
		t = op[sz];			rop[sz+big] = (t<<l);
		t>>=r;				rop[sz+big+1]|= t;
		--sz;
	}
	--big;
	while(big!=-1){	rop[big--] = 0;	}
}