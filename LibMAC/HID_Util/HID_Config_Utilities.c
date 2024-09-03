/*
*	File:		HID_Config_Utilities.c
*
*	Contains: 	Implementation of the HID configuration utilities for the HID utilities.
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
#pragma mark - includes & imports
/*****************************************************/
#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>

#include <stdlib.h> // malloc
#include <time.h> // clock

#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDUsageTables.h>

#if 0   // NOTE: These are now in <IOKit/hid/IOHIDUsageTables.h>
#include "PID.h"
#include "IOHIDPowerUsage.h"
#endif

#include "HID_Utilities_Internal.h"
#include "HID_Utilities_External.h"
/*****************************************************/
#pragma mark - typedefs, enums, defines, etc.
/*****************************************************/
#pragma mark - local ( static ) function prototypes
/*****************************************************/
#pragma mark - exported globals
/*****************************************************/
#pragma mark - local ( static ) globals
/*****************************************************/
#pragma mark - exported function implementations
/*****************************************************/

/*************************************************************************
 *
 * HIDConfigureSingleDeviceAction( inDevice, outElement, inTimeout )
 *
 * Purpose:	polls single device's elements for a change greater than kPercentMove.  
 *			Times out after given time
 *			returns TRUE and pointer to element if found
 *			returns FALSE and NULL for pointer to element if not found
 *
 * Inputs:  inDevice	- the device to poll
 *			outElement	- address where to store the found element
 *			inTimeout	- the timeout
 *
 * Returns: Boolean		- if successful
 *			outElement	- the element
 */

Boolean HIDConfigureSingleDeviceAction( const hu_device_t * inDevice, hu_element_t **outElement, float inTimeout )
{
	if ( ! inDevice ) {
		return 0;
	}
	if ( 0 == HIDHaveDeviceList( ) ) {   // if we do not have a device list
		return 0;
	}

	if ( outElement ) {
		*outElement = NULL;
	}

	clock_t start = clock ( );
	
	// build list of device and elements to save current values
	int maxElements = HIDCountDeviceElements( inDevice, kHIDElementTypeIO );
	long * saveValueArray = ( long * ) calloc( sizeof ( long ), maxElements ); // 2D array to save values

	// store current values
	short elementNum = 0;
	hu_element_t * pElement = HIDGetFirstDeviceElement( inDevice, kHIDElementTypeIO );
	while ( pElement ) {
		saveValueArray[elementNum] = HIDGetElementValue( inDevice, pElement );
		pElement = HIDGetNextDeviceElement ( pElement, kHIDElementTypeIO ); 
		elementNum++;
	}
	
	// poll all devices and elements, compare current value to save +/- kPercentMove
	Boolean found = FALSE, done = FALSE;
	while ( !found &&  !done ) {
		// are we done?
		clock_t end = clock( );
		double secs = ( double )( end - start ) / CLOCKS_PER_SEC;
		if ( secs > inTimeout ) {
			done = TRUE;
		}
		elementNum = 0;
		pElement = HIDGetFirstDeviceElement ( inDevice, kHIDElementTypeIO );
		while ( pElement ) {
			long initialValue = saveValueArray[elementNum];
			long value = HIDGetElementValue ( inDevice, pElement );
			long delta = ( float )( pElement->max - pElement->min ) * kPercentMove * 0.01;
			if ( ( ( initialValue + delta ) < value ) || ( ( initialValue - delta ) > value ) ) {
				if ( outElement ) {
					*outElement = pElement;
				}
				found = TRUE;
				break;
			}
			pElement = HIDGetNextDeviceElement ( pElement, kHIDElementTypeIO ); 
			elementNum++;
		}
	}

	return found;
}

/*************************************************************************
*
* HIDConfigureAction( inDevice, outElement, inTimeout )
*
* Purpose:  polls all devices and elements for a change greater than kPercentMove.
*			Times out after given time returns 1 and pointer to device and element
*			if found; returns 0 and NULL for both parameters if not found
*
* Inputs:   outDevice	- address where to store the device
*			outElement	- address where to store the element
*			inTimeout	- the timeout
* Returns:  Boolean		- if successful
*			outDevice	- the device
*			outElement	- the element
*/

