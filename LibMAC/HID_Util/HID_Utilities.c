/*
*	File:		HID_Utilities.c of HID Utilities
*
*	Contains:	Implementation of HID Utilities
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

/*****************************************************/
#pragma mark - Compiling directives to enable/disable code
/*****************************************************/

#define USE_HOTPLUGGING 	1 //TRUE	// set TRUE to enable hot plugging!
#define USE_NOTIFICATIONS 	1// TRUE	// set TRUE to use notifications instead of device callbacks for hot unplugging!
#define LOG_DEVICES			0 //FALSE	// for debugging; Logs new devices to stdout
#define LOG_ELEMENTS		0 //FALSE	// for debugging; Logs new elements to stdout
#define LOG_SCORING			0 //FALSE	// for debugging; Logs HIDFindDevice & HIDFindActionDeviceAndElement scoring to stdout
#define LOG_SEARCHING		0 //FALSE	// for debugging; Logs HIDFindSubElement searching info to stdout

/*****************************************************/
#pragma mark - includes & imports
/*****************************************************/

#include <IOKit/IOCFPlugIn.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/IOMessage.h>
#include <IOKit/hid/IOHIDUsageTables.h>
#include <Memory_Z.h>

#include "HID_Utilities_Internal.h"
#include "HID_Utilities_External.h"

#if 0   // NOTE: These are now in <IOKit/hid/IOHIDUsageTables.h>
#include "PID.h"
#include "IOHIDPowerUsage.h"
#endif

/*****************************************************/
#pragma mark - typedef's, struct's, enums, defines, etc.
/*****************************************************/

/*****************************************************/
#pragma mark - local ( static ) function prototypes
/*****************************************************/
static char hu_MapChar( char c );
static void hu_CleanString( char* inCStr );
static void hu_GetElementInfo( CFTypeRef inElementCFDictRef, hu_element_t * inElement );
static void hu_AddElement( CFTypeRef inElementCFDictRef, hu_element_t **inCurrentElement );
static void hu_GetElementsCFArrayHandler( const void* value, void* parameter );
static void hu_GetElements( CFTypeRef inElementCFDictRef, hu_element_t **outCurrentElement );
static void hu_GetCollectionElements( CFDictionaryRef deviceProperties, hu_element_t **outCurrentCollection );
static void hu_TopLevelElementHandler( const void* value, void* parameter );
static void hu_GetDeviceInfo( io_object_t inHIDDevice, CFDictionaryRef inDeviceCFDictionaryRef, hu_device_t * inDevice );
static hu_device_t **hu_AddDevice( hu_device_t **inDeviceListHead, hu_device_t * inNewDevice );
static hu_device_t * hu_MoveDevice( hu_device_t **inDeviceListHead, hu_device_t * inNewDevice, hu_device_t **inOldListDeviceHead );
static hu_device_t * hu_BuildDevice( io_object_t inHIDDevice );
static hu_device_t * hu_CreateSingleTypeDeviceList( io_iterator_t inHIDObjectIterator );
static hu_device_t * hu_CreateMultiTypeDeviceList( const UInt32 *inUsagePage, const UInt32 *inUsage, int inNumDeviceTypes );
static Boolean hu_FindDeviceInList( hu_device_t * inDeviceList, hu_device_t * inFindDevice );
static Boolean hu_CompareUpdateDeviceList( hu_device_t **inDeviceListHead, hu_device_t **inNewDeviceList );
static void hu_MergeDeviceList( hu_device_t **inNewDeviceList, hu_device_t **inDeviceList );

#if USE_NOTIFICATIONS
static void hu_DeviceNotification( void *inRefCon, io_service_t inService, natural_t inMessageType, void *inMessageArgument );
#else
static void hu_RemovalCallbackFunction( void* target, IOReturn inResult, void* inRefCon, void* inSender );
#endif USE_NOTIFICATIONS

static void hu_AddDevices( hu_device_t **inDeviceListHead, io_iterator_t inIODeviceIterator );

#if USE_HOTPLUGGING
static void hu_IOServiceMatchingNotification( void *inRefCon, io_iterator_t inIODeviceIterator );
#endif USE_HOTPLUGGING

static CFMutableDictionaryRef hu_SetUpMatchingDictionary( UInt32 inUsagePage, UInt32 inUsage );
static void hu_DisposeDeviceElements( hu_element_t * inElement );
static hu_device_t * hu_DisposeDevice( hu_device_t * inDevice );
static int hu_CountCurrentDevices( void );
static Boolean hu_MatchElementTypeMask( IOHIDElementType inIOHIDElementType, HIDElementTypeMask inTypeMask );
static hu_element_t * hu_GetDeviceElement( hu_element_t * inElement, HIDElementTypeMask inTypeMask );

/*****************************************************/
#pragma mark - exported globals
/*****************************************************/
#pragma mark - local ( static ) globals
/*****************************************************/

#if USE_HOTPLUGGING
static HotPlugCallbackProcPtr	gHotPlugCallbackProcPtr = NULL;
static IONotificationPortRef	gNotifyPort;
static CFRunLoopRef				gRunLoop;
#endif USE_HOTPLUGGING

// for element retrieval
static hu_device_t *				gCurrentDevice  = NULL;
static Boolean					gAddAsChild		= FALSE;
static int						gDepth			= FALSE;

static hu_device_t *				gDeviceList		= NULL;
static int						gNumDevices		= 0;

/*****************************************************/
#pragma mark - exported function implementations
/*****************************************************/

/*************************************************************************
*
* HIDCreateOpenDeviceInterface( inHIDDevice, inDevice )
*
* Purpose:  Create and open an interface to device
*
* Notes:	required prior to extracting values or building queues
*			appliction now owns the device and must close and release it prior to exiting
*
* Inputs:   inHIDDevice  - the HID ( service ) device
*			inDevice		- the device
*
* Returns:  IOReturn		- error code ( if any )
*/

IOReturn HIDCreateOpenDeviceInterface( UInt32 inHIDDevice, hu_device_t * inDevice )
{
	IOReturn				result				= kIOReturnSuccess;	// assume success( optimist! )
	HRESULT					plugInResult		= S_OK;				// assume success( optimist! )
	SInt32					score				= 0;
	IOCFPlugInInterface		**tPlugInInterface = NULL;

	if ( !inDevice->interface ) {
		result = IOCreatePlugInInterfaceForService( inHIDDevice, kIOHIDDeviceUserClientTypeID,
												   kIOCFPlugInInterfaceID, &tPlugInInterface, &score );
		if ( kIOReturnSuccess == result ) {
			// Call a method of the intermediate plug-in to create the device interface
			plugInResult = ( *tPlugInInterface )->QueryInterface( tPlugInInterface,
															   CFUUIDGetUUIDBytes( kIOHIDDeviceInterfaceID ), ( void* ) & ( inDevice->interface ) );
			if ( S_OK != plugInResult ) {
				HIDReportErrorNum( "\nHIDCreateOpenDeviceInterface: Couldn't query HID class device interface from plugInInterface", plugInResult );
			}
			IODestroyPlugInInterface( tPlugInInterface ); // replace( *tPlugInInterface )->Release( tPlugInInterface )
		} else {
			HIDReportErrorNum( "\nHIDCreateOpenDeviceInterface: Failed to create plugInInterface via IOCreatePlugInInterfaceForService.", result );
		}
	}
	if ( inDevice->interface ) {
		result = ( *( IOHIDDeviceInterface** )inDevice->interface )->open( inDevice->interface, 0 );
		if ( kIOReturnSuccess != result ) {
			HIDReportErrorNum( "\nHIDCreateOpenDeviceInterface: Failed to open inDevice->interface via open.", result );
		}
	}
	return result;
}

/*************************************************************************
*
* HIDBuildMultiDeviceList( inUsagePages, inUsages, inNumDeviceTypes )
*
* Purpose:  builds list of devices with elements
*
* Notes:	allocates memory and captures devices
*			list is allocated internally within HID Utilites and can be accessed via accessor functions
*			structures within list are considered flat and user accessable, but not user modifiable
*			can be called again to rebuild list to account for new devices
*			( will do the right thing in case of disposing existing list )
*
* Inputs:   inUsagePages		- inNumDeviceTypes sized array of matching usage pages
*			inUsages			- inNumDeviceTypes sized array of matching usages
*			inNumDeviceTypes - number of usage pages & usages
*
* Returns:  Boolean		- if successful
*/

Boolean HIDBuildMultiDeviceList( const UInt32 *inUsagePages, const UInt32 *inUsages, int inNumDeviceTypes )
{
	gDeviceList = hu_CreateMultiTypeDeviceList( inUsagePages, inUsages, inNumDeviceTypes );
	gNumDevices = hu_CountCurrentDevices( ); // set count

	return ( NULL != gDeviceList );
}

/*************************************************************************
*
* HIDBuildDeviceList( inUsagePage, inUsage )
*
* Purpose:  builds list of devices with elements
*
* Notes:	same as above but this uses a single inUsagePage and usage
*			allocates memory and captures devices
*			list is allocated internally within HID Utilites and can be accessed via accessor functions
*			structures within list are considered flat and user accessable, but not user modifiable
*			can be called again to rebuild list to account for new devices
*			( will do the right thing in case of disposing existing list )
*
* Inputs:   inUsagePage		- usage page
*			inUsage			- usages
*
* Returns:  Boolean		- if successful
*/

Boolean HIDBuildDeviceList( UInt32 inUsagePage, UInt32 inUsage )
{
	return HIDBuildMultiDeviceList( &inUsagePage, &inUsage, 1 ); // call HIDBuildMultiDeviceList with a single usage
}

/*************************************************************************
*
* HIDUpdateDeviceList( inUsagePages, inUsages, inNumDeviceTypes )
*
* Purpose:  updates the current device list for any new/removed devices
*
* Notes:	if this is called before HIDBuildDeviceList then it functions like HIDBuildMultiDeviceList
*			inUsagePage & inUsage are each a inNumDeviceTypes sized array of matching usage and usage pages
*
* Inputs:   inUsagePages		- inNumDeviceTypes sized array of matching usage pages
*			inUsages			- inNumDeviceTypes sized array of matching usages
*			inNumDeviceTypes - number of usage pages & usages
*
* Returns:  Boolean		- TRUE if the device config changed
*/

Boolean HIDUpdateDeviceList( const UInt32 *inUsagePages, const UInt32 *inUsages, int inNumDeviceTypes )
{
	Boolean updateResult = FALSE;
	hu_device_t * newDeviceList = hu_CreateMultiTypeDeviceList( inUsagePages, inUsages, inNumDeviceTypes ); // get current list
	if ( gDeviceList ) {	// if we have a list already
		updateResult = hu_CompareUpdateDeviceList( &gDeviceList, &newDeviceList ); // update main list
		while ( newDeviceList ) // dispose new list after compare and update of main list
			newDeviceList = hu_DisposeDevice( newDeviceList ); // dispose current device return next device
	} else {
		updateResult = TRUE;
		gDeviceList = newDeviceList;
	}
	gNumDevices = hu_CountCurrentDevices( ); // set count
	return updateResult;
}

/*************************************************************************
*
* HIDReleaseDeviceList( void )
*
* Purpose:  release list built by above functions
*
* Notes:	MUST be called prior to application exit to properly release devices
*			if not called( or app crashes ) devices can be recovered by pluging into different location in USB chain
*
* Inputs:   none
*
* Returns:  none
*/

void HIDReleaseDeviceList( void )
{
	while ( gDeviceList ) {
		gDeviceList = hu_DisposeDevice( gDeviceList ); // dispose current device return next device will set gDeviceList to NULL
	}
	gNumDevices = 0;
}

/*************************************************************************
*
* HIDHaveDeviceList( void )
*
* Purpose:  does a device list exist?
*
* Inputs:   none
*
* Returns:  Boolean		- TRUE if we have previously built a device list
*/

Boolean HIDHaveDeviceList( void )
{
	return ( NULL != gDeviceList );
}

