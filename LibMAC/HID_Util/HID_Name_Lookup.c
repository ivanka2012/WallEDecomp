/*
*	File:		HID_Name_Lookup.c
*
*	Contains:	Implementation of the HID device name lookup functions for the HID utilites.
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
/*****************************************************/
#pragma mark - includes & imports
/*****************************************************/
#include "HID_Utilities_Internal.h"
#include "HID_Name_Lookup.h"
/*****************************************************/
#pragma mark - typedefs, enums, defines, etc.
/*****************************************************/
#define FAKE_MISSING_NAMES		0	// for debugging; returns the vendor, product & cookie ( or usage info ) as numbers.
#define VERBOSE_ELEMENT_NAMES	0	// set TRUE to include vender & product names in element names ( useful for debugging )

#define kNameKeyCFStringRef CFSTR( "Name" )
/*****************************************************/
#pragma mark - local ( static ) function prototypes
/*****************************************************/

static SInt32 hu_SaveToXMLFile( CFPropertyListRef inCFPRef, CFURLRef inCFURLRef );
static SInt32 hu_XMLSave( CFPropertyListRef inCFPropertyListRef, CFStringRef inResourceName, CFStringRef inResourceExtension );

static CFPropertyListRef hu_LoadFromXMLFile( CFURLRef inCFURLRef );
static CFPropertyListRef hu_XMLLoad( CFStringRef inResourceName, CFStringRef inResourceExtension );

static Boolean hu_XMLSearchForElementNameByCookie( long inVendorID, long inProductID, long inCookie, char* outCStr );
static Boolean hu_XMLSearchForElementNameByUsage( long inVendorID, long inProductID, long inUsagePage, long inUsage, char* outCStr );

static Boolean hu_XMLSearchForVendorNameByVendorID( long inVendorID, char* outCStr );
static Boolean hu_XMLSearchForProductNameByVendorProductID( long inVendorID, long inProductID, char* outCStr );

static __attribute__((used)) Boolean hu_XMLGetUsageName( long inUsagePage, long inUsage, char* outCStr );

static Boolean hu_AddVendorProductToCFDict( CFMutableDictionaryRef inCFMutableDictionaryRef, long inVendorID, CFStringRef inVendorCFStringRef, long inProductID, CFStringRef inProductCFStringRef );
static Boolean hu_AddDeviceElementToUsageXML( const hu_device_t * inDevice, const hu_element_t * inElement );
/*****************************************************/
#pragma mark - exported globals
/*****************************************************/
#pragma mark - local ( static ) globals
/*****************************************************/
static CFPropertyListRef gCookieCFPropertyListRef = NULL;
static CFPropertyListRef gUsageCFPropertyListRef = NULL;

/*****************************************************/
#pragma mark - exported function implementations
/*****************************************************/

/*************************************************************************
*
* HIDGetVendorNameFromVendorID( inVendorID, inProductID, inCookie, outCStrName )
*
* Purpose:  Uses an devices vendor ID to generate a name for it.
*
* Notes:	Now uses XML files to store dictionary of names
*
* Inputs:   inVendorID   - the elements vendor ID
*			outCStrName   - address where result will be returned
* Returns:  Boolean		- if successful
*/
Boolean HIDGetVendorNameFromVendorID( long inVendorID, char* outCStrName )
{
	Boolean result = FALSE;
	*outCStrName = 0; // clear name

	if ( hu_XMLSearchForVendorNameByVendorID( inVendorID, outCStrName ) )
		return TRUE;

#if FAKE_MISSING_NAMES
	sprintf( outCStrName, "#{V:%ld}#", inVendorID );
	result = TRUE;
#endif FAKE_MISSING_NAMES
	return result;
}	// HIDGetVendorNameFromVendorID

/*************************************************************************
*
* HIDGetProductNameFromVendorProductID( inVendorID, inProductID, outCStrName )
*
* Purpose:  Uses an elements vendor, product & usage info to generate a name for it.
*
* Notes:	Now uses XML files to store dictionary of names
*
* Inputs:   inVendorID   - the elements vendor ID
*			inProductID  - the elements product ID
*			inUsagePage	- the elements usage page
*			inUsage		- the elements usage
*			outCStrName   - address where result will be returned
* Returns:  Boolean		- if successful
*/
Boolean HIDGetProductNameFromVendorProductID( long inVendorID, long inProductID, char* outCStrName )
{
	Boolean result = FALSE;
	*outCStrName = 0; // clear name

	if ( hu_XMLSearchForProductNameByVendorProductID( inVendorID, inProductID, outCStrName ) )
		return TRUE;

#if FAKE_MISSING_NAMES
	sprintf( outCStrName, "#{V:%ld, P:%ld, U:%ld:%ld}#", inVendorID, inProductID, inUsagePage, inUsage );
	result = TRUE;
#endif FAKE_MISSING_NAMES
	return result;
}	// HIDGetProductNameFromVendorProductID

/*************************************************************************
*
* HIDGetElementNameFromVendorProductCookie( inVendorID, inProductID, inCookie, outCStrName )
*
* Purpose:  Uses an elements vendor, product & cookie to generate a name for it.
*
* Notes:	Now uses XML files to store dictionary of names
*
* Inputs:   inVendorID   - the elements vendor ID
*			inProductID  - the elements product ID
*			inCookie		- the elements cookie
*			outCStrName   - address where result will be returned
* Returns:  Boolean		- if successful
*/
Boolean HIDGetElementNameFromVendorProductCookie( long inVendorID, long inProductID, long inCookie, char* outCStrName )
{
	Boolean result = FALSE;
	*outCStrName = 0; // clear name

	// Look in the XML file first
	if ( hu_XMLSearchForElementNameByCookie( inVendorID, inProductID, inCookie, outCStrName ) )
		return TRUE;

#if FAKE_MISSING_NAMES
	sprintf( outCStrName, "#{V:%ld, P:%ld, C:%ld}#", inVendorID, inProductID, inCookie );
#else
	result = FALSE;
#endif FAKE_MISSING_NAMES
	return result;
}	// HIDGetElementNameFromVendorProductCookie

/*************************************************************************
*
* HIDGetElementNameFromVendorProductUsage( inVendorID, inProductID, inUsagePage, inUsage, outCStrName )
*
* Purpose:  Uses an elements vendor, product & usage info to generate a name for it.
*
* Notes:	Now uses XML files to store dictionary of names
*
* Inputs:   inVendorID   - the elements vendor ID
*			inProductID  - the elements product ID
*			inUsagePage	- the elements usage page
*			inUsage		- the elements usage
*			outCStrName   - address where result will be returned
* Returns:  Boolean		- if successful
*/
Boolean HIDGetElementNameFromVendorProductUsage( long inVendorID, long inProductID, long inUsagePage, long inUsage, char* outCStrName )
{
	Boolean result = FALSE;
	*outCStrName = 0; // clear name

	if ( hu_XMLSearchForElementNameByUsage( inVendorID, inProductID, inUsagePage, inUsage, outCStrName ) )
		return TRUE;

#if FAKE_MISSING_NAMES
	sprintf( outCStrName, "#{V:%ld, P:%ld, U:%ld:%ld}#", inVendorID, inProductID, inUsagePage, inUsage );
	result = TRUE;
#endif FAKE_MISSING_NAMES
	return result;
}	// HIDGetElementNameFromVendorProductUsage

/*************************************************************************
*
* HIDAddDeviceToXML( inDevice )
*
* Purpose: Adds a devices info to the HID_device_usage_strings.plist( XML ) file
*
* Inputs:   inDevice		- the device
* Returns:  Boolean		- if successful
*/
Boolean HIDAddDeviceToXML( const hu_device_t * inDevice )
{
	Boolean result = FALSE;

	if ( HIDIsValidDevice( inDevice ) ) {
		CFStringRef vendorCFString = CFStringCreateWithCString( kCFAllocatorDefault, ( const char* ) inDevice->manufacturer, kCFStringEncodingMacRoman );
		CFStringRef productCFString = CFStringCreateWithCString( kCFAllocatorDefault, ( const char* ) inDevice->product, kCFStringEncodingMacRoman );

#if 0 // don't update the cookie xml file
		gCookieCFPropertyListRef = hu_XMLLoad( CFSTR( "HID_cookie_strings" ), CFSTR( "plist" ) );
		if ( gCookieCFPropertyListRef ) {
			CFMutableDictionaryRef tCFMutableDictionaryRef = CFDictionaryCreateMutableCopy( kCFAllocatorDefault, 0, gCookieCFPropertyListRef );
			if ( tCFMutableDictionaryRef ) {
				if ( hu_AddVendorProductToCFDict( tCFMutableDictionaryRef, inDevice->vendorID, vendorCFString, inDevice->productID, productCFString ) ) {
					hu_XMLSave( tCFMutableDictionaryRef, CFSTR( "HID_cookie_strings" ), CFSTR( "plist" ) );
					result = TRUE;
				}
				CFRelease( tCFMutableDictionaryRef );
			}
		}
#endif
		if ( gUsageCFPropertyListRef )
			CFRelease( gUsageCFPropertyListRef );

		gUsageCFPropertyListRef = hu_XMLLoad( CFSTR( "HID_device_usage_strings" ), CFSTR( "plist" ) );
		if ( gUsageCFPropertyListRef ) {
			CFMutableDictionaryRef tCFMutableDictionaryRef = CFDictionaryCreateMutableCopy( kCFAllocatorDefault, 0, gUsageCFPropertyListRef );
			if ( tCFMutableDictionaryRef ) {
				if ( hu_AddVendorProductToCFDict( tCFMutableDictionaryRef, inDevice->vendorID, vendorCFString, inDevice->productID, productCFString ) ) {
					hu_XMLSave( tCFMutableDictionaryRef, CFSTR( "HID_device_usage_strings" ), CFSTR( "plist" ) );
					result = TRUE;
				}
				CFRelease( tCFMutableDictionaryRef );
			}
		}
		if ( vendorCFString ) {
			CFRelease( vendorCFString );
		}
		if ( productCFString ) {
			CFRelease( productCFString );
		}
	}
	return result;
}	// HIDAddDeviceToXML

/*************************************************************************
*
* HIDAddDeviceElementToXML( inDevice, inElement )
*
* Purpose: Adds a devices info to the HID_device_usage_strings.plist( XML ) file
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*
* Returns:  Boolean		- if successful
*/
Boolean HIDAddDeviceElementToXML( const hu_device_t * inDevice, hu_element_t * inElement )
{
	Boolean result = FALSE;

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( HIDAddDeviceToXML( inDevice ) )
			result = TRUE;

		if ( hu_AddDeviceElementToUsageXML( inDevice, inElement ) ) {
			result = TRUE;
		}
	}
	return result;
}	// HIDAddDeviceElementToXML

/*************************************************************************
*
* HIDGetTypeName( inIOHIDElementType, outCStrName )
*
* Purpose:  return a C string for a given element type( see IOHIDKeys.h )
* Notes:	returns "Unknown Type" for invalid types
*
* Inputs:   inIOHIDElementType	- type element type
*			outCStrName			- address where to store element type string
*
* Returns:  outCStrName			- the element type string
*/

void HIDGetTypeName( IOHIDElementType inIOHIDElementType, char* outCStrName )
{
	switch( inIOHIDElementType ) {
		case kIOHIDElementTypeInput_Misc: {
			sprintf( outCStrName, "Miscellaneous Input" );
			break;
		}
		case kIOHIDElementTypeInput_Button: {
			sprintf( outCStrName, "Button Input" );
			break;
		}
		case kIOHIDElementTypeInput_Axis: {
			sprintf( outCStrName, "Axis Input" );
			break;
		}
		case kIOHIDElementTypeInput_ScanCodes: {
			sprintf( outCStrName, "Scan Code Input" );
			break;
		}
		case kIOHIDElementTypeOutput:	{
			sprintf( outCStrName, "Output" );
			break;
		}
		case kIOHIDElementTypeFeature: {
			sprintf( outCStrName, "Feature" );
			break;
		}
		case kIOHIDElementTypeCollection: {
			sprintf( outCStrName, "Collection" );
			break;
		}
		default: {
			sprintf( outCStrName, "Unknown Type" );
			break;
		}
	}
}	// HIDGetTypeName

/*************************************************************************
*
* HIDGetUsageName( inUsagePage, inUsage, outCStrName )
*
* Purpose:  return a C string for a given usage page & usage( see IOUSBHIDParser.h )
* Notes:	returns usage page and usage values in string form for unknown values
*
* Inputs:   inUsagePage	- the usage page
*			inUsage		- the usage
*			outCStrName   - address where to store usage string
*
* Returns:  outCStrName	- the usage string
*/

