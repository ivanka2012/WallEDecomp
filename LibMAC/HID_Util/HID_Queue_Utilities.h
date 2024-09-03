/*
*	File:		HID_Queue_Utilities.h
*
*	Contains:	Definition of the HID queue functions for the HID utilites.
*
*	Copyright:	Copyright � 2001-2008 Apple Inc., All Rights Reserved
*
*	Disclaimer:	IMPORTANT: This Apple software is supplied to you by Apple Inc., Inc.
*				( "Apple" ) in consideration of your agreement to the following terms, and your
*				use, installation, modification or redistribution of this Apple software
*				constitutes acceptance of these terms. If you do not agree with these terms,
*				please do not use, install, modify or redistribute this Apple software.
*
*				In consideration of your agreement to abide by the following terms, and subject
*				to these terms, Apple grants you a personal, non-exclusive license, under Apple�s
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

#ifndef _HID_Queue_Utilities_h_
#define _HID_Queue_Utilities_h_

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

enum {
    kDeviceQueueSize = 50	// this is wired kernel memory so should be set to as small as possible
							// but should account for the maximum possible events in the queue
							// USB updates will likely occur at 100 Hz so one must account for this rate of
							// if states change quickly ( updates are only posted on state changes )
};

/*****************************************************/
#pragma mark - exported globals

/*****************************************************/
#pragma mark - exported function prototypes

// queues specific element, performing any device queue set up required
extern unsigned long HIDQueueElement( hu_device_t * inDevice, hu_element_t * inElement );

// adds all elements to queue, performing any device queue set up required
extern unsigned long HIDQueueDevice( hu_device_t * inDevice );

// removes element for queue, if last element in queue will release queue and device
extern unsigned long HIDDequeueElement( hu_device_t * inDevice, hu_element_t * inElement );

// completely removes all elements from queue and releases queue and device
extern unsigned long HIDDequeueDevice( hu_device_t * inDevice );

// releases all device queues for quit or rebuild( must be called )
extern unsigned long HIDReleaseAllDeviceQueues( void );

// releases interface to device, should be done prior to exiting application( called from HIDReleaseDeviceList )
extern unsigned long HIDCloseReleaseInterface( hu_device_t * inDevice );

// returns TRUE if an event is avialable for the element and fills out *outHIDEvent structure, returns FALSE otherwise
// outHIDEvent is a poiner to a IOHIDEventStruct, using void here for compatibility, users can cast a required
extern unsigned char HIDGetEvent( hu_device_t * inDevice, void* outHIDEvent );

// returns current value for element, creating device interface as required, polling element
extern long HIDGetElementEvent( hu_device_t * inDevice, hu_element_t * inElement, IOHIDEventStruct* outIOHIDEvent );

// returns current value for element, creating device interface as required, polling element
extern long HIDGetElementValue( hu_device_t * inDevice, hu_element_t * inElement );

// Set an elements value
// NOTE: This should only be used when a single element report needs to be sent.
// If multiple elements reports are to be send then transactions should be used.
extern long HIDSetElementValue( hu_device_t * inDevice, hu_element_t * inElement, IOHIDEventStruct* outIOHIDEvent );

// Set a callback to be called when a queue goes from empty to non-empty
// Notes: This is a MachO function pointer. If you're using CFM you have to call MachOFunctionPointerForCFMFunctionPointer.
extern long HIDSetQueueCallback( hu_device_t * inDevice, IOHIDCallbackFunction callback, void* inCallbackTarget, void* inCallbackRefcon );

#if defined( AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER )
// Get a report from a device
extern long HIDGetReport( hu_device_t * inDevice, IOHIDReportType pReportType, UInt32 inReportID, void* inReportBuffer, unsigned long * inReportBufferSize );

// Send a report to a device
extern long HIDSetReport( hu_device_t * inDevice, IOHIDReportType pReportType, UInt32 inReportID, void* inReportBuffer, int inReportBufferSize );
#endif // defined( AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER )

#if defined( AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER )
// copy matching elements
long HIDCopyMatchingElements( hu_device_t * inDevice, CFDictionaryRef inMatchingDict, CFArrayRef* inElements )
// Set a callback to be called when a report comes in the interrupt pipe
// Notes: This is a MachO function pointer. If you're using CFM you have to call MachOFunctionPointerForCFMFunctionPointer.
long HIDSetInterruptReportHandlerCallback( hu_device_t * inDevice, void* inReportBuffer, int inReportBufferSize, IOHIDCallbackFunction callback, void* inCallbackTarget, void* inCallbackRefcon );
#endif // defined( AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER )

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
#endif // _HID_Queue_Utilities_h_

