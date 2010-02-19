/*****************************************************************************/
/*
/*      tbecc_int.h
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
#ifndef _TBECC_INT_H
#define _TBECC_INT_H

#include "tinyBECC.h"

#define	ABS(x)			(((x)>0)?(x):(-1*(x)))
#define	MAX(h,i)		((h) > (i) ? (h) : (i))
#define	MIN(h,i)		((h) < (i) ? (h) : (i))
#define	SIGN(x)			(((x)>0)?(1):(-1))

int     tbecc_int_cmp(uint sz1, uint sz2, uint *op1, uint *op2);
uint    _tbecc_int_add(int sz,  uint *rop,  uint *op1,  uint *op2);
uint    _tbecc_int_add_n(uint sz1, uint sz2, uint *rop, uint *op1, uint *op2);
int     int_add(int sz1, int sz2, uint *rop, uint *op1, uint *op2);
int     _tbecc_int_sub(int sz,  uint *rop,  uint *op1,  uint *op2);
void    _int_mul( int sz1, int sz2, uint *rop, uint *op1,  uint *op2);
uint    tbecc_int_div_by_2(uint sz, uint *rop, uint *op);
#endif /* TBECC_INT_H */