void HIDGetUsageName( long inUsagePage, long inUsage, char* outCStrName )
{
	if ( hu_XMLGetUsageName( inUsagePage, inUsage, outCStrName ) )
		return;

	switch( inUsagePage ) {
		case kHIDPage_Undefined: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Undefined Page, Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_GenericDesktop: {
			switch( inUsage ) {
				case kHIDUsage_GD_Pointer: sprintf( outCStrName, "Pointer" ); break;
				case kHIDUsage_GD_Mouse: sprintf( outCStrName, "Mouse" ); break;
				case kHIDUsage_GD_Joystick: sprintf( outCStrName, "Joystick" ); break;
				case kHIDUsage_GD_GamePad: sprintf( outCStrName, "GamePad" ); break;
				case kHIDUsage_GD_Keyboard: sprintf( outCStrName, "Keyboard" ); break;
				case kHIDUsage_GD_Keypad: sprintf( outCStrName, "Keypad" ); break;
				case kHIDUsage_GD_MultiAxisController: sprintf( outCStrName, "Multi-Axis Controller" ); break;

				case kHIDUsage_GD_X: sprintf( outCStrName, "X-Axis" ); break;
				case kHIDUsage_GD_Y: sprintf( outCStrName, "Y-Axis" ); break;
				case kHIDUsage_GD_Z: sprintf( outCStrName, "Z-Axis" ); break;
				case kHIDUsage_GD_Rx: sprintf( outCStrName, "X-Rotation" ); break;
				case kHIDUsage_GD_Ry: sprintf( outCStrName, "Y-Rotation" ); break;
				case kHIDUsage_GD_Rz: sprintf( outCStrName, "Z-Rotation" ); break;
				case kHIDUsage_GD_Slider: sprintf( outCStrName, "Slider" ); break;
				case kHIDUsage_GD_Dial: sprintf( outCStrName, "Dial" ); break;
				case kHIDUsage_GD_Wheel: sprintf( outCStrName, "Wheel" ); break;
				case kHIDUsage_GD_Hatswitch: sprintf( outCStrName, "Hatswitch" ); break;
				case kHIDUsage_GD_CountedBuffer: sprintf( outCStrName, "Counted Buffer" ); break;
				case kHIDUsage_GD_ByteCount: sprintf( outCStrName, "Byte Count" ); break;
				case kHIDUsage_GD_MotionWakeup: sprintf( outCStrName, "Motion Wakeup" ); break;
				case kHIDUsage_GD_Start: sprintf( outCStrName, "Start" ); break;
				case kHIDUsage_GD_Select: sprintf( outCStrName, "Select" ); break;

				case kHIDUsage_GD_Vx: sprintf( outCStrName, "X-Velocity" ); break;
				case kHIDUsage_GD_Vy: sprintf( outCStrName, "Y-Velocity" ); break;
				case kHIDUsage_GD_Vz: sprintf( outCStrName, "Z-Velocity" ); break;
				case kHIDUsage_GD_Vbrx: sprintf( outCStrName, "X-Rotation Velocity" ); break;
				case kHIDUsage_GD_Vbry: sprintf( outCStrName, "Y-Rotation Velocity" ); break;
				case kHIDUsage_GD_Vbrz: sprintf( outCStrName, "Z-Rotation Velocity" ); break;
				case kHIDUsage_GD_Vno: sprintf( outCStrName, "Vno" ); break;

				case kHIDUsage_GD_SystemControl: sprintf( outCStrName, "System Control" ); break;
				case kHIDUsage_GD_SystemPowerDown: sprintf( outCStrName, "System Power Down" ); break;
				case kHIDUsage_GD_SystemSleep: sprintf( outCStrName, "System Sleep" ); break;
				case kHIDUsage_GD_SystemWakeUp: sprintf( outCStrName, "System Wake Up" ); break;
				case kHIDUsage_GD_SystemContextMenu: sprintf( outCStrName, "System Context Menu" ); break;
				case kHIDUsage_GD_SystemMainMenu: sprintf( outCStrName, "System Main Menu" ); break;
				case kHIDUsage_GD_SystemAppMenu: sprintf( outCStrName, "System App Menu" ); break;
				case kHIDUsage_GD_SystemMenuHelp: sprintf( outCStrName, "System Menu Help" ); break;
				case kHIDUsage_GD_SystemMenuExit: sprintf( outCStrName, "System Menu Exit" ); break;
				case kHIDUsage_GD_SystemMenu: sprintf( outCStrName, "System Menu" ); break;
				case kHIDUsage_GD_SystemMenuRight: sprintf( outCStrName, "System Menu Right" ); break;
				case kHIDUsage_GD_SystemMenuLeft: sprintf( outCStrName, "System Menu Left" ); break;
				case kHIDUsage_GD_SystemMenuUp: sprintf( outCStrName, "System Menu Up" ); break;
				case kHIDUsage_GD_SystemMenuDown: sprintf( outCStrName, "System Menu Down" ); break;

				case kHIDUsage_GD_DPadUp: sprintf( outCStrName, "DPad Up" ); break;
				case kHIDUsage_GD_DPadDown: sprintf( outCStrName, "DPad Down" ); break;
				case kHIDUsage_GD_DPadRight: sprintf( outCStrName, "DPad Right" ); break;
				case kHIDUsage_GD_DPadLeft: sprintf( outCStrName, "DPad Left" ); break;

				case kHIDUsage_GD_Reserved: sprintf( outCStrName, "Reserved" ); break;

				default: sprintf( outCStrName, "Generic Desktop Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_Simulation: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Simulation Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_VR: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "VR Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_Sport: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Sport Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_Game: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Game Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_KeyboardOrKeypad: {
			switch( inUsage ) {
				case kHIDUsage_KeyboardErrorRollOver: sprintf( outCStrName, "Error Roll Over" ); break;
				case kHIDUsage_KeyboardPOSTFail: sprintf( outCStrName, "POST Fail" ); break;
				case kHIDUsage_KeyboardErrorUndefined: sprintf( outCStrName, "Error Undefined" ); break;
				case kHIDUsage_KeyboardA: sprintf( outCStrName, "A" ); break;
				case kHIDUsage_KeyboardB: sprintf( outCStrName, "B" ); break;
				case kHIDUsage_KeyboardC: sprintf( outCStrName, "C" ); break;
				case kHIDUsage_KeyboardD: sprintf( outCStrName, "D" ); break;
				case kHIDUsage_KeyboardE: sprintf( outCStrName, "E" ); break;
				case kHIDUsage_KeyboardF: sprintf( outCStrName, "F" ); break;
				case kHIDUsage_KeyboardG: sprintf( outCStrName, "G" ); break;
				case kHIDUsage_KeyboardH: sprintf( outCStrName, "H" ); break;
				case kHIDUsage_KeyboardI: sprintf( outCStrName, "I" ); break;
				case kHIDUsage_KeyboardJ: sprintf( outCStrName, "J" ); break;
				case kHIDUsage_KeyboardK: sprintf( outCStrName, "K" ); break;
				case kHIDUsage_KeyboardL: sprintf( outCStrName, "L" ); break;
				case kHIDUsage_KeyboardM: sprintf( outCStrName, "M" ); break;
				case kHIDUsage_KeyboardN: sprintf( outCStrName, "N" ); break;
				case kHIDUsage_KeyboardO: sprintf( outCStrName, "O" ); break;
				case kHIDUsage_KeyboardP: sprintf( outCStrName, "P" ); break;
				case kHIDUsage_KeyboardQ: sprintf( outCStrName, "Q" ); break;
				case kHIDUsage_KeyboardR: sprintf( outCStrName, "R" ); break;
				case kHIDUsage_KeyboardS: sprintf( outCStrName, "S" ); break;
				case kHIDUsage_KeyboardT: sprintf( outCStrName, "T" ); break;
				case kHIDUsage_KeyboardU: sprintf( outCStrName, "U" ); break;
				case kHIDUsage_KeyboardV: sprintf( outCStrName, "V" ); break;
				case kHIDUsage_KeyboardW: sprintf( outCStrName, "W" ); break;
				case kHIDUsage_KeyboardX: sprintf( outCStrName, "X" ); break;
				case kHIDUsage_KeyboardY: sprintf( outCStrName, "Y" ); break;
				case kHIDUsage_KeyboardZ: sprintf( outCStrName, "Z" ); break;
				case kHIDUsage_Keyboard1: sprintf( outCStrName, "1" ); break;
				case kHIDUsage_Keyboard2: sprintf( outCStrName, "2" ); break;
				case kHIDUsage_Keyboard3: sprintf( outCStrName, "3" ); break;
				case kHIDUsage_Keyboard4: sprintf( outCStrName, "4" ); break;
				case kHIDUsage_Keyboard5: sprintf( outCStrName, "5" ); break;
				case kHIDUsage_Keyboard6: sprintf( outCStrName, "6" ); break;
				case kHIDUsage_Keyboard7: sprintf( outCStrName, "7" ); break;
				case kHIDUsage_Keyboard8: sprintf( outCStrName, "8" ); break;
				case kHIDUsage_Keyboard9: sprintf( outCStrName, "9" ); break;
				case kHIDUsage_Keyboard0: sprintf( outCStrName, "0" ); break;
				case kHIDUsage_KeyboardReturnOrEnter: sprintf( outCStrName, "Return" ); break;
				case kHIDUsage_KeyboardEscape: sprintf( outCStrName, "Escape" ); break;
				case kHIDUsage_KeyboardDeleteOrBackspace: sprintf( outCStrName, "Delete" ); break;
				case kHIDUsage_KeyboardTab: sprintf( outCStrName, "Tab" ); break;
				case kHIDUsage_KeyboardSpacebar: sprintf( outCStrName, "Spacebar" ); break;
				case kHIDUsage_KeyboardHyphen: sprintf( outCStrName, "Dash" ); break;
				case kHIDUsage_KeyboardEqualSign: sprintf( outCStrName, "Equal" ); break;
				case kHIDUsage_KeyboardOpenBracket: sprintf( outCStrName, "Left Square Bracket" ); break;
				case kHIDUsage_KeyboardCloseBracket: sprintf( outCStrName, "Right Square Bracket" ); break;
				case kHIDUsage_KeyboardBackslash: sprintf( outCStrName, "Slash" ); break;
				case kHIDUsage_KeyboardNonUSPound: sprintf( outCStrName, "Non-US #" ); break;
				case kHIDUsage_KeyboardSemicolon: sprintf( outCStrName, "Semi-Colon" ); break;
				case kHIDUsage_KeyboardQuote: sprintf( outCStrName, "Single Quote" ); break;
				case kHIDUsage_KeyboardGraveAccentAndTilde: sprintf( outCStrName, "Grave Accent" ); break;
				case kHIDUsage_KeyboardComma: sprintf( outCStrName, "Comma" ); break;
				case kHIDUsage_KeyboardPeriod: sprintf( outCStrName, "Period" ); break;
				case kHIDUsage_KeyboardSlash: sprintf( outCStrName, "Slash" ); break;
				case kHIDUsage_KeyboardCapsLock: sprintf( outCStrName, "Caps Lock" ); break;
				case kHIDUsage_KeyboardF1: sprintf( outCStrName, "F1" ); break;
				case kHIDUsage_KeyboardF2: sprintf( outCStrName, "F2" ); break;
				case kHIDUsage_KeyboardF3: sprintf( outCStrName, "F3" ); break;
				case kHIDUsage_KeyboardF4: sprintf( outCStrName, "F4" ); break;
				case kHIDUsage_KeyboardF5: sprintf( outCStrName, "F5" ); break;
				case kHIDUsage_KeyboardF6: sprintf( outCStrName, "F6" ); break;
				case kHIDUsage_KeyboardF7: sprintf( outCStrName, "F7" ); break;
				case kHIDUsage_KeyboardF8: sprintf( outCStrName, "F8" ); break;
				case kHIDUsage_KeyboardF9: sprintf( outCStrName, "F9" ); break;
				case kHIDUsage_KeyboardF10: sprintf( outCStrName, "F10" ); break;
				case kHIDUsage_KeyboardF11: sprintf( outCStrName, "F11" ); break;
				case kHIDUsage_KeyboardF12: sprintf( outCStrName, "F12" ); break;
				case kHIDUsage_KeyboardPrintScreen: sprintf( outCStrName, "Print Screen" ); break;
				case kHIDUsage_KeyboardScrollLock: sprintf( outCStrName, "Scroll Lock" ); break;
				case kHIDUsage_KeyboardPause: sprintf( outCStrName, "Pause" ); break;
				case kHIDUsage_KeyboardInsert: sprintf( outCStrName, "Insert" ); break;
				case kHIDUsage_KeyboardHome: sprintf( outCStrName, "Home" ); break;
				case kHIDUsage_KeyboardPageUp: sprintf( outCStrName, "Page Up" ); break;
				case kHIDUsage_KeyboardDeleteForward: sprintf( outCStrName, "Delete Forward" ); break;
				case kHIDUsage_KeyboardEnd: sprintf( outCStrName, "End" ); break;
				case kHIDUsage_KeyboardPageDown: sprintf( outCStrName, "Page Down" ); break;
				case kHIDUsage_KeyboardRightArrow: sprintf( outCStrName, "Right Arrow" ); break;
				case kHIDUsage_KeyboardLeftArrow: sprintf( outCStrName, "Left Arrow" ); break;
				case kHIDUsage_KeyboardDownArrow: sprintf( outCStrName, "Down Arrow" ); break;
				case kHIDUsage_KeyboardUpArrow: sprintf( outCStrName, "Up Arrow" ); break;
				case kHIDUsage_KeypadNumLock: sprintf( outCStrName, "Keypad NumLock" ); break;
				case kHIDUsage_KeypadSlash: sprintf( outCStrName, "Keypad Slash" ); break;
				case kHIDUsage_KeypadAsterisk: sprintf( outCStrName, "Keypad Asterisk" ); break;
				case kHIDUsage_KeypadHyphen: sprintf( outCStrName, "Keypad Dash" ); break;
				case kHIDUsage_KeypadPlus: sprintf( outCStrName, "Keypad Plus" ); break;
				case kHIDUsage_KeypadEnter: sprintf( outCStrName, "Keypad Enter" ); break;
				case kHIDUsage_Keypad1: sprintf( outCStrName, "Keypad 1" ); break;
				case kHIDUsage_Keypad2: sprintf( outCStrName, "Keypad 2" ); break;
				case kHIDUsage_Keypad3: sprintf( outCStrName, "Keypad 3" ); break;
				case kHIDUsage_Keypad4: sprintf( outCStrName, "Keypad 4" ); break;
				case kHIDUsage_Keypad5: sprintf( outCStrName, "Keypad 5" ); break;
				case kHIDUsage_Keypad6: sprintf( outCStrName, "Keypad 6" ); break;
				case kHIDUsage_Keypad7: sprintf( outCStrName, "Keypad 7" ); break;
				case kHIDUsage_Keypad8: sprintf( outCStrName, "Keypad 8" ); break;
				case kHIDUsage_Keypad9: sprintf( outCStrName, "Keypad 9" ); break;
				case kHIDUsage_Keypad0: sprintf( outCStrName, "Keypad 0" ); break;
				case kHIDUsage_KeypadPeriod: sprintf( outCStrName, "Keypad Period" ); break;
				case kHIDUsage_KeyboardNonUSBackslash: sprintf( outCStrName, "Non-US Backslash" ); break;
				case kHIDUsage_KeyboardApplication: sprintf( outCStrName, "Application" ); break;
				case kHIDUsage_KeyboardPower: sprintf( outCStrName, "Power" ); break;
				case kHIDUsage_KeypadEqualSign: sprintf( outCStrName, "Keypad Equal" ); break;
				case kHIDUsage_KeyboardF13: sprintf( outCStrName, "F13" ); break;
				case kHIDUsage_KeyboardF14: sprintf( outCStrName, "F14" ); break;
				case kHIDUsage_KeyboardF15: sprintf( outCStrName, "F15" ); break;
				case kHIDUsage_KeyboardF16: sprintf( outCStrName, "F16" ); break;
				case kHIDUsage_KeyboardF17: sprintf( outCStrName, "F17" ); break;
				case kHIDUsage_KeyboardF18: sprintf( outCStrName, "F18" ); break;
				case kHIDUsage_KeyboardF19: sprintf( outCStrName, "F19" ); break;
				case kHIDUsage_KeyboardF20: sprintf( outCStrName, "F20" ); break;
				case kHIDUsage_KeyboardF21: sprintf( outCStrName, "F21" ); break;
				case kHIDUsage_KeyboardF22: sprintf( outCStrName, "F22" ); break;
				case kHIDUsage_KeyboardF23: sprintf( outCStrName, "F23" ); break;
				case kHIDUsage_KeyboardF24: sprintf( outCStrName, "F24" ); break;
				case kHIDUsage_KeyboardExecute: sprintf( outCStrName, "Execute" ); break;
				case kHIDUsage_KeyboardHelp: sprintf( outCStrName, "Help" ); break;
				case kHIDUsage_KeyboardMenu: sprintf( outCStrName, "Menu" ); break;
				case kHIDUsage_KeyboardSelect: sprintf( outCStrName, "Select" ); break;
				case kHIDUsage_KeyboardStop: sprintf( outCStrName, "Stop" ); break;
				case kHIDUsage_KeyboardAgain: sprintf( outCStrName, "Again" ); break;
				case kHIDUsage_KeyboardUndo: sprintf( outCStrName, "Undo" ); break;
				case kHIDUsage_KeyboardCut: sprintf( outCStrName, "Cut" ); break;
				case kHIDUsage_KeyboardCopy: sprintf( outCStrName, "Copy" ); break;
				case kHIDUsage_KeyboardPaste: sprintf( outCStrName, "Paste" ); break;
				case kHIDUsage_KeyboardFind: sprintf( outCStrName, "Find" ); break;
				case kHIDUsage_KeyboardMute: sprintf( outCStrName, "Mute" ); break;
				case kHIDUsage_KeyboardVolumeUp: sprintf( outCStrName, "Volume Up" ); break;
				case kHIDUsage_KeyboardVolumeDown: sprintf( outCStrName, "Volume Down" ); break;
				case kHIDUsage_KeyboardLockingCapsLock: sprintf( outCStrName, "Locking Caps Lock" ); break;
				case kHIDUsage_KeyboardLockingNumLock: sprintf( outCStrName, "Locking Num Lock" ); break;
				case kHIDUsage_KeyboardLockingScrollLock: sprintf( outCStrName, "Locking Scroll Lock" ); break;
				case kHIDUsage_KeypadComma: sprintf( outCStrName, "Keypad Comma" ); break;
				case kHIDUsage_KeypadEqualSignAS400: sprintf( outCStrName, "Keypad Equal Sign for AS-400" ); break;
				case kHIDUsage_KeyboardInternational1: sprintf( outCStrName, "International1" ); break;
				case kHIDUsage_KeyboardInternational2: sprintf( outCStrName, "International2" ); break;
				case kHIDUsage_KeyboardInternational3: sprintf( outCStrName, "International3" ); break;
				case kHIDUsage_KeyboardInternational4: sprintf( outCStrName, "International4" ); break;
				case kHIDUsage_KeyboardInternational5: sprintf( outCStrName, "International5" ); break;
				case kHIDUsage_KeyboardInternational6: sprintf( outCStrName, "International6" ); break;
				case kHIDUsage_KeyboardInternational7: sprintf( outCStrName, "International7" ); break;
				case kHIDUsage_KeyboardInternational8: sprintf( outCStrName, "International8" ); break;
				case kHIDUsage_KeyboardInternational9: sprintf( outCStrName, "International9" ); break;
				case kHIDUsage_KeyboardLANG1: sprintf( outCStrName, "LANG1" ); break;
				case kHIDUsage_KeyboardLANG2: sprintf( outCStrName, "LANG2" ); break;
				case kHIDUsage_KeyboardLANG3: sprintf( outCStrName, "LANG3" ); break;
				case kHIDUsage_KeyboardLANG4: sprintf( outCStrName, "LANG4" ); break;
				case kHIDUsage_KeyboardLANG5: sprintf( outCStrName, "LANG5" ); break;
				case kHIDUsage_KeyboardLANG6: sprintf( outCStrName, "LANG6" ); break;
				case kHIDUsage_KeyboardLANG7: sprintf( outCStrName, "LANG7" ); break;
				case kHIDUsage_KeyboardLANG8: sprintf( outCStrName, "LANG8" ); break;
				case kHIDUsage_KeyboardLANG9: sprintf( outCStrName, "LANG9" ); break;
				case kHIDUsage_KeyboardAlternateErase: sprintf( outCStrName, "Alternate Erase" ); break;
				case kHIDUsage_KeyboardSysReqOrAttention: sprintf( outCStrName, "SysReq or Attention" ); break;
				case kHIDUsage_KeyboardCancel: sprintf( outCStrName, "Cancel" ); break;
				case kHIDUsage_KeyboardClear: sprintf( outCStrName, "Clear" ); break;
				case kHIDUsage_KeyboardPrior: sprintf( outCStrName, "Prior" ); break;
				case kHIDUsage_KeyboardReturn: sprintf( outCStrName, "Return" ); break;
				case kHIDUsage_KeyboardSeparator: sprintf( outCStrName, "Separator" ); break;
				case kHIDUsage_KeyboardOut: sprintf( outCStrName, "Out" ); break;
				case kHIDUsage_KeyboardOper: sprintf( outCStrName, "Oper" ); break;
				case kHIDUsage_KeyboardClearOrAgain: sprintf( outCStrName, "Clear or Again" ); break;
				case kHIDUsage_KeyboardCrSelOrProps: sprintf( outCStrName, "CrSel or Props" ); break;
				case kHIDUsage_KeyboardExSel: sprintf( outCStrName, "ExSel" ); break;
				case kHIDUsage_KeyboardLeftControl: sprintf( outCStrName, "Left Control" ); break;
				case kHIDUsage_KeyboardLeftShift: sprintf( outCStrName, "Left Shift" ); break;
				case kHIDUsage_KeyboardLeftAlt: sprintf( outCStrName, "Left Alt" ); break;
				case kHIDUsage_KeyboardLeftGUI: sprintf( outCStrName, "Left GUI" ); break;
				case kHIDUsage_KeyboardRightControl: sprintf( outCStrName, "Right Control" ); break;
				case kHIDUsage_KeyboardRightShift: sprintf( outCStrName, "Right Shift" ); break;
				case kHIDUsage_KeyboardRightAlt: sprintf( outCStrName, "Right Alt" ); break;
				case kHIDUsage_KeyboardRightGUI: sprintf( outCStrName, "Right GUI" ); break;
				case kHIDUsage_Keyboard_Reserved: sprintf( outCStrName, "Reserved" ); break;
				default: sprintf( outCStrName, "Keyboard Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_LEDs: {
			switch( inUsage ) {
				// some LED usages
				case kHIDUsage_LED_IndicatorRed: sprintf( outCStrName, "Red LED" ); break;
				case kHIDUsage_LED_IndicatorGreen: sprintf( outCStrName, "Green LED" ); break;
				case kHIDUsage_LED_IndicatorAmber: sprintf( outCStrName, "Amber LED" ); break;
				case kHIDUsage_LED_GenericIndicator: sprintf( outCStrName, "Generic LED" ); break;
				case kHIDUsage_LED_SystemSuspend: sprintf( outCStrName, "System Suspend LED" ); break;
				case kHIDUsage_LED_ExternalPowerConnected: sprintf( outCStrName, "External Power LED" ); break;
				default: sprintf( outCStrName, "LED Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_Button: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Button #%ld", inUsage ); break;
			}
			break;
		}
		case kHIDPage_Ordinal: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Ordinal Instance %lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_Telephony: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Telephony Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_Consumer: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Consumer Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_Digitizer: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Digitizer Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_PID: {
			if ( ( ( inUsage >= 0x02 ) && ( inUsage <= 0x1F ) ) || ( ( inUsage >= 0x29 ) && ( inUsage <= 0x2F ) ) ||
				( ( inUsage >= 0x35 ) && ( inUsage <= 0x3F ) ) || ( ( inUsage >= 0x44 ) && ( inUsage <= 0x4F ) ) ||
				( inUsage == 0x8A ) || ( inUsage == 0x93 ) || ( ( inUsage >= 0x9D ) && ( inUsage <= 0x9E ) ) ||
				( ( inUsage >= 0xA1 ) && ( inUsage <= 0xA3 ) ) || ( ( inUsage >= 0xAD ) && ( inUsage <= 0xFFFF ) ) ) {
				sprintf( outCStrName, "PID Reserved" );
			} else {
				switch( inUsage ) {
					case 0x00: sprintf( outCStrName, "PID Undefined Usage" ); break;
					case kHIDUsage_PID_PhysicalInterfaceDevice: sprintf( outCStrName, "Physical Interface Device" ); break;
					case kHIDUsage_PID_Normal: sprintf( outCStrName, "Normal Force" ); break;
						
					case kHIDUsage_PID_SetEffectReport: sprintf( outCStrName, "Set Effect Report" ); break;
					case kHIDUsage_PID_EffectBlockIndex: sprintf( outCStrName, "Effect Block Index" ); break;
					case kHIDUsage_PID_ParamBlockOffset: sprintf( outCStrName, "Parameter Block Offset" ); break;
					case kHIDUsage_PID_ROM_Flag: sprintf( outCStrName, "ROM Flag" ); break;
						
					case kHIDUsage_PID_EffectType: sprintf( outCStrName, "Effect Type" ); break;
					case kHIDUsage_PID_ET_ConstantForce: sprintf( outCStrName, "Effect Type Constant Force" ); break;
					case kHIDUsage_PID_ET_Ramp: sprintf( outCStrName, "Effect Type Ramp" ); break;
					case kHIDUsage_PID_ET_CustomForceData: sprintf( outCStrName, "Effect Type Custom Force Data" ); break;
					case kHIDUsage_PID_ET_Square: sprintf( outCStrName, "Effect Type Square" ); break;
					case kHIDUsage_PID_ET_Sine: sprintf( outCStrName, "Effect Type Sine" ); break;
					case kHIDUsage_PID_ET_Triangle: sprintf( outCStrName, "Effect Type Triangle" ); break;
					case kHIDUsage_PID_ET_SawtoothUp: sprintf( outCStrName, "Effect Type Sawtooth Up" ); break;
					case kHIDUsage_PID_ET_SawtoothDown: sprintf( outCStrName, "Effect Type Sawtooth Down" ); break;
					case kHIDUsage_PID_ET_Spring: sprintf( outCStrName, "Effect Type Spring" ); break;
					case kHIDUsage_PID_ET_Damper: sprintf( outCStrName, "Effect Type Damper" ); break;
					case kHIDUsage_PID_ET_Inertia: sprintf( outCStrName, "Effect Type Inertia" ); break;
					case kHIDUsage_PID_ET_Friction: sprintf( outCStrName, "Effect Type Friction" ); break;
					case kHIDUsage_PID_Duration: sprintf( outCStrName, "Effect Duration" ); break;
					case kHIDUsage_PID_SamplePeriod: sprintf( outCStrName, "Effect Sample Period" ); break;
					case kHIDUsage_PID_Gain: sprintf( outCStrName, "Effect Gain" ); break;
					case kHIDUsage_PID_TriggerButton: sprintf( outCStrName, "Effect Trigger Button" ); break;
					case kHIDUsage_PID_TriggerRepeatInterval: sprintf( outCStrName, "Effect Trigger Repeat Interval" ); break;
						
					case kHIDUsage_PID_AxesEnable: sprintf( outCStrName, "Axis Enable" ); break;
					case kHIDUsage_PID_DirectionEnable: sprintf( outCStrName, "Direction Enable" ); break;
						
					case kHIDUsage_PID_Direction: sprintf( outCStrName, "Direction" ); break;
						
					case kHIDUsage_PID_TypeSpecificBlockOffset: sprintf( outCStrName, "Type Specific Block Offset" ); break;
						
					case kHIDUsage_PID_BlockType: sprintf( outCStrName, "Block Type" ); break;
						
					case kHIDUsage_PID_SetEnvelopeReport: sprintf( outCStrName, "Set Envelope Report" ); break;
					case kHIDUsage_PID_AttackLevel: sprintf( outCStrName, "Envelope Attack Level" ); break;
					case kHIDUsage_PID_AttackTime: sprintf( outCStrName, "Envelope Attack Time" ); break;
					case kHIDUsage_PID_FadeLevel: sprintf( outCStrName, "Envelope Fade Level" ); break;
					case kHIDUsage_PID_FadeTime: sprintf( outCStrName, "Envelope Fade Time" ); break;
						
					case kHIDUsage_PID_SetConditionReport: sprintf( outCStrName, "Set Condition Report" ); break;
					case kHIDUsage_PID_CP_Offset: sprintf( outCStrName, "Condition CP Offset" ); break;
					case kHIDUsage_PID_PositiveCoefficient: sprintf( outCStrName, "Condition Positive Coefficient" ); break;
					case kHIDUsage_PID_NegativeCoefficient: sprintf( outCStrName, "Condition Negative Coefficient" ); break;
					case kHIDUsage_PID_PositiveSaturation: sprintf( outCStrName, "Condition Positive Saturation" ); break;
					case kHIDUsage_PID_NegativeSaturation: sprintf( outCStrName, "Condition Negative Saturation" ); break;
					case kHIDUsage_PID_DeadBand: sprintf( outCStrName, "Condition Dead Band" ); break;
						
					case kHIDUsage_PID_DownloadForceSample: sprintf( outCStrName, "Download Force Sample" ); break;
					case kHIDUsage_PID_IsochCustomForceEnable: sprintf( outCStrName, "Isoch Custom Force Enable" ); break;
						
					case kHIDUsage_PID_CustomForceDataReport: sprintf( outCStrName, "Custom Force Data Report" ); break;
					case kHIDUsage_PID_CustomForceData: sprintf( outCStrName, "Custom Force Data" ); break;
						
					case kHIDUsage_PID_CustomForceVendorDefinedData: sprintf( outCStrName, "Custom Force Vendor Defined Data" ); break;
					case kHIDUsage_PID_SetCustomForceReport: sprintf( outCStrName, "Set Custom Force Report" ); break;
					case kHIDUsage_PID_CustomForceDataOffset: sprintf( outCStrName, "Custom Force Data Offset" ); break;
					case kHIDUsage_PID_SampleCount: sprintf( outCStrName, "Custom Force Sample Count" ); break;
						
					case kHIDUsage_PID_SetPeriodicReport: sprintf( outCStrName, "Set Periodic Report" ); break;
					case kHIDUsage_PID_Offset: sprintf( outCStrName, "Periodic Offset" ); break;
					case kHIDUsage_PID_Magnitude: sprintf( outCStrName, "Periodic Magnitude" ); break;
					case kHIDUsage_PID_Phase: sprintf( outCStrName, "Periodic Phase" ); break;
					case kHIDUsage_PID_Period: sprintf( outCStrName, "Periodic Period" ); break;
						
					case kHIDUsage_PID_SetConstantForceReport: sprintf( outCStrName, "Set Constant Force Report" ); break;
						
					case kHIDUsage_PID_SetRampForceReport: sprintf( outCStrName, "Set Ramp Force Report" ); break;
					case kHIDUsage_PID_RampStart: sprintf( outCStrName, "Ramp Start" ); break;
					case kHIDUsage_PID_RampEnd: sprintf( outCStrName, "Ramp End" ); break;
						
					case kHIDUsage_PID_EffectOperationReport: sprintf( outCStrName, "Effect Operation Report" ); break;
						
					case kHIDUsage_PID_EffectOperation: sprintf( outCStrName, "Effect Operation" ); break;
					case kHIDUsage_PID_OpEffectStart: sprintf( outCStrName, "Op Effect Start" ); break;
					case kHIDUsage_PID_OpEffectStartSolo: sprintf( outCStrName, "Op Effect Start Solo" ); break;
					case kHIDUsage_PID_OpEffectStop: sprintf( outCStrName, "Op Effect Stop" ); break;
					case kHIDUsage_PID_LoopCount: sprintf( outCStrName, "Op Effect Loop Count" ); break;
						
					case kHIDUsage_PID_DeviceGainReport: sprintf( outCStrName, "Device Gain Report" ); break;
					case kHIDUsage_PID_DeviceGain: sprintf( outCStrName, "Device Gain" ); break;
						
					case kHIDUsage_PID_PoolReport: sprintf( outCStrName, "PID Pool Report" ); break;
					case kHIDUsage_PID_RAM_PoolSize: sprintf( outCStrName, "RAM Pool Size" ); break;
					case kHIDUsage_PID_ROM_PoolSize: sprintf( outCStrName, "ROM Pool Size" ); break;
					case kHIDUsage_PID_ROM_EffectBlockCount: sprintf( outCStrName, "ROM Effect Block Count" ); break;
					case kHIDUsage_PID_SimultaneousEffectsMax: sprintf( outCStrName, "Simultaneous Effects Max" ); break;
					case kHIDUsage_PID_PoolAlignment: sprintf( outCStrName, "Pool Alignment" ); break;
						
					case kHIDUsage_PID_PoolMoveReport: sprintf( outCStrName, "PID Pool Move Report" ); break;
					case kHIDUsage_PID_MoveSource: sprintf( outCStrName, "Move Source" ); break;
					case kHIDUsage_PID_MoveDestination: sprintf( outCStrName, "Move Destination" ); break;
					case kHIDUsage_PID_MoveLength: sprintf( outCStrName, "Move Length" ); break;
						
					case kHIDUsage_PID_BlockLoadReport: sprintf( outCStrName, "PID Block Load Report" ); break;
						
					case kHIDUsage_PID_BlockLoadStatus: sprintf( outCStrName, "Block Load Status" ); break;
					case kHIDUsage_PID_BlockLoadSuccess: sprintf( outCStrName, "Block Load Success" ); break;
					case kHIDUsage_PID_BlockLoadFull: sprintf( outCStrName, "Block Load Full" ); break;
					case kHIDUsage_PID_BlockLoadError: sprintf( outCStrName, "Block Load Error" ); break;
					case kHIDUsage_PID_BlockHandle: sprintf( outCStrName, "Block Handle" ); break;
						
					case kHIDUsage_PID_BlockFreeReport: sprintf( outCStrName, "PID Block Free Report" ); break;
						
					case kHIDUsage_PID_TypeSpecificBlockHandle: sprintf( outCStrName, "Type Specific Block Handle" ); break;
						
					case kHIDUsage_PID_StateReport: sprintf( outCStrName, "PID State Report" ); break;
					case kHIDUsage_PID_EffectPlaying: sprintf( outCStrName, "Effect Playing" ); break;
						
					case kHIDUsage_PID_DeviceControlReport: sprintf( outCStrName, "PID Device Control Report" ); break;
						
					case kHIDUsage_PID_DeviceControl: sprintf( outCStrName, "PID Device Control" ); break;
					case kHIDUsage_PID_DC_EnableActuators: sprintf( outCStrName, "Device Control Enable Actuators" ); break;
					case kHIDUsage_PID_DC_DisableActuators: sprintf( outCStrName, "Device Control Disable Actuators" ); break;
					case kHIDUsage_PID_DC_StopAllEffects: sprintf( outCStrName, "Device Control Stop All Effects" ); break;
					case kHIDUsage_PID_DC_DeviceReset: sprintf( outCStrName, "Device Control Reset" ); break;
					case kHIDUsage_PID_DC_DevicePause: sprintf( outCStrName, "Device Control Pause" ); break;
					case kHIDUsage_PID_DC_DeviceContinue: sprintf( outCStrName, "Device Control Continue" ); break;
					case kHIDUsage_PID_DevicePaused: sprintf( outCStrName, "Device Paused" ); break;
					case kHIDUsage_PID_ActuatorsEnabled: sprintf( outCStrName, "Actuators Enabled" ); break;
					case kHIDUsage_PID_SafetySwitch: sprintf( outCStrName, "Safety Switch" ); break;
					case kHIDUsage_PID_ActuatorOverrideSwitch: sprintf( outCStrName, "Actuator Override Switch" ); break;
					case kHIDUsage_PID_ActuatorPower: sprintf( outCStrName, "Actuator Power" ); break;
					case kHIDUsage_PID_StartDelay: sprintf( outCStrName, "Start Delay" ); break;
						
					case kHIDUsage_PID_ParameterBlockSize: sprintf( outCStrName, "Parameter Block Size" ); break;
					case kHIDUsage_PID_DeviceManagedPool: sprintf( outCStrName, "Device Managed Pool" ); break;
					case kHIDUsage_PID_SharedParameterBlocks: sprintf( outCStrName, "Shared Parameter Blocks" ); break;
						
					case kHIDUsage_PID_CreateNewEffectReport: sprintf( outCStrName, "Create New Effect Report" ); break;
					case kHIDUsage_PID_RAM_PoolAvailable: sprintf( outCStrName, "RAM Pool Available" ); break;
					default: sprintf( outCStrName, "PID Usage 0x%lx", inUsage ); break;
				}
			}
			break;
		}
		case kHIDPage_Unicode: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Unicode Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_PowerDevice: {
			if ( ( ( inUsage >= 0x06 ) && ( inUsage <= 0x0F ) ) || ( ( inUsage >= 0x26 ) && ( inUsage <= 0x2F ) ) ||
				( ( inUsage >= 0x39 ) && ( inUsage <= 0x3F ) ) || ( ( inUsage >= 0x48 ) && ( inUsage <= 0x4F ) ) ||
				( ( inUsage >= 0x58 ) && ( inUsage <= 0x5F ) ) || ( inUsage == 0x6A ) ||
				( ( inUsage >= 0x74 ) && ( inUsage <= 0xFC ) ) ) {
				sprintf( outCStrName, "Power Device Reserved" );
			} else {
				switch( inUsage ) {
					case kHIDUsage_PD_Undefined: sprintf( outCStrName, "Power Device Undefined Usage" ); break;
					case kHIDUsage_PD_iName: sprintf( outCStrName, "Power Device Name Index" ); break;
					case kHIDUsage_PD_PresentStatus: sprintf( outCStrName, "Power Device Present Status" ); break;
					case kHIDUsage_PD_ChangedStatus: sprintf( outCStrName, "Power Device Changed Status" ); break;
					case kHIDUsage_PD_UPS: sprintf( outCStrName, "Uninterruptible Power Supply" ); break;
					case kHIDUsage_PD_PowerSupply: sprintf( outCStrName, "Power Supply" ); break;

					case kHIDUsage_PD_BatterySystem: sprintf( outCStrName, "Battery System Power Module" ); break;
					case kHIDUsage_PD_BatterySystemID: sprintf( outCStrName, "Battery System ID" ); break;
					case kHIDUsage_PD_Battery: sprintf( outCStrName, "Battery" ); break;
					case kHIDUsage_PD_BatteryID: sprintf( outCStrName, "Battery ID" ); break;
					case kHIDUsage_PD_Charger: sprintf( outCStrName, "Charger" ); break;
					case kHIDUsage_PD_ChargerID: sprintf( outCStrName, "Charger ID" ); break;
					case kHIDUsage_PD_PowerConverter: sprintf( outCStrName, "Power Converter Power Module" ); break;
					case kHIDUsage_PD_PowerConverterID: sprintf( outCStrName, "Power Converter ID" ); break;
					case kHIDUsage_PD_OutletSystem: sprintf( outCStrName, "Outlet System power module" ); break;
					case kHIDUsage_PD_OutletSystemID: sprintf( outCStrName, "Outlet System ID" ); break;
					case kHIDUsage_PD_Input: sprintf( outCStrName, "Power Device Input" ); break;
					case kHIDUsage_PD_InputID: sprintf( outCStrName, "Power Device Input ID" ); break;
					case kHIDUsage_PD_Output: sprintf( outCStrName, "Power Device Output" ); break;
					case kHIDUsage_PD_OutputID: sprintf( outCStrName, "Power Device Output ID" ); break;
					case kHIDUsage_PD_Flow: sprintf( outCStrName, "Power Device Flow" ); break;
					case kHIDUsage_PD_FlowID: sprintf( outCStrName, "Power Device Flow ID" ); break;
					case kHIDUsage_PD_Outlet: sprintf( outCStrName, "Power Device Outlet" ); break;
					case kHIDUsage_PD_OutletID: sprintf( outCStrName, "Power Device Outlet ID" ); break;
					case kHIDUsage_PD_Gang: sprintf( outCStrName, "Power Device Gang" ); break;
					case kHIDUsage_PD_GangID: sprintf( outCStrName, "Power Device Gang ID" ); break;
					case kHIDUsage_PD_PowerSummary: sprintf( outCStrName, "Power Device Power Summary" ); break;
					case kHIDUsage_PD_PowerSummaryID: sprintf( outCStrName, "Power Device Power Summary ID" ); break;

					case kHIDUsage_PD_Voltage: sprintf( outCStrName, "Power Device Voltage" ); break;
					case kHIDUsage_PD_Current: sprintf( outCStrName, "Power Device Current" ); break;
					case kHIDUsage_PD_Frequency: sprintf( outCStrName, "Power Device Frequency" ); break;
					case kHIDUsage_PD_ApparentPower: sprintf( outCStrName, "Power Device Apparent Power" ); break;
					case kHIDUsage_PD_ActivePower: sprintf( outCStrName, "Power Device RMS Power" ); break;
					case kHIDUsage_PD_PercentLoad: sprintf( outCStrName, "Power Device Percent Load" ); break;
					case kHIDUsage_PD_Temperature: sprintf( outCStrName, "Power Device Temperature" ); break;
					case kHIDUsage_PD_Humidity: sprintf( outCStrName, "Power Device Humidity" ); break;
					case kHIDUsage_PD_BadCount: sprintf( outCStrName, "Power Device Bad Condition Count" ); break;

					case kHIDUsage_PD_ConfigVoltage: sprintf( outCStrName, "Power Device Nominal Voltage" ); break;
					case kHIDUsage_PD_ConfigCurrent: sprintf( outCStrName, "Power Device Nominal Current" ); break;
					case kHIDUsage_PD_ConfigFrequency: sprintf( outCStrName, "Power Device Nominal Frequency" ); break;
					case kHIDUsage_PD_ConfigApparentPower: sprintf( outCStrName, "Power Device Nominal Apparent Power" ); break;
					case kHIDUsage_PD_ConfigActivePower: sprintf( outCStrName, "Power Device Nominal RMS Power" ); break;
					case kHIDUsage_PD_ConfigPercentLoad: sprintf( outCStrName, "Power Device Nominal Percent Load" ); break;
					case kHIDUsage_PD_ConfigTemperature: sprintf( outCStrName, "Power Device Nominal Temperature" ); break;

					case kHIDUsage_PD_ConfigHumidity: sprintf( outCStrName, "Power Device Nominal Humidity" ); break;
					case kHIDUsage_PD_SwitchOnControl: sprintf( outCStrName, "Power Device Switch On Control" ); break;
					case kHIDUsage_PD_SwitchOffControl: sprintf( outCStrName, "Power Device Switch Off Control" ); break;
					case kHIDUsage_PD_ToggleControl: sprintf( outCStrName, "Power Device Toogle Sequence Control" ); break;
					case kHIDUsage_PD_LowVoltageTransfer: sprintf( outCStrName, "Power Device Min Transfer Voltage" ); break;
					case kHIDUsage_PD_HighVoltageTransfer: sprintf( outCStrName, "Power Device Max Transfer Voltage" ); break;
					case kHIDUsage_PD_DelayBeforeReboot: sprintf( outCStrName, "Power Device Delay Before Reboot" ); break;
					case kHIDUsage_PD_DelayBeforeStartup: sprintf( outCStrName, "Power Device Delay Before Startup" ); break;
					case kHIDUsage_PD_DelayBeforeShutdown: sprintf( outCStrName, "Power Device Delay Before Shutdown" ); break;
					case kHIDUsage_PD_Test: sprintf( outCStrName, "Power Device Test Request/Result" ); break;
					case kHIDUsage_PD_ModuleReset: sprintf( outCStrName, "Power Device Reset Request/Result" ); break;
					case kHIDUsage_PD_AudibleAlarmControl: sprintf( outCStrName, "Power Device Audible Alarm Control" ); break;

					case kHIDUsage_PD_Present: sprintf( outCStrName, "Power Device Present" ); break;
					case kHIDUsage_PD_Good: sprintf( outCStrName, "Power Device Good" ); break;
					case kHIDUsage_PD_InternalFailure: sprintf( outCStrName, "Power Device Internal Failure" ); break;
					case kHIDUsage_PD_VoltageOutOfRange: sprintf( outCStrName, "Power Device Voltage Out Of Range" ); break;
					case kHIDUsage_PD_FrequencyOutOfRange: sprintf( outCStrName, "Power Device Frequency Out Of Range" ); break;
					case kHIDUsage_PD_Overload: sprintf( outCStrName, "Power Device Overload" ); break;
					case kHIDUsage_PD_OverCharged: sprintf( outCStrName, "Power Device Over Charged" ); break;
					case kHIDUsage_PD_OverTemperature: sprintf( outCStrName, "Power Device Over Temperature" ); break;
					case kHIDUsage_PD_ShutdownRequested: sprintf( outCStrName, "Power Device Shutdown Requested" ); break;

					case kHIDUsage_PD_ShutdownImminent: sprintf( outCStrName, "Power Device Shutdown Imminent" ); break;
					case kHIDUsage_PD_SwitchOnOff: sprintf( outCStrName, "Power Device On/Off Switch Status" ); break;
					case kHIDUsage_PD_Switchable: sprintf( outCStrName, "Power Device Switchable" ); break;
					case kHIDUsage_PD_Used: sprintf( outCStrName, "Power Device Used" ); break;
					case kHIDUsage_PD_Boost: sprintf( outCStrName, "Power Device Boosted" ); break;
					case kHIDUsage_PD_Buck: sprintf( outCStrName, "Power Device Bucked" ); break;
					case kHIDUsage_PD_Initialized: sprintf( outCStrName, "Power Device Initialized" ); break;
					case kHIDUsage_PD_Tested: sprintf( outCStrName, "Power Device Tested" ); break;
					case kHIDUsage_PD_AwaitingPower: sprintf( outCStrName, "Power Device Awaiting Power" ); break;
					case kHIDUsage_PD_CommunicationLost: sprintf( outCStrName, "Power Device Communication Lost" ); break;

					case kHIDUsage_PD_iManufacturer: sprintf( outCStrName, "Power Device Manufacturer String Index" ); break;
					case kHIDUsage_PD_iProduct: sprintf( outCStrName, "Power Device Product String Index" ); break;
					case kHIDUsage_PD_iserialNumber: sprintf( outCStrName, "Power Device Serial Number String Index" ); break;
					default: sprintf( outCStrName, "Power Device Usage 0x%lx", inUsage ); break;
				}
			}
			break;
		}
		case kHIDPage_BatterySystem: {
			if ( ( ( inUsage >= 0x0A ) && ( inUsage <= 0x0F ) ) || ( ( inUsage >= 0x1E ) && ( inUsage <= 0x27 ) ) ||
				( ( inUsage >= 0x30 ) && ( inUsage <= 0x3F ) ) || ( ( inUsage >= 0x4C ) && ( inUsage <= 0x5F ) ) ||
				( ( inUsage >= 0x6C ) && ( inUsage <= 0x7F ) ) || ( ( inUsage >= 0x90 ) && ( inUsage <= 0xBF ) ) ||
				( ( inUsage >= 0xC3 ) && ( inUsage <= 0xCF ) ) || ( ( inUsage >= 0xDD ) && ( inUsage <= 0xEF ) ) ||
				( ( inUsage >= 0xF2 ) && ( inUsage <= 0xFF ) ) ) {
				sprintf( outCStrName, "Power Device Reserved" );
			} else {
				switch( inUsage ) {
					case kHIDUsage_BS_Undefined: sprintf( outCStrName, "Battery System Undefined" ); break;
					case kHIDUsage_BS_SMBBatteryMode: sprintf( outCStrName, "SMB Mode" ); break;
					case kHIDUsage_BS_SMBBatteryStatus: sprintf( outCStrName, "SMB Status" ); break;
					case kHIDUsage_BS_SMBAlarmWarning: sprintf( outCStrName, "SMB Alarm Warning" ); break;
					case kHIDUsage_BS_SMBChargerMode: sprintf( outCStrName, "SMB Charger Mode" ); break;
					case kHIDUsage_BS_SMBChargerStatus: sprintf( outCStrName, "SMB Charger Status" ); break;
					case kHIDUsage_BS_SMBChargerSpecInfo: sprintf( outCStrName, "SMB Charger Extended Status" ); break;
					case kHIDUsage_BS_SMBSelectorState: sprintf( outCStrName, "SMB Selector State" ); break;
					case kHIDUsage_BS_SMBSelectorPresets: sprintf( outCStrName, "SMB Selector Presets" ); break;
					case kHIDUsage_BS_SMBSelectorInfo: sprintf( outCStrName, "SMB Selector Info" ); break;
					case kHIDUsage_BS_OptionalMfgFunction1: sprintf( outCStrName, "Battery System Optional SMB Mfg Function 1" ); break;
					case kHIDUsage_BS_OptionalMfgFunction2: sprintf( outCStrName, "Battery System Optional SMB Mfg Function 2" ); break;
					case kHIDUsage_BS_OptionalMfgFunction3: sprintf( outCStrName, "Battery System Optional SMB Mfg Function 3" ); break;
					case kHIDUsage_BS_OptionalMfgFunction4: sprintf( outCStrName, "Battery System Optional SMB Mfg Function 4" ); break;
					case kHIDUsage_BS_OptionalMfgFunction5: sprintf( outCStrName, "Battery System Optional SMB Mfg Function 5" ); break;
					case kHIDUsage_BS_ConnectionToSMBus: sprintf( outCStrName, "Battery System Connection To System Management Bus" ); break;
					case kHIDUsage_BS_OutputConnection: sprintf( outCStrName, "Battery System Output Connection Status" ); break;
					case kHIDUsage_BS_ChargerConnection: sprintf( outCStrName, "Battery System Charger Connection" ); break;
					case kHIDUsage_BS_BatteryInsertion: sprintf( outCStrName, "Battery System Battery Insertion" ); break;
					case kHIDUsage_BS_Usenext: sprintf( outCStrName, "Battery System Use Next" ); break;
					case kHIDUsage_BS_OKToUse: sprintf( outCStrName, "Battery System OK To Use" ); break;
					case kHIDUsage_BS_BatterySupported: sprintf( outCStrName, "Battery System Battery Supported" ); break;
					case kHIDUsage_BS_SelectorRevision: sprintf( outCStrName, "Battery System Selector Revision" ); break;
					case kHIDUsage_BS_ChargingIndicator: sprintf( outCStrName, "Battery System Charging Indicator" ); break;
					case kHIDUsage_BS_ManufacturerAccess: sprintf( outCStrName, "Battery System Manufacturer Access" ); break;
					case kHIDUsage_BS_RemainingCapacityLimit: sprintf( outCStrName, "Battery System Remaining Capacity Limit" ); break;
					case kHIDUsage_BS_RemainingTimeLimit: sprintf( outCStrName, "Battery System Remaining Time Limit" ); break;
					case kHIDUsage_BS_AtRate: sprintf( outCStrName, "Battery System At Rate..." ); break;
					case kHIDUsage_BS_CapacityMode: sprintf( outCStrName, "Battery System Capacity Mode" ); break;
					case kHIDUsage_BS_BroadcastToCharger: sprintf( outCStrName, "Battery System Broadcast To Charger" ); break;
					case kHIDUsage_BS_PrimaryBattery: sprintf( outCStrName, "Battery System Primary Battery" ); break;
					case kHIDUsage_BS_ChargeController: sprintf( outCStrName, "Battery System Charge Controller" ); break;
					case kHIDUsage_BS_TerminateCharge: sprintf( outCStrName, "Battery System Terminate Charge" ); break;
					case kHIDUsage_BS_TerminateDischarge: sprintf( outCStrName, "Battery System Terminate Discharge" ); break;
					case kHIDUsage_BS_BelowRemainingCapacityLimit: sprintf( outCStrName, "Battery System Below Remaining Capacity Limit" ); break;
					case kHIDUsage_BS_RemainingTimeLimitExpired: sprintf( outCStrName, "Battery System Remaining Time Limit Expired" ); break;
					case kHIDUsage_BS_Charging: sprintf( outCStrName, "Battery System Charging" ); break;
					case kHIDUsage_BS_Discharging: sprintf( outCStrName, "Battery System Discharging" ); break;
					case kHIDUsage_BS_FullyCharged: sprintf( outCStrName, "Battery System Fully Charged" ); break;
					case kHIDUsage_BS_FullyDischarged: sprintf( outCStrName, "Battery System Fully Discharged" ); break;
					case kHIDUsage_BS_ConditioningFlag: sprintf( outCStrName, "Battery System Conditioning Flag" ); break;
					case kHIDUsage_BS_AtRateOK: sprintf( outCStrName, "Battery System At Rate OK" ); break;
					case kHIDUsage_BS_SMBErrorCode: sprintf( outCStrName, "Battery System SMB Error Code" ); break;
					case kHIDUsage_BS_NeedReplacement: sprintf( outCStrName, "Battery System Need Replacement" ); break;
					case kHIDUsage_BS_AtRateTimeToFull: sprintf( outCStrName, "Battery System At Rate Time To Full" ); break;
					case kHIDUsage_BS_AtRateTimeToEmpty: sprintf( outCStrName, "Battery System At Rate Time To Empty" ); break;
					case kHIDUsage_BS_AverageCurrent: sprintf( outCStrName, "Battery System Average Current" ); break;
					case kHIDUsage_BS_Maxerror: sprintf( outCStrName, "Battery System Max Error" ); break;
					case kHIDUsage_BS_RelativeStateOfCharge: sprintf( outCStrName, "Battery System Relative State Of Charge" ); break;
					case kHIDUsage_BS_AbsoluteStateOfCharge: sprintf( outCStrName, "Battery System Absolute State Of Charge" ); break;
					case kHIDUsage_BS_RemainingCapacity: sprintf( outCStrName, "Battery System Remaining Capacity" ); break;
					case kHIDUsage_BS_FullChargeCapacity: sprintf( outCStrName, "Battery System Full Charge Capacity" ); break;
					case kHIDUsage_BS_RunTimeToEmpty: sprintf( outCStrName, "Battery System Run Time To Empty" ); break;
					case kHIDUsage_BS_AverageTimeToEmpty: sprintf( outCStrName, "Battery System Average Time To Empty" ); break;
					case kHIDUsage_BS_AverageTimeToFull: sprintf( outCStrName, "Battery System Average Time To Full" ); break;
					case kHIDUsage_BS_CycleCount: sprintf( outCStrName, "Battery System Cycle Count" ); break;
					case kHIDUsage_BS_BattPackModelLevel: sprintf( outCStrName, "Battery System Batt Pack Model Level" ); break;
					case kHIDUsage_BS_InternalChargeController: sprintf( outCStrName, "Battery System Internal Charge Controller" ); break;
					case kHIDUsage_BS_PrimaryBatterySupport: sprintf( outCStrName, "Battery System Primary Battery Support" ); break;
					case kHIDUsage_BS_DesignCapacity: sprintf( outCStrName, "Battery System Design Capacity" ); break;
					case kHIDUsage_BS_SpecificationInfo: sprintf( outCStrName, "Battery System Specification Info" ); break;
					case kHIDUsage_BS_ManufacturerDate: sprintf( outCStrName, "Battery System Manufacturer Date" ); break;
					case kHIDUsage_BS_SerialNumber: sprintf( outCStrName, "Battery System Serial Number" ); break;
					case kHIDUsage_BS_iManufacturerName: sprintf( outCStrName, "Battery System Manufacturer Name Index" ); break;
					case kHIDUsage_BS_iDevicename: sprintf( outCStrName, "Battery System Device Name Index" ); break;
					case kHIDUsage_BS_iDeviceChemistry: sprintf( outCStrName, "Battery System Device Chemistry Index" ); break;
					case kHIDUsage_BS_ManufacturerData: sprintf( outCStrName, "Battery System Manufacturer Data" ); break;
					case kHIDUsage_BS_Rechargable: sprintf( outCStrName, "Battery System Rechargable" ); break;
					case kHIDUsage_BS_WarningCapacityLimit: sprintf( outCStrName, "Battery System Warning Capacity Limit" ); break;
					case kHIDUsage_BS_CapacityGranularity1: sprintf( outCStrName, "Battery System Capacity Granularity 1" ); break;
					case kHIDUsage_BS_CapacityGranularity2: sprintf( outCStrName, "Battery System Capacity Granularity 2" ); break;
					case kHIDUsage_BS_iOEMInformation: sprintf( outCStrName, "Battery System OEM Information Index" ); break;
					case kHIDUsage_BS_InhibitCharge: sprintf( outCStrName, "Battery System Inhibit Charge" ); break;
					case kHIDUsage_BS_EnablePolling: sprintf( outCStrName, "Battery System Enable Polling" ); break;
					case kHIDUsage_BS_ResetToZero: sprintf( outCStrName, "Battery System Reset To Zero" ); break;
					case kHIDUsage_BS_ACPresent: sprintf( outCStrName, "Battery System AC Present" ); break;
					case kHIDUsage_BS_BatteryPresent: sprintf( outCStrName, "Battery System Battery Present" ); break;
					case kHIDUsage_BS_PowerFail: sprintf( outCStrName, "Battery System Power Fail" ); break;
					case kHIDUsage_BS_AlarmInhibited: sprintf( outCStrName, "Battery System Alarm Inhibited" ); break;
					case kHIDUsage_BS_ThermistorUnderRange: sprintf( outCStrName, "Battery System Thermistor Under Range" ); break;
					case kHIDUsage_BS_ThermistorHot: sprintf( outCStrName, "Battery System Thermistor Hot" ); break;
					case kHIDUsage_BS_ThermistorCold: sprintf( outCStrName, "Battery System Thermistor Cold" ); break;
					case kHIDUsage_BS_ThermistorOverRange: sprintf( outCStrName, "Battery System Thermistor Over Range" ); break;
					case kHIDUsage_BS_VoltageOutOfRange: sprintf( outCStrName, "Battery System Voltage Out Of Range" ); break;
					case kHIDUsage_BS_CurrentOutOfRange: sprintf( outCStrName, "Battery System Current Out Of Range" ); break;
					case kHIDUsage_BS_CurrentNotRegulated: sprintf( outCStrName, "Battery System Current Not Regulated" ); break;
					case kHIDUsage_BS_VoltageNotRegulated: sprintf( outCStrName, "Battery System Voltage Not Regulated" ); break;
					case kHIDUsage_BS_MasterMode: sprintf( outCStrName, "Battery System Master Mode" ); break;
					case kHIDUsage_BS_ChargerSelectorSupport: sprintf( outCStrName, "Battery System Charger Support Selector" ); break;
					case kHIDUsage_BS_ChargerSpec: sprintf( outCStrName, "attery System Charger Specification" ); break;
					case kHIDUsage_BS_Level2: sprintf( outCStrName, "Battery System Charger Level 2" ); break;
					case kHIDUsage_BS_Level3: sprintf( outCStrName, "Battery System Charger Level 3" ); break;
					default: sprintf( outCStrName, "Battery System Usage 0x%lx", inUsage ); break;
				}
			}
			break;
		}
		case kHIDPage_AlphanumericDisplay: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Alphanumeric Display Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_BarCodeScanner: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Bar Code Scanner Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_Scale: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Scale Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_CameraControl: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Camera Control Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		case kHIDPage_Arcade: {
			switch( inUsage ) {
				default: sprintf( outCStrName, "Arcade Usage 0x%lx", inUsage ); break;
			}
			break;
		}
		default: {
			if ( inUsagePage >= kHIDPage_VendorDefinedStart ) {
				sprintf( outCStrName, "Vendor Defined Usage 0x%lx", inUsage );
			} else {
				sprintf( outCStrName, "Page: 0x%lx, Usage: 0x%lx", inUsagePage, inUsage );
			}
			break;
		}
	}
}	// HIDGetUsageName

/*****************************************************/
#pragma mark - local ( static ) function implementations
/*****************************************************/

/*************************************************************************
*
* hu_SaveToXMLFile( inCFPRef, inCFURLRef )
*
* Purpose:  save a property list into an XML file
*
* Inputs:   inCFPRef		- the data
*			inCFURLRef	- URL for the file
*
* Returns:  SInt32		- error code ( if any )
*/
static SInt32 hu_SaveToXMLFile( CFPropertyListRef inCFPRef, CFURLRef inCFURLRef )
{
	CFDataRef xmlCFDataRef;
	Boolean status;
	SInt32 error = coreFoundationUnknownErr;

	// Convert the property list into XML data.
	xmlCFDataRef = CFPropertyListCreateXMLData( kCFAllocatorDefault, inCFPRef );
	if ( xmlCFDataRef ) {
		// Write the XML data to the file.
		status = CFURLWriteDataAndPropertiesToResource( inCFURLRef, xmlCFDataRef, NULL, &error );

		// Release the XML data
		CFRelease( xmlCFDataRef );
	}
	return error;
}	// hu_SaveToXMLFile

/*************************************************************************
*
* hu_LoadFromXMLFile( inCFURLRef )
*
* Purpose:  load a property list from an XML file
*
* Inputs:   inCFURLRef			- URL for the file
*
* Returns:  CFPropertyListRef   - the data
*/
static CFPropertyListRef hu_LoadFromXMLFile( CFURLRef inCFURLRef )
{
	CFDataRef xmlCFDataRef;
	CFPropertyListRef myCFPropertyListRef = NULL;

	// Read the XML file.
	SInt32 error;
	if ( CFURLCreateDataAndPropertiesFromResource( kCFAllocatorDefault, inCFURLRef, &xmlCFDataRef, NULL, NULL, &error ) ) {
		CFStringRef errorString;
		// Reconstitute the dictionary using the XML data.
		myCFPropertyListRef = CFPropertyListCreateFromXMLData( kCFAllocatorDefault, xmlCFDataRef, kCFPropertyListImmutable, &errorString );
		// Release the XML data
		CFRelease( xmlCFDataRef );
	}
	return myCFPropertyListRef;
}	// hu_LoadFromXMLFile

/*************************************************************************
*
* hu_XMLSave( inCFPropertyListRef, inResourceName, inResourceExtension )
*
* Purpose:  save a CFPropertyListRef into a resource( XML ) file
*
* Inputs:   inCFPropertyListRef  - the data
*			inResourceName		- name of the resource file
*			inResourceExtension  - extension of the resource file
*
* Returns:  SInt32				- error code ( if any )
*/
static SInt32 hu_XMLSave( CFPropertyListRef inCFPropertyListRef, CFStringRef inResourceName, CFStringRef inResourceExtension )
{
	CFURLRef resFileCFURLRef;
	SInt32 error = -1;

	resFileCFURLRef = CFBundleCopyResourceURL( CFBundleGetMainBundle( ), inResourceName, inResourceExtension, NULL );
	if ( resFileCFURLRef ) {
		error = hu_SaveToXMLFile( inCFPropertyListRef, resFileCFURLRef );
		CFRelease( resFileCFURLRef );
	}
	return error;
}	// hu_XMLSave

/*************************************************************************
*
* hu_XMLLoad( inResourceName, inResourceExtension )
*
* Purpose:  Load a resource( XML ) file into a CFPropertyListRef
*
* Inputs:   inResourceName		- name of the resource file
*			inResourceExtension  - extension of the resource file
*
* Returns:  CFPropertyListRef   - the data
*/
static CFPropertyListRef hu_XMLLoad( CFStringRef inResourceName, CFStringRef inResourceExtension )
{
	CFURLRef resFileCFURLRef;
	CFPropertyListRef tCFPropertyListRef = NULL;

	resFileCFURLRef = CFBundleCopyResourceURL( CFBundleGetMainBundle( ), inResourceName, inResourceExtension, NULL );
	if ( resFileCFURLRef ) {
		tCFPropertyListRef = hu_LoadFromXMLFile( resFileCFURLRef );
		CFRelease( resFileCFURLRef );
	}
	return tCFPropertyListRef;
}	// hu_XMLLoad

/*************************************************************************
*
* hu_XMLSearchForVendorNameByVendorID( inVendorID, outCStr )
*
* Purpose:  Find a vendor string in the <HID_device_usage_strings.plist> resource ( XML ) file
*
* Inputs:   inVendorID   - the elements vendor ID
*			inProductID  - the elements product ID
*			outCStr		- address where result will be returned
*
* Returns:  Boolean		- if successful
*/
static Boolean hu_XMLSearchForVendorNameByVendorID( long inVendorID, char* outCStr )
{
	Boolean results = FALSE;

	if ( !gUsageCFPropertyListRef )
		gUsageCFPropertyListRef = hu_XMLLoad( CFSTR( "HID_device_usage_strings" ), CFSTR( "plist" ) );

	if ( gUsageCFPropertyListRef ) {
		if ( CFDictionaryGetTypeID( ) == CFGetTypeID( gUsageCFPropertyListRef ) ) {
			CFDictionaryRef vendorCFDictionaryRef;
			CFStringRef	vendorKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inVendorID );
			if ( vendorKeyCFStringRef ) {
				if ( CFDictionaryGetValueIfPresent( gUsageCFPropertyListRef, vendorKeyCFStringRef, ( const void** ) &vendorCFDictionaryRef ) ) {
					CFStringRef	vendorCFStringRef = NULL;
					if ( CFDictionaryGetValueIfPresent( vendorCFDictionaryRef, kNameKeyCFStringRef, ( const void** ) &vendorCFStringRef ) && vendorCFStringRef ) {
						// CFShow( vendorCFStringRef );
						results = CFStringGetCString( vendorCFStringRef, outCStr, CFStringGetLength( vendorCFStringRef ) * sizeof( UniChar ) + 1, kCFStringEncodingMacRoman );
					}
				}
				CFRelease( vendorKeyCFStringRef );
			}
		}
		//++CFRelease( gUsageCFPropertyListRef );	// Leak this!
	}
	return results;
}	// hu_XMLSearchForVendorNameByVendorID

/*************************************************************************
*
* hu_XMLSearchForProductNameByVendorProductID( inVendorID, inProductID, outCStr )
*
* Purpose:  Find an product string in the <HID_device_usage_strings.plist> resource ( XML ) file
*
* Inputs:   inVendorID   - the elements vendor ID
*			inProductID  - the elements product ID
*			outCStr		- address where result will be returned
*
* Returns:  Boolean		- if successful
*/
static Boolean hu_XMLSearchForProductNameByVendorProductID( long inVendorID, long inProductID, char* outCStr )
{
	Boolean results = FALSE;

	if ( !gUsageCFPropertyListRef )
		gUsageCFPropertyListRef = hu_XMLLoad( CFSTR( "HID_device_usage_strings" ), CFSTR( "plist" ) );

	if ( gUsageCFPropertyListRef ) {
		if ( CFDictionaryGetTypeID( ) == CFGetTypeID( gUsageCFPropertyListRef ) ) {
			// first we make our vendor ID key
			CFStringRef	vendorKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inVendorID );
			if ( vendorKeyCFStringRef ) {
				// and use it to look up our vendor dictionary
				CFDictionaryRef vendorCFDictionaryRef;
				if ( CFDictionaryGetValueIfPresent( gUsageCFPropertyListRef, vendorKeyCFStringRef, ( const void** ) &vendorCFDictionaryRef ) ) {
					// pull our vendor name our of that dictionary
					CFStringRef	vendorCFStringRef = NULL;
					if ( CFDictionaryGetValueIfPresent( vendorCFDictionaryRef, kNameKeyCFStringRef, ( const void** ) &vendorCFStringRef ) ) {
#if FAKE_MISSING_NAMES
						CFRetain( vendorCFStringRef );	// so we can CFRelease it later
					} else {
						vendorCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "V: %@" ), vendorKeyCFStringRef );
#endif
					}

					// now we make our product ID key
					CFStringRef	productKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inProductID );
					if ( productKeyCFStringRef ) {
						// and use that key to look up our product dictionary in the vendor dictionary
						CFDictionaryRef productCFDictionaryRef;
						if ( CFDictionaryGetValueIfPresent( vendorCFDictionaryRef, productKeyCFStringRef, ( const void** ) &productCFDictionaryRef ) ) {
							// pull our product name our of the product dictionary
							CFStringRef	productCFStringRef = NULL;
							if ( CFDictionaryGetValueIfPresent( productCFDictionaryRef, kNameKeyCFStringRef, ( const void** ) &productCFStringRef ) ) {
#if FAKE_MISSING_NAMES
								CFRetain( productCFStringRef );	// so we can CFRelease it later
							} else {
								productCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "P: %@" ), kNameKeyCFStringRef );
#endif
							}
							CFStringRef fullCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%@ %@" ), vendorCFStringRef, productCFStringRef );
							if ( fullCFStringRef ) {
								// CFShow( fullCFStringRef );
								results = CFStringGetCString( fullCFStringRef, outCStr, CFStringGetLength( fullCFStringRef ) * sizeof( UniChar ) + 1, kCFStringEncodingMacRoman );
								CFRelease( fullCFStringRef );
							}
#if FAKE_MISSING_NAMES
							if ( productCFStringRef ) {
								CFRelease( productCFStringRef );
							}
#endif
						}
						CFRelease( productKeyCFStringRef );
					}
					
#if FAKE_MISSING_NAMES
					if ( vendorCFStringRef ) {
						CFRelease( vendorCFStringRef );
					}
#endif
				}
				CFRelease( vendorKeyCFStringRef );
			}
		}
		//++CFRelease( gUsageCFPropertyListRef );	// Leak this!
	}
	return results;
}	// hu_XMLSearchForProductNameByVendorProductID

