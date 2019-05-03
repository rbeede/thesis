#include "TCPClient.hpp"

const int TCPClient::TIMEOUT_SECONDS = 5;

TCPClient::TCPClient(const std::string address, const std::string service) : address(address), service(service), sck(io_service) {
	boost::asio::ip::tcp::resolver resolver(this->io_service);

	// Resolve address and service
	boost::asio::ip::tcp::resolver::query query(address, service);
	
	// Multiple possible (IPv4, IPv6, etc)
	boost::system::error_code ec;
	this->remoteEndpoint_iter = resolver.resolve(query, ec);
	if(ec) {
		this->lastError = ec.message();
		return;
	}
}

TCPClient::~TCPClient() {
}


std::string TCPClient::getLastError() {
	return this->lastError;
}


bool TCPClient::connect() {
	// Do an async connect with a timeout
	logger->log("DEBUG:  Starting connect attempt to " + this->address + ":" + this->service);
	
	// Need async mode to update value we can check.  Since async_connect will never set would_block we can use that as
	//	a value to indicate connect has not completed
	boost::system::error_code connectResult_ec = boost::asio::error::would_block;
	
	boost::asio::deadline_timer timer(this->io_service);
	timer.expires_from_now(boost::posix_time::seconds(TCPClient::TIMEOUT_SECONDS));
	
	logger->log("DEBUG:  TCPClient async_connect call start");
	boost::asio::async_connect(this->sck, this->remoteEndpoint_iter, boost::lambda::var(connectResult_ec) = boost::lambda::_1);
	logger->log("DEBUG:  TCPClient async_connect call end");
	
	// Loop until we've either timed out or a successful connection has been made
	while(boost::asio::error::would_block == connectResult_ec && !timer.expires_from_now().is_negative()) {
		this->io_service.run_one();
	}
	

	// Look for any reported errors
	if(connectResult_ec) {
		this->lastError = connectResult_ec.message();
		return false;
	} else if(timer.expires_from_now().is_negative()) {
		this->lastError = "Timed out connecting to " + this->address + ":" + this->service;
		return false;
	} else {
		// successful connection
		logger->log("DEBUG:  TCPClient successful connection");
		return true;
	}
}


void TCPClient::close() {
	if(this->sck.is_open()) {
		logger->log("DEBUG:  TCPClient close() for " + this->address + ":" + this->service);
		boost::system::error_code ignored_ec;  // prevents thrown error
		this->sck.close(ignored_ec);
	}
}


bool TCPClient::send(const unsigned char * bytes, const int bytes_length) {
	if(bytes_length <= 0) {
		return true;
	}
	
	std::size_t byteCount = 0;
	
	// Need async mode to update value we can check.  Since async operations will never set would_block we can use that
	//	as a value to indicate connect has not completed
	boost::system::error_code result_ec = boost::asio::error::would_block;
	
	boost::asio::deadline_timer timer(this->io_service);
	timer.expires_from_now(boost::posix_time::seconds(TCPClient::TIMEOUT_SECONDS * 10));
	
	boost::asio::async_write(this->sck, boost::asio::buffer(bytes, bytes_length),
		   boost::lambda::unlambda((
			(boost::lambda::var(result_ec) = boost::lambda::_1, boost::lambda::var(byteCount) = boost::lambda::_2)
		   ))
		   );
	
	// Loop until we've either timed out or a successful send has finished
	boost::system::error_code io_service_ec;
	while(boost::asio::error::would_block == result_ec && !timer.expires_from_now().is_negative()) {
		this->io_service.run_one(io_service_ec);
	}
	
	// Verify what we sent
	if(boost::asio::error::would_block == result_ec && timer.expires_from_now().is_negative()) {
		// timeout
		this->lastError = "Socket timeout";
		return false;
	} else if(result_ec) {
		this->lastError = result_ec.message();
		return false;
	} else if(bytes_length != byteCount) {
		this->lastError = "Only sent " + boost::lexical_cast<std::string>(byteCount)
			   + " bytes when expected "
			   + boost::lexical_cast<std::string>(bytes_length)
			   + " bytes";
		return false;
	} else {
		// Success
		timer.cancel();
		return true;
	}
}


std::string TCPClient::getLocalEndpointDetails() {
	std::string details;
	
	// need to catch thrown exception to prevent app crash
	boost::system::error_code ec;
	
	ec.clear();
	boost::asio::ip::tcp::endpoint localEndpoint = this->sck.local_endpoint(ec);  
	if(ec) {
		// Connection was just dropped by either side or one side has not accepted/handled
		return "NOT CONNECTED";
	} else {
		ec.clear();
		details += localEndpoint.address().to_string(ec);
		if(ec) {
			details += "(WITH address().to_string(ec) ERROR of " + ec.message() + ")";
		}
		
		details += ":";
		
		details += boost::lexical_cast<std::string>(localEndpoint.port());
	}
	
	return details;
}


std::string TCPClient::getConnectionDetails() {
	std::string details;
	
	if(!this->sck.is_open()) {  // is_open does not test if connection is still established, only if socket thinks it is
		return "NOT CONNECTED";
	}
	
	if(this->getLocalEndpointDetails().empty()) {
		return "NOT CONNECTED";
	} else {
		details += this->getLocalEndpointDetails();
	}
	
	details += " -> ";
	
	boost::system::error_code ec;
	ec.clear();
	boost::asio::ip::tcp::endpoint remoteEndpoint = this->sck.remote_endpoint(ec);  
	if(ec) {
		// Connection was just dropped by either side or one side has not accepted/handled
		return "NOT CONNECTED";
	} else {
		ec.clear();
		details += remoteEndpoint.address().to_string(ec);
		if(ec) {
			details += "(WITH address().to_string(ec) ERROR of " + ec.message() + ")";
		}
		
		details += ":";
		
		details += boost::lexical_cast<std::string>(remoteEndpoint.port());
	}
	
	return details;
}