/*
*	File:		HID_Transaction_Utilities.h
*
*	Contains:	Definitions of the HID queue functions for the HID utilites.
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

#include <CoreServices/CoreServices.h>

#include "HID_Utilities_Internal.h"
#include "HID_Utilities_External.h"

/*****************************************************/
#pragma mark - typedefs, enums, defines, etc.
/*****************************************************/

/*****************************************************/
#pragma mark - local ( static ) function prototypes
/*****************************************************/

static IOReturn hu_CreateTransaction( hu_device_t * inDevice );

/*****************************************************/
#pragma mark - exported globals
/*****************************************************/

/*****************************************************/
#pragma mark - local ( static ) globals
/*****************************************************/

/*****************************************************/
#pragma mark - exported function implementations
/*****************************************************/

/*************************************************************************
*
* HIDTransactionAddElement( inDevice, inElement )
*
* Purpose:  add an element to a Transaction
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*
* Returns:  IOReturn	- error code ( if any )
*
*/

IOReturn HIDTransactionAddElement( hu_device_t * inDevice, const hu_element_t * inElement )
{
	IOReturn result = hu_CreateTransaction( inDevice );

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( inDevice->transaction ) {
			result = ( *( IOHIDOutputTransactionInterface** ) inDevice->transaction )->addElement( inDevice->transaction, inElement->cookie ); // add element
			if ( kIOReturnSuccess != result )
				HIDReportErrorNum( "\nHIDTransactionAddElement failed to add Element: error = %ld.", result );
		} else {
			HIDReportError( "\nHIDTransactionAddElement failed: no transaction interface" );
			if ( !result )
				result = kIOReturnError; // synthesis error
		}
	}
	return result;
}

/*************************************************************************
*
* HIDTransactionRemoveElement( inDevice, inElement )
*
* Purpose:  removes an element from a Transaction
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*
* Returns:  IOReturn	- error code ( if any )
*
*/

IOReturn HIDTransactionRemoveElement( hu_device_t * inDevice, const hu_element_t * inElement )
{
	IOReturn result = hu_CreateTransaction( inDevice );

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( inDevice->transaction ) {
			result = ( *( IOHIDOutputTransactionInterface** ) inDevice->transaction )->removeElement( inDevice->transaction, inElement->cookie ); // remove element
			if ( kIOReturnSuccess != result )
				HIDReportErrorNum( "\nHIDTransactionRemoveElement failed to remove Element: error = %ld.", result );
		} else {
			HIDReportError( "\nHIDTransactionRemoveElement failed: no transaction interface" );
			if ( !result )
				result = kIOReturnError; // synthesis error
		}
	}
	return result;
}

/*************************************************************************
*
* HIDTransactionHasElement( inDevice, inElement )
*
* Purpose:  return TRUE if transaction contains this element
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*
* Returns:  Boolean	- TRUE if transaction contains element
*
*/
Boolean HIDTransactionHasElement( hu_device_t * inDevice, const hu_element_t * inElement )
{
	Boolean result = FALSE;

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		( void ) hu_CreateTransaction( inDevice );

		if ( inDevice->transaction ) {
			result = ( *( IOHIDOutputTransactionInterface** ) inDevice->transaction )->hasElement( inDevice->transaction, inElement->cookie ); // remove element
		} else {
			HIDReportError( "\nHIDTransactionHasElement failed: no transaction interface" );
		}
	}
	return result;
}

/*************************************************************************
*
* HIDTransactionSetElementDefault( inDevice, inElement, inValueEvent )
*
* Purpose:  sets the default value of an element
*
* Notes:	when the values of the elements are cleared, on clear or commit,
*			they are reset to this default value.
*			this call can be made on elements that are not in the transaction,
*			but has undefined behavior if made on elements not in the transaction
*			which are later added to the transaction. In other words, an element
*			should be added before its default is set, for well defined behavior.
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*			inValueEvent - the value to set the default to
*
* Returns:  IOReturn	- error code ( if any )
*
*/

