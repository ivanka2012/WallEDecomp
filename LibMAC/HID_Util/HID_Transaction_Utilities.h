/*
*	File:		HID_Transaction_Utilities.h
*
*	Contains:	Implementation of the HID queue functions for the HID utilites.
*
*	Copyright:	Copyright © 2001-2008 Apple Inc., All Rights Reserved
*
*	Disclaimer:	IMPORTANT: This Apple software is supplied to you by Apple Inc., Inc.
*				( "Apple" ) in consideration of your agreement to the following terms, and your
*				use, installation, modification or redistribution of this Apple software
*				constitutes acceptance of these terms. If you do not agree with these terms,
*				please do not use, install, modify or redistribute this Apple software.
*
*				In consideration of your agreement to abide by the following terms, and subject
*				to these terms, Apple grants you a personal, non-exclusive license, under Apple’s
*				copyrights in this original Apple software ( the "Apple Software" ), to use,
*				reproduce, modify and redistribute the Apple Software, with or without
*				modifications, in source and/or binary forms; provided that if you redistribute
*				the Apple Software in its entirety and without modifications, you must retain
*				this notice and the following text and disclaimers in all such redistributions of
*				the Apple Software. Neither the name, trademarks, service marks or logos of
*				Apple Inc., Inc. may be used to endorse or promote products derived from the
*				Apple Software without specific prior written permission from Apple. Except as
*				expressly stated in this notice, no other rights or licenses, express or implied,
*				are granted by Apple herein, including but not limited to any patent rights that
*				may be infringed by your derivative works or by other works in which the Apple
*				Software may be incorporated.
*
*				The Apple Software is provided by Apple on an "AS IS" basis. APPLE MAKES NO
*				WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
*				WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
*				PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
*				COMBINATION WITH YOUR PRODUCTS.
*
*				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
*				CONSEQUENTIAL DAMAGES ( INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
*				GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION )
*				ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION
*				OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
*				( INCLUDING NEGLIGENCE ), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN
*				ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _HID_Transaction_Utilities_h_
#define _HID_Transaction_Utilities_h_

/*****************************************************/
#pragma mark - includes & imports
#include "HID_Utilities.h"

/*****************************************************/
#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_IMPORT
#pragma import on
#endif

#if PRAGMA_STRUCT_ALIGN
#pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
#pragma pack( push, 2 )
#elif PRAGMA_STRUCT_PACK
#pragma pack( 2 )
#endif

/*****************************************************/
#pragma mark - typedef's, struct's, enums, defines, etc.

/*****************************************************/
#pragma mark - exported globals

/*****************************************************/
#pragma mark - exported function prototypes

// Create and open an transaction interface to device, required prior to extracting values or building Transactions
extern unsigned long HIDTransactionAddElement( const hu_device_t * inDevice, hu_element_t * inElement );

// removes an element from a Transaction
extern unsigned long HIDTransactionRemoveElement( hu_device_t * inDevice, hu_element_t * inElement );

// return TRUE if this transaction contains this element
extern Boolean HIDTransactionHasElement( hu_device_t * inDevice, hu_element_t * inElement );

/* This changes the default value of an element, when the values of the */
/* elements are cleared, on clear or commit, they are reset to the */
/* default value */
/* This call can be made on elements that are not in the transaction, but */
/* has undefined behavior if made on elements not in the transaction */
/* which are later added to the transaction. */
/* In other words, an element should be added before its default is */
/* set, for well defined behavior. */
extern unsigned long HIDTransactionSetElementDefault( hu_device_t * inDevice, hu_element_t * inElement, IOHIDEventStruct* inValueEvent );

/* Get the current setting of an element's default value */
extern unsigned long HIDTransactionGetElementDefault( hu_device_t * inDevice, hu_element_t * inElement, IOHIDEventStruct* inValueEvent );

/* Add a change to the transaction, by setting an element value */
/* The change is not actually made until it is commited */
/* The element must be part of the transaction or this call will fail */
extern unsigned long HIDTransactionSetElementValue( hu_device_t * inDevice, hu_element_t * inElement, IOHIDEventStruct* inValueEvent );

/* Get the current setting of an element value */
extern unsigned long HIDTransactionGetElementValue( hu_device_t * inDevice, hu_element_t * inElement, IOHIDEventStruct* inValueEvent );

/* Commit the transaction, or clear all the changes and start over */
extern unsigned long HIDTransactionCommit( hu_device_t * inDevice );

/* Clear all the changes and start over */
extern unsigned long HIDTransactionClear( hu_device_t * inDevice );

/*****************************************************/
#if PRAGMA_STRUCT_ALIGN
#pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
#pragma pack( pop )
#elif PRAGMA_STRUCT_PACK
#pragma pack( )
#endif

#ifdef PRAGMA_IMPORT_OFF
#pragma import off
#elif PRAGMA_IMPORT
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif
/*****************************************************/
#endif // _HID_Transaction_Utilities_h_