/*************************************************************************
*
* hu_XMLSearchForElementNameByCookie( inVendorID, inProductID, inCookie, outCStr )
*
* Purpose:  Find an element string in the <HID_cookie_strings.plist> resource( XML ) file
*
* Inputs:   inVendorID   - the elements vendor ID
*			inProductID  - the elements product ID
*			inCookie		- the elements cookie
*			outCStr		- address where result will be returned
*
* Returns:  Boolean		- if successful
*/
static Boolean hu_XMLSearchForElementNameByCookie( long inVendorID, long inProductID, long inCookie, char* outCStr )
{
	Boolean results = FALSE;

	if ( !gCookieCFPropertyListRef )
		gCookieCFPropertyListRef = hu_XMLLoad( CFSTR( "HID_cookie_strings" ), CFSTR( "plist" ) );

	if ( gCookieCFPropertyListRef ) {
		if ( CFDictionaryGetTypeID( ) == CFGetTypeID( gCookieCFPropertyListRef ) ) {
			CFStringRef	vendorKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inVendorID );
			if ( vendorKeyCFStringRef ) {
				CFDictionaryRef vendorCFDictionaryRef;
				if ( CFDictionaryGetValueIfPresent( gCookieCFPropertyListRef, vendorKeyCFStringRef, ( const void** ) &vendorCFDictionaryRef ) ) {
					CFDictionaryRef productCFDictionaryRef;
					CFStringRef	productKeyCFStringRef;
					CFStringRef	vendorCFStringRef;

					if ( CFDictionaryGetValueIfPresent( vendorCFDictionaryRef, kNameKeyCFStringRef, ( const void** ) &vendorCFStringRef ) ) {
						//CFShow( vendorCFStringRef );
					}
					productKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inProductID );

					if ( CFDictionaryGetValueIfPresent( vendorCFDictionaryRef, productKeyCFStringRef, ( const void** ) &productCFDictionaryRef ) ) {
						CFStringRef fullCFStringRef = NULL;
						CFStringRef	cookieKeyCFStringRef;
						CFStringRef	productCFStringRef;
						CFStringRef	cookieCFStringRef;

						if ( CFDictionaryGetValueIfPresent( productCFDictionaryRef, kNameKeyCFStringRef, ( const void** ) &productCFStringRef ) ) {
							//CFShow( productCFStringRef );
						}
						cookieKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inCookie );

						if ( CFDictionaryGetValueIfPresent( productCFDictionaryRef, cookieKeyCFStringRef, ( const void** ) &cookieCFStringRef ) ) {
#if VERBOSE_ELEMENT_NAMES
							fullCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%@ %@ %@" ), vendorCFStringRef, productCFStringRef, cookieCFStringRef );
#else
							fullCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%@" ), cookieCFStringRef );
#endif VERBOSE_ELEMENT_NAMES
							// CFShow( cookieCFStringRef );
						}
#if FAKE_MISSING_NAMES
						else {
							fullCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%@ %@ #%@" ), vendorCFStringRef, productCFStringRef, cookieKeyCFStringRef );
						}
#endif FAKE_MISSING_NAMES
						if ( fullCFStringRef ) {
							// CFShow( fullCFStringRef );
							results = CFStringGetCString( fullCFStringRef, outCStr, CFStringGetLength( fullCFStringRef ) * sizeof( UniChar ) + 1, kCFStringEncodingMacRoman );
							CFRelease( fullCFStringRef );
						}
						CFRelease( cookieKeyCFStringRef );
					}
					CFRelease( productKeyCFStringRef );
				}
				CFRelease( vendorKeyCFStringRef );
			}
		}
		//++CFRelease( gCookieCFPropertyListRef );	// Leak this!
	}
	return results;
}	// hu_XMLSearchForElementNameByCookie