Boolean HIDConfigureAction( hu_device_t **outDevice, hu_element_t **outElement, float inTimeout )
{
	if ( !HIDHaveDeviceList( ) ) // if we do not have a device list
		if ( 0 == HIDBuildDeviceList( kHIDPage_GenericDesktop, 0 ) ) // if we could not build another list ( use generic page )
			return 0; // return 0

	// build list of device and elements to save current values
	long numDevices = HIDCountDevices( ), maxElements = 0;

	hu_device_t * tDevice = HIDGetFirstDevice( );
	while ( tDevice ) {
		long numElements = HIDCountDeviceElements( tDevice, kHIDElementTypeInput );
		if ( numElements > maxElements )
			maxElements = numElements;
		tDevice = HIDGetNextDevice( tDevice );
	}
	long * saveValueArray = ( long * ) calloc( sizeof( long ), numDevices * maxElements ); // 2D array to save values

	// store current values
	short deviceNum = 0;
	tDevice = HIDGetFirstDevice( );
	hu_element_t * tElement = NULL;
	while ( tDevice ) {
		short elementNum = 0;
		tElement = HIDGetFirstDeviceElement( tDevice, kHIDElementTypeInput );
		while ( tElement ) {
			*( saveValueArray + ( deviceNum * maxElements ) + elementNum ) = HIDGetElementValue( tDevice, tElement );
			tElement = HIDGetNextDeviceElement( tElement, kHIDElementTypeInput );
			elementNum++;
		}
		tDevice = HIDGetNextDevice( tDevice );
		deviceNum++;
	}

	// poll all devices and elements, compare current value to save +/- kPercentMove
	Boolean found = FALSE, done = FALSE;
	clock_t start = clock( ), end;
	while ( ( !found ) && ( !done ) ) {
		double secs;
		// are we done?
		end = clock( );
		secs = ( double ) ( end - start ) / CLOCKS_PER_SEC;
		if ( secs > inTimeout )
			done = 1;
		deviceNum = 0;
		tDevice = HIDGetFirstDevice( );
		while ( tDevice ) {
			short elementNum = 0;
			tElement = HIDGetFirstDeviceElement( tDevice, kHIDElementTypeInput );
			while ( tElement ) {
				// ignore PID elements AND arrays
				if ( ( kHIDPage_PID != tElement->usagePage ) && ( -1 != tElement->usage ) ) {
					long initialValue = *( saveValueArray + ( deviceNum * maxElements ) + elementNum );
					long value = HIDGetElementValue( tDevice, tElement );
					long delta = ( float ) ( tElement->max - tElement->min ) * kPercentMove * 0.01f;

					if ( ( ( initialValue + delta ) < value ) || ( ( initialValue - delta ) > value ) ) {
						found = 1;
						break;
					}
				}
				tElement = HIDGetNextDeviceElement( tElement, kHIDElementTypeInput );
				elementNum++;
			}
			if ( found )
				break;
			tDevice = HIDGetNextDevice( tDevice );
			deviceNum++;
		}
	}

	// return device and element moved
	if ( found ) {
		*outDevice = tDevice;
		*outElement = tElement;
		return TRUE;
	} else {
		*outDevice = NULL;
		*outElement = NULL;
		return FALSE;
	}
}

/*************************************************************************
*
* HIDSaveElementConfig( inFILE, inDevice, inElement, inActionCookie )
*
* Purpose:  Save device & element config to file
*
* Notes:	assume file is open and at correct position.
*			will always write to file ( if file exists ) size of hu_SaveRec_t,
*			even if device and or element is bad.
*
* Inputs:   inFILE			- the file to write to
*			inDevice		- the device
*			inElement		- the element
*			inActionCookie	- the action cookie
* Returns:  nothing
*/

void HIDSaveElementConfig( FILE* inFILE, const hu_device_t * inDevice, const hu_element_t * inElement, long inActionCookie )
{
	hu_SaveRec_t saveRec;

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		HIDSetElementConfig( &saveRec, inDevice, inElement, inActionCookie );
		// write to file
		if ( inFILE )
			fwrite( ( void* ) &saveRec, sizeof( hu_SaveRec_t ), 1, inFILE );
	}
}

