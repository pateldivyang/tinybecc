/*****************************************************************************/
/*
/*		tbecc_f2x_283.c
/*  
/*	  	This file is part of TinyBECC.
/*
/*    	TinyBECC is free software: you can redistribute it and/or modify
/*    	it under the terms of the GNU General Public License as published by
/*    	the Free Software Foundation, either version 3 of the License, or
/*   	(at your option) any later version.
/*
/*    	TinyBECC is distributed in the hope that it will be useful,
/*    	but WITHOUT ANY WARRANTY; without even the implied warranty of
/*    	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/*    	GNU General Public License for more details.
/*
/*    	You should have received a copy of the GNU General Public License
/*		along with TinyBECC.  If not, see <http://www.gnu.org/licenses/>.
/*
/*	  	$Author$
/*    	$Date$
/*	  	$Revision$
/*	  	$Id$
/*
/*****************************************************************************/
#include <memory.h>
#include "tinyBECC.h"
#include "tbecc_f2x.h"
#include "tbecc_f2x_283.h"

uint gPOLY283[SECT283_SIZE] =    { 0x000010A1, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000000	};
/*****************************************************************************/
/*
/*	tbecc_f2x_283_mod()	Performs modular reduction by the polynomial reduce
/*                      modulo f(x) = x^283 + x^12 + x^7 + x^5 + 1   
/*	
/*                      See [1], Algorithm 2.43, page 56
/*
/*	RESTRICTIONS:	deg(op(x)) < 565
/*					op IS DESTROYED
/*
/*****************************************************************************/
void    _tbecc_f2x_283_mod(uint *rop, uint *op)
{
	uint j, h1;
	for(j=17;j>8;j--){
		h1 = op[j];
		op[j-9]^=(h1<<5)^(h1<<10)^(h1<<12)^(h1<<17);
		op[j-8]^=(h1>>27)^(h1>>22)^(h1>>20)^(h1>>15);
	}
	h1 = op[8]>>27;
	op[0] ^= h1^(h1<<5)^(h1<<7)^(h1<<12);
	op[8] &=0x07FFFFFF;
	memcpy(rop, op, sizeof(uint)*SECT283_SIZE);
}
/*****************************************************************************/
/*
/*  tbecc_f2x_283_mul_mod() modular polynomial multiplication in F_2[x]/(f(x))
/*					rop(x) = op1(x)*op2(x) in F_2[x]/(f(x)), where both
/*                  op1(x) and op2(x) < f(x) = x^283 + x^12 + x^7 + x^5 + 1 
/*
/*					performs right-to-left comb method, see [1], Algorithm
/*					2.34, p 49
/*
/*****************************************************************************/
void    tbecc_f2x_283_mul_mod(uint *rop, uint *op1, uint *op2)
{
    uint    tmp[(3*SECT283_SIZE)+2], *top2;
    
    memset(tmp, 0, sizeof(uint)*((3*SECT283_SIZE)+2));
    top2 = tmp + 2*SECT283_SIZE;
    memcpy(top2, op2, sizeof(uint)*SECT283_SIZE);
    
    _tbecc_f2x_mul(SECT283_SIZE, tmp, op1, top2);
    _tbecc_f2x_283_mod(rop, tmp);
}
/*****************************************************************************/
/*
/*	tbecc_f2x_283_inv()	perform a field inversion (expensive) in F_2[x]/f(x),
/*                      where f(x) = x^283 + x^12 + x^7 + x^5 + 1   
/*
/*****************************************************************************/
void	tbecc_f2x_inv_283(uint *rop, uint *op)
{
	uint	t[6*(SECT283_SIZE+1)], *u, *v, *g1, *g2;

	if(tbecc_is_val_ui(SECT283_SIZE, op, 0)){
		memset(rop, 0, sizeof(uint)*SECT283_SIZE);		return;
	}
	
    memset(t, 0, sizeof(uint)*6*(SECT283_SIZE+1));
	u = t + 2*(SECT283_SIZE+1);		v = u + (SECT283_SIZE+1);
	g1 = v + (SECT283_SIZE+1);		g2 = g1 + (SECT283_SIZE+1);
	memcpy(u, op, sizeof(uint)*SECT283_SIZE);		
	memcpy(v, gPOLY283, sizeof(uint)*SECT283_SIZE);
	g1[0] = 1;

    _tbecc_f2x_inv(SECT283_SIZE, rop, u, v, g1, g2, t);
}
/*****************************************************************************/
/*
/*	[1] Guide to Elliptic Curve Cryptography, Hankerson, D., Menezes, A., 
/*		Vanstone, S., Springer-Verlag, New York, 2004.
/*
/*  [2] ECOH, Source Code submission, ecoh.c, Brown, D., 2009.
/*      http://csrc.nist.gov/groups/ST/hash/sha-3/Round1/documents/ECOH.zip
/*
/******************************************************************************/