/*****************************************************************************/
/*
/*      tbecc_int.c
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
#include "tbecc_int.h"
#include <memory.h>
/*****************************************************************************/
/*
/*    tbecc_int_cmp       compares two multi-precision integers.
/*
/*    RETURN VALUES:      0   if op1 = op2
/*                        1   if (op1>op2)
/*                       -1   if (op1<op2)
/*
/*****************************************************************************/
int     tbecc_int_cmp(uint sz1, uint sz2, uint *op1, uint *op2)
{
    if(sz1>sz2)            {    return 1;    }
    else if(sz1<sz2)    {    return -1;    }
    --sz1;
    for( ;sz1!=-1;--sz1){
        if(op1[sz1]!=op2[sz1]){
            if(op1[sz1]>op2[sz1])    return 1;
            else                    return -1;
        }
    }
    return 0;
}
/*****************************************************************************/
/*
/*    _tbecc_int_add        adds two arrays of equal size, returns carry bit
/*
/*    RETURN VALUE:        carry bit
/*
/*****************************************************************************/
uint    _tbecc_int_add(int sz,  uint *rop,  uint *op1,  uint *op2)
{
    uint    cy, x, y;
    int     i;
    if(sz==0)    return 0;
    cy = 0;     i = -sz;    op1 -= i;   op2 -= i;   rop  -= i;        

    do{
        y = op2[i];        x = op1[i];
        y+=cy;          cy = (y<cy);
        y = x + y;      cy = (y<x) + cy;
        rop[i] = y;
    }while(++i!=0);
    return cy;
}
/*****************************************************************************/
/*
/*    _tbecc_int_add_n      adds two integer arrays
/*    
/*    RETURN VALUES:        length of the non-zero part of the array
/*
/*****************************************************************************/
uint    _tbecc_int_add_n(uint sz1, uint sz2, uint *rop, uint *op1, uint *op2)
{
    uint    *pop1, y, cy, min, max;
    
    max = MAX(sz1, sz2);
    min = MIN(sz1, sz2);
    if(sz1 > sz2)    {    pop1 = op1;    }
    else                    {    pop1 = op2;    }
    cy = _tbecc_int_add(min, rop, op1, op2);
    while((min<max)){
        y = pop1[min];      y += cy;    cy = (y < cy);      rop[min] = y;
        ++min;
    }
    if(cy)    {    rop[min] = cy;    ++min;    }
    else    {    rop[min] = 0;    }
    return min;
}
/*****************************************************************************/
/*
/*  tbecc_int_add()   this function adds two (signed) integer arrays together
/*
/*  RETURN VALUE:       length of the non-zero part of the array
/*
/*****************************************************************************/
int    int_add(int sz1, int sz2, uint *rop, uint *op1, uint *op2)
{
    int        rlen;
    if(sz2 == 0)        {    
        memcpy(rop, op1, LIMB_SIZE*ABS(sz1));    
        rlen = sz1;
    }
    else if(sz1 == 0) {    
        memcpy(rop, op2, LIMB_SIZE*ABS(sz2));
        rlen = sz2;
    }
    else if ((sz1>0)&& (sz2>0)){
        rlen = MAX(sz1, sz2);
        rop[rlen] = _tbecc_int_add(rlen, rop, op1, op2);
        rlen = tbecc_get_limbsize(rlen+1, rop);
    }
    else if ((sz1<0) && (sz2 < 0)){
        rlen = MAX(ABS(sz1), ABS(sz2));
        rop[rlen] = _tbecc_int_add(rlen, rop, op1, op2);
        rlen = -(int)(tbecc_get_limbsize(rlen + 1, rop));
    }
    else if ((sz1>0) && (sz2 < 0)){
        if(tbecc_int_cmp(sz1, -sz2, op1, op2)>-1){
            _tbecc_int_sub(sz1, rop, op1, op2);
            rlen = tbecc_get_limbsize(sz1, rop);
        }
        else{
            _tbecc_int_sub(-sz2, rop, op2, op1);
            rlen = -(int)tbecc_get_limbsize(-sz2, rop);
        }
    }
    else if ((sz1<0) && (sz2 > 0)){
        if(tbecc_int_cmp(-sz1, sz2, op1, op2)>-1){
            _tbecc_int_sub(-sz2, rop, op1, op2);
            rlen = -(int)(tbecc_get_limbsize(-sz1, rop));
        }
        else{
            _tbecc_int_sub(sz2, rop, op2, op1);
            rlen = tbecc_get_limbsize(sz2, rop);
        }
    }
    return rlen;
}
/*****************************************************************************/
/*
/*    _tbecc_int_sub()  this function subtracts one array from another array
/*                      of equal sizes storing the result in the result array
/*
/*    RETURN VALUE:     carry bit
/*
/*****************************************************************************/
int     _tbecc_int_sub(int sz,  uint *rop,  uint *op1,  uint *op2)
{
     uint   cy, x, y;
     int    i;

    if(sz == 0)    {    memset(rop, 0, LIMB_SIZE*sz);    return 0;    }
    i = 0;    cy = 0;    i = -sz;    op1-=i;    op2-=i;    rop-=i;
    do{
        x = op1[i];     y = op2[i];     y += cy;    
        cy = (y < cy);  y = x - y;      cy += (y > x);            
        rop[i] = y;                
    }while(++i!=0);
    return cy;
}
/*****************************************************************************/
/*
/*    _mul                this is macro code for multiply.  It is strongly
/*                        recommended that this be done natively on the 
/*                        processor using assembly - see the x86 assembly 
/*                        example.
/*
/*****************************************************************************/
unsigned __int64  x;
#define _mul(LOW, HIGH, OP1, OP2) {\
    x = (unsigned __int64)OP1*(unsigned __int64)OP2;\
    HIGH = (uint)(x>>32);\
    LOW = (uint)(x&0xFFFFFFFF);\
}
/*
#define    _mul(z1, z2, a, b) {\
    __asm    push           eax \
    __asm    push           edx    \
    __asm    mov            eax, a \
    __asm    mov            edx, b \
    __asm    mul            edx    \
    __asm    mov            z1, eax\
    __asm    mov            z2, edx\
    __asm    pop            edx    \
    __asm    pop            eax    \
}
/*****************************************************************************/
/*
/*    tbecc_int_mul         multiplication of arrays of uintegers.
/*                          rop = op1*op2
/*                          rop!=op1 or op2
/*                          sz1, sz2 > 0
/*
/*****************************************************************************/
void    _tbecc_int_mul( int sz1, int sz2, uint *rop, uint *op1,  uint *op2)
{
    uint    z1, z2, cr, o1, o2;
    int     i, j, l;

    memset(rop, 0, LIMB_SIZE*(sz1 + sz2));
    i = -sz1;    j = -sz2;    op1 -=i;    op2 -=j;    rop -=(i+j);    
    do{
        cr = 0;
        o1 = op1[i];
        j = -sz2;
        do{
            o2 = op2[j];
            _mul(z1, z2, o1, o2);
            rop[i+j] +=z1;              cr = (rop[i+j]<z1);
            z2+=cr;                     cr = (z2<cr);
            rop[i+j+1] += z2;           cr += (rop[i+j+1]<z2);
            l = 2;
            while(cr){
                rop[i+j+l]+=cr;         cr = (rop[i+j+l++]<cr);
            }
        }while(++j!=0);
    }while(++i!=0);
}
/*****************************************************************************/
/*
/*	tbecc_int_div_by_2()    this function divides an integer by 2
/*
/*	RETURN VALUES:          the length of the non-zero value in limbs
/*
/*****************************************************************************/
uint    tbecc_int_div_by_2(uint sz, uint *rop, uint *op)
{
	int		i, size;
	uint	t, s;

	size = sz;	    s = 0;	    i=size-1;

	for(;i>-1;--i){
		t = op[i]&0x01;		rop[i] = op[i]>>1;		rop[i]|=s;
		if(t)	{	s = 0x80000000;	}
		else	{	s = 0x00000000;	}
	}
	
    if(!rop[size-1]){	size = MAX(size-1, 0);	}
	return size;
}

