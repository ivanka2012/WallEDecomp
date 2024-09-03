/*
*	File:		HID_Queue_Utilities.c
*
*	Contains:	Implementation of the HID queue functions for the HID utilites.
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
#include "HID_Utilities_External.h"
/*****************************************************/
#pragma mark - typedefs, enums, defines, etc.
/*****************************************************/
#define USE_ASYNC_EVENTS TRUE
/*****************************************************/
#pragma mark - local ( static ) function prototypes
/*****************************************************/
static IOReturn hu_CreateQueue( hu_device_t * inDevice );
static unsigned char hu_IsDeviceQueueEmpty( const hu_device_t * inDevice );
static IOReturn hu_DisposeReleaseQueue( hu_device_t * inDevice );
/*****************************************************/
#pragma mark - exported globals
/*****************************************************/
#pragma mark - local ( static ) globals
/*****************************************************/
#pragma mark - exported function implementations
/*****************************************************/

/*************************************************************************
*
* HIDQueueElement( inDevice, inElement )
*
* Purpose:  queues specified element, performing any device queue set up required
*
* Notes:	queue is started and ready to return events on exit from this function
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*
* Returns:  SInt32		- error code ( if any )
*/

IOReturn HIDQueueElement( hu_device_t * inDevice, const hu_element_t * inElement )
{
	IOReturn result = kIOReturnSuccess;	// assume success( optimist! )

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( !inDevice->interface ) {	// must have interface
			HIDReportError( "\nHIDQueueElement - Device does not have interface." );
			return kIOReturnError;
		}
		if ( !inDevice->queue ) {	// if no queue create queue
			result = hu_CreateQueue( inDevice );
			if ( ( kIOReturnSuccess != result ) || ( !inDevice->queue ) ) {
				HIDReportErrorNum( "\nHIDQueueElement - problem creating queue.", result );
				if ( kIOReturnSuccess != result ) {
					return result;
				} else {
					return kIOReturnError;
				}
			}
		}

		// stop queue
		result = ( *( IOHIDQueueInterface** ) inDevice->queue )->stop( inDevice->queue );
		if ( kIOReturnSuccess != result ) {
			HIDReportError( "\nHIDQueueElement - Failed to stop queue." );
		}

		// queue element
		if ( !( *( IOHIDQueueInterface** ) inDevice->queue )->hasElement( inDevice->queue, inElement->cookie ) ) {
			result = ( *( IOHIDQueueInterface** ) inDevice->queue )->addElement( inDevice->queue, inElement->cookie, 0 );
			if ( kIOReturnSuccess != result ) {
				HIDReportError( "\nHIDQueueElement - Failed to add Element to queue." );
			}
		}

		// restart queue
		result = ( *( IOHIDQueueInterface** ) inDevice->queue )->start( inDevice->queue );
		if ( kIOReturnSuccess != result ) {
			HIDReportError( "\nHIDQueueElement - Failed to start queue." );
		}
	} else {
		HIDReportError( "\nHIDQueueElement - Invalid Device and/or element." );
		return kIOReturnBadArgument;
	}
	return result;
}

/*************************************************************************
*
* HIDQueueElement( inDevice, inElement )
*
* Purpose: adds all elements to queue, performing any device queue set up required
*
* Notes:	queue is started and ready to return events on exit from this function
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*
* Returns:  IOReturn		- error code ( if any )
*/