/*************************************************************************
*
* HIDCountDevices( void )
*
* Purpose:  how many HID devices have been found?
*
* Notes:	returns 0 if no device list exists
*
* Inputs:   none
*
* Returns:  int  - number of HID devices
*/

int HIDCountDevices( void )
{
	gNumDevices = hu_CountCurrentDevices( );
	return gNumDevices;
}

/*************************************************************************
*
* HIDCountDeviceElements( inDevice, inTypeMask )
*
* Purpose:  how many elements of a specific type does this device have?
*
* Notes:	returns 0 if device is invlaid or NULL
*
* Inputs:   inDevice		- the device
*			inTypeMask   - type type of elements we're interested in
*
* Returns:  int  - number of elements of this type on this device
*/

int HIDCountDeviceElements( const hu_device_t * inDevice, HIDElementTypeMask inTypeMask )
{
	long count = 0;

	if ( HIDIsValidDevice( inDevice ) ) {
		if ( inTypeMask & kHIDElementTypeInput )
			count += inDevice->inputs;
		if ( inTypeMask & kHIDElementTypeOutput )
			count += inDevice->outputs;
		if ( inTypeMask & kHIDElementTypeFeature )
			count += inDevice->features;
		if ( inTypeMask & kHIDElementTypeCollection )
			count += inDevice->collections;
	}
	return count;
}

/*************************************************************************
*
* HIDGetFirstDevice( void )
*
* Purpose:  get the first device in the device list
*
* Notes:	returns NULL if no list exists
*
* Inputs:   none
*
* Returns:  hu_device_t  - the first device in our device list
*/

hu_device_t * HIDGetFirstDevice( void )
{
	return gDeviceList;
}

/*************************************************************************
*
* HIDGetNextDevice( inDevice )
*
* Purpose:  get the next device in the device list
*
* Notes:	returns NULL if end-of-list
*
* Inputs:   inDevice		- the current device
*
* Returns:  hu_device_t - the next device in our device list
*/

hu_device_t * HIDGetNextDevice( const hu_device_t * inDevice )
{
	hu_device_t * result = NULL;	// assume failure ( pessimist! )
	if ( HIDIsValidDevice( inDevice ) ) {
		result = inDevice->pNext;
	}
	return result;
}

/*************************************************************************
*
* HIDGetFirstDeviceElement( inDevice, inTypeMask )
*
* Purpose:  get the first element of this type on this device
*
* Notes:	returns NULL if no list exists or device does not exists or
*			is NULL or no elements of this type exist on this device
*
* Inputs:   inDevice		- the current device
*			inTypeMask   - the type of element we're interested in
*
* Returns:  hu_element_t  - the next element
*/

hu_element_t * HIDGetFirstDeviceElement( const hu_device_t * inDevice, HIDElementTypeMask inTypeMask )
{
	hu_element_t * result = NULL;
	if ( HIDIsValidDevice( inDevice ) ) {
		if ( hu_MatchElementTypeMask( inDevice->pListElements->type, inTypeMask ) ) {	// ensure first type matches
			result = inDevice->pListElements;
		} else {
			result = HIDGetNextDeviceElement( inDevice->pListElements, inTypeMask );
		}
	}
	return result;
}

/*************************************************************************
*
* HIDGetNextDeviceElement( inElement, inTypeMask )
*
* Purpose:  get the next element of this type on this device
*
* Notes:	returns NULL if no list exists or device does not exists or
*			is NULL or no elements of this type exist on this device
*
* Inputs:   inElement	- the current element
*			inTypeMask   - the type of element we're interested in
*
* Returns:  hu_element_t  - the next element
*/

hu_element_t * HIDGetNextDeviceElement( hu_element_t * inElement, HIDElementTypeMask inTypeMask )
{
	// should only have elements passed in( though someone could mix calls and pass us a collection )
	// collection means return the next child or sibling( in that order )
	// element means return the next sibling( as elements can't have children )
	if ( inElement ) {
		if ( inElement->pChild ) {
			if ( inElement->type != kIOHIDElementTypeCollection ) {
				HIDReportError( "Malformed element list: found child of element." );
			} else {
				return hu_GetDeviceElement( inElement->pChild, inTypeMask ); // return the child of this element
			}
		} else if ( inElement->pSibling ) {
			return hu_GetDeviceElement( inElement->pSibling, inTypeMask ); //return the sibling of this element
		} else {	// at end, back up correctly
			hu_element_t * previousElement = NULL;
			// malformed device ending in collection
			if ( kIOHIDElementTypeCollection == inElement->type ) {
				HIDReportError( "Malformed device: found collection at end of element chain." );
			}
			// walk back up tree to element prior to first collection ecountered and take next element
			while ( inElement->pPrevious ) {
				previousElement = inElement;
				inElement = inElement->pPrevious; // look at previous element
												  // if we have a collection and the previous element is the branch element( should have both a colection and next element attached to it )
												  // if we found a collection, which we are not at the sibling level that actually does have siblings
				if ( ( ( kIOHIDElementTypeCollection == inElement->type ) && ( previousElement != inElement->pSibling ) && inElement->pSibling ) ||
					// or if we are at the top
					( !inElement->pPrevious ) ) // at top of tree
					break;
			}
			if ( ( !inElement->pPrevious ) && ( ( !inElement->pSibling ) || ( previousElement == inElement->pSibling ) ) )
				return NULL; // got to top of list with only a collection as the first element
							 // now we must have been down the child route so go down the sibling route
			inElement = inElement->pSibling; // element of interest
			return hu_GetDeviceElement( inElement, inTypeMask ); // otherwise return this element
		}
	}
	return NULL;
}

/*************************************************************************
*
* HIDGetPreviousDeviceElement( inElement, inTypeMask )
*
* Purpose:  get the previous element of this type on this device
*
* Notes:	returns NULL if no list exists or device does not exists or
*			is NULL or no elements of this type exist on this device
*
* Inputs:   inElement	- the current element
*			inTypeMask   - the type of element we're interested in
*
* Returns:  hu_element_t  - the next element
*/

hu_element_t * HIDGetPreviousDeviceElement( const hu_element_t * inElement, HIDElementTypeMask inTypeMask )
{
	hu_element_t * previousElement = inElement->pPrevious;
	// walk back up tree to element prior
	while ( previousElement && !hu_MatchElementTypeMask( previousElement->type, inTypeMask ) ) {
		inElement = previousElement; // look at previous element
		previousElement = inElement->pPrevious;
	}
	return previousElement; // return this element
}

/*************************************************************************
*
* HIDCalibrateValue( inValue, inElement )
*
* Purpose:  returns calibrated value given raw value passed in
*
* Notes:	calibrated value is equal to min and max values returned by HIDGetElementValue
*			since device list built scaled to element reported min and max values
*
* Inputs:   inValue		- the value to be calibrated
*			inElement	- the element
*
* Returns:  SInt32		- the calibrated value
*/

SInt32 HIDCalibrateValue( SInt32 inValue, hu_element_t * inElement )
{
	SInt32 result = 0;	// assume bad element passed in ( pessimist! )
	if ( inElement ) {
		float reportRange, deviceRange = inElement->max - inElement->min;
		
		if ( !inElement->hasCenter ) {	// no center for this element type
			if ( inElement->maxReport == inElement->minReport ) {
				result = inValue; // no scaling
			} else {
				reportRange = inElement->maxReport - inElement->minReport;
				result = ( ( inValue - inElement->minReport ) * deviceRange / reportRange ) + inElement->min;
			}
		} else { // has center
			if ( ( long ) 0x80000000 == inElement->initialCenter ) {
				inElement->initialCenter = inValue;
			}
			if ( inValue < inElement->initialCenter ) {
				reportRange = inElement->initialCenter - inElement->minReport;
				if ( reportRange > 0.0f ) { // if we have a positve range
					result = ( ( inValue - inElement->minReport ) * deviceRange * 0.5f / reportRange ) + inElement->min;
				} else {
					result = inValue; // bad scaling	
				}
			} else if ( inValue > inElement->initialCenter ) {
				reportRange = inElement->maxReport - inElement->initialCenter;
				if ( reportRange > 0.0f ) { // if we have a positve range
					result = ( ( inValue - inElement->initialCenter ) * deviceRange * 0.5f / reportRange ) + inElement->min + deviceRange / 2.0;
				} else {
					result = inValue; // bad scaling
				}
			} else {	// at center so return center of range
				result = ( inElement->min + deviceRange / 2.0);
			}
		}
	}
	return result;
}

/*************************************************************************
*
* HIDScaleValue( inValue, inElement )
*
* Purpose:  returns input value scaled to user min and max values
*
* Notes:	scaled value is equal to min and max values returned by HIDGetElementValue
*			since device list built scaled to user set min and max values
*
* Inputs:   inValue		- the value to be scaled
*			inElement	- the element
*
* Returns:  SInt32		- the scaled value
*/

SInt32 HIDScaleValue( SInt32 inValue, const hu_element_t * inElement )
{
	float deviceRange = inElement->userMax - inElement->userMin;
	float reportRange = inElement->max - inElement->min;
	SInt32 result = inValue;

	if ( reportRange ) {
		result = ( ( inValue - inElement->min ) * deviceRange / reportRange ) + inElement->userMin;
	}
	return result;
}

/*************************************************************************
*
*  HIDConvertElementTypeToMask( inIOHIDElementType )
*
* Purpose:  convert an element type to a mask
*
* Inputs:   inIOHIDElementType   - the element type
*
* Returns:  HIDElementTypeMask  - the mask
*/

HIDElementTypeMask HIDConvertElementTypeToMask( IOHIDElementType inIOHIDElementType )
{
	HIDElementTypeMask result = kHIDElementTypeAll;

	switch( inIOHIDElementType ) {
		case kIOHIDElementTypeInput_Misc:
		case kIOHIDElementTypeInput_Button:
		case kIOHIDElementTypeInput_Axis:
		case kIOHIDElementTypeInput_ScanCodes:
			result = kHIDElementTypeInput;
			break;
		case kIOHIDElementTypeOutput:
			result = kHIDElementTypeOutput;
			break;
		case kIOHIDElementTypeFeature:
			result = kHIDElementTypeFeature;
			break;
		case kIOHIDElementTypeCollection:
			result = kHIDElementTypeCollection;
			break;
		default:
			result = kHIDElementTypeAll;
			break;
	}
	return result;
}

/*************************************************************************
*
* HIDFindDevice( inSearchDevice, outFoundDevice )
*
* Purpose:  searches the internal list of devices for the best match
*
* Notes:
*
* Inputs:   inSearchDevice   - the device we're searching for
*			outFoundDevice	- the address of the best match
*
* Returns:  Boolean			- TRUE if we find a match
*			outFoundDevice	- the best match
*/

Boolean HIDFindDevice( const hu_device_t * inSearchDevice, hu_device_t **outFoundDevice )
{
	hu_device_t * tDevice;
	hu_device_t * bestDevice = NULL;
	long bestScore = 0;
	Boolean result = FALSE;
	
	// iterate over all devices
	tDevice = HIDGetFirstDevice( );
	while ( tDevice ) {
		long deviceScore = 1;

		if ( inSearchDevice->vendorID && ( inSearchDevice->vendorID == tDevice->vendorID ) ) {
			deviceScore += 10;
			if ( inSearchDevice->productID && ( inSearchDevice->productID == tDevice->productID ) )
				deviceScore += 8;
		}

		if ( ( inSearchDevice->usagePage && ( inSearchDevice->usagePage == tDevice->usagePage ) ) &&
			( inSearchDevice->usage && ( inSearchDevice->usage == tDevice->usage ) ) )
			deviceScore += 9;

		if ( inSearchDevice->locID && ( inSearchDevice->locID == tDevice->locID ) )
			deviceScore += 5;

		if ( deviceScore > bestScore ) {
			bestDevice = tDevice;
			bestScore = deviceScore;
#if LOG_SCORING	// set TRUE to output scoring informaton
			printf( "\n-HIDFindDevice( %ld:%ld )-I-Debug, better score: %ld.", inSearchElement->usagePage, inSearchElement->usage, score );
			//HIDPrintElement( pBestElement );
#endif
		}
		tDevice = HIDGetNextDevice( tDevice );
	}

	if ( bestDevice ) {
		*outFoundDevice = bestDevice;
#if LOG_SCORING	// set TRUE to output scoring informaton
		printf( "\n-HIDFindDevice( %ld:%ld )-I-Debug, best score: %ld.", inSearchElement->usagePage, inSearchElement->usage, bestScore );
		//HIDPrintElement( pBestElement );
		printf( "\n" );
#endif
		result = TRUE;
	}
	return result;
}