/*************************************************************************
*
* hu_XMLSearchForElementNameByUsage( inVendorID, inProductID, inUsagePage, inUsage, outCStr )
*
* Purpose:  Find an element string in the <HID_device_usage_strings.plist> resource( XML ) file
*
* Inputs:   inVendorID   - the elements vendor ID
*			inProductID  - the elements product ID
*			inUsagePage	- the elements usage page
*			inUsage		- the elements usage
*			outCStr		- address where result will be returned
*
* Returns:  Boolean		- if successful
*/
static Boolean hu_XMLSearchForElementNameByUsage( long inVendorID, long inProductID, long inUsagePage, long inUsage, char* outCStr )
{
	Boolean results = FALSE;

	if ( !gUsageCFPropertyListRef )
		gUsageCFPropertyListRef = hu_XMLLoad( CFSTR( "HID_device_usage_strings" ), CFSTR( "plist" ) );

	if ( gUsageCFPropertyListRef ) {
		if ( CFDictionaryGetTypeID( ) == CFGetTypeID( gUsageCFPropertyListRef ) ) {
			CFDictionaryRef vendorCFDictionaryRef;
			CFStringRef	vendorKeyCFStringRef;
			vendorKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inVendorID );

			if ( CFDictionaryGetValueIfPresent( gUsageCFPropertyListRef, vendorKeyCFStringRef, ( const void** ) &vendorCFDictionaryRef ) ) {
				CFDictionaryRef productCFDictionaryRef;
				CFStringRef	productKeyCFStringRef;
				CFStringRef	vendorCFStringRef;

				if ( !CFDictionaryGetValueIfPresent( vendorCFDictionaryRef, kNameKeyCFStringRef, ( const void** ) &vendorCFStringRef ) ) {
					vendorCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "v: %ld" ), inVendorID );
					//CFShow( vendorCFStringRef );
				}
				productKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inProductID );

				if ( CFDictionaryGetValueIfPresent( vendorCFDictionaryRef, productKeyCFStringRef, ( const void** ) &productCFDictionaryRef ) ) {
					CFStringRef fullCFStringRef = NULL;
					CFStringRef	usageKeyCFStringRef;
					CFStringRef	productCFStringRef;
					CFStringRef	usageCFStringRef;

					if ( CFDictionaryGetValueIfPresent( productCFDictionaryRef, kNameKeyCFStringRef, ( const void** ) &productCFStringRef ) ) {
						//CFShow( productCFStringRef );
					}
					usageKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld:%ld" ), inUsagePage, inUsage );

					if ( CFDictionaryGetValueIfPresent( productCFDictionaryRef, usageKeyCFStringRef, ( const void** ) &usageCFStringRef ) ) {
#if VERBOSE_ELEMENT_NAMES
						fullCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%@ %@ %@" ),
																   vendorCFStringRef, productCFStringRef, usageCFStringRef );
#else
						fullCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%@" ), usageCFStringRef );
#endif VERBOSE_ELEMENT_NAMES
						// CFShow( usageCFStringRef );
					}
