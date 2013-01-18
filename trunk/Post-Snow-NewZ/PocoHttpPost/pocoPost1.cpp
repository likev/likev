#include<iostream>
#include "Poco/Net/HTMLForm.h"
#include "Poco/URI.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/NetException.h"

void pocoPost1()
{
	Poco::Net::HTMLForm form1;
	form1.add("abc","333");
	form1.add("abc","222");

	form1.write(std::cout);
}

void pocoPost2(const std::string &url, const std::string &key, const std::string &value)
{
	Poco::URI purl(url);

	try
	{
		Poco::Net::HTTPClientSession session( purl.getHost(), purl.getPort() );
		session.setProxy("172.18.172.251",80);

		Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, purl.getPath(), Poco::Net::HTTPMessage::HTTP_1_1);

		Poco::Net::HTMLForm form;
		form.add(key, value);

		// Send the request.
		form.prepareSubmit(req);
		std::ostream& ostr = session.sendRequest(req);
		form.write(ostr);

		Poco::Net::HTTPResponse res;

		std::istream& istr = session.receiveResponse(res);
		Poco::StreamCopier::copyStream(istr, std::cout);
		std::cout<<std::endl;
	}
	catch(Poco::Net::NetException& ex)
	{
		std::cout<<"post wrong: "<<ex.displayText();
	}
}