IOReturn HIDQueueDevice( hu_device_t * inDevice )
{
	IOReturn result = kIOReturnError;	// assume failure ( pessimist! )
	hu_element_t * inElement;

	if ( HIDIsValidDevice( inDevice ) ) {
		// error checking
		if ( !inDevice ) {
			HIDReportError( "\nHIDQueueDevice - Device does not exist." );
			return kIOReturnBadArgument;
		}
		if ( !inDevice->interface ) {	// must have interface
			HIDReportError( "\nHIDQueueDevice - Device does not have interface." );
			return kIOReturnError;
		}
		if ( !inDevice->queue ) {	// if no queue create queue
			result = hu_CreateQueue( inDevice );
			if ( ( kIOReturnSuccess != result ) || ( !inDevice->queue ) ) {
				HIDReportErrorNum( "\nHIDQueueDevice - problem creating queue.", result );
				if ( kIOReturnSuccess != result ) {
					return result;
				} else {
					return kIOReturnError;
				}
			}
		}

		// stop queue
		result = ( *( IOHIDQueueInterface** ) inDevice->queue )->stop( inDevice->queue );
		if ( kIOReturnSuccess != result ) {
			HIDReportErrorNum( "\nHIDQueueDevice - Failed to stop queue.", result );
		}

		// queue element
		//� inElement = HIDGetFirstDeviceElement( inDevice, kHIDElementTypeIO );
		inElement = HIDGetFirstDeviceElement( inDevice, kHIDElementTypeInput | kHIDElementTypeFeature );

		while ( inElement ) {
			if ( !( *( IOHIDQueueInterface** ) inDevice->queue )->hasElement( inDevice->queue, inElement->cookie ) ) {
				result = ( *( IOHIDQueueInterface** ) inDevice->queue )->addElement( inDevice->queue, inElement->cookie, 0 );
				if ( kIOReturnSuccess != result ) {
					HIDReportErrorNum( "\nHIDQueueDevice - Failed to add element to queue.", result );
				}
			}
			//� inElement = HIDGetNextDeviceElement( inElement, kHIDElementTypeIO );
			inElement = HIDGetNextDeviceElement( inElement, kHIDElementTypeInput | kHIDElementTypeFeature );
		}

		// start queue
		result = ( *( IOHIDQueueInterface** ) inDevice->queue )->start( inDevice->queue );
		if ( kIOReturnSuccess != result ) {
			HIDReportErrorNum( "\nHIDQueueDevice - Failed to start queue.", result );
		}

	} else {
		HIDReportError( "\nHIDQueueDevice - Invalid device." );
	}
	return result;
}

/*************************************************************************
*
* HIDDequeueElement( inDevice, inElement )
*
* Purpose: removes element for queue
*
* Notes:	if last element in queue then this will release queue and close device interface
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*
* Returns:  IOReturn		- error code ( if any )
*/

IOReturn HIDDequeueElement( hu_device_t * inDevice, const hu_element_t * inElement )
{
	IOReturn result = kIOReturnError;	// assume failure ( pessimist! )

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( !inDevice || !inElement ) {
			result = kIOReturnBadArgument;
		} else {
			if ( ( inDevice->interface ) && ( inDevice->queue ) ) {
				// stop queue
				result = ( *( IOHIDQueueInterface** ) inDevice->queue )->stop( inDevice->queue );
				if ( kIOReturnSuccess != result ) {
					HIDReportErrorNum( "\nHIDDequeueElement - Failed to stop queue.", result );
				}

				if ( ( *( IOHIDQueueInterface** ) inDevice->queue )->hasElement( inDevice->queue, inElement->cookie ) ) {	// if has element then remove
					result = ( *( IOHIDQueueInterface** ) inDevice->queue )->removeElement( inDevice->queue, inElement->cookie );
					if ( kIOReturnSuccess != result ) {
						HIDReportErrorNum( "\nHIDDequeueElement - Failed to add element to queue", result );
					}
				}

				if ( hu_IsDeviceQueueEmpty( inDevice ) ) {	// release device queue and close interface if queue empty
					result = hu_DisposeReleaseQueue( inDevice );
					if ( kIOReturnSuccess != result ) {
						HIDReportErrorNum( "\nHIDDequeueElement - Failed to dispose and release queue.", result );
					}
				} else {	// not empty so restart queue
					result = ( *( IOHIDQueueInterface** ) inDevice->queue )->start( inDevice->queue );
					if ( kIOReturnSuccess != result ) {
						HIDReportErrorNum( "\nHIDDequeueElement - Failed to start queue.", result );
					}
				}
			} else {
				HIDReportError( "\nHIDDequeueElement - No device inteface or queue." );
				return kIOReturnError;
			}
		}
	} else {
		HIDReportError( "\nHIDDequeueElement - Invalid device." );
	}
	return result;
}

/*************************************************************************
*
* HIDDequeueDevice( inDevice )
*
* Purpose: removes all device elements from queue
*
* Notes:	releases queue and closes device interface
*			does not release device interfaces,
*			application must call HIDReleaseDeviceList on exit
*
* Inputs:   inDevice		- the device
*
* Returns:  IOReturn		- error code ( if any )
*/