#if FAKE_MISSING_NAMES
					else {
						fullCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%@ %@ #%@" ), vendorCFStringRef, productCFStringRef, usageKeyCFStringRef );
					}
#endif FAKE_MISSING_NAMES
					if ( fullCFStringRef ) {
						// CFShow( fullCFStringRef );
						results = CFStringGetCString( fullCFStringRef, outCStr, CFStringGetLength( fullCFStringRef ) * sizeof( UniChar ) + 1, kCFStringEncodingMacRoman );
						CFRelease( fullCFStringRef );
					}
					CFRelease( usageKeyCFStringRef );
				}
				CFRelease( productKeyCFStringRef );
			}
			CFRelease( vendorKeyCFStringRef );
		}
		//++CFRelease( gUsageCFPropertyListRef );	// Leak this!
	}
	return results;
}	// hu_XMLSearchForElementNameByUsage

/*************************************************************************
*
* hu_AddVendorProductToCFDict( inCFMutableDictionaryRef, inVendorID, inVendorCFStringRef, inProductID, inProductCFStringRef )
*
* Purpose:  add a vendor & product to a dictionary
*
* Inputs:   inCFMutableDictionaryRef - the dictionary
*			inVendorID				- the elements vendor ID
*			inProductID				- the elements product ID
*			inProductCFStringRef	- the string to be added
*
* Returns:  Boolean		- if successful
*/
static Boolean hu_AddVendorProductToCFDict( CFMutableDictionaryRef inCFMutableDictionaryRef, long inVendorID, CFStringRef inVendorCFStringRef, long inProductID, CFStringRef inProductCFStringRef )
{
	Boolean results = FALSE;

	if ( inCFMutableDictionaryRef && ( CFDictionaryGetTypeID( ) == CFGetTypeID( inCFMutableDictionaryRef ) ) ) {
		CFMutableDictionaryRef vendorCFMutableDictionaryRef;
		CFStringRef	vendorKeyCFStringRef;

		CFMutableDictionaryRef productCFMutableDictionaryRef;
		CFStringRef	productKeyCFStringRef;

		// if the vendor dictionary doesn't exist
		vendorKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inVendorID );
		if ( CFDictionaryGetValueIfPresent( inCFMutableDictionaryRef, vendorKeyCFStringRef, ( const void** ) &vendorCFMutableDictionaryRef ) ) {
			// copy it.
			vendorCFMutableDictionaryRef = CFDictionaryCreateMutableCopy( kCFAllocatorDefault, 0, vendorCFMutableDictionaryRef );
		} else {	// ...otherwise...
			// create it.
			vendorCFMutableDictionaryRef = CFDictionaryCreateMutable( kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks );
			results = TRUE;
		}

		// if the vendor name key doesn't exist
		if ( !CFDictionaryContainsKey( vendorCFMutableDictionaryRef, kNameKeyCFStringRef ) ) {
			// create it.
			CFDictionaryAddValue( vendorCFMutableDictionaryRef, kNameKeyCFStringRef, inVendorCFStringRef );
			results = TRUE;
		}

		// if the product key exists in the vendor dictionary
		productKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inProductID );
		if ( CFDictionaryGetValueIfPresent( vendorCFMutableDictionaryRef, productKeyCFStringRef, ( const void** ) &productCFMutableDictionaryRef ) ) {
			// copy it.
			productCFMutableDictionaryRef = CFDictionaryCreateMutableCopy( kCFAllocatorDefault, 0, productCFMutableDictionaryRef );
		} else {	// ...otherwise...
			// create it.
			productCFMutableDictionaryRef = CFDictionaryCreateMutable( kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks );
			results = TRUE;
		}

		// if the product name key doesn't exist
		if ( !CFDictionaryContainsKey( productCFMutableDictionaryRef, kNameKeyCFStringRef ) ) {
			// create it.
			CFDictionaryAddValue( productCFMutableDictionaryRef, kNameKeyCFStringRef, inProductCFStringRef );
			results = TRUE;
		}

		if ( vendorCFMutableDictionaryRef ) {
			if ( productCFMutableDictionaryRef ) {
				if ( results )
					CFDictionarySetValue( vendorCFMutableDictionaryRef, productKeyCFStringRef, productCFMutableDictionaryRef );
				CFRelease( productCFMutableDictionaryRef );
			}
			if ( results )
				CFDictionarySetValue( inCFMutableDictionaryRef, vendorKeyCFStringRef, vendorCFMutableDictionaryRef );
			CFRelease( vendorCFMutableDictionaryRef );
		}
		if ( productKeyCFStringRef )
			CFRelease( productKeyCFStringRef );
		if ( vendorKeyCFStringRef )
			CFRelease( vendorKeyCFStringRef );
	}
	return results;
}	// hu_AddVendorProductToCFDict

