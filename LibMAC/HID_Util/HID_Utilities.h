/*
*	File:		HID_Utilities.h
*
*	Contains:	External interface for HID Utilities
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

#ifndef _HID_Utilities_h_
#define _HID_Utilities_h_

/*****************************************************/
#pragma mark - includes & imports
#include <Carbon/Carbon.h>

#include <IOKit/IOTypes.h>
// 10.0.x
//#include <IOKit/IOUSBHIDParser.h>
// 10.1.x
#include <IOKit/hid/IOHIDUsageTables.h>

#include <IOKit/HID/IOHIDLib.h>

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
	kDefaultUserMin = 0, 					// default user min and max used for scaling
	kDefaultUserMax = 255,
};

typedef enum HIDElementTypeMask
{
	kHIDElementTypeInput			= 1 << 1,
	kHIDElementTypeOutput			= 1 << 2,
	kHIDElementTypeFeature      	= 1 << 3,
	kHIDElementTypeCollection    	= 1 << 4,
	kHIDElementTypeIO				= kHIDElementTypeInput | kHIDElementTypeOutput | kHIDElementTypeFeature,
	kHIDElementTypeAll				= kHIDElementTypeIO | kHIDElementTypeCollection
}HIDElementTypeMask;

struct hu_element_t
{
	IOHIDElementType type;					// the type defined by IOHIDElementType in IOHIDKeys.h
	long usage;								// usage within above page from IOUSBHIDParser.h which defines specific usage
	long usagePage;							// usage page from IOUSBHIDParser.h which defines general usage
	IOHIDElementCookie cookie;				// unique value( within device of specific vendorID and productID ) which identifies element, will NOT change
	long min;								// reported min value possible
	long max;								// reported max value possible
	long scaledMin;							// reported scaled min value possible
	long scaledMax;							// reported scaled max value possible
	long size;								// size in bits of data return from element
	Boolean relative;						// are reports relative to last report( deltas )
	Boolean wrapping;						// does element wrap around( one value higher than max is min )
	Boolean nonLinear;						// are the values reported non-linear relative to element movement
	Boolean preferredState;					// does element have a preferred state( such as a button )
	Boolean nullState;						// does element have null state
	long units;								// units value is reported in( not used very often )
	long unitExp;							// exponent for units( also not used very often )
	char name[256];							// name of element ( c string )

	// runtime variables
	long initialCenter; 					// center value at start up
	unsigned char hasCenter; 				// whether or not to use center for calibration
	long minReport; 						// min returned value
	long maxReport; 						// max returned value( calibrate call )
	long userMin; 							// user set value to scale to( scale call )
	long userMax;

	struct hu_element_t * pPrevious;			// previous element( NULL at list head )
	struct hu_element_t * pChild;				// next child( only of collections )
	struct hu_element_t * pSibling;			// next sibling( for elements and collections )

	long depth;
};
typedef struct hu_element_t hu_element_t;

struct hu_device_t
{
	struct IOCFPlugInInterface ** interface;// interface to device, NULL = no interface
	IOHIDQueueInterface  **queue;          // device queue, NULL = no queue
	CFRunLoopSourceRef	runLoopSource;       // device run loop source, NULL == no source
	CFRunLoopSourceRef	queueRunLoopSource;     // device queue run loop source, NULL == no source
	IOHIDOutputTransactionInterface  **transaction; // output transaction interface, NULL == no transaction
	io_object_t notification;            // notifications
	char transport[256];					// device transport( c string )
	long vendorID;                 // id for device vendor, unique across all devices
	long productID;                 // id for particular product, unique across all of a vendors devices
	long version;                  // version of product
	char manufacturer[256];					// name of manufacturer
	char product[256];						// name of product
	char serial[256];						// serial number of specific product, can be assumed unique across specific product or specific vendor( not used often )
	long locID;                   // long representing location in USB( or other I/O ) chain which device is pluged into, can identify specific device on machine
	long usage;                   // usage page from IOUSBHID Parser.h which defines general usage
	long usagePage;                 // usage within above page from IOUSBHID Parser.h which defines specific usage
	long totalElements;               // number of total elements ( should be total of all elements on device including collections ) ( calculated, not reported by device )
	long features;                 // number of elements of type kIOHIDElementTypeFeature
	long inputs;                  // number of elements of type kIOHIDElementTypeInput_Misc or kIOHIDElementTypeInput_Button or kIOHIDElementTypeInput_Axis or kIOHIDElementTypeInput_ScanCodes
	long outputs;                  // number of elements of type kIOHIDElementTypeOutput
	long collections;                // number of elements of type kIOHIDElementTypeCollection
	long axis;                   // number of axis( calculated, not reported by device )
	long buttons;                  // number of buttons( calculated, not reported by device )
	long hats;                   // number of hat switches( calculated, not reported by device )
	long sliders;                  // number of sliders( calculated, not reported by device )
	long dials;                   // number of dials( calculated, not reported by device )
	long wheels;                  // number of wheels( calculated, not reported by device )
	hu_element_t * pListElements;           // head of linked list of elements
	struct hu_device_t * pNext;            // next device
};
typedef struct hu_device_t hu_device_t;