/*****************************************************************************/
/*
/*	tbecc_int_mod_p	        this function implements the barret reduction for
/*							for p, the order of the subgroup as specified in 
/*                          Algorithm 2.14 in [1]
/*
/*	RESTRICTIONS:			op is allocated to size 2*sz and is
/*							0 filled containing a value of lesser length, and
/*							0 <= op < p^2
/*                          mu = \floor(b^2k/p),
/*                          qhat, q of length 2*(sz+1), and r of sz + 2.
/*			
/*							rop is of length sz
/*
/*	RETURN VALUES           the length of the non-zero part of the result
/*
/*****************************************************************************/
uint	tbecc_int_mod_p(uint sz, uint *rop, uint *op, uint *p, uint *mu, uint *q, uint *qhat, uint *r)
{
	uint	rsize;
	int		sgn;
	
	_tbecc_int_mul(sz + 1, sz+1, q, op + sz -1, mu);
	_tbecc_int_mul(sz + 1, sz, qhat, q + sz + 1, p);
	
	sgn = _tbecc_int_sub(sz+1, r, op, qhat);

	if(sgn){
		q[sz + 1] = 1;
		memset(q, 0, LIMB_SIZE*(sz+1));
		r[sz + 1] = 0;
		_tbecc_int_sub(sz+2, r, q, r);
	}
	rsize = tbecc_get_limbsize(sz, r);
	while(tbecc_int_cmp(sz, rsize, p, r)<0){
		_tbecc_int_sub(sz, r, r, p);
		rsize = tbecc_get_limbsize(rsize, r);
	}
	memcpy(rop, r, LIMB_SIZE*sz);
	return tbecc_get_limbsize(sz, rop);
}
/*****************************************************************************/
/*
/*  [1] Guide to Elliptic Curve Cryptography, Hankerson, D., Menezes, A., 
/*        Vanstone, S., Springer-Verlag, New York, 2004.
/*
/*****************************************************************************/