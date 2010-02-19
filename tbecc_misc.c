/*****************************************************************************/
/*
/*      tbecc_misc.c
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
#include "tinyBECC.h"
#include "tbecc_misc.h"
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
}
/*****************************************************************************/
/*
/*	tbecc_get_limbsize()    returns the length of the integer held in the
/*                          array.
/*
/*	RETURN VALUE:		length of op as a multi-precision integer
/*
/*****************************************************************************/
uint tbecc_get_limbsize(uint sz, uint *op)
{
	int i;
	i = sz - 1;
	while(i>-1){	if(op[i])	break;	--i;}
	return  ++i;	
}
/*****************************************************************************/
/*
/*	tbecc_load()        this function loads a byte array into a multi-precision
/*                      array.
/*
/*	RETURN VALUE:       the length in non-zero value of the array
/*
/*****************************************************************************/
uint	tbecc_load(uint *rop, uchar *val, uint length)
{
	uint i, size;
	/*	compute the required length		*/
	size = length/LIMB_SIZE;
	if(length%LIMB_SIZE)	size++;
	if(size == 0)	return 0;
	for(i=0;i<size-1;i++){
		rop[i] = val[length - 4*i - 4]<<24 | val[length - 4*i - 3]<<16 | val[length - 4*i - 2]<<8 | val[length-4*i-1];
	}
	switch(length%4)
	{
	case 0:
		rop[i] = val[length - 4*i - 4]<<24 | val[length - 4*i - 3]<<16 | val[length - 4*i - 2]<<8 | val[length-4*i-1];
		break;
	case 1:
		rop[i] = val[length-4*i-1];
		break;
	case 2:
		rop[i] = val[length - 4*i - 2]<<8 | val[length-4*i-1];
		break;
	default:
		rop[i] = val[length - 4*i - 3]<<16 | val[length - 4*i - 2]<<8 | val[length-4*i-1];
		break;
	}
	return tbecc_get_limbsize(size, rop);
}
/*****************************************************************************/
/*
/*	tbecc_unload    this function unloads into a byte array on 4 byte boundary
/*
/*****************************************************************************/
void    tbecc_unload(uint sz, uchar *rop, uint *op)
{
	uint	i, front;
    front = sz*LIMB_SIZE;
	for(i=0;i<sz;i++){
		rop[front - LIMB_SIZE*i - 4] = (uchar)((op[i]&0xFF000000)>>24);
		rop[front - LIMB_SIZE*i - 3] = (uchar)((op[i]&0xFF0000)>>16);
		rop[front - LIMB_SIZE*i - 2] = (uchar)((op[i]&0xFF00)>>8);
		rop[front - LIMB_SIZE*i - 1] = (uchar)(op[i]&0xFF);
	}
}
/****************************************************************************/
/*
/*	tbecc_shift_left()  This shifts the value to the left by amt many bits, or
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