/*****************************************************/
#pragma mark - exported globals

/*****************************************************/
#pragma mark - exported function prototypes

// Create and open an interface to device, required prior to extracting values or building queues
// Notes: appliction now owns the device and must close and release it prior to exiting
extern IOReturn HIDCreateOpenDeviceInterface( io_object_t inHIDDevice, hu_device_t * inDevice );

// builds list of device with elements( allocates memory and captures devices )
// list is allcoated internally within HID Utilites and can be accessed via accessor functions
// structures within list are considered flat and user accessable, butnot user modifiable
// can be called again to rebuild list to account for new devices( will do the right thing in case of disposing existing list )
extern Boolean HIDBuildDeviceList( UInt32 inUsagePage, UInt32 inUsage );

// release list built by above function
// MUST be called prior to application exit to properly release devices
// if not called( or app crashes ) devices can be recovered by pluging into different location in USB chain
extern void HIDReleaseDeviceList( void );

// does a device list exist
extern Boolean HIDHaveDeviceList( void );

// how many HID devices have been found
// returns 0 if no device list exist
extern int HIDCountDevices( void );

// how many elements does a specific device have
// returns 0 if device is invalid or NULL
// uses mask of HIDElementTypeMask to restrict element found
// use kHIDElementTypeIO to get non-collection elements
extern int HIDCountDeviceElements( hu_device_t * inDevice, HIDElementTypeMask inTypeMask );

// get the first device in the device list
// returns NULL if no list exists
extern hu_device_t * HIDGetFirstDevice( void );

// get next device in list given current device as parameter
// returns NULL if end of list
extern hu_device_t * HIDGetNextDevice( hu_device_t * inDevice );

// get the first element of device passed in as parameter
// returns NULL if no list exists or device does not exists or is NULL
// uses mask of HIDElementTypeMask to restrict element found
// use kHIDElementTypeIO to get previous HIDGetFirstDeviceElement functionality
extern hu_element_t * HIDGetFirstDeviceElement( const hu_device_t * inDevice, HIDElementTypeMask inTypeMask );

// get next element of given device in list given current element as parameter
// will walk down each collection then to next element or collection( depthwise traverse )
// returns NULL if end of list
// uses mask of HIDElementTypeMask to restrict element found
// use kHIDElementTypeIO to get previous HIDGetNextDeviceElement functionality
extern hu_element_t * HIDGetNextDeviceElement( hu_element_t * inElement, HIDElementTypeMask inTypeMask );

// get previous element of given device in list given current element as parameter
// this wlaks directly up the tree to the top element and does not search at each level
// returns NULL if beginning of list
// uses mask of HIDElementTypeMask to restrict element found
// use kHIDElementTypeIO to get non-collection elements
extern hu_element_t * HIDGetPreviousDeviceElement( hu_element_t * inElement, HIDElementTypeMask inTypeMask );

// returns calibrated value given raw value passed in
// calibrated value is equal to min and max values returned by HIDGetElementValue since device list built scaled to element reported min and max values
extern SInt32 HIDCalibrateValue( SInt32 inValue, hu_element_t * inElement );

// returns scaled value given raw value passed in
// scaled value is equal to current value assumed to be in the range of element reported min and max values scaled to user min and max scaled values
extern SInt32 HIDScaleValue( SInt32 inValue, hu_element_t * inElement );

/*****************************************************/
// convert an element type to a mask
extern HIDElementTypeMask HIDConvertElementTypeToMask( IOHIDElementType inIOHIDElementType );

// find this device
extern Boolean HIDFindDevice( const hu_device_t * inSearchDevice, hu_device_t **outFoundDevice );

// find the device and element for this action
// Device: serial, vendorID, productID, location, inUsagePage, usage
// Element: cookie, inUsagePage, usage,
extern Boolean HIDFindActionDeviceAndElement( const hu_device_t * inSearchDevice, const hu_element_t * inSearchElement, hu_device_t **outFoundDevice, hu_element_t **outFoundElement );

// find the device and element for this action
// Device: serial, vendorID, productID, location, inUsagePage, usage
// Element: cookie, inUsagePage, usage,

extern Boolean HIDFindSubElement( const hu_element_t * inStartElement, const hu_element_t * inSearchElement, hu_element_t **outFoundElement );

// print out all of an elements information
extern int HIDPrintElement( const hu_element_t * inElement );

// return TRUE if this is a valid device pointer
extern Boolean HIDIsValidDevice( const hu_device_t * inSearchDevice );

// return TRUE if this is a valid element pointer for this device
extern Boolean HIDIsValidElement( const hu_device_t * inSearchDevice, const hu_element_t * inSearchElement );

// Sets the client hot plug callback routine
typedef OSStatus ( *HotPlugCallbackProcPtr )( io_iterator_t inIODeviceIterator );
extern OSStatus HIDSetHotPlugCallback( HotPlugCallbackProcPtr inHotPlugCallbackProcPtr );
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
#endif // _HID_Utilities_h_
