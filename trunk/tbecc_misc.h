/*****************************************************************************
*
*      tbecc_misc.h
*
*      This file is part of TinyBECC.
*
*      TinyBECC is free software: you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation, either version 3 of the License, or
*      (at your option) any later version.
*
*      TinyBECC is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*
*      You should have received a copy of the GNU General Public License
*      along with TinyBECC.  If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************/
#ifndef _TBECC_MISC_H
#define _TBECC_MISC_H

#include "tinyBECC.h"

uint	tbecc_is_val_ui(uint sz, uint *op, uint ui);
uint	tbecc_get_bitlength(uint sz, uint *op);
uint    tbecc_get_limbsize(uint sz, uint *op);
uint	tbecc_load(uint *rop, uchar *val, uint length);
void    tbecc_unload(uint sz, uchar *rop, uint *op);
void	tbecc_shift_left(uint amt, uint sz, uint *rop, uint *op);
#endif /* TBECC_INT_H */