unsigned long HIDDequeueDevice( hu_device_t * inDevice )
{
	IOReturn result = kIOReturnSuccess;	// assume success( optimist! )

	if ( HIDIsValidDevice( inDevice ) ) {
		if ( ( inDevice->interface ) && ( inDevice->queue ) ) {
			// iterate through elements and if queued, remove
			hu_element_t * inElement = HIDGetFirstDeviceElement( inDevice, kHIDElementTypeIO );
			while ( inElement ) {
				if ( ( *( IOHIDQueueInterface** ) inDevice->queue )->hasElement( inDevice->queue, inElement->cookie ) ) {
					result = ( *( IOHIDQueueInterface** ) inDevice->queue )->removeElement( inDevice->queue, inElement->cookie );
					if ( kIOReturnSuccess != result ) {
						HIDReportErrorNum( "\nHIDDequeueDevice - Failed to remove element from queue.", result );
					}
				}
				inElement = HIDGetNextDeviceElement( inElement, kHIDElementTypeIO );
			}
		}
		// ensure queue is disposed and released
		// interface will be closed and released on call to HIDReleaseDeviceList
		if ( inDevice->queue ) {
			result = hu_DisposeReleaseQueue( inDevice );
			if ( kIOReturnSuccess == result ) {
				
			} else {
				HIDReportErrorNum( "\nremoveElement - Failed to dispose and release queue.", result );
			}
		}
	} else {
		HIDReportError( "\nHIDDequeueDevice - Invalid device." );
		result = kIOReturnBadArgument;
	}
	return result;
}

/*************************************************************************
*
* HIDReleaseAllDeviceQueues( )
*
* Purpose: releases all device queues for quit or rebuild
*
* Notes:	MUST BE CALLED
*			does not release device interfaces,
*			application must call HIDReleaseDeviceList on exit
*
* Inputs:   none
*
* Returns:  IOReturn		- error code ( if any )
*/

IOReturn HIDReleaseAllDeviceQueues( void )
{
	IOReturn result = kIOReturnBadArgument;	// assume failure ( pessimist! )
	hu_device_t * tDevice = HIDGetFirstDevice( );

	while ( tDevice ) {
		result = HIDDequeueDevice( tDevice );
		if ( kIOReturnSuccess != result ) {
			HIDReportErrorNum( "\nHIDReleaseAllDeviceQueues - Could not dequeue device.", result );
		}
		tDevice = HIDGetNextDevice( tDevice );
	}
	return result;
}

/*************************************************************************
*
* HIDCloseReleaseInterface( inDevice )
*
* Purpose: Closes and releases interface to device
*
* Notes:	should be done prior to exting application
*			will have no affect if device or interface do not exist
*			application will "own" the device if interface is not closed
*			device may have to be plug and re-plugged in different location
*			to get it working again without a restart )
*
* Inputs:   inDevice		- the device
*
* Returns:  IOReturn		- error code ( if any )
*/

unsigned long HIDCloseReleaseInterface( hu_device_t * inDevice )
{
	IOReturn result = kIOReturnSuccess;
	if ( HIDIsValidDevice( inDevice ) && inDevice->interface ) {
		// close the interface
		result = ( *( IOHIDDeviceInterface** ) inDevice->interface )->close( inDevice->interface );
		if ( kIOReturnNotOpen == result ) {
			// do nothing as device was not opened, thus can't be closed
		} else if ( kIOReturnSuccess != result ) {
			HIDReportErrorNum( "\nHIDCloseReleaseInterface - Failed to close IOHIDDeviceInterface.", result );
		}
		//release the interface
		result = ( *( IOHIDDeviceInterface** ) inDevice->interface )->Release( inDevice->interface );
		if ( kIOReturnSuccess != result ) {
			HIDReportErrorNum( "\nHIDCloseReleaseInterface - Failed to release interface.", result );
		}
		inDevice->interface = NULL;
	}
	return result;
}