/*************************************************************************
*
* HIDRestoreElementConfig( inFILE, outDevice, outElement )
*
* Purpose:  restore device & element from to file
*
* Notes:	assume file is open and at correct position.
*
* Inputs:   inFILE			- the file to write to
*			outDevice		- address where to restore the device
*			outElement		- address where to restore the element
* Returns:  the action cookie
*			outDevice		- the device
*			outElement		- the element
*/

long HIDRestoreElementConfig( FILE* inFILE, hu_device_t **outDevice, hu_element_t **outElement )
{
	hu_SaveRec_t restoreRec;

	fread( ( void* ) &restoreRec, 1, sizeof( hu_SaveRec_t ), inFILE );
	return HIDGetElementConfig( &restoreRec, outDevice, outElement );
}

/*************************************************************************
*
* HIDSaveElementPref( inKeyCFStringRef, inAppCFStringRef, inDevice, inElement )
*
* Purpose:  Save the device & element values into the specified key in the specified applications preferences
*
* Notes:	assume file is open and at correct position.
*			will always write to file ( if file exists ) size of hu_SaveRec_t,
*			even if device and or element is bad.
*
* Inputs:   inKeyCFStringRef	- the preference key
*			inAppCFStringRef	- the application identifier
*			inDevice			- the device
*			inElement			- the element
* Returns:  Boolean				- if successful
*/

Boolean HIDSaveElementPref( const CFStringRef inKeyCFStringRef, CFStringRef inAppCFStringRef, const hu_device_t * inDevice, const hu_element_t * inElement )
{
	Boolean success = FALSE;

	if ( inKeyCFStringRef && inAppCFStringRef && HIDIsValidElement( inDevice, inElement ) ) {
		CFStringRef prefCFStringRef =
		CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "d:{v:%ld, p:%ld, l:%ld, p:%ld, u:%ld}, e:{t:%ld, p:%ld, u:%ld, c:%ld}" ),
								  inDevice->vendorID, inDevice->productID, inDevice->locID, inDevice->usagePage, inDevice->usage,
								  inElement->type, inElement->usagePage, inElement->usage, inElement->cookie );

		if ( prefCFStringRef ) {
			CFPreferencesSetAppValue( inKeyCFStringRef, prefCFStringRef, inAppCFStringRef );
			CFRelease( prefCFStringRef );
			success = TRUE;
		}
	}
	return success;
}

/*************************************************************************
*
* HIDRestoreElementPref( inKeyCFStringRef, inAppCFStringRef, outDevice, outElement )
*
* Purpose:  Find the specified preference in the specified application
*
* Notes:	assume file is open and at correct position.
*			will always write to file ( if file exists ) size of hu_SaveRec_t,
*			even if device and or element is bad.
*
* Inputs:   inKeyCFStringRef - the preference key
*			inAppCFStringRef - the application identifier
*			outDevice		- address where to restore the device
*			outElement		- address where to restore the element
* Returns:  Boolean			- if successful
*			outDevice		- the device
*			outElement		- the element
*/