/*************************************************************************
*
* hu_AddDeviceElementToUsageXML( inDevice, inElement )
*
* Purpose:  add a device and it's elements to our usage( XML ) file
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*
* Returns:  Boolean		- if successful
*/
static Boolean hu_AddDeviceElementToUsageXML( const hu_device_t * inDevice, const hu_element_t * inElement )
{
	Boolean results = FALSE;

	if ( gUsageCFPropertyListRef )
		CFRelease( gUsageCFPropertyListRef );

	gUsageCFPropertyListRef = hu_XMLLoad( CFSTR( "HID_device_usage_strings" ), CFSTR( "plist" ) );
	if ( gUsageCFPropertyListRef ) {
		CFMutableDictionaryRef tCFMutableDictionaryRef = CFDictionaryCreateMutableCopy( kCFAllocatorDefault, 0, gUsageCFPropertyListRef );

		if ( tCFMutableDictionaryRef ) {
			CFStringRef	vendorKeyCFStringRef;
			CFMutableDictionaryRef vendorCFMutableDictionaryRef;

			CFMutableDictionaryRef productCFMutableDictionaryRef;
			CFStringRef	productKeyCFStringRef;

			CFStringRef usageKeyCFStringRef;

			// if the vendor dictionary exists...
			vendorKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inDevice->vendorID );
			if ( CFDictionaryGetValueIfPresent( tCFMutableDictionaryRef, vendorKeyCFStringRef, ( const void** ) &vendorCFMutableDictionaryRef ) ) {
				// ...copy it...
				vendorCFMutableDictionaryRef = CFDictionaryCreateMutableCopy( kCFAllocatorDefault, 0, vendorCFMutableDictionaryRef );
			} else {	// ...otherwise...
				// ...create it.
				vendorCFMutableDictionaryRef = CFDictionaryCreateMutable( kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks );
				results = TRUE;
			}

			// if the vendor name key doesn't exist...
			if ( !CFDictionaryContainsKey( vendorCFMutableDictionaryRef, kNameKeyCFStringRef ) ) {
				CFStringRef vendorCFStringRef = CFStringCreateWithCString( kCFAllocatorDefault, ( const char* ) inDevice->manufacturer, kCFStringEncodingMacRoman );
				// ...create it.
				CFDictionaryAddValue( vendorCFMutableDictionaryRef, kNameKeyCFStringRef, vendorCFStringRef );
				CFRelease( vendorCFStringRef );
				results = TRUE;
			}

			// if the product key exists in the vendor dictionary...
			productKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld" ), inDevice->productID );
			if ( CFDictionaryGetValueIfPresent( vendorCFMutableDictionaryRef, productKeyCFStringRef, ( const void** ) &productCFMutableDictionaryRef ) ) {
				// ...copy it...
				productCFMutableDictionaryRef = CFDictionaryCreateMutableCopy( kCFAllocatorDefault, 0, productCFMutableDictionaryRef );
			} else {	// ...otherwise...
				// ...create it.
				productCFMutableDictionaryRef = CFDictionaryCreateMutable( kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks );
				results = TRUE;
			}

			// if the product name key doesn't exist...
			if ( !CFDictionaryContainsKey( productCFMutableDictionaryRef, kNameKeyCFStringRef ) ) {
				CFStringRef productCFStringRef = CFStringCreateWithCString( kCFAllocatorDefault, ( const char* ) inDevice->product, kCFStringEncodingMacRoman );
				// ...create it.
				CFDictionaryAddValue( productCFMutableDictionaryRef, kNameKeyCFStringRef, productCFStringRef );
				CFRelease( productCFStringRef );
				results = TRUE;
			}

			// if the usage key doesn't exist in the product dictionary...
			usageKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%ld:%ld" ), inElement->usagePage, inElement->usage );
			if ( usageKeyCFStringRef ) {
				if ( !CFDictionaryContainsKey( productCFMutableDictionaryRef, usageKeyCFStringRef ) ) {
					char name[256];

					// find it's generic name
					HIDGetUsageName( inElement->usagePage, inElement->usage, name );
					if ( name[0] ) {
						CFStringRef usageCFStringRef = CFStringCreateWithCString( kCFAllocatorDefault, name, kCFStringEncodingMacRoman );
						if ( usageCFStringRef ) {
							// and add that.
							CFDictionaryAddValue( productCFMutableDictionaryRef, usageKeyCFStringRef, usageCFStringRef );
							results = TRUE;
							CFRelease( usageCFStringRef );
						}
					}
				}
				CFRelease( usageKeyCFStringRef );
			}

			if ( vendorCFMutableDictionaryRef ) {
				if ( productCFMutableDictionaryRef ) {
					if ( results ) {
						CFDictionarySetValue( vendorCFMutableDictionaryRef, productKeyCFStringRef, productCFMutableDictionaryRef );
					}
					CFRelease( productCFMutableDictionaryRef );
				}
				if ( results ) {
					CFDictionarySetValue( tCFMutableDictionaryRef, vendorKeyCFStringRef, vendorCFMutableDictionaryRef );
				}
				CFRelease( vendorCFMutableDictionaryRef );
			}
			if ( productKeyCFStringRef ) {
				CFRelease( productKeyCFStringRef );
			}
			if ( results ) {
				hu_XMLSave( tCFMutableDictionaryRef, CFSTR( "HID_device_usage_strings" ), CFSTR( "plist" ) );
			}
			CFRelease( tCFMutableDictionaryRef );
		}
	}
	return results;
}	// hu_AddDeviceElementToUsageXML