/*************************************************************************
*
* HIDFindActionDeviceAndElement( inSearchDevice, inSearchElement, outFoundDevice, outFoundElement )
*
* Purpose:  find the closest matching device and element for this action
*
* Notes:	matches device: serial, vendorID, productID, location, inUsagePage, usage
*			matches element: cookie, inUsagePage, usage,
*
* Inputs:   inSearchDevice   - the device we're searching for
*			inSearchElement  - the element we're searching for
*			outFoundDevice	- the address of the best matching device
*			outFoundElement	- the address of the best matching element
*
* Returns:  Boolean			- TRUE if we find a match
*			outFoundDevice	- the best matching device
*			outFoundElement	- the best matching element
*/

Boolean HIDFindActionDeviceAndElement( const hu_device_t * inSearchDevice, const hu_element_t * inSearchElement, hu_device_t **outFoundDevice, hu_element_t **outFoundElement )
{
	hu_device_t *tDevice, *bestDevice = NULL;
	hu_element_t *tElement, *bestElement = NULL;
	HIDElementTypeMask hidMask = HIDConvertElementTypeToMask( inSearchElement->type );
	long bestScore = 0;
	Boolean result = FALSE;

	// iterate over all devices
	tDevice = HIDGetFirstDevice( );
	while ( tDevice ) {
		long deviceScore = 1;

		if ( inSearchDevice->vendorID && ( inSearchDevice->vendorID == tDevice->vendorID ) ) {
			deviceScore += 10;
			if ( inSearchDevice->productID && ( inSearchDevice->productID == tDevice->productID ) )
				deviceScore += 8;
		}
		if ( ( inSearchDevice->usagePage && ( inSearchDevice->usagePage == tDevice->usagePage ) ) &&
			( inSearchDevice->usage && ( inSearchDevice->usage == tDevice->usage ) ) )
			deviceScore += 9;

		if ( inSearchDevice->locID && ( inSearchDevice->locID == tDevice->locID ) )
			deviceScore += 5;

		// iterate over all elements of this device
		tElement = HIDGetFirstDeviceElement( tDevice, hidMask );
		while ( tElement ) {
			long score = deviceScore;

			if ( ( inSearchElement->usagePage && ( inSearchElement->usagePage == tElement->usagePage ) ) &&
				( inSearchElement->usage && ( inSearchElement->usage == tElement->usage ) ) ) {
				score += 5;

				if ( inSearchElement->cookie && ( inSearchElement->cookie == tElement->cookie ) )
					score += 4;
			} else {
				score = 0;
			}
#if LOG_SCORING
			if ( kHIDPage_KeyboardOrKeypad != tElement->usagePage ) {	// skip keyboards here
				printf( "\n-HIDFindActionDeviceAndElement( %ld:%ld )-I-Debug, score: %ld.", inSearchElement->usagePage, inSearchElement->usage, score );
				HIDPrintElement( tElement );
			}
#endif LOG_SCORING
			if ( score > bestScore ) {
				bestDevice = tDevice;
				bestElement = tElement;
				bestScore = score;
#if LOG_SCORING
				printf( "\n-HIDFindActionDeviceAndElement( %ld:%ld )-I-Debug, better score: %ld.", inSearchElement->usagePage, inSearchElement->usage, score );
				HIDPrintElement( bestElement );
#endif LOG_SCORING
			}
			tElement = HIDGetNextDeviceElement( tElement, hidMask );
		}
		tDevice = HIDGetNextDevice( tDevice );
	}

	if ( bestDevice || bestElement ) {
		*outFoundDevice = bestDevice;
		*outFoundElement = bestElement;
#if LOG_SCORING
		printf( "\n-HIDFindActionDeviceAndElement( %ld:%ld )-I-Debug, best score: %ld.", inSearchElement->usagePage, inSearchElement->usage, bestScore );
		HIDPrintElement( bestElement );
		printf( "\n" );
#endif LOG_SCORING
		result = TRUE;
	}
	return result;
}

/*************************************************************************
*
* HIDFindSubElement( inStartElement, inSearchElement, outFoundElement )
*
* Purpose:  find the matching sub element
*
* Notes:	matches element: cookie, inUsagePage, usage,
*
* Inputs:   inStartElement   - the current element
*			inSearchElement  - the element we're searching for
*			outFoundElement	- the address of the best matching element
*
* Returns:  Boolean			- TRUE if we find a match
*			outFoundElement	- the next matching element
*/

Boolean HIDFindSubElement( const hu_element_t * inStartElement, const hu_element_t * inSearchElement, hu_element_t **outFoundElement )
{
	hu_element_t *tElement, *bestElement = NULL;
	HIDElementTypeMask hidMask = HIDConvertElementTypeToMask( inSearchElement->type );
	long bestScore = 0;

	if ( ( !inStartElement ) || ( !inSearchElement ) || ( !outFoundElement ) )
		return FALSE;

	// iterate over all children of this element
	tElement = inStartElement->pChild;

	while ( tElement ) {
		long score = 0;
#if LOG_SEARCHING
		printf( "\n-HIDFindSubElement, search = {t:%.2lX, u:%.4lX:%.4lX}, match = {t:%.2lX, u:%.4lX:%.4lX, s:\"%s\"}",
			   inSearchElement->type, inSearchElement->usagePage, inSearchElement->usage,
			   tElement->type, tElement->usagePage, tElement->usage, tElement->name );
		fflush( stdout );
#endif LOG_SEARCHING
		if ( ( inSearchElement->usagePage && ( inSearchElement->usagePage == tElement->usagePage ) ) &&
			 ( inSearchElement->usage && ( inSearchElement->usage == tElement->usage ) ) ) {
			score += 4;
			if ( inSearchElement->cookie && ( inSearchElement->cookie == tElement->cookie ) ) {
				score += 5;
			}
		}
#if LOG_SEARCHING
		if ( kHIDPage_KeyboardOrKeypad != tElement->usagePage ) {	// skip keyboards here
			printf( "\n-HIDFindSubElement( %ld:%ld )-I-Debug, score: %ld.", inSearchElement->usagePage, inSearchElement->usage, score );
			HIDPrintElement( tElement );
		}
#endif LOG_SEARCHING

		if ( score > bestScore ) {
			bestElement = tElement;
			bestScore = score;
#if LOG_SEARCHING
			printf( "\n-HIDFindSubElement( %ld:%ld )-I-Debug, better score: %ld.", inSearchElement->usagePage, inSearchElement->usage, score );
			HIDPrintElement( bestElement );
#endif LOG_SEARCHING
		}
		tElement = HIDGetNextDeviceElement( tElement, hidMask );
	}
#if LOG_SEARCHING
	if ( bestElement ) {
		printf( "\n-HIDFindSubElement( %ld:%ld )-I-Debug, best score: %ld.", inSearchElement->usagePage, inSearchElement->usage, bestScore );
		HIDPrintElement( bestElement );
		printf( "\n" );
	}
#endif LOG_SEARCHING

	*outFoundElement = bestElement;

	return ( NULL != bestElement );
}

/*************************************************************************
*
* HIDPrintElement( inElement )
*
* Purpose:  printf out all of an elements information
*
* Inputs:   inElement	- the element
*
* Returns:  int			- number of char's output
*/
int HIDPrintElement( const hu_element_t * inElement )
{
	int results;
	int count;

	printf( "\n" );

	if ( gDepth != inElement->depth )
		printf( "%d", gDepth );
	for ( count = 0;count < inElement->depth;count++ )
		printf( " | " );

#if 0	// this is verbose
	results = printf( "-HIDPrintElement = {name: \"%s\", t: 0x%.2lX, u:%ld:%ld, c: %ld, min/max: %ld/%ld, "   \
					 "scaled: %ld/%ld, size: %ld, rel: %s, wrap: %s, nonLinear: %s, preferred: %s, nullState: %s, "  \
					 "units: %ld, exp: %ld, cal: %ld/%ld, user: %ld/%ld, depth: %ld}.",
					 inElement->name, 						// name of element( c string )
					 inElement->type, 						// the type defined by IOHIDElementType in IOHIDKeys.h
					 inElement->usagePage, 					// usage page from IOUSBHIDParser.h which defines general usage
					 inElement->usage, 						// usage within above page from IOUSBHIDParser.h which defines specific usage
					 ( long ) inElement->cookie, 			// unique value( within device of specific vendorID and productID ) which identifies element, will NOT change
					 inElement->min, 						// reported min value possible
					 inElement->max, 						// reported max value possible
					 inElement->scaledMin, 					// reported scaled min value possible
					 inElement->scaledMax, 					// reported scaled max value possible
					 inElement->size, 						// size in bits of data return from element
					 inElement->relative ? "YES" : "NO", 	// are reports relative to last report( deltas )
					 inElement->wrapping ? "YES" : "NO", 	// does element wrap around( one value higher than max is min )
					 inElement->nonLinear ? "YES" : "NO", 	// are the values reported non-linear relative to element movement
					 inElement->preferredState ? "YES" : "NO", // does element have a preferred state( such as a button )
					 inElement->nullState ? "YES" : "NO", 	// does element have null state
					 inElement->units, 						// units value is reported in( not used very often )
					 inElement->unitExp, 					// exponent for units( also not used very often )
					 inElement->minReport, 					// min returned value( for calibrate call )
					 inElement->maxReport, 					// max returned value
					 inElement->userMin, 					// user set min to scale to( for scale call )
					 inElement->userMax, 					// user set max
					 inElement->depth
					 );
#else	// this is brief
	results = printf( "-HIDPrintElement = {t: 0x%lX, u:%ld:%ld, c: %ld, name: \"%s\", d: %ld}.",
					 ( long unsigned int ) inElement->type,	// the type defined by IOHIDElementType in IOHIDKeys.h
					 ( long int ) inElement->usagePage,		// usage page from IOUSBHIDParser.h which defines general usage
					 ( long int ) inElement->usage,			// usage within above page from IOUSBHIDParser.h which defines specific usage
					 ( long ) inElement->cookie, 		// unique value( within device of specific vendorID and productID ) which identifies element, will NOT change
					 inElement->name, 				// name of element( c string )
					 inElement->depth
					 );
#endif
	fflush( stdout );
	return results;
}

/*************************************************************************
*
* HIDIsValidDevice( inSearchDevice )
*
* Purpose:  validate this device
*
* Inputs:   inSearchDevice   - the device
*
* Returns:  Boolean			- TRUE if we find the device in our( internal ) device list
*/

Boolean HIDIsValidDevice( const hu_device_t * inSearchDevice )
{
	hu_device_t * tDevice = gDeviceList;

	while ( tDevice ) {
		if ( tDevice == inSearchDevice )
			return TRUE;
		tDevice = tDevice->pNext;
	}
	return FALSE;
}

