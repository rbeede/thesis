/* 
 * File:   TCPClient.h
 * Author: rbeede
 *
 * Created on March 23, 2012, 11:21 AM
 * 
 * Does connect and other socket operations with timeout option
 * 
 * getLastError() can be used after any call to look for errors
 */

#ifndef TCPCLIENT_H
#define	TCPCLIENT_H


#include <boost/asio.hpp>
#include <boost/lambda/lambda.hpp>  // useful for async handlers in-lined
#include <boost/lexical_cast.hpp>

#include "logger.hpp"
extern Logger * logger;


class TCPClient {
public:
	static const int TIMEOUT_SECONDS;
	
	/**
	 * 
      * @param _address
      * @param service Name of service or port number
      */
	TCPClient(const std::string address, const std::string service);
	virtual ~TCPClient();
	
	std::string getLastError();
	
	/**
	 * Consult getLastError() for error details
	 * 
      * @return true if successful, false if not.
      */
	bool connect();
	
	void close();
	
	/**
	 * Consult getLastError() for error details
	 * 
	 * Writes the exact specified number of bytes or fails with error
	 * 
      * @return true if successful, false if not.
      */
	bool send(const unsigned char * const bytes, const int bytes_length);
	
	//TODO receive method
	
	
	/**
	 * 
      * @return local-ip:port -> remote-ip:port if connected.  "NOT CONNECTED" otherwise
      */
	std::string getConnectionDetails();
	
	
	/**
	 * 
	 * @return local-ip:port if connected and local endpoint details is available.  empty string otherwise.
	 */
	std::string getLocalEndpointDetails();
private:
	const std::string address;
	const std::string service;  // name or port number

	std::string lastError;
	
	boost::asio::ip::tcp::resolver::iterator remoteEndpoint_iter;
	
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket sck;
};

#endif	/* TCPCLIENT_H */