/*************************************************************************
*
* HIDGetEvent( inDevice, outHIDEvent )
*
* Purpose: Get the next event in the queue for a device
*
* Notes:	elements or entire device should be queued prior to calling this with HIDQueueElement or HIDQueueDevice
*			kIOReturnUnderrun returned from getNextEvent indicates an empty queue not an error condition
*			application should pass in a pointer to a IOHIDEventStruct cast to a void( for CFM compatibility )
*
* Inputs:   inDevice		- the device
*			outHIDEvent   - address where to put event info if available
*
* Returns:  Boolean		- TRUE if an event is avialable for the element.
*			outHIDEvent   - filled out if return is TRUE.
*/

Boolean HIDGetEvent( const hu_device_t * inDevice, void* outHIDEvent )
{
	IOReturn result = kIOReturnBadArgument;	// assume failure ( pessimist! )
	AbsoluteTime zeroTime = {0, 0};

	if ( HIDIsValidDevice( inDevice ) ) {
		if ( inDevice->queue ) {
			result = ( *( IOHIDQueueInterface** ) inDevice->queue )->getNextEvent( inDevice->queue, ( IOHIDEventStruct * )outHIDEvent, zeroTime, 0 );
			if ( kIOReturnUnderrun == result ) {
				return FALSE; // no events in queue not an error per say
			} else if ( kIOReturnSuccess != result ) { // actual error versus just an empty queue
				HIDReportErrorNum( "\nHIDGetEvent - Could not get HID event via getNextEvent.", result );
			} else {
				return TRUE;
			}
		} else {
			HIDReportError( "\nHIDGetEvent - queue does not exist." );
		}
	} else  {
		HIDReportError( "\nHIDGetEvent - invalid device." );
	}
	return FALSE; // did not get event
}


/*************************************************************************
*
* HIDGetElementEvent( inDevice, inElement, outIOHIDEvent )
*
* Purpose:  returns current value for element, polling element
*
* Inputs:   inDevice				- the device
*			inElement			- the element
*			outIOHIDEvent			- address where to return the event
*
* Returns:  IOReturn				- error code ( if any )
*			outIOHIDEvent			- the event
*/
IOReturn HIDGetElementEvent( const hu_device_t * inDevice, hu_element_t * inElement, IOHIDEventStruct* outIOHIDEvent )
{
	IOReturn result = kIOReturnBadArgument; 	// assume failure ( pessimist! )
	IOHIDEventStruct hidEvent;

	hidEvent.value = 0;
	hidEvent.longValueSize = 0;
	hidEvent.longValue = nil;

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( inDevice->interface ) {
			// ++ NOTE: If the element type is feature then use queryElementValue instead of getElementValue
			if ( kIOHIDElementTypeFeature == inElement->type ) {
				result = ( *( IOHIDDeviceInterface** ) inDevice->interface )->queryElementValue( inDevice->interface, inElement->cookie, &hidEvent, 0, NULL, NULL, NULL );
				if ( kIOReturnUnsupported == result )	// unless it's unsuported.
					goto try_getElementValue;
				else if ( kIOReturnSuccess != result ) {
					HIDReportErrorNum( "\nHIDGetElementEvent - Could not get HID element value via queryElementValue.", result );
				}
			} else if ( inElement->type <= kIOHIDElementTypeInput_ScanCodes ) {
try_getElementValue:
				result = ( *( IOHIDDeviceInterface** ) inDevice->interface )->getElementValue( inDevice->interface, inElement->cookie, &hidEvent );
				if ( kIOReturnSuccess != result ) {
					HIDReportErrorNum( "\nHIDGetElementEvent - Could not get HID element value via getElementValue.", result );
				}
			}

			// on 10.0.x this returns the incorrect result for negative ranges, so fix it!!!
			// this is not required on Mac OS X 10.1+
			if ( ( inElement->min < 0 ) && ( hidEvent.value > inElement->max ) ) {	// assume range problem
				hidEvent.value = hidEvent.value + inElement->min - inElement->max - 1;
			}

			*outIOHIDEvent = hidEvent;
		} else {
			HIDReportError( "\nHIDGetElementEvent - no interface for device." );
		}
	} else {
		HIDReportError( "\nHIDGetElementEvent - invalid device and/or element." );
	}

	// record min and max for auto scale and auto ...
	if ( hidEvent.value < inElement->minReport )
		inElement->minReport = hidEvent.value;
	if ( hidEvent.value > inElement->maxReport )
		inElement->maxReport = hidEvent.value;
	return result;
}