IOReturn HIDTransactionSetElementDefault( hu_device_t * inDevice, const hu_element_t * inElement, IOHIDEventStruct* inValueEvent )
{
	IOReturn result = hu_CreateTransaction( inDevice );

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( inDevice->transaction ) {
			result = ( *( IOHIDOutputTransactionInterface** ) inDevice->transaction )->setElementDefault( inDevice->transaction, inElement->cookie, inValueEvent );
			if ( kIOReturnSuccess != result )
				HIDReportErrorNum( "\nHIDTransactionSetElementDefault failed to set Element Default: error = %ld.", result );
		} else {
			HIDReportError( "\nHIDTransactionSetElementDefault failed: no transaction interface" );
			if ( !result )
				result = kIOReturnError; // synthesis error
		}
	}
	return result;
}

/*************************************************************************
*
* HIDTransactionGetElementDefault( inDevice, inElement, inValueEvent )
*
* Purpose:  gets the default value of an element
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*			inValueEvent - address where to store default
*
* Returns:  IOReturn	- error code ( if any )
*			inValueEvent - the default
*
*/

IOReturn HIDTransactionGetElementDefault( hu_device_t * inDevice, const hu_element_t * inElement, IOHIDEventStruct* inValueEvent )
{
	IOReturn result = hu_CreateTransaction( inDevice );

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( inDevice->transaction ) {
			result = ( *( IOHIDOutputTransactionInterface** ) inDevice->transaction )->getElementDefault( inDevice->transaction, inElement->cookie, inValueEvent );
			if ( kIOReturnSuccess != result )
				HIDReportErrorNum( "\nHIDTransactionGetElementDefault failed to get Element Default: error = %ld.", result );
		} else {
			HIDReportError( "\nHIDTransactionGetElementDefault failed: no transaction interface" );
			if ( !result )
				result = kIOReturnError; // synthesis error
		}
	}
	return result;
}

/*************************************************************************
*
* HIDTransactionSetElementValue( inDevice, inElement, inValueEvent )
*
* Purpose:  Add a change to the transaction, by setting an element value
*
* Notes:	The change is not actually made until it is commited.
*			The element must be part of the transaction or this call will fail
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*			inValueEvent - the value to set the element to
*
* Returns:  IOReturn	- error code ( if any )
*
*/

IOReturn HIDTransactionSetElementValue( hu_device_t * inDevice, const hu_element_t * inElement, IOHIDEventStruct* inValueEvent )
{
	IOReturn result = hu_CreateTransaction( inDevice );

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( inDevice->transaction ) {
			result = ( *( IOHIDOutputTransactionInterface** ) inDevice->transaction )->setElementValue( inDevice->transaction, inElement->cookie, inValueEvent );
			if ( kIOReturnSuccess != result )
				HIDReportErrorNum( "\nHIDTransactionSetElementValue failed to set Element Default: error = %ld.", result );
		} else {
			HIDReportError( "\nHIDTransactionSetElementValue failed: no transaction interface" );
			if ( !result )
				result = kIOReturnError; // synthesis error
		}
	}
	return result;
}

/*************************************************************************
*
* HIDTransactionGetElementValue( inDevice, inElement, inValueEvent )
*
* Purpose:  get the value of a transactions element
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*			inValueEvent - address of where to store the value
*
* Returns:  IOReturn	- error code ( if any )
*			inValueEvent - the value
*
*/

IOReturn HIDTransactionGetElementValue( hu_device_t * inDevice, const hu_element_t * inElement, IOHIDEventStruct* inValueEvent )
{
	IOReturn result = hu_CreateTransaction( inDevice );

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( inDevice->transaction ) {
			result = ( *( IOHIDOutputTransactionInterface** ) inDevice->transaction )->getElementValue( inDevice->transaction, inElement->cookie, inValueEvent );
			if ( kIOReturnSuccess != result )
				HIDReportErrorNum( "\nHIDTransactionGetElementValue failed to get Element Default: error = %ld.", result );
		} else {
			HIDReportError( "\nHIDTransactionGetElementValue failed: no transaction interface" );
			if ( !result )
				result = kIOReturnError; // synthesis error
		}
	}
	return result;
}

