/*****************************************************************************/
/*
/*      tinyBECC.h
/*  
/*		This file is part of TinyBECC.
/*
/*		TinyBECC is free software: you can redistribute it and/or modify
/*		it under the terms of the GNU General Public License as published by
/*		the Free Software Foundation, either version 3 of the License, or
/*		(at your option) any later version.
/*
/*		TinyBECC is distributed in the hope that it will be useful,
/*		but WITHOUT ANY WARRANTY; without even the implied warranty of
/*		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/*		GNU General Public License for more details.
/*
/*		You should have received a copy of the GNU General Public License
/*		along with TinyBECC.  If not, see <http://www.gnu.org/licenses/>.
/*
		$Author$
		$Date$
		$Revision$
		$Id$
/*
/*****************************************************************************/
#ifndef _TINY_BECC_H
#define _TINY_BECC_H

#define uchar					unsigned char
#define uint					unsigned int
#define sint					signed int

#define LIMB_BIT_SIZE			32
#define LIMB_SIZE				(LIMB_BIT_SIZE/8)

#define	SUCCESS					0x00
#define BAD_CERTIFICATE			0x01
#define ERROR_VALUE				0xFFFFFFFF

#define FALSE					0
#define TRUE					1

#endif /*	_TINY_BECC_H  */