# Application Test

```
#ifndef _APPLOGIN_H_
#define _APPLOGIN_H_

#include "Post.h"

namespace rest {

/*
 *
 */
class AppLogin: public Post {
public:
	AppLogin();
	virtual ~AppLogin();

public:
	int setUserAccount(std::string account);
	int setUserPassword(std::string password);
	std::string getConsumerKey();
	std::string getAuthorizationToken();
	std::string getAutoLoginKey();

	virtual bool setResponse(const cpr::Response& r)  throw (RestException, RestExceptionExt);
};

} /* namespace rest */ //end of rest

#endif /* _APPLOGIN_H_ */
```

#include "AppLogin.h"
#include "log/log_utils.h"

namespace rest {

const char * const vId     					= "id";
const char * const vPassword   				= "password";
const char * const vAutoLoginFlag			= "autoLoginFlag";
const char * const vServiceId				= "serviceId";

const char * const vConsumerKey				= "consumerKey";
const char * const vAuthorizationToken		= "authorizationToken";
const char * const vAutoLoginKey			= "autoLoginKey";
const char * const vUserStatus				= "userStatus";
const char * const vRequiredConfirmTerms	= "requiredConfirmTerms";
const char * const vReadOnly				= "readOnly";

AppLogin::AppLogin()
: Post(cpr::Url{"http://<ip>/uri"},
	   cpr::Header{{"Content-Type","application/json"}},
	   cpr::Body("{\"id\":\"\",\"password\":\"\",\"autoLoginFlag\":\"N\",\"serviceId\":\"XXXXXXXXXXXXX\"}"))
{
	// TODO Auto-generated constructor stub

}

AppLogin::~AppLogin() {
	// TODO Auto-generated destructor stub
}

int AppLogin::setUserAccount(std::string account)
{
	Json::Reader reader;
	Json::FastWriter fastWriter;
	Json::Value root;
	bool parsingRet;

    parsingRet = reader.parse(m_body, root);

	if (!parsingRet) {
		log_error("Failed to parse Json : %s", reader.getFormattedErrorMessages().c_str());
		return -1;
	}

	root[vId] = account;
	setBody(cpr::Body(fastWriter.write(root)));

	log_debug("body: %s", m_body.c_str());

	return 0;
}

int AppLogin::setUserPassword(std::string password)
{
	Json::Reader reader;
	Json::FastWriter fastWriter;
	Json::Value root;
	bool parsingRet;

    parsingRet = reader.parse(m_body, root);

	if (!parsingRet) {
		log_error("Failed to parse Json : %s", reader.getFormattedErrorMessages().c_str());
		return -1;
	}

    root[vPassword] = password;
    setBody(cpr::Body(fastWriter.write(root)));

    log_debug("body: %s", m_body.c_str());

    return 0;
}

bool AppLogin::setResponse(const cpr::Response& r)  throw (RestException, RestExceptionExt)
{
	bool parsingRet = Post::setResponse(r);

    if(parsingRet) {
    	log_debug("ConsumerKey: %s", m_root[vData].get(vConsumerKey,"").asString().c_str());
    	log_debug("AuthorizationToken: %s", m_root[vData].get(vAuthorizationToken,"").asString().c_str());
    	log_debug("AutoLoginKey: %s", m_root[vData].get(vAutoLoginKey,"").asString().c_str());
    	log_debug("UserStatus: %s", m_root[vData].get(vUserStatus,"").asString().c_str());
    	log_debug("RequiredConfirmTerms: %s", m_root[vData].get(vRequiredConfirmTerms,"").asString().c_str());
    	log_debug("ReadOnly: %s", m_root[vData].get(vReadOnly,"").asString().c_str());
    }

    return parsingRet;
}


std::string AppLogin::getConsumerKey()
{
	return m_root[vData].get(vConsumerKey,"").asString();
}

std::string AppLogin::getAuthorizationToken()
{
	return m_root[vData].get(vAuthorizationToken,"").asString();
}

std::string AppLogin::getAutoLoginKey()
{
	return m_root[vData].get(vAutoLoginKey,"").asString();
}


/*
int status_callback_ref(int& status_code, const cpr::Response& r)
{
    log_info("Response Code: %d", r.status_code);
    log_info("Response: %s", r.text.c_str());

    return r.status_code;
}
*/

} /* namespace rest */ //end of rest