/*************************************************************************
*
* HIDIsValidElement( inSearchDevice, inSearchElement )
*
* Purpose:  validate this element
*
* Inputs:   inSearchDevice   - the device
*			inSearchElement  - the element
*
* Returns:  Boolean			- TRUE if this is a valid element pointer for this device
*/
Boolean HIDIsValidElement( const hu_device_t * inSearchDevice, const hu_element_t * inSearchElement )
{
	if ( HIDIsValidDevice( inSearchDevice ) ) {
		hu_element_t * tElement = HIDGetFirstDeviceElement( inSearchDevice, kHIDElementTypeAll );
		while ( tElement ) {
			if ( tElement == inSearchElement )
				return TRUE;
			tElement = HIDGetNextDeviceElement( tElement, kHIDElementTypeAll );
		}
	}
	return FALSE;
}

/*************************************************************************
*
* HIDSetHotPlugCallback( inHotPlugCallbackProcPtr )
*
* Purpose:  set's client hot plug callback routine
*
* Inputs:   inHotPlugCallbackProcPtr   - the routine to be called when a device is plug in
*
* Returns:  SInt32		- error code ( if any )
*/
OSStatus HIDSetHotPlugCallback( HotPlugCallbackProcPtr inHotPlugCallbackProcPtr )
{
	gHotPlugCallbackProcPtr = inHotPlugCallbackProcPtr;
	return noErr;
}

/*****************************************************/
#pragma mark - local ( static ) function implementations
/*****************************************************/

/*************************************************************************
*
* hu_MapChar( c )
*
* Purpose:  Maps bad chars to good chars for html/printing ASCII
*
* Inputs:   c				- the( bad? ) characater
*
* Returns:  char			- the good characater
*/

static char hu_MapChar( char c )
{
	unsigned char uc = ( unsigned char ) c;

	switch( uc ) {
		case '/': return '-'; // use dash instead of slash

		case 0x7F: return ' ';
		case 0x80: return 'A';
		case 0x81: return 'A';
		case 0x82: return 'C';
		case 0x83: return 'E';
		case 0x84: return 'N';
		case 0x85: return 'O';
		case 0x86: return 'U';
		case 0x87: return 'a';
		case 0x88: return 'a';
		case 0x89: return 'a';
		case 0x8A: return 'a';
		case 0x8B: return 'a';
		case 0x8C: return 'a';
		case 0x8D: return 'c';
		case 0x8E: return 'e';
		case 0x8F: return 'e';
		case 0x90: return ' ';
		case 0x91: return ' '; // ? '
		case 0x92: return ' '; // ? '
		case 0x93: return ' '; // ? "
		case 0x94: return ' '; // ? "
		case 0x95: return ' ';
		case 0x96: return ' ';
		case 0x97: return ' ';
		case 0x98: return ' ';
		case 0x99: return ' ';
		case 0x9A: return ' ';
		case 0x9B: return 0x27;
		case 0x9C: return 0x22;
		case 0x9D: return ' ';
		case 0x9E: return ' ';
		case 0x9F: return ' ';
		case 0xA0: return ' ';
		case 0xA1: return ' ';
		case 0xA2: return ' ';
		case 0xA3: return ' ';
		case 0xA4: return ' ';
		case 0xA5: return ' ';
		case 0xA6: return ' ';
		case 0xA7: return ' ';
		case 0xA8: return ' ';
		case 0xA9: return ' ';
		case 0xAA: return ' ';
		case 0xAB: return ' ';
		case 0xAC: return ' ';
		case 0xAD: return ' ';
		case 0xAE: return ' ';
		case 0xAF: return ' ';
		case 0xB0: return ' ';
		case 0xB1: return ' ';
		case 0xB2: return ' ';
		case 0xB3: return ' ';
		case 0xB4: return ' ';
		case 0xB5: return ' ';
		case 0xB6: return ' ';
		case 0xB7: return ' ';
		case 0xB8: return ' ';
		case 0xB9: return ' ';
		case 0xBA: return ' ';
		case 0xBB: return ' ';
		case 0xBC: return ' ';
		case 0xBD: return ' ';
		case 0xBE: return ' ';
		case 0xBF: return ' ';
		case 0xC0: return ' ';
		case 0xC1: return ' ';
		case 0xC2: return ' ';
		case 0xC3: return ' ';
		case 0xC4: return ' ';
		case 0xC5: return ' ';
		case 0xC6: return ' ';
		case 0xC7: return ' ';
		case 0xC8: return ' ';
		case 0xC9: return ' ';
		case 0xCA: return ' ';
		case 0xCB: return 'A';
		case 0xCC: return 'A';
		case 0xCD: return 'O';
		case 0xCE: return ' ';
		case 0xCF: return ' ';
		case 0xD0: return '-';
		case 0xD1: return '-';
		case 0xD2: return 0x22;
		case 0xD3: return 0x22;
		case 0xD4: return 0x27;
		case 0xD5: return 0x27;
		case 0xD6: return '-'; // use dash instead of slash
		case 0xD7: return ' ';
		case 0xD8: return 'y';
		case 0xD9: return 'Y';
		case 0xDA: return '-'; // use dash instead of slash
		case 0xDB: return ' ';
		case 0xDC: return '<';
		case 0xDD: return '>';
		case 0xDE: return ' ';
		case 0xDF: return ' ';
		case 0xE0: return ' ';
		case 0xE1: return ' ';
		case 0xE2: return ',';
		case 0xE3: return ',';
		case 0xE4: return ' ';
		case 0xE5: return 'A';
		case 0xE6: return 'E';
		case 0xE7: return 'A';
		case 0xE8: return 'E';
		case 0xE9: return 'E';
		case 0xEA: return 'I';
		case 0xEB: return 'I';
		case 0xEC: return 'I';
		case 0xED: return 'I';
		case 0xEE: return 'O';
		case 0xEF: return 'O';
		case 0xF0: return ' ';
		case 0xF1: return 'O';
		case 0xF2: return 'U';
		case 0xF3: return 'U';
		case 0xF4: return 'U';
		case 0xF5: return '|';
		case 0xF6: return ' ';
		case 0xF7: return ' ';
		case 0xF8: return ' ';
		case 0xF9: return ' ';
		case 0xFA: return '.';
		case 0xFB: return ' ';
		case 0xFC: return ' ';
		case 0xFD: return 0x22;
		case 0xFE: return ' ';
		case 0xFF: return ' ';
	}
	return c;
}

/*************************************************************************
*
* hu_CleanString( inCStr )
*
* Purpose:  ensures the string only contains printable ASCII characters
* Notes:	input is null terminated( C ) string, change is made in place
*
* Inputs:   inCStr	- the address of the C string
*
* Returns:  nothing
*/

static void hu_CleanString( char* inCStr )
{
	char* charIt = inCStr;
	while ( *charIt ) {
		*charIt = hu_MapChar( *charIt );
		charIt++;
	}
}

/*************************************************************************
*
* hu_GetElementInfo( inElementCFDictRef, inElement )
*
* Purpose:  extracts element information from an elements CF dictionary
*			into a element data structure
* Notes:	only called by hu_AddElement
*
* Inputs:   inElementCFDictRef   - the elements dictionary
*			inElement			- pointer to elements data structure
*
* Returns:  nothing
*/

static void hu_GetElementInfo( CFTypeRef inElementCFDictRef, hu_element_t * inElement )
{
	long number;
	CFTypeRef tCFTypeRef;

	// type, inUsagePage, usage already stored

	// get the cookie
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementCookieKey ) );
	if ( tCFTypeRef && CFNumberGetValue( tCFTypeRef, kCFNumberLongType, &number ) ) {
		inElement->cookie = ( IOHIDElementCookie ) number;
	} else {
		inElement->cookie = ( IOHIDElementCookie ) 0;
	}

	// get the min
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementMinKey ) );
	if ( tCFTypeRef && CFNumberGetValue( tCFTypeRef, kCFNumberLongType, &number ) ) {
		inElement->min = number;
	} else {
		inElement->min = 0;
	}

	inElement->maxReport = inElement->min;
	inElement->userMin = kDefaultUserMin;

	// get the max
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementMaxKey ) );
	if ( tCFTypeRef && CFNumberGetValue( tCFTypeRef, kCFNumberLongType, &number ) ) {
		inElement->max = number;
	} else {
		inElement->max = 0;
	}

	inElement->minReport = inElement->max;
	inElement->userMax = kDefaultUserMax;

	// get the scaled min
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementScaledMinKey ) );
	if ( tCFTypeRef && CFNumberGetValue( tCFTypeRef, kCFNumberLongType, &number ) ) {
		inElement->scaledMin = number;
	} else {
		inElement->scaledMin = 0;
	}

	// get the scaled max
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementScaledMaxKey ) );
	if ( tCFTypeRef && CFNumberGetValue( tCFTypeRef, kCFNumberLongType, &number ) ) {
		inElement->scaledMax = number;
	} else {
		inElement->scaledMax = 0;
	}

	// get the size
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementSizeKey ) );
	if ( tCFTypeRef && CFNumberGetValue( tCFTypeRef, kCFNumberLongType, &number ) ) {
		inElement->size = number;
	} else {
		inElement->size = 0;
	}

	// get the "is relative" boolean
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementIsRelativeKey ) );
	if ( tCFTypeRef ) {
		inElement->relative = CFBooleanGetValue( tCFTypeRef );
	} else {
		inElement->relative = 0;
	}

	// get the "is wrapping" boolean
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementIsWrappingKey ) );
	if ( tCFTypeRef ) {
		inElement->wrapping = CFBooleanGetValue( tCFTypeRef );
	} else {
		inElement->wrapping = FALSE;
	}

	// get the "is non linear" boolean
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementIsNonLinearKey ) );
	if ( tCFTypeRef ) {
		inElement->nonLinear = CFBooleanGetValue( tCFTypeRef );
	} else {
		inElement->nonLinear = FALSE;
	}

	// get the "Has Preferred State" boolean
#ifdef kIOHIDElementHasPreferredStateKey
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementHasPreferredStateKey ) );
#else // Mac OS X 10.0 has spelling error
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementHasPreferedStateKey ) );
#endif
	if ( tCFTypeRef ) {
		inElement->preferredState = CFBooleanGetValue( tCFTypeRef );
	} else {
		inElement->preferredState = FALSE;
	}

	// get the "Has Null State" boolean
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementHasNullStateKey ) );
	if ( tCFTypeRef ) {
		inElement->nullState = CFBooleanGetValue( tCFTypeRef );
	} else {
		inElement->nullState = FALSE;
	}

	// get the units
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementUnitKey ) );
	if ( tCFTypeRef && CFNumberGetValue( tCFTypeRef, kCFNumberLongType, &number ) ) {
		inElement->units = number;
	} else {
		inElement->units = 0;
	}

	// get the units exponent
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementUnitExponentKey ) );
	if ( tCFTypeRef && CFNumberGetValue( tCFTypeRef, kCFNumberLongType, &number ) ) {
		inElement->unitExp = number;
	} else {
		inElement->unitExp = 0;
	}

	// get the name
	tCFTypeRef = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementNameKey ) );
	if ( tCFTypeRef ) {
		if ( !CFStringGetCString( tCFTypeRef, inElement->name, 256, CFStringGetSystemEncoding() ) ) {
			HIDReportError( "hu_GetElementInfo: CFStringGetCString error retrieving inElement->name." );
		}
	}
	if ( !*inElement->name ) {
		// set name from vendor id, product id & usage info look up
		if ( !HIDGetElementNameFromVendorProductUsage( gCurrentDevice->vendorID, gCurrentDevice->productID, inElement->usagePage, inElement->usage, inElement->name ) ) {
			// set name from vendor id/product id look up
			HIDGetElementNameFromVendorProductCookie( gCurrentDevice->vendorID, gCurrentDevice->productID, ( long ) inElement->cookie, inElement->name );
			if ( !*inElement->name ) { // if no name
				HIDGetUsageName( inElement->usagePage, inElement->usage, inElement->name );
				if ( !*inElement->name ) // if not usage
					sprintf( inElement->name, "Element" );
			}
		}
	}
}