/*************************************************************************
*
* HIDTransactionCommit( inDevice )
*
* Purpose:  Commit the transaction
*
* Inputs:   inDevice		- the device
*
* Returns:  IOReturn	- error code ( if any )
*
*/

IOReturn HIDTransactionCommit( hu_device_t * inDevice )
{
	IOReturn result = hu_CreateTransaction( inDevice );

	if ( HIDIsValidDevice( inDevice ) ) {
		if ( inDevice->transaction ) {
			result = ( *( IOHIDOutputTransactionInterface** ) inDevice->transaction )->commit( inDevice->transaction, -1, NULL, NULL, NULL );
			if ( kIOReturnSuccess != result )
				HIDReportErrorNum( "\nHIDTransactionCommit failed to commit: error = %ld.", result );
		} else {
			HIDReportError( "\nHIDTransactionCommit failed: no transaction interface" );
			if ( !result )
				result = kIOReturnError; // synthesis error
		}
	}
	return result;
}

/*************************************************************************
*
* HIDTransactionClear( inDevice )
*
* Purpose:  Clear all the changes and start over
*
* Inputs:   inDevice		- the device
*
* Returns:  IOReturn	- error code ( if any )
*
*/

IOReturn HIDTransactionClear( hu_device_t * inDevice )
{
	IOReturn result = hu_CreateTransaction( inDevice );

	if ( HIDIsValidDevice( inDevice ) ) {
		if ( inDevice->transaction ) {
			result = ( *( IOHIDOutputTransactionInterface** ) inDevice->transaction )->clear( inDevice->transaction );
			if ( kIOReturnSuccess != result )
				HIDReportErrorNum( "\nHIDTransactionClear failed to get Element Default: error = %ld.", result );
		} else {
			HIDReportError( "\nHIDTransactionClear failed: no transaction interface" );
			if ( !result )
				result = kIOReturnError; // synthesis error
		}
	}
	return result;
}

/*****************************************************/
#pragma mark - local ( static ) function implementations
/*****************************************************/

/*************************************************************************
*
* hu_CreateTransaction( inDevice )
*
* Purpose:  creates a transaction for a device.
*
* Notes:	allocates and creates the transaction interface if required
*
* Inputs:   inDevice		- the device
*
* Returns:  IOReturn	- error code ( if any )
*
*/

static IOReturn hu_CreateTransaction( hu_device_t * inDevice )
{
	IOReturn result = kIOReturnSuccess;	// assume success( optimist! )

	if ( HIDIsValidDevice( inDevice ) ) {
		if ( !inDevice->transaction ) {	// if we don't already have a transaction…
			if ( inDevice->interface ) {	// and we do have an interface…
				inDevice->transaction = ( void* ) ( *( IOHIDDeviceInterface** ) inDevice->interface )->allocOutputTransaction( inDevice->interface ); // alloc Transaction
				if ( inDevice->transaction ) {	// if it was successful…
					result = ( *( IOHIDOutputTransactionInterface** ) inDevice->transaction )->create( inDevice->transaction ); // create actual transaction
					if ( kIOReturnSuccess != result )
						HIDReportErrorNum( "\nFailed to create transaction via create: error = %ld.", result );
				} else {
					HIDReportError( "\nhu_CreateTransaction failed to allocOutputTransaction" );
					if ( !result )
						result = kIOReturnError; // synthesis error
				}
			} else {
				HIDReportErrorNum( "\nhu_CreateTransaction failed: Device inteface does not exist.", result );
			}
		}
	}
	return result;
}