Boolean HIDRestoreElementPref( CFStringRef inKeyCFStringRef, CFStringRef inAppCFStringRef, hu_device_t **outDevice, hu_element_t **outElement )
{
	Boolean found = FALSE;

	if ( inKeyCFStringRef && inAppCFStringRef && outDevice && outElement ) {
		CFPropertyListRef prefCFPropertyListRef = CFPreferencesCopyAppValue( inKeyCFStringRef, inAppCFStringRef );

		if ( prefCFPropertyListRef ) {
			if ( CFStringGetTypeID( ) == CFGetTypeID( prefCFPropertyListRef ) ) {
				char buffer[256];

				if ( CFStringGetCString( ( CFStringRef ) prefCFPropertyListRef, buffer, sizeof( buffer ), kCFStringEncodingASCII ) ) {
					hu_device_t	searchDevice;
					hu_element_t	searchElement;
					int count = sscanf( buffer, "d:{v:%ld, p:%ld, l:%ld, p:%ld, u:%ld}, e:{t:%ld, p:%ld, u:%ld, c:%ld}",
									   &searchDevice.vendorID, &searchDevice.productID, &searchDevice.locID, ( long int * ) &searchDevice.usagePage, ( long int * ) &searchDevice.usage,
									   ( long int * ) &searchElement.type, ( long int * ) &searchElement.usagePage, ( long int * ) &searchElement.usage,( long * ) &searchElement.cookie );

					if ( 9 == count ) {	// if we found all nine parameters…
						// and can find a device & element that matches these…
						if ( HIDFindActionDeviceAndElement( &searchDevice, &searchElement, outDevice, outElement ) ) {
							found = TRUE;
						}
					}
				}
			} else {
				// We found the entry with this key but it's the wrong type; delete it.
				CFPreferencesSetAppValue( inKeyCFStringRef, NULL, inAppCFStringRef );
				( void ) CFPreferencesAppSynchronize( inAppCFStringRef );
			}
			CFRelease( prefCFPropertyListRef );
		}
	}
	return found;
}


/*************************************************************************
*
* HIDSetElementConfig( inConfigRec, inDevice, inElement, inActionCookie )
*
* Purpose:  Set up a config record for saving
*
* Notes:	the save rec must be pre-allocated by the calling app and will be filled out
*
* Inputs:   inConfigRec		- the config record to restore from
*			inDevice			- the device
*			inElement		- the element
*			inActionCookie	- the action cookie
* Returns:  nothing
*
*/
void HIDSetElementConfig( hu_SaveRec_t* inConfigRec, const hu_device_t * inDevice, const hu_element_t * inElement, long inActionCookie )
{
	// clear rec
	bzero( inConfigRec, sizeof( hu_SaveRec_t ) );

	// must save:
	// inActionCookie
	inConfigRec->actionCookie = inActionCookie;

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		// Device: serial, vendorID, productID, location, inUsagePage, usage
		// need to add serial number when I have a test case
		inConfigRec->vendorID = inDevice->vendorID;
		inConfigRec->productID = inDevice->productID;
		inConfigRec->locID = inDevice->locID;
		inConfigRec->usage = inDevice->usage;
		inConfigRec->usagePage = inDevice->usagePage;

		// Element: cookie, inUsagePage, usage,
		inConfigRec->usagePageE = inElement->usagePage;
		inConfigRec->usageE = inElement->usage;
		inConfigRec->cookie = inElement->cookie;
	}
}

/*************************************************************************
*
* HIDGetElementConfig( inConfigRec, outDevice, outElement )
*
* Purpose:  restore device & element from a config record
*
* Notes:	assume file is open and at correct position.
*
* Inputs:   inConfigRec		- the config record to restore from
*			outDevice		- address where to restore the device
*			outElement		- address where to restore the element
* Returns:  the action cookie
*			outDevice		- the device
*			outElement		- the element
*/
long HIDGetElementConfig( hu_SaveRec_t* inConfigRec, hu_device_t **outDevice, hu_element_t **outElement )
{
	long result;
	hu_device_t searchDevice;
	hu_element_t searchElement;

	// Device: serial, vendorID, productID, location, inUsagePage, usage
	// need to add serial number when I have a test case
	searchDevice.vendorID = inConfigRec->vendorID;
	searchDevice.productID = inConfigRec->productID;
	searchDevice.locID = inConfigRec->locID;
	searchDevice.usage = inConfigRec->usage;
	searchDevice.usagePage = inConfigRec->usagePage;

	// Element: cookie, inUsagePage, usage,
	searchElement.usagePage = inConfigRec->usagePageE;
	searchElement.usage = inConfigRec->usageE;
	searchElement.cookie = inConfigRec->cookie;

	if ( HIDFindActionDeviceAndElement( &searchDevice, &searchElement, outDevice, outElement ) ) {
		result = ( long ) ( *outElement )->cookie;
	} else {
		result = inConfigRec->actionCookie;
	}
	return result;
}