/*************************************************************************
*
* hu_AddElement( inElementCFDictRef, inCurrentElement )
*
* Purpose:  examines CF dictionary vlaue in device element hierarchy to determine
*			if it is element of interest or a collection of more elements.
*			if element of interest allocate storage, add to list and retrieve element specific info.
*			if collection then pass on to hu_GetCollectionElements to deconstruct into additional individual elements.
* Notes:	only called by hu_GetElementsCFArrayHandler
*
* Inputs:   inElementCFDictRef   - the elements dictionary
*			inCurrentElement	- pointer to address of current elements structure
*
* Returns:  nothing
*/

static void hu_AddElement( CFTypeRef inElementCFDictRef, hu_element_t **inCurrentElement )
{
	if(CFGetTypeID(inElementCFDictRef) == CFDictionaryGetTypeID()){
		hu_device_t *	tDevice			= gCurrentDevice;
		hu_element_t *   tElement		= NULL;
		CFTypeRef		tElementCFDictRefType  = CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementTypeKey ) );
		CFTypeRef		refUsagePage	= CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementUsagePageKey ) );
		CFTypeRef		refUsage		= CFDictionaryGetValue( inElementCFDictRef, CFSTR( kIOHIDElementUsageKey ) );
		long			elementType, usagePage, usage;

		if ( tElementCFDictRefType )
			CFNumberGetValue( tElementCFDictRefType, kCFNumberLongType, &elementType );
		if ( refUsagePage )
			CFNumberGetValue( refUsagePage, kCFNumberLongType, &usagePage );
		if ( refUsage )
			CFNumberGetValue( refUsage, kCFNumberLongType, &usage );

		if ( !tDevice )
			return;

		if ( elementType ) {
			// look at types of interest
			if ( elementType != kIOHIDElementTypeCollection ) {
				if ( usagePage && usage ) {	// if valid usage and page
					switch( usagePage ) {	// only interested in kHIDPage_GenericDesktop and kHIDPage_Button usage pages
						case kHIDPage_GenericDesktop: {
							switch( usage ) {	// look at usage to determine function
								case kHIDUsage_GD_X:
								case kHIDUsage_GD_Y:
								case kHIDUsage_GD_Z:
								case kHIDUsage_GD_Rx:
								case kHIDUsage_GD_Ry:
								case kHIDUsage_GD_Rz:
									tElement = ( hu_element_t * ) Alloc_Z( sizeof( hu_element_t ) );
									if ( tElement ) tDevice->axis++;
										break;
								case kHIDUsage_GD_Slider:
									tElement = ( hu_element_t * ) Alloc_Z( sizeof( hu_element_t ) );
									if ( tElement ) tDevice->sliders++;
										break;
								case kHIDUsage_GD_Dial:
									tElement = ( hu_element_t * ) Alloc_Z( sizeof( hu_element_t ) );
									if ( tElement ) tDevice->dials++;
										break;
								case kHIDUsage_GD_Wheel:
									tElement = ( hu_element_t * ) Alloc_Z( sizeof( hu_element_t ) );
									if ( tElement ) tDevice->wheels++;
										break;
								case kHIDUsage_GD_Hatswitch:
									tElement = ( hu_element_t * ) Alloc_Z( sizeof( hu_element_t ) );
									if ( tElement ) tDevice->hats++;
										break;
								default:
									tElement = ( hu_element_t * ) Alloc_Z( sizeof( hu_element_t ) );
									break;
							}
						}
							break;
						case kHIDPage_Button:
							tElement = ( hu_element_t * ) Alloc_Z( sizeof( hu_element_t ) );
							if ( tElement ) tDevice->buttons++;
								break;
						default:
							// just add a generic element
							tElement = ( hu_element_t * ) Alloc_Z( sizeof( hu_element_t ) );
							break;
					}
				}
#if 0		// ignore these errors
				else {
					HIDReportError( "hu_AddElement: CFNumberGetValue error when getting value for refUsage or refUsagePage." );
				}
#endif 0
			} else {	// collection
				tElement = ( hu_element_t * ) Alloc_Z( sizeof( hu_element_t ) );
			}
		} else {
			HIDReportError( "hu_AddElement: CFNumberGetValue error when getting value for tElementCFDictRefType." );
		}

		if ( tElement ) {	// add to list

			// this code builds a binary tree based on the collection hierarchy of inherent in the device element layout
			// it preserves the structure of the elements as collections have children and elements are siblings to each other

			// clear record
			bzero( tElement, sizeof( hu_element_t ) );

			// get element info
			tElement->type = elementType;
			tElement->usagePage = usagePage;
			tElement->usage = usage;
			tElement->depth = 0;		// assume root object

			// extract element information from the CF dictionary into a element data structure
			hu_GetElementInfo( inElementCFDictRef, tElement );

			// count elements
			tDevice->totalElements++;

			switch( tElement->type ) {
				case kIOHIDElementTypeInput_Misc:
				case kIOHIDElementTypeInput_Button:
				case kIOHIDElementTypeInput_Axis:
				case kIOHIDElementTypeInput_ScanCodes: {
					tDevice->inputs++;
					break;
				}
				case kIOHIDElementTypeOutput: {
					tDevice->outputs++;
					break;
				}
				case kIOHIDElementTypeFeature: {
					tDevice->features++;
					break;
				}
				case kIOHIDElementTypeCollection: {
					tDevice->collections++;
					break;
				}
				default: {
					HIDReportErrorNum( "\nhu_AddElement: Unknown element type: %d", tElement->type );
					break;
				}
			}

			if ( !*inCurrentElement ) {	// if at list head
				tDevice->pListElements = tElement; // add current element
				*inCurrentElement = tElement; // set current element to element we just added
			} else {	// have exsiting structure
				if ( gAddAsChild ) {	// if the previous element was a collection, let's add this as a child of the previous
					// this iteration should not be needed but there maybe some untested degenerate case which this code will ensure works
					while ( ( *inCurrentElement )->pChild ) {	// step down tree until free child node found
						*inCurrentElement = ( *inCurrentElement )->pChild;
					}

					( *inCurrentElement )->pChild = tElement; // insert there
					tElement->depth = ( *inCurrentElement )->depth + 1;
				} else { // add as sibling
					// this iteration should not be needed but there maybe some untested degenerate case which this code will ensure works
					while ( ( *inCurrentElement )->pSibling ) {	// step down tree until free sibling node found
						*inCurrentElement = ( *inCurrentElement )->pSibling;
					}
					( *inCurrentElement )->pSibling = tElement; // insert there
					tElement->depth = ( *inCurrentElement )->depth;
				}
				tElement->pPrevious = *inCurrentElement; // point to previous
				*inCurrentElement = tElement; // set current to our collection
			}

			// if a type that is normally an axis and has a preferred state
			tElement->hasCenter = FALSE;

			if ( ( tElement->preferredState ) && ( kHIDPage_GenericDesktop == tElement->usagePage ) ) {
				switch( tElement->usage ) {
					case kHIDUsage_GD_X:
					case kHIDUsage_GD_Y:
					case kHIDUsage_GD_Z:
					case kHIDUsage_GD_Rx:
					case kHIDUsage_GD_Ry:
					case kHIDUsage_GD_Rz:
					case kHIDUsage_GD_Slider:
					case kHIDUsage_GD_Dial:
					case kHIDUsage_GD_Wheel:
					case kHIDUsage_GD_Hatswitch:
						tElement->hasCenter = TRUE; // respect center
						tElement->initialCenter = 0x80000000; // HIDGetElementValue( tDevice, tElement );
				}
			}

	#if LOG_ELEMENTS
			HIDPrintElement( tElement );
	#endif LOG_ELEMENTS

			if ( kIOHIDElementTypeCollection == elementType ) { // if this element is a collection of other elements
				gAddAsChild = TRUE; // add next set as children to this element
				gDepth++;
				hu_GetCollectionElements( inElementCFDictRef, &tElement ); // recursively process the collection
				gDepth--;
			}
			gAddAsChild = FALSE; // add next as this elements sibling( when return from a collection or with non-collections )
		}
#if 0		// ignore these errors
		else {
			HIDReportError( "hu_AddElement: no element added." );
		}
#endif
	}
}

/*************************************************************************
*
* hu_GetElementsCFArrayHandler( value, parameter )
*
* Purpose:  the CFArrayApplierFunction called by the CFArrayApplyFunction in hu_GetElements
*
* Inputs:   value			- the value from the array
*			parameter		- the context passed to CFArrayApplyFunction( in our case, inCurrentElement )
*
* Returns:  nothing
*/

static void hu_GetElementsCFArrayHandler( const void* value, void* parameter )
{
	if ( CFGetTypeID( value ) == CFDictionaryGetTypeID( ) ) {
		hu_AddElement( ( CFTypeRef ) value, ( hu_element_t ** ) parameter );
	}
}

/*************************************************************************
*
* hu_GetElements( inElementCFDictRef, outCurrentElement )
*
* Purpose:  handles retrieval of element information from arrays of elements in device IO registry information
*
* Notes:	Only called by hu_GetCollectionElements
*
* Inputs:   inElementCFDictRef   - the I/O registry dictionary of all elements for a device
*			outCurrentElement	- adress where to store new elements
*
* Returns:  nothing
*/

static void hu_GetElements( CFTypeRef inElementCFDictRef, hu_element_t **outCurrentElement )
{
	CFTypeID tCFTypeID = CFGetTypeID( inElementCFDictRef );
	if ( tCFTypeID == CFArrayGetTypeID( ) ) {	// if element is an array
		CFRange range = {0, CFArrayGetCount( inElementCFDictRef )};
		// CountElementsCFArrayHandler called for each array member
		CFArrayApplyFunction( inElementCFDictRef, range, hu_AddElement, outCurrentElement );
	}
}

/*************************************************************************
*
* hu_GetCollectionElements( deviceProperties, outCurrentCollection )
*
* Purpose:  handles extracting element information from element collection CF types
*
* Notes:	used from top level element decoding and hierarchy deconstruction to flatten device element list.
*			Called by hu_AddElement and hu_BuildDevice.
*
* Inputs:   deviceProperties	- the I/O registry dictionary for the device
*			outCurrentCollection  - adress where to store new elements
*
* Returns:  nothing
*/

static void hu_GetCollectionElements( CFDictionaryRef deviceProperties, hu_element_t **outCurrentCollection )
{
	CFTypeRef inElementCFDictRef = CFDictionaryGetValue( deviceProperties, CFSTR( kIOHIDElementKey ) );
	if ( inElementCFDictRef ) {
		hu_GetElements( inElementCFDictRef, outCurrentCollection );
	} else {
		HIDReportError( "hu_GetCollectionElements: CFDictionaryGetValue error when creating CFTypeRef for kIOHIDElementKey." );
	}
}

/*************************************************************************
*
* hu_TopLevelElementHandler( value, parameter )
*
* Purpose:  use top level element usage page and usage to discern device usage page and usage setting appropriate values in device record
*
* Notes:	callback for CFArrayApplyFunction in hu_GetDeviceInfo
*
* Inputs:   value			- the value from the array( should be a CFDictionaryRef )
*			parameter		- the context passed to CFArrayApplyFunction( in our case, NULL )
*
* Returns:  nothing
*/

static void hu_TopLevelElementHandler( const void* value, void* parameter )
{
	CFTypeRef refCF = 0;
	if ( value &&  parameter ) {
		if ( CFGetTypeID( value ) == CFDictionaryGetTypeID( ) ) {
			refCF = CFDictionaryGetValue( value, CFSTR( kIOHIDElementUsagePageKey ) );
			if ( !CFNumberGetValue( refCF, kCFNumberLongType, & ( ( hu_device_t * ) parameter )->usagePage ) ) {
				HIDReportError( "hu_TopLevelElementHandler: CFNumberGetValue error retrieving inDevice->usagePage." );
			}
			refCF = CFDictionaryGetValue( value, CFSTR( kIOHIDElementUsageKey ) );
			if ( !CFNumberGetValue( refCF, kCFNumberLongType, & ( ( hu_device_t * ) parameter )->usage ) ) {
				HIDReportError( "hu_TopLevelElementHandler: CFNumberGetValue error retrieving inDevice->usage." );
			}
		}
	}
}

