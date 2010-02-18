/*****************************************************************************/
/*
/*      tbecc_f2x.h			
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
#ifndef _TBECC_F2X_H
#define _TBECC_F2X_H

uint	tbecc_is_val_ui(uint sz, uint *op, uint ui);
uint	tbecc_get_bitlength(uint sz, uint *op);

void	tbecc_shift_left(uint amt, uint len, uint *dst, uint *src);
void	tbecc_f2x_add(uint sz, uint *rop, uint *op1, uint *op2);

#endif  /* _TBECC_F2X_H */