/*************************************************************************
*
* HIDGetElementValue( inDevice, inElement )
*
* Purpose:  returns the current value for an element( polling )
*
* Notes:		will return 0 on error conditions which should be accounted for by application
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*
* Returns:  SInt32		- current value for element
*/

long HIDGetElementValue( const hu_device_t * inDevice, hu_element_t * inElement )
{
	long result = 0;

	IOHIDEventStruct hidEvent;
	if ( kIOReturnSuccess == HIDGetElementEvent( inDevice, inElement, &hidEvent ) ) {
		result = hidEvent.value;
	}
	return result;
}

/*************************************************************************
*
* HIDSetElementValue( inDevice, inElement, outIOHIDEvent )
*
* Purpose:  Set an elements value
*
* Notes:	This should only be used when a single element of a report needs to be sent.
*			If multiple elements are to be send then transactions should be used.
*
* Inputs:   inDevice		- the device
*			inElement	- the element
*			outIOHIDEvent - the element value to be set
*
* Returns:  IOReturn		- error code ( if any )
*/

IOReturn HIDSetElementValue( const hu_device_t * inDevice, const hu_element_t * inElement, void* outIOHIDEvent )
{
	IOHIDEventStruct* pMyIOHIDEvent = ( IOHIDEventStruct* ) outIOHIDEvent;
	IOReturn result = kIOReturnError;	// assume failure ( pessimist! )

	if ( HIDIsValidElement( inDevice, inElement ) ) {
		if ( inDevice->interface ) {
			result = ( *( IOHIDDeviceInterface** ) inDevice->interface )->setElementValue( inDevice->interface, inElement->cookie, pMyIOHIDEvent, -1, nil, nil, nil );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nHIDSetElementValue - Could not set HID element value via setElementValue.", result );
			}
		} else {
			HIDReportError( "\nHIDSetElementValue - no interface for device." );
		}
	} else {
		HIDReportError( "\nHIDSetElementValue - invalid device and/or element." );
	}
	return result;
}

/*************************************************************************
*
* HIDSetQueueCallback( inDevice, inIOHIDCallback, inCallbackTarget, inCallbackRefcon )
*
* Purpose:  Set a callback to be called when a queue goes from empty to non-empty
*
* Notes:	inIOHIDCallback is a MachO function pointer.
*			If you're using CFM you have to call MachOFunctionPointerForCFMFunctionPointer.
*
* Inputs:   inDevice			- the device
*			inIOHIDCallback  - address of( MachO ) callback routine
*			inCallbackTarget - callback target
*			inCallbackRefcon - callback refcon
*
* Returns:  IOReturn		- error code ( if any )
*/
IOReturn HIDSetQueueCallback( hu_device_t * inDevice, IOHIDCallbackFunction inIOHIDCallback, void* inCallbackTarget, void* inCallbackRefcon )
{
	IOReturn result = kIOReturnError;	// assume failure ( pessimist! )
#if USE_ASYNC_EVENTS
	if ( HIDIsValidDevice( inDevice ) ) {
		if ( !inDevice->queue ) {	// if no queue create queue
			result = hu_CreateQueue( inDevice );
			if ( ( kIOReturnSuccess != result ) || ( !inDevice->queue ) ) {
				HIDReportErrorNum( "\nHIDSetQueueCallback - problem creating queue.", result );
				if ( kIOReturnSuccess != result ) {
					return result;
				} else {
					return kIOReturnError;
				}
			}
		}

		// if we don't have a queue runloop source�
		if ( !inDevice->queueRunLoopSource ) {
			// then create one
			result = ( *( IOHIDQueueInterface** ) inDevice->queue )->createAsyncEventSource( ( void* ) inDevice->queue,
																					  ( CFRunLoopSourceRef* ) &inDevice->queueRunLoopSource );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nHIDSetQueueCallback - Failed to createAsyncEventSource error: ", result );
			}
		}
		// if we have one now�
		if ( inDevice->queueRunLoopSource ) {
			// and it's not already attached to our runloop�
			if ( !CFRunLoopContainsSource( CFRunLoopGetCurrent( ), inDevice->queueRunLoopSource, kCFRunLoopDefaultMode ) )
				// then attach it now.
				CFRunLoopAddSource( CFRunLoopGetCurrent( ), inDevice->queueRunLoopSource, kCFRunLoopDefaultMode );
		}

		// now install our callback
		result = ( *( IOHIDQueueInterface** ) inDevice->queue )->setEventCallout( inDevice->queue, inIOHIDCallback, inCallbackTarget, inCallbackRefcon );
		if ( kIOReturnSuccess != result ) {
			HIDReportErrorNum( "\nHIDSetQueueCallback - Could not set HID queue callback via setEventCallout.", result );
		}
	} else {
		HIDReportError( "\nHIDSetQueueCallback - invalid device and/or element." );
	}