/*************************************************************************
*
* hu_GetDeviceInfo( inHIDDevice, inDeviceCFDictionaryRef, inDevice )
*
* Purpose:  extracts device info from dictionary records in IO registry
*
* Notes:	only called by hu_BuildDevice
*
* Inputs:   inHIDDevice				- our HID object
*			inDeviceCFDictionaryRef  - dictionary properties for this device
*			inDevice					- address where to store device properties
*
* Returns:  nothing
*/

static void hu_GetDeviceInfo( io_object_t inHIDDevice, CFDictionaryRef inDeviceCFDictionaryRef, hu_device_t * inDevice )
{
	CFMutableDictionaryRef usbProperties = 0;
	io_registry_entry_t parent1, parent2;
	
	// Mac OS X currently is not mirroring all USB properties to HID page so need to look at USB device page also
	// get dictionary for usb properties: step up two levels and get CF dictionary for USB properties
	if ( ( KERN_SUCCESS == IORegistryEntryGetParentEntry( inHIDDevice, kIOServicePlane, &parent1 ) ) &&
		 ( KERN_SUCCESS == IORegistryEntryGetParentEntry( parent1, kIOServicePlane, &parent2 ) ) &&
		 ( KERN_SUCCESS == IORegistryEntryCreateCFProperties( parent2, &usbProperties, kCFAllocatorDefault, kNilOptions ) ) )
	{
		if ( usbProperties ) {
			CFTypeRef refCF = 0;
			// get device info
			// try hid dictionary first, if fail then go to usb dictionary
			
			// get transport
			refCF = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDTransportKey ) );
			if ( refCF ) {
				if ( !CFStringGetCString( refCF, inDevice->transport, 256, CFStringGetSystemEncoding() ) ) {
					HIDReportError( "hu_GetDeviceInfo: CFStringGetCString error retrieving inDevice->transport." );
				}
				hu_CleanString( inDevice->transport );
			}
			
			// get vendorID
			refCF = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDVendorIDKey ) );
			if ( !refCF ) {
				refCF = CFDictionaryGetValue( usbProperties, CFSTR( "idVendor" ) );
			}
			if ( refCF ) {
				if ( !CFNumberGetValue( refCF, kCFNumberLongType, &inDevice->vendorID ) ) {
					HIDReportError( "hu_GetDeviceInfo: CFNumberGetValue error retrieving inDevice->vendorID." );
				}
			}
			
			// get product ID
			refCF = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDProductIDKey ) );
			if ( !refCF ) {
				refCF = CFDictionaryGetValue( usbProperties, CFSTR( "idProduct" ) );
			}
			if ( refCF ) {
				if ( !CFNumberGetValue( refCF, kCFNumberLongType, &inDevice->productID ) ) {
					HIDReportError( "hu_GetDeviceInfo: CFNumberGetValue error retrieving inDevice->productID." );
				}
			}
			
			// get product version
			refCF = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDVersionNumberKey ) );
			if ( refCF ) {
				if ( !CFNumberGetValue( refCF, kCFNumberLongType, &inDevice->version ) ) {
					HIDReportError( "hu_GetDeviceInfo: CFNumberGetValue error retrieving inDevice->version." );
				}
			}
			
			// get manufacturer name
			refCF = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDManufacturerKey ) );
			if ( !refCF ) {
				refCF = CFDictionaryGetValue( usbProperties, CFSTR( "USB Vendor Name" ) );
			}
			if ( refCF ) {
				if ( !CFStringGetCString( refCF, inDevice->manufacturer, 256, CFStringGetSystemEncoding() ) ) {
					HIDReportError( "hu_GetDeviceInfo: CFStringGetCString error retrieving inDevice->manufacturer." );
				}
				hu_CleanString( inDevice->manufacturer );
			}
			
			// get product name
			refCF = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDProductKey ) );
			if ( !refCF ) {
				refCF = CFDictionaryGetValue( usbProperties, CFSTR( "USB Product Name" ) );
			}
			if ( refCF ) {
				if ( !CFStringGetCString( refCF, inDevice->product, 256, CFStringGetSystemEncoding() ) ) {
					HIDReportError( "hu_GetDeviceInfo: CFStringGetCString error retrieving inDevice->product." );
				}
				hu_CleanString( inDevice->product );
			}
			
			// get serial
			refCF = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDSerialNumberKey ) );
			if ( refCF ) {
				if ( !CFStringGetCString( refCF, inDevice->serial, 256, CFStringGetSystemEncoding() ) ) {
					HIDReportError( "hu_GetDeviceInfo: CFStringGetCString error retrieving inDevice->serial." );
				}
				hu_CleanString( inDevice->serial );
			}
			
			// get location ID
			refCF = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDLocationIDKey ) );
			if ( !refCF ) {
				refCF = CFDictionaryGetValue( usbProperties, CFSTR( "locationID" ) );
			}
			if ( refCF ) {
				if ( !CFNumberGetValue( refCF, kCFNumberLongType, &inDevice->locID ) ) {
					HIDReportError( "hu_GetDeviceInfo: CFNumberGetValue error retrieving inDevice->locID." );
				}
			}
			
			// get usage page and usage
			refCF = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDPrimaryUsagePageKey ) );
			if ( refCF ) {
				if ( !CFNumberGetValue( refCF, kCFNumberLongType, &inDevice->usagePage ) ) {
					HIDReportError( "hu_GetDeviceInfo: CFNumberGetValue error retrieving inDevice->usagePage." );
				}
				refCF = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDPrimaryUsageKey ) );
				if ( refCF )
					if ( !CFNumberGetValue( refCF, kCFNumberLongType, &inDevice->usage ) ) {
						HIDReportError( "hu_GetDeviceInfo: CFNumberGetValue error retrieving inDevice->usage." );
					}
			}
				if ( !refCF ) { // get top level element HID usage page or usage
								// use top level element instead
					CFTypeRef refCFTopElement = 0;
					refCFTopElement = CFDictionaryGetValue( inDeviceCFDictionaryRef, CFSTR( kIOHIDElementKey ) );
					{
						// refCFTopElement points to an array of element dictionaries
						CFRange range = {0, CFArrayGetCount( refCFTopElement )};
						CFArrayApplyFunction( refCFTopElement, range, hu_TopLevelElementHandler, NULL );
					}
				}
		} else {
			HIDReportError( "hu_GetDeviceInfo: IORegistryEntryCreateCFProperties failed to create usbProperties." );
		}

		CFRelease( usbProperties );
		if ( kIOReturnSuccess != IOObjectRelease( parent2 ) ) {
			HIDReportError( "hu_GetDeviceInfo: IOObjectRelease error with parent2." );
		}
		if ( kIOReturnSuccess != IOObjectRelease( parent1 ) ) {
			HIDReportError( "hu_GetDeviceInfo: IOObjectRelease error with parent1." );
		}
	}
}

/*************************************************************************
*
* hu_AddDevice( inDeviceListHead, inNewDevice )
*
* Purpose:  adds device to linked list of devices passed in
*
* Notes:	handles NULL lists properly
*
* Inputs:   inDeviceListHead - the head of the device list
*			inNewDevice		- the new device
*
* Returns:  hu_device_t **	- address where it was added to list
*/

static hu_device_t **hu_AddDevice( hu_device_t **inDeviceListHead, hu_device_t * inNewDevice )
{
	hu_device_t **result = NULL;

	if ( !*inDeviceListHead ) {
		result = inDeviceListHead;
	} else {
		hu_device_t *previousDevice = NULL, *tDevice = *inDeviceListHead;
		while ( tDevice ) {
			previousDevice = tDevice;
			tDevice = previousDevice->pNext;
		}
		result = &previousDevice->pNext;
	}
	inNewDevice->pNext = NULL;

	*result = inNewDevice;
	return result;
}

/*************************************************************************
*
* hu_MoveDevice( inDeviceListHead, inNewDevice, inOldListDeviceHead )
*
* Purpose:  moves a device from one list to another
*
* Notes:	handles NULL lists properly
*
* Inputs:   inDeviceListHead - the head of the( new ) device list
*			inNewDevice		- the device
*			inOldListDeviceHead  - the head of the old device list
*
* Returns:  hu_device_t *	- next device in old list( for properly iterating )
*/

static hu_device_t * hu_MoveDevice( hu_device_t **inDeviceListHead, hu_device_t * inNewDevice, hu_device_t **inOldListDeviceHead )
{
	hu_device_t * tDeviceNext = NULL;
	if ( !inNewDevice || !inOldListDeviceHead || !inDeviceListHead ) { // handle NULL pointers
		HIDReportError( "hu_MoveDevice: NULL input error." );
		return tDeviceNext;
	}

	// remove from old
	if ( inNewDevice == *inOldListDeviceHead ) { // replacing head
		*inOldListDeviceHead = inNewDevice->pNext;
		tDeviceNext = *inOldListDeviceHead;
	} else {
		hu_device_t *previousDevice = NULL, *tDevice = *inOldListDeviceHead;
		while ( tDevice && ( tDevice != inNewDevice ) ) { // step through list until match or end
			previousDevice = tDevice;
			tDevice = previousDevice->pNext;
		}
		if ( tDevice == inNewDevice ) { // if there was a match
			previousDevice->pNext = tDevice->pNext; // skip this device
			tDeviceNext = tDevice->pNext;
		} else {
			HIDReportError( "hu_MoveDevice: device not found when moving." );
		}
	}

	// add to new list
	hu_AddDevice( inDeviceListHead, inNewDevice );
	return tDeviceNext; // return next device
}

/*************************************************************************
*
* hu_BuildDevice( inHIDDevice )
*
* Purpose:  given a IO device object build a flat device record including device info and all elements
*
* Notes:	handles NULL lists properly
*
* Inputs:   inHIDDevice		- the I/O device object
*
* Returns:  hu_device_t *	- the address of the new device record
*/

static hu_device_t * hu_BuildDevice( io_object_t inHIDDevice )
{ //CHEAT! I don't want to move lines for this case
#line 1856
	hu_device_t * tDevice = ( hu_device_t * ) Alloc_Z( sizeof( hu_device_t ) );

	if ( tDevice ) {
		// clear our device struct
		bzero( tDevice, sizeof( hu_device_t ) );

		// get dictionary for the device properties
		CFMutableDictionaryRef deviceCFDictRef = 0;
		kern_return_t result = IORegistryEntryCreateCFProperties( inHIDDevice, &deviceCFDictRef, kCFAllocatorDefault, kNilOptions );

		if ( ( KERN_SUCCESS == result ) && deviceCFDictRef ) {
			// create device interface
			result = HIDCreateOpenDeviceInterface( inHIDDevice, tDevice );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nhu_BuildDevice: HIDCreateOpenDeviceInterface failed.", result );
			}

			// extract all the device info from the device dictionary into our device struct
			//( inHIDDevice is used to find parents in registry tree )
			hu_GetDeviceInfo( inHIDDevice, deviceCFDictRef, tDevice );

			// set current device for use in getting elements
			gCurrentDevice = tDevice;

			// Add all elements
			hu_element_t * currentElement = NULL;
			hu_GetCollectionElements( deviceCFDictRef, &currentElement );

			gCurrentDevice = NULL;
			CFRelease( deviceCFDictRef );
		} else {
			HIDReportErrorNum( "\nhu_BuildDevice: IORegistryEntryCreateCFProperties error when creating deviceProperties.", result );
		}
	} else {
		HIDReportError( "malloc error when allocating hu_device_t *." );
	}
	return tDevice;
}

/*************************************************************************
*
* hu_CreateSingleTypeDeviceList( inHIDObjectIterator )
*
* Purpose:  build flat linked list of devices from hid object iterator
*
* Notes:	Only called by hu_CreateMultiTypeDeviceList
*
* Inputs:   inHIDObjectIterator	- the HID object iterator
*
* Returns:  hu_device_t *		- the address of the new device list head
*/

