/*****************************************************************************
*
*      tbecc_f2x_283.h
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
#ifndef _TBECC_F2X_283_H
#define _TBECC_F2X_283_H

#define SECT283_SIZE        9

void    _tbecc_f2x_283_mod(uint *rop, uint *op);
void    tbecc_f2x_283_mul_mod(uint *rop, uint *op1, uint *op2);
void    tbecc_f2x_283_inv(uint *rop, uint *op);

#endif  /* _TBECC_F2X_283_H */