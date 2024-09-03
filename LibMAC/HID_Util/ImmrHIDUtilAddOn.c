/*
 *  ImmrHIDUtilAddOn.c
 *  UseFFAPIFromHIDUtilities
 *
 *  Created by rlacroix on Wed Oct 16 2002.
 *  Copyright( c ) 2002 Immersion Corporation. All rights reserved.
 *
 */

#include <mach/mach.h>
#include <mach/mach_error.h>

#include <IOKit/IOKitLib.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/hid/IOHIDLib.h>
#include <IOKit/hid/IOHIDUsageTables.h>

#include "HID_Utilities_External.h"
#include "ImmrHIDUtilAddOn.h"

//---------------------------------------------------------------------------------
//
// AllocateHIDObjectFromRecDevice( )
//
//	returns:
//		NULL, or acceptable io_object_t
//
//---------------------------------------------------------------------------------
io_service_t AllocateHIDObjectFromRecDevice( hu_device_t * inDevice )
{
	io_service_t			tHIDObject		= 0;

	// Set up the matching criteria for the devices we're interested in.
	// We are interested in instances of class IOHIDDevice.
	// matchingDict is consumed below( in IOServiceGetMatchingService )
	// so we have no leak here.
	CFMutableDictionaryRef	matchingDict = IOServiceMatching( kIOHIDDeviceKey );
	if ( matchingDict ) {
		// Add a key for locationID to our matching dictionary.  This works for matching to
		// IOHIDDevices, so we will only look for a device attached to that particular port
		// on the machine.
		CFNumberRef refUsage = CFNumberCreate( kCFAllocatorDefault, kCFNumberSInt32Type, &inDevice->locID );
		CFDictionaryAddValue( matchingDict, CFSTR( kIOHIDLocationIDKey ), refUsage );
		CFRelease( refUsage );
		
		// IOServiceGetMatchingService assumes that we already know that there is only one device
		// that matches.  This way we don't have to do the whole iteration dance to look at each
		// device that matches.  This is a new API in 10.2
		tHIDObject = IOServiceGetMatchingService( kIOMasterPortDefault, matchingDict );
		// Note: We're not leaking the matchingDict.
		// One reference is consumed by IOServiceGetMatchingServices
	}
	return tHIDObject;
}

//---------------------------------------------------------------------------------
//
// FreeHIDObject( )
//
//---------------------------------------------------------------------------------
bool FreeHIDObject( io_service_t pHIDObject )
{
	kern_return_t			kr;

	kr = IOObjectRelease( pHIDObject );

	return( kIOReturnSuccess == kr );
}
