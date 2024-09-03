/*
*	File:		HID_Config_Utilities.h
*
*	Contains:   Definition of the interfaces to <HID_Config_Utilities.c>
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

#ifndef _HID_Config_Utilities_h_
#define _HID_Config_Utilities_h_

/*****************************************************/
#pragma mark - includes & imports

#include <stdio.h>

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

enum
{
    kPercentMove = 10 // precent of overall range a element must move to register
};

struct hu_SaveRec_t
{
    long actionCookie;
    // device
	// need to add serial number when I have a test case
    long vendorID;
    long productID;
    long locID;
    long usage;
    long usagePage;
    // elements
    long usagePageE;
    long usageE;
    void* cookie;
};
typedef struct hu_SaveRec_t hu_SaveRec_t;

/*****************************************************/
#pragma mark - exported globals

/*****************************************************/
#pragma mark - exported function prototypes

// polls single device's elements for a change greater than kPercentMove.  
// Times out after given time
// returns TRUE and pointer to element if found
// returns FALSE and NULL for pointer to element if not found
extern Boolean HIDConfigureSingleDeviceAction( hu_device_t * inDevice, hu_element_t **outElement, float inTimeout );

// polls all devices and elements for a change greater than kPercentMove. Times out after given time
// returns TRUE and pointer to device and element if found
// returns FALSE and NULL for both parameters if not found
extern Boolean HIDConfigureAction( hu_device_t **outDevice, hu_element_t **outElement, float inTimeout );

// -- These are routines to use if the applcation wants HID Utilities to do the file handling --
// Notes: the FILE* is a MachO posix FILE and will not work with the MW MSL FILE* type.

// take input records, save required info
// assume file is open and at correct position.
extern void HIDSaveElementConfig( FILE* inFILE, hu_device_t * inDevice, hu_element_t * inElement, long actionCookie );

// take file, read one record( assume file position is correct and file is open )
// search for matching device
// return inDevice, inElement and cookie for action
extern long HIDRestoreElementConfig( FILE* inFILE, hu_device_t **outDevice, hu_element_t **outElement );

// -- These routines use the CFPreferences API's.

// Save the device & element values into the specified key in the specified applications preferences
extern Boolean HIDSaveElementPref( CFStringRef inKeyCFStringRef, CFStringRef inAppCFStringRef, hu_device_t * inDevice, hu_element_t * inElement );

// Find the specified preference in the specified application
// search for matching device and element
// return inDevice, inElement that matches

extern Boolean HIDRestoreElementPref( CFStringRef inKeyCFStringRef, CFStringRef inAppCFStringRef, hu_device_t **outDevice, hu_element_t **outElement );

// -- These are routines to use if the client wants to use their own file handling --

// Set up a config record for saving
// takes an input records, returns record user can save as they want
// Notes: the save rec must be pre-allocated by the calling app and will be filled out
extern void HIDSetElementConfig( hu_SaveRec_t* inConfigRec, hu_device_t * inDevice, hu_element_t * inElement, long actionCookie );

// Get matching element from config record
// takes a pre-allocated and filled out config record
// search for matching device
// return outDevice, outElement and cookie for action
extern long HIDGetElementConfig( hu_SaveRec_t* inConfigRec, hu_device_t **outDevice, hu_element_t **outElement );

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
#endif /* _HID_Config_Utilities_h_ */