#endif USE_ASYNC_EVENTS
	return result;
}

#if defined( AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER )
/*************************************************************************
*
* HIDGetReport( inDevice, inIOHIDReportType, inReportID, inReportBuffer, inReportBufferSize )
*
* Purpose:  Get a report from a device
*
* Inputs:   inDevice				- the device
*			inIOHIDReportType	- the type of report to get
*			inReportID			- the report ID to get
*			inReportBuffer		- the address of the report buffer
*			inReportBufferSize   - the size of the report buffer
*
* Returns:  IOReturn		- error code ( if any )
*/
IOReturn HIDGetReport( const hu_device_t * inDevice, IOHIDReportType inIOHIDReportType, UInt32 inReportID, void* inReportBuffer, int* inReportBufferSize )
{
	IOReturn result = kIOReturnError;	// assume failure ( pessimist! )

	if ( HIDIsValidDevice( inDevice ) ) {
		if ( inDevice->interface ) {
			result = ( *( IOHIDDeviceInterface121** ) inDevice->interface )->getReport( inDevice->interface, inIOHIDReportType, inReportID, inReportBuffer, ( void* ) inReportBufferSize, -1, nil, nil, nil );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nHIDGetReport - Could not getReport, error: ", result );
			}
		} else {
			HIDReportError( "\nHIDGetReport - no interface for device." );
		}
	} else {
		HIDReportError( "\nHIDGetReport - invalid device." );
	}
	return result;
}

/*************************************************************************
*
* HIDSetReport( inDevice, inIOHIDReportType, inReportID, inReportBuffer, inReportBufferSize )
*
* Purpose:  Send a report to a device
*
* Inputs:   inDevice				- the device
*			inIOHIDReportType	- the type of report to send
*			inReportID			- the report ID to send
*			inReportBuffer		- the address of the report buffer to send
*			inReportBufferSize   - the size of the report buffer to send
*
* Returns:  IOReturn		- error code ( if any )
*/
IOReturn HIDSetReport( const hu_device_t * inDevice, IOHIDReportType inIOHIDReportType, UInt32 inReportID, void* inReportBuffer, int inReportBufferSize )
{
	IOReturn result = kIOReturnError;	// assume failure ( pessimist! )

	if ( HIDIsValidDevice( inDevice ) ) {
		if ( inDevice->interface ) {
			result = ( *( IOHIDDeviceInterface121** ) inDevice->interface )->setReport( inDevice->interface, inIOHIDReportType, inReportID, inReportBuffer, inReportBufferSize, -1, nil, nil, nil );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nHIDSetReport - Could not setReport; error: ", result );
			}
		} else {
			HIDReportError( "\nHIDSetReport - no interface for device." );
		}
	} else {
		HIDReportError( "\nHIDSetReport - invalid device." );
	}
	return result;
}
#endif // defined( AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER )


#if defined( AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER )
/*************************************************************************
*
* HIDCopyMatchingElements( inDevice, inMatchingDict, inElements )
*
* Purpose:  copy matching elements
*
* Inputs:   inDevice				- the device
*			inMatchingDict		- the matching dictionary
*			inElements			- the address where to store elements that match
*
* Returns:  IOReturn				- error code ( if any )
*			inElements			- the elements that match
*/
IOReturn HIDCopyMatchingElements( const hu_device_t * inDevice, CFDictionaryRef inMatchingDict, CFArrayRef* inElements )
{
	IOReturn result = kIOReturnError;	// assume failure ( pessimist! )

	if ( HIDIsValidDevice( inDevice ) ) {
		if ( inDevice->interface ) {
			result = ( *( IOHIDDeviceInterface122** ) inDevice->interface )->copyMatchingElements( inDevice->interface, inMatchingDict, inElements );
			if ( kIOReturnSuccess != result )
				HIDReportErrorNum( "\nHIDCopyMatchingElements - Could not getReport, error: ", result );
		} else {
			HIDReportError( "\nHIDCopyMatchingElements - no interface for device." );
		}
	} else {
		HIDReportError( "\nHIDCopyMatchingElements - invalid device." );
	}
	return result;
}