/*************************************************************************
*
* hu_XMLGetUsageName( inUsagePage, inUsage, outCStr )
*
* Purpose:  Find a usage string in the <HID_usage_strings.plist> resource( XML ) file
*
* Inputs:   inUsagePage	- the usage page
*			inUsage		- the usage
*			outCStr		- address where the usage name will be returned
*
* Returns:  Boolean		- if successful
*			outCStr		- the usage name
*/

static __attribute__((used)) Boolean hu_XMLGetUsageName( long inUsagePage, long inUsage, char* outCStr )
{
	static CFPropertyListRef tCFPropertyListRef = NULL;
	Boolean results = FALSE;

	if ( !tCFPropertyListRef )
		tCFPropertyListRef = hu_XMLLoad( CFSTR( "HID_usage_strings" ), CFSTR( "plist" ) );

	if ( tCFPropertyListRef ) {
		if ( CFDictionaryGetTypeID( ) == CFGetTypeID( tCFPropertyListRef ) ) {
			CFStringRef	pageKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "0x%4.4lX" ), inUsagePage );
			if ( pageKeyCFStringRef ) {
				CFDictionaryRef pageCFDictionaryRef;
				if ( CFDictionaryGetValueIfPresent( tCFPropertyListRef, pageKeyCFStringRef, ( const void** ) &pageCFDictionaryRef ) ) {
					CFStringRef	pageCFStringRef;
					if ( CFDictionaryGetValueIfPresent( pageCFDictionaryRef, kNameKeyCFStringRef, ( const void** ) &pageCFStringRef ) ) {
						CFStringRef fullCFStringRef = NULL;
						CFStringRef	usageKeyCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "0x%4.4lX" ), inUsage );
						if ( usageKeyCFStringRef ) {
							CFStringRef	usageCFStringRef;
							if ( CFDictionaryGetValueIfPresent( pageCFDictionaryRef, usageKeyCFStringRef, ( const void** ) &usageCFStringRef ) ) {
								fullCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%@ %@" ), pageCFStringRef, usageCFStringRef );
							}
#if FAKE_MISSING_NAMES
							else {
								fullCFStringRef = CFStringCreateWithFormat( kCFAllocatorDefault, NULL, CFSTR( "%@ #%@" ), pageCFStringRef, usageKeyCFStringRef );
							}
#endif
							if ( fullCFStringRef ) {
								// CFShow( fullCFStringRef );
								results = CFStringGetCString( fullCFStringRef, outCStr, CFStringGetLength( fullCFStringRef ) * sizeof( UniChar ) + 1, kCFStringEncodingMacRoman );
								CFRelease( fullCFStringRef );
							}
							CFRelease( usageKeyCFStringRef );
						}
					}
				}
				CFRelease( pageKeyCFStringRef );
			}
		}
		//++CFRelease( tCFPropertyListRef );	// Leak this!
	}
	return results;
}	// hu_XMLGetUsageName