static hu_device_t * hu_CreateSingleTypeDeviceList( io_iterator_t inHIDObjectIterator )
{
	hu_device_t * deviceListHead = NULL;

	hu_AddDevices( &deviceListHead, inHIDObjectIterator );
	return deviceListHead;
}

/*************************************************************************
*
* hu_CreateMultiTypeDeviceList( inUsagePages, inUsages, inNumDeviceTypes )
*
* Purpose:  build flat linked list of devices from list of usages and usagePages
*
* Notes:	Only called by HIDBuildMultiDeviceList & HIDUpdateDeviceList
*
* Inputs:   inUsagePages		- inNumDeviceTypes sized array of matching usage pages
*			inUsages			- inNumDeviceTypes sized array of matching usages
*			inNumDeviceTypes - number of usage pages & usages
*
* Returns:  hu_device_t *		- the address of the new device list head
*/

static hu_device_t * hu_CreateMultiTypeDeviceList( const UInt32 *inUsagePages, const UInt32 *inUsages, int inNumDeviceTypes )
{
	io_iterator_t hidObjectIterator = 0;
	hu_device_t * newDeviceList = NULL; // build new list
	int i;

	if ( !inUsages || !inUsagePages || !inNumDeviceTypes ) {
		HIDReportError( "hu_CreateMultiTypeDeviceList: NULL inUsages, inUsagePages or inNumDeviceTypes." );
	} else {
		for ( i = 0; i != inNumDeviceTypes; i++ ) {	// for all usage and usage page types
			hu_device_t * deviceList = NULL;
			CFMutableDictionaryRef hidMatchingCFDictRef;
			IOReturn result = kIOReturnSuccess;	// assume success( optimist! )

			// Set up matching dictionary to search the I/O Registry for HID devices we are interested in. Dictionary reference is NULL if error.
			hidMatchingCFDictRef = hu_SetUpMatchingDictionary( inUsagePages[i], inUsages[i] );
			if ( !hidMatchingCFDictRef ) {
				HIDReportError( "hu_SetUpMatchingDictionary: Couldn't create a matching dictionary." );
			}

			// BUG FIX! one reference is consumed by IOServiceGetMatchingServices
			CFRetain( hidMatchingCFDictRef );

			// create an IO object iterator
			result = IOServiceGetMatchingServices( kIOMasterPortDefault, hidMatchingCFDictRef, &hidObjectIterator );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nhu_CreateMultiTypeDeviceList: Failed to create IO object iterator, error:", result );
			} else if ( !hidObjectIterator ) { // likely no HID devices which matched selection criteria are connected
				HIDReportError( "hu_CreateMultiTypeDeviceList: Could not find any matching devices, thus iterator creation failed." );
			}

			if ( hidObjectIterator ) {
#if USE_HOTPLUGGING
				CFRunLoopSourceRef		runLoopSource;
				IOReturn result = kIOReturnSuccess;	// assume success( optimist! )

				// Create a notification port and add its run loop event source to our run loop
				// This is how async notifications get set up.

				gNotifyPort = IONotificationPortCreate( kIOMasterPortDefault );
				runLoopSource = IONotificationPortGetRunLoopSource( gNotifyPort );

				gRunLoop = CFRunLoopGetCurrent( );
				CFRunLoopAddSource( gRunLoop, runLoopSource, kCFRunLoopDefaultMode );

				// BUG FIX! one reference is consumed by IOServiceAddMatchingNotification
				CFRetain( hidMatchingCFDictRef );

				// Now set up a notification to be called when a device is first matched by I/O Kit.
				result = IOServiceAddMatchingNotification( gNotifyPort, kIOFirstMatchNotification, hidMatchingCFDictRef,
														  hu_IOServiceMatchingNotification, 	// callback
														  &gDeviceList, &hidObjectIterator );
#endif USE_HOTPLUGGING
				// add all existing devices
				deviceList = hu_CreateSingleTypeDeviceList( hidObjectIterator ); // build device list

			}
			if ( deviceList ) // if there are devices to merge
				hu_MergeDeviceList( &newDeviceList, &deviceList ); // merge into new list
			while ( deviceList ) // dump what is left of source list
				deviceList = hu_DisposeDevice( deviceList ); // dispose current device & return next device, will set deviceList to NULL

			// BUG FIX! we weren't releasing this
			CFRelease( hidMatchingCFDictRef );
		}
	}
	return newDeviceList;
}

/*************************************************************************
*
* hu_FindDeviceInList( inDeviceList, inFindDevice )
*
* Purpose:  given a device list and a device find if device is in list
*
* Notes:	called by hu_CompareUpdateDeviceList & hu_MergeDeviceList
*
* Inputs:   inDeviceList - the device list
*			inFindDevice - the device
*
* Returns:  Boolean		- TRUE if device in list
*/

static Boolean hu_FindDeviceInList( hu_device_t * inDeviceList, hu_device_t * inFindDevice )
{
	Boolean found = FALSE; // not found
	hu_device_t * tDevice = inDeviceList; // not really needed but is clearer this way
	while ( tDevice && !found ) {	// while we still have device to look at and have not found the target device
		if ( ( tDevice->vendorID == inFindDevice->vendorID ) && // if we match same vendor, product & location
			 ( tDevice->productID == inFindDevice->productID ) && // this is not quite right for same tyes plugged into the same location but different physical devices
			 ( tDevice->locID == inFindDevice->locID ) &&      // since this is a corner and impossible to detect without serial numbers case we will ignore it
			 ( tDevice->usage == inFindDevice->usage ) )
		{
			found = TRUE; // found device
		}
		tDevice = tDevice->pNext; // step to next device
	}
	return found;
}

/*************************************************************************
*
* hu_CompareUpdateDeviceList( inDeviceListHead, inNewDeviceList )
*
* Purpose:  update main list with new device list and remove unplugged devices
*
* Notes:	startegy is to update based on location of device, if this changed then previous device was
*			at least unplugged and plugged in somewhere else, thus can't be considered the same
*
* Inputs:   inDeviceListHead - the old list
*			inNewDeviceList  - the new list
*
* Returns:  Boolean		- TRUE if any changes
*/

static Boolean hu_CompareUpdateDeviceList( hu_device_t **inDeviceListHead, hu_device_t **inNewDeviceList )
{
	hu_device_t * tDevice = *inDeviceListHead;
	Boolean changedList = FALSE;

	while ( tDevice ) {	// for all the devices in main list
		Boolean present = FALSE;
		// ensure they are in new list
		present = hu_FindDeviceInList( *inNewDeviceList, tDevice );
		// remove those that are not
		if ( !present ) {
			changedList = TRUE;
			if ( tDevice == *inDeviceListHead ) // if we are removing the list head
				*inDeviceListHead = tDevice->pNext; // move list head
			tDevice = hu_DisposeDevice( tDevice ); // remove device from list and dispose device and step to next device
		} else {
			tDevice = tDevice->pNext; // step to next device
		}
	}
	tDevice = *inNewDeviceList;
	while ( tDevice ) { // for all the devices in new list
		Boolean present = FALSE;
		present = hu_FindDeviceInList( *inDeviceListHead, tDevice ); // ensure they are in original list
		if ( !present ) { // not found in old list so move to old list from new
			changedList = TRUE;
			tDevice = hu_MoveDevice( inDeviceListHead, tDevice, inNewDeviceList ); // move those that are not
		} else { // found
			tDevice = tDevice->pNext; // just step to next device
		}
	}
	return changedList;
}

/*************************************************************************
*
* hu_MergeDeviceList( inNewDeviceList, inDeviceList )
*
* Purpose:  merges two devicelist into single *inNewDeviceList
*
* Notes:	inNewDeviceList may have head device modified( such as if it is NULL ) thus pointer to pointer to device.
*			devices are matched on vendorID, productID, locID by hu_FindDeviceInList.
*			device record in inNewDeviceList maintained.
*
* Inputs:   inNewDeviceList  - the new list
*			inDeviceList		- the device list to add
*
* Returns:  nothing
*/

static void hu_MergeDeviceList( hu_device_t **inNewDeviceList, hu_device_t **inDeviceList )
{
	hu_device_t * tDevice = *inDeviceList;
	while ( tDevice ) { // for all the devices in old list
		Boolean present = hu_FindDeviceInList( *inNewDeviceList, tDevice ); // ensure they are in new list
		if ( !present ) { // not found in new list
			tDevice = hu_MoveDevice( inNewDeviceList, tDevice, inDeviceList ); // move to new list and get next
		} else { // found in new list( so don't do anything
			tDevice = tDevice->pNext; // just step to next device
		}
	}
}

#if USE_NOTIFICATIONS
/*************************************************************************
*
* hu_DeviceNotification( inRefCon, inService, inMessageType, inMessageArgument )
*
* Purpose:  callback for kIOGeneralInterest notifications
*
* Notes:	notification installed( IOServiceAddInterestNotification ) in hu_AddDevices
*			This routine will get called whenever any kIOGeneralInterest notification happens. We are
*			interested in the kIOMessageServiceIsTerminated message so that's what we look for. Other
*			messages are defined in IOMessage.h.
*
* Inputs:   inRefCon			- refcon passed when the notification was installed.
*			inService			- IOService whose state has changed.
*			inMessageType		- A inMessageType enum, defined by IOKit/IOMessage.h or by the IOService's family.
*			inMessageArgument - An argument for the message, dependent on the inMessageType.
*
* Returns:  nothing
*/

static void hu_DeviceNotification( void *inRefCon, io_service_t inService, natural_t inMessageType, void *inMessageArgument )
{
	hu_device_t * tDevice = ( hu_device_t * ) inRefCon;

	if ( kIOMessageServiceIsTerminated == inMessageType ) {
		printf( "Device 0x%08x \"%s\"removed.\n", inService, tDevice->product );

		// Free the data we're no longer using now that the device is going away
		hu_DisposeDevice( tDevice );
	}
}
#else
/*************************************************************************
*
* hu_RemovalCallbackFunction( void* target, IOReturn inResult, void* inRefCon, void* inSender )
*
* Purpose:  callback for device removal notifications
*
* Notes:	removal notification installed( setRemovalCallback ) in hu_AddDevices
*			This routine will get called whenever a device is removed( unplugged ).
*
* Inputs:   target			- pointer to your data, often a pointer to an object.
*			inResult		- Completion result of desired operation.
*			inRefCon		- pointer to more data.
*			inSender		- Interface instance sending the completion routine.
*
* Returns:  nothing
*/

static void hu_RemovalCallbackFunction( void* target, IOReturn inResult, void* inRefCon, void* inSender )
{
	hu_DisposeDevice( ( hu_device_t * ) target );
}

#endif USE_NOTIFICATIONS

/*************************************************************************
*
* hu_AddDevices( inDeviceListHead, inIODeviceIterator )
*
* Purpose:  given a IO device iterator, iterate it and for each device object do:
*			1. Create some private data to relate to each device.
*			2. Submit an IOServiceAddInterestNotification of type kIOGeneralInterest for this device,
*			using the refCon field to store a pointer to our data. When we get called with
*			this interest notification, we can grab the refCon and access our private data.
*
* Inputs:   inDeviceListHead		- the address of our device list
*			inIODeviceIterator   - IO device iterator
*
* Returns:  nothing
*/