/*************************************************************************
*
* HIDSetInterruptReportHandlerCallback( inDevice, inReportBuffer, inReportBufferSize, inIOHIDReportCallback, inCallbackTarget, inCallbackRefcon )
*
* Purpose:  Set a callback to be called when a report comes in the interrupt pipe
*
* Notes:	inIOHIDCallback is a MachO function pointer.
*			If you're using CFM you have to call MachOFunctionPointerForCFMFunctionPointer.
*
* Inputs:   inDevice					- the device
*			inReportBuffer			- the address where the report will be stored
*			inReportBufferSize		- the size of the buffer where the report will be stored
*			inIOHIDReportCallback	- address of( MachO ) callback routine
*			inCallbackTarget			- callback target
*			inCallbackRefcon			- callback refcon
*
* Returns:  IOReturn				- error code ( if any )
*/
IOReturn HIDSetInterruptReportHandlerCallback( const hu_device_t * inDevice, void* inReportBuffer, int inReportBufferSize, IOHIDReportCallbackFunction inIOHIDReportCallback, void* inCallbackTarget, void* inCallbackRefcon )
{
	IOReturn result = kIOReturnError;	// assume failure ( pessimist! )
#if USE_ASYNC_EVENTS
	if ( HIDIsValidDevice( inDevice ) ) {
		// if we don't have a runloop source�
		if ( !inDevice->runLoopSource ) {
			// then create one
			result = ( *( IOHIDDeviceInterface** ) inDevice->interface )->createAsyncEventSource( ( void* ) inDevice->interface, ( CFRunLoopSourceRef* ) &inDevice->runLoopSource );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nHIDSetInterruptReportHandlerCallback - Failed to createAsyncEventSource error: ", result );
			}
		}
		// if we have one now�
		if ( inDevice->runLoopSource ) {
			// and it's not already attached to our runloop�
			if ( !CFRunLoopContainsSource( CFRunLoopGetCurrent( ), inDevice->runLoopSource, kCFRunLoopDefaultMode ) )
				// then attach it now.
				CFRunLoopAddSource( CFRunLoopGetCurrent( ), inDevice->runLoopSource, kCFRunLoopDefaultMode );
		}

		// now install our callback
		result = ( *( IOHIDDeviceInterface122** ) inDevice->interface )->setInterruptReportHandlerCallback( inDevice->interface, inReportBuffer, inReportBufferSize, inIOHIDReportCallback, inCallbackTarget, inCallbackRefcon );
		if ( kIOReturnSuccess != result ) {
			HIDReportErrorNum( "\nHIDSetInterruptReportHandlerCallback - Could not set HID queue callback via setEventCallout.", result );
		}
	} else {
		HIDReportError( "\nHIDSetInterruptReportHandlerCallback - invalid device and/or element." );
	}
#endif USE_ASYNC_EVENTS
	return result;
}

#endif // defined( AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER )

/*****************************************************/
#pragma mark - local ( static ) function implementations
/*****************************************************/

