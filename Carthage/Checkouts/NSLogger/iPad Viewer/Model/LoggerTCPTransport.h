/*
 * LoggerTCPTransport.h
 *
 * Default transport for NSLogger messages, publishes a Bonjour service,
 * and can listen on a specific port (or by default on a port attributed by
 * the OS). In case we listen on a specific, user-defined port, the Bonjour
 * service name will be suffixed
 *
 * BSD license follows (http://www.opensource.org/licenses/bsd-license.php)
 * 
 * Copyright (c) 2010-2013 Florent Pillet <fpillet@gmail.com> All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of  source code  must retain  the above  copyright notice,
 * this list of  conditions and the following  disclaimer. Redistributions in
 * binary  form must  reproduce  the  above copyright  notice,  this list  of
 * conditions and the following disclaimer  in the documentation and/or other
 * materials  provided with  the distribution.  Neither the  name of  Florent
 * Pillet nor the names of its contributors may be used to endorse or promote
 * products  derived  from  this  software  without  specific  prior  written
 * permission.  THIS  SOFTWARE  IS  PROVIDED BY  THE  COPYRIGHT  HOLDERS  AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A  PARTICULAR PURPOSE  ARE DISCLAIMED.  IN  NO EVENT  SHALL THE  COPYRIGHT
 * HOLDER OR  CONTRIBUTORS BE  LIABLE FOR  ANY DIRECT,  INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY,  OR CONSEQUENTIAL DAMAGES (INCLUDING,  BUT NOT LIMITED
 * TO, PROCUREMENT  OF SUBSTITUTE GOODS  OR SERVICES;  LOSS OF USE,  DATA, OR
 * PROFITS; OR  BUSINESS INTERRUPTION)  HOWEVER CAUSED AND  ON ANY  THEORY OF
 * LIABILITY,  WHETHER  IN CONTRACT,  STRICT  LIABILITY,  OR TORT  (INCLUDING
 * NEGLIGENCE  OR OTHERWISE)  ARISING  IN ANY  WAY  OUT OF  THE  USE OF  THIS
 * SOFTWARE,   EVEN  IF   ADVISED  OF   THE  POSSIBILITY   OF  SUCH   DAMAGE.
 * 
 */

#import "LoggerTransport.h"

@class LoggerTCPConnection;

@interface LoggerTCPTransport : LoggerTransport <NSNetServiceDelegate, NSStreamDelegate>
{
	NSThread			*listenerThread;
	NSNetService		*bonjourService;
	CFSocketRef			listenerSocket_ipv4;
	CFSocketRef			listenerSocket_ipv6;
	NSString			*bonjourServiceName;
	NSInteger			listenerPort;
	BOOL				publishBonjourService;
}

@property (nonatomic, assign) NSInteger listenerPort;
@property (nonatomic, assign) BOOL publishBonjourService;
@property (nonatomic, readonly) CFSocketRef listenerSocket_ipv4;
@property (nonatomic, readonly) CFSocketRef listenerSocket_ipv6;


// methods to override by subclasses
- (NSString *)bonjourServiceName;
- (NSString *)bonjourServiceType;
- (NSInteger)tcpPort;
- (LoggerConnection *)connectionWithInputStream:(NSInputStream *)is clientAddress:(NSData *)addr;
- (void)processIncomingData:(LoggerTCPConnection *)cnx;

// added for iPad Version
- (void)closeSockets;
@end

extern void AcceptSocketCallback(CFSocketRef sock, CFSocketCallBackType type, CFDataRef address, const void *data, void *info);