static void hu_AddDevices( hu_device_t **inDeviceListHead, io_iterator_t inIODeviceIterator )
{
	IOReturn result = kIOReturnSuccess;	// assume success( optimist! )
	io_object_t ioHIDDeviceObject = 0;

	while ( 0 != ( ioHIDDeviceObject = IOIteratorNext( inIODeviceIterator ) ) ) {
		hu_device_t **newDeviceAt = nil;
		hu_device_t * newDevice = hu_BuildDevice( ioHIDDeviceObject );
		if ( newDevice ) {
#if LOG_DEVICES
#if 0	// set TRUE for verbose output
			printf( "\nhu_AddDevices: newDevice = {t: \"%s\", v: %ld, p: %ld, v: %ld, m: \"%s\", " \
				   "p: \"%s\", l: %ld, u: %4.4lX:%4.4lX, #e: %ld, #f: %ld, #i: %ld, #o: %ld, " \
				   "#c: %ld, #a: %ld, #b: %ld, #h: %ld, #s: %ld, #d: %ld, #w: %ld}.",
				   newDevice->transport,
				   newDevice->vendorID,
				   newDevice->productID,
				   newDevice->version,
				   newDevice->manufacturer,
				   newDevice->product,
				   newDevice->locID,
				   newDevice->usagePage,
				   newDevice->usage,
				   newDevice->totalElements,
				   newDevice->features,
				   newDevice->inputs,
				   newDevice->outputs,
				   newDevice->collections,
				   newDevice->axis,
				   newDevice->buttons,
				   newDevice->hats,
				   newDevice->sliders,
				   newDevice->dials,
				   newDevice->wheels
				 );
			fflush( stdout );
#else	// otherwise output brief description
			printf( "\nhu_AddDevices: newDevice = {m: \"%s\" p: \"%s\", vid: %ld, pid: %ld, loc: %08lX, usage: %4.4lX:%4.4lX}.",
				   newDevice->manufacturer,
				   newDevice->product,
				   newDevice->vendorID,
				   newDevice->productID,
				   newDevice->locID,
				   newDevice->usagePage,
				   newDevice->usage
				 );
			fflush( stdout );
#endif
#endif LOG_DEVICES
			newDeviceAt = hu_AddDevice( inDeviceListHead, newDevice );

#if USE_NOTIFICATIONS
			// Register for an interest notification of this device being removed. Use a reference to our
			// private data as the refCon which will be passed to the notification callback.
			result = IOServiceAddInterestNotification( gNotifyPort, 				// notifyPort
													  ioHIDDeviceObject, 		// service
													  kIOGeneralInterest, 		// interestType
													  hu_DeviceNotification, 	// callback
													  newDevice, 				// refCon
													  ( io_object_t* ) &newDevice->notification );	// notification
			if ( KERN_SUCCESS != result ) {
				HIDReportErrorNum( "\nhu_AddDevices: IOServiceAddInterestNotification error: x0%08lX.", result );
			}
#else
			result = ( *( IOHIDDeviceInterface** )newDevice->interface )->setRemovalCallback( newDevice->interface, hu_RemovalCallbackFunction, newDeviceAt, 0 );
#endif USE_NOTIFICATIONS
		}

		// release the device object, it is no longer needed
		result = IOObjectRelease( ioHIDDeviceObject );
		if ( KERN_SUCCESS != result ) {
			HIDReportErrorNum( "\nhu_AddDevices: IOObjectRelease error with ioHIDDeviceObject.", result );
		}
	}
}

#if USE_HOTPLUGGING
/*************************************************************************
*
* hu_IOServiceMatchingNotification( inRefCon, inIODeviceIterator )
*
* Purpose:  This routine is the callback for our IOServiceAddMatchingNotification in hu_CreateMultiTypeDeviceList.
*
* Inputs:   inDeviceListHead		- the address of our device list
*			inIODeviceIterator   - IO device iterator
*
* Returns:  nothing
*/

static void hu_IOServiceMatchingNotification( void *inRefCon, io_iterator_t inIODeviceIterator )
{
	OSStatus status = noErr;
	if ( gHotPlugCallbackProcPtr ) {
		status = gHotPlugCallbackProcPtr( inIODeviceIterator );
	}
	if ( noErr == status ) {
		hu_AddDevices( ( hu_device_t ** ) inRefCon, inIODeviceIterator );
	}
}
#endif USE_HOTPLUGGING

/*************************************************************************
*
* hu_SetUpMatchingDictionary( inUsagePage, inUsage )
*
* Purpose:  builds a matching dictionary based on usage page and usage
*
* Notes:	Only called by hu_CreateMultiTypeDeviceList
*
* Inputs:   inUsagePage				- usage page
*			inUsage					- usages
*
* Returns:  CFMutableDictionaryRef  - the matching dictionary
*/

static CFMutableDictionaryRef hu_SetUpMatchingDictionary( UInt32 inUsagePage, UInt32 inUsage )
{
	CFNumberRef refUsage = NULL, refUsagePage = NULL;
	CFMutableDictionaryRef refHIDMatchDictionary = NULL;

	// Set up a matching dictionary to search I/O Registry by class name for all HID class devices.
	refHIDMatchDictionary = IOServiceMatching( kIOHIDDeviceKey );
	if ( refHIDMatchDictionary ) {
		if ( inUsagePage ) {
			// Add key for device type( joystick, in this case ) to refine the matching dictionary.
			refUsagePage = CFNumberCreate( kCFAllocatorDefault, kCFNumberIntType, &inUsagePage );
			CFDictionarySetValue( refHIDMatchDictionary, CFSTR( kIOHIDPrimaryUsagePageKey ), refUsagePage );
			CFRelease( refUsagePage );

			// note: the usage is only valid if the usage page is also defined
			if ( inUsage ) {
				refUsage = CFNumberCreate( kCFAllocatorDefault, kCFNumberIntType, &inUsage );
				CFDictionarySetValue( refHIDMatchDictionary, CFSTR( kIOHIDPrimaryUsageKey ), refUsage );
				CFRelease( refUsage );
			}
		}
	} else if ( !refHIDMatchDictionary ) {
		HIDReportError( "hu_SetUpMatchingDictionary: Failed to get HID CFMutableDictionaryRef via IOServiceMatching." );
	}
	return refHIDMatchDictionary;
}

/*************************************************************************
*
* hu_DisposeDeviceElements( inElement )
*
* Purpose:  disposes of the element list associated with a device and the memory associated with the list
*
* Notes:	uses recursion to dispose both children and siblings.
*
* Inputs:   inElement	- the element
*
* Returns:  nothing
*/

static void hu_DisposeDeviceElements( hu_element_t * inElement )
{
	if ( inElement ) {
		hu_DisposeDeviceElements( inElement->pChild );
		hu_DisposeDeviceElements( inElement->pSibling );
		Z_Free( inElement );
	}
}

/*************************************************************************
*
* hu_DisposeDevice( inDevice )
*
* Purpose:  disposes of a single device,
*
* Notes:	closes and releases the device interface,
*			frees memory for the device and all its elements
*			sets device pointer to NULL
*			all your device no longer belong to us...
*			... you do not 'own' the device anymore.
*
* Inputs:   inDevice			- the device
*
* Returns:  hu_device_t *	- pointer to next device
*/

static hu_device_t * hu_DisposeDevice( hu_device_t * inDevice )
{
	kern_return_t result = KERN_SUCCESS;	// assume success( optimist! )
	hu_device_t * tDeviceNext = NULL;

	if ( HIDIsValidDevice( inDevice ) ) {
		// save next device prior to disposing of this device
		tDeviceNext = inDevice->pNext;

		result = HIDDequeueDevice( inDevice );
#if 0		// ignore these errors
		if ( kIOReturnSuccess != result ) {
			HIDReportErrorNum( "\nhu_DisposeDevice: HIDDequeueDevice error: 0x%08lX.", result );
		}
#endif

		hu_DisposeDeviceElements( inDevice->pListElements );
		inDevice->pListElements = NULL;

		result = HIDCloseReleaseInterface( inDevice ); // function sanity checks interface value( now application does not own device )
		if ( kIOReturnSuccess != result ) {
			HIDReportErrorNum( "\nhu_DisposeDevice: HIDCloseReleaseInterface error: 0x%08lX.", result );
		}

#if USE_NOTIFICATIONS
		if ( inDevice->interface ) {
			// NOT( *inDevice->interface )->Release( inDevice->interface );
			result = IODestroyPlugInInterface( ( IOCFPlugInInterface ** ) inDevice->interface );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nhu_DisposeDevice: IODestroyPlugInInterface error: 0x%08lX.", result );
			}
		}

		if ( inDevice->notification ) {
			result = IOObjectRelease( ( io_object_t ) inDevice->notification );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nhu_DisposeDevice: IOObjectRelease error: 0x%08lX.", result );
			}
		}
#endif USE_NOTIFICATIONS

		// remove this device from the device list
		if ( gDeviceList == inDevice ) {	// head of list?
			gDeviceList = tDeviceNext;
		} else {
			hu_device_t * tDeviceTemp = tDeviceNext = gDeviceList;	// we're going to return this if we don't find ourselfs in the list
			while ( tDeviceTemp ) {
				if ( tDeviceTemp->pNext == inDevice ) { // found us!
					// take us out of linked list
					tDeviceTemp->pNext = tDeviceNext = inDevice->pNext;
					break;
				}
				tDeviceTemp = tDeviceTemp->pNext;
			}
		}
		Z_Free( inDevice );
	}

	// update device count
	gNumDevices = hu_CountCurrentDevices( );
	return tDeviceNext;
}

/*************************************************************************
*
* hu_CountCurrentDevices( void )
*
* Purpose:  count number of devices in global device list( gDeviceList )
*
* Inputs:   none
*
* Returns:  unsigned long  - the count
*/

static int hu_CountCurrentDevices( void )
{
	hu_device_t * tDevice = gDeviceList;
	int count = 0;
	while ( tDevice ) {
		count++;
		tDevice = tDevice->pNext;
	}
	return count;
}

/*************************************************************************
*
* hu_MatchElementTypeMask( inIOHIDElementType, inTypeMask )
*
* Purpose:  matches type masks passed in to actual element types( which are not set up to be used as a mask )
*
* Inputs:   inIOHIDElementType   - the element type
*			inTypeMask			- the element type mask
*
* Returns:  Boolean				- TRUE if they match
*/

static Boolean hu_MatchElementTypeMask( IOHIDElementType inIOHIDElementType, HIDElementTypeMask inTypeMask )
{
	Boolean result = FALSE;	// assume failure ( pessimist! )
	if ( inTypeMask & kHIDElementTypeInput ) {
		if ( 	( kIOHIDElementTypeInput_Misc == inIOHIDElementType ) ||
				( kIOHIDElementTypeInput_Button == inIOHIDElementType ) ||
				( kIOHIDElementTypeInput_Axis == inIOHIDElementType ) ||
				( kIOHIDElementTypeInput_ScanCodes == inIOHIDElementType ) )
		{
			result = TRUE;
		}
	}

	if ( inTypeMask & kHIDElementTypeOutput ) {
		if ( kIOHIDElementTypeOutput == inIOHIDElementType ) {
			result = TRUE;
		}
	}

	if ( inTypeMask & kHIDElementTypeFeature ) {
		if ( kIOHIDElementTypeFeature == inIOHIDElementType ) {
			result = TRUE;
		}
	}

	if ( inTypeMask & kHIDElementTypeCollection ) {
		if ( kIOHIDElementTypeCollection == inIOHIDElementType ) {
			result = TRUE;
		}
	}
	return result;
}

/*************************************************************************
*
* hu_GetDeviceElement( inElement, inTypeMask )
*
* Purpose:  resurcively search for element of type( mask )
*
* Notes:	called( multiple times ) by HIDGetNextDeviceElement
*
* Inputs:   inElement			- the current element
*			inTypeMask			- the element type mask
*
* Returns:  hu_element_t		- the element of type( mask )
*/
static hu_element_t * hu_GetDeviceElement( hu_element_t * inElement, HIDElementTypeMask inTypeMask )
{
	hu_element_t * result = inElement;	// return the element passed in...
	if ( inElement ) {
		// unless it's doesn't match the type we're looking for
		if ( !hu_MatchElementTypeMask( inElement->type, inTypeMask ) ) {
			// in which case we return the next one
			result = HIDGetNextDeviceElement( inElement, inTypeMask );
		}
	}
	return result;
}