/*************************************************************************
*
* hu_CreateQueue( inDevice )
*
* Purpose:  creates a queue for a device
*
* Inputs:   inDevice					- the device
*
* Returns:  IOReturn 				- error code ( if any )
*/
static IOReturn hu_CreateQueue( hu_device_t * inDevice )
{
	IOReturn result = kIOReturnSuccess;	// assume success( optimist! )

	if ( HIDIsValidDevice( inDevice ) ) {
		if ( !inDevice->queue ) {	// do we already have a queue
			if ( inDevice->interface ) {
				inDevice->queue = ( void* ) ( *( IOHIDDeviceInterface** ) inDevice->interface )->allocQueue( inDevice->interface ); // alloc queue
				if ( inDevice->queue ) {
#ifndef kIOHIDQueueOptionsTypeEnqueueAll
#define kIOHIDQueueOptionsTypeEnqueueAll 1
#endif
					result = ( *( IOHIDQueueInterface** ) inDevice->queue )->create( inDevice->queue, kIOHIDQueueOptionsTypeEnqueueAll, kDeviceQueueSize ); // create actual queue
					if ( kIOReturnSuccess != result ) {
						HIDReportErrorNum( "\nhu_CreateQueue - Failed to create queue via create", result );
					}
				} else {
					HIDReportError( "\nhu_CreateQueue - Failed to alloc IOHIDQueueInterface  **via allocQueue" );
					result = kIOReturnError; // synthesis error
				}
			} else {
				HIDReportErrorNum( "\nhu_CreateQueue - Device inteface does not exist for queue creation", result );
			}
		}
	} else {
		HIDReportErrorNum( "\nhu_CreateQueue - Invalid Device", result );
	}
	return result;
}	// hu_CreateQueue

/*************************************************************************
*
* hu_IsDeviceQueueEmpty( inDevice )
*
* Purpose:  checks a devices queue for incomming events
*
* Inputs:   inDevice					- the device
*
* Returns:  Boolean 				- TRUE if queue is empty; FALSE otherwise.
*/

static unsigned char hu_IsDeviceQueueEmpty( const hu_device_t * inDevice )
{
	if ( HIDIsValidDevice( inDevice ) ) {	// need valid device
		if ( inDevice->queue ) {	// and queue
			hu_element_t * inElement = HIDGetFirstDeviceElement( inDevice, kHIDElementTypeIO );
			while ( inElement ) {
				if ( ( *( IOHIDQueueInterface** ) inDevice->queue )->hasElement( inDevice->queue, inElement->cookie ) ) {
					return FALSE;
				}
				inElement = HIDGetNextDeviceElement( inElement, kHIDElementTypeIO );
			}
		} else {
			HIDReportError( "\nhu_IsDeviceQueueEmpty - no queue." );
		}
	} else {
		HIDReportError( "\nhu_IsDeviceQueueEmpty - Invalid device." );
	}
	return TRUE;
}

/*************************************************************************
*
* hu_DisposeReleaseQueue( inDevice )
*
* Purpose:  disposes and releases queue, sets queue to NULL
*
* Inputs:   inDevice					- the device
*
* Returns:  IOReturn 				- error code ( if any )
*/

static IOReturn hu_DisposeReleaseQueue( hu_device_t * inDevice )
{
	IOReturn result = kIOReturnSuccess;	// assume success( optimist! )

	if ( HIDIsValidDevice( inDevice ) ) {	// need valid device
		if ( inDevice->queue ) {	// and queue
			// stop queue
			result = ( *( IOHIDQueueInterface** ) inDevice->queue )->stop( inDevice->queue );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nhu_DisposeReleaseQueue - Failed to stop queue.", result );
			}
			// dispose of queue
			result = ( *( IOHIDQueueInterface** ) inDevice->queue )->dispose( inDevice->queue );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nhu_DisposeReleaseQueue - Failed to dipose queue.", result );
			}
			// release the queue
			result = ( *( IOHIDQueueInterface** ) inDevice->queue )->Release( inDevice->queue );
			if ( kIOReturnSuccess != result ) {
				HIDReportErrorNum( "\nhu_DisposeReleaseQueue - Failed to release queue.", result );
			}

			inDevice->queue = NULL;
#if USE_ASYNC_EVENTS
			if ( inDevice->queueRunLoopSource ) {
				if ( CFRunLoopContainsSource( CFRunLoopGetCurrent( ), inDevice->queueRunLoopSource, kCFRunLoopDefaultMode ) )
					CFRunLoopRemoveSource( CFRunLoopGetCurrent( ), inDevice->queueRunLoopSource, kCFRunLoopDefaultMode );
				CFRelease( inDevice->queueRunLoopSource );
				inDevice->queueRunLoopSource = NULL;
			}
#endif USE_ASYNC_EVENTS
		} else {
			HIDReportError( "\nhu_DisposeReleaseQueue - no queue." );
		}
	} else {
		HIDReportError( "\nhu_DisposeReleaseQueue - Invalid device." );
	}
	return result;
}
