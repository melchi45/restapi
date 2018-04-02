/*******************************************************************************
*  Copyright (c) 1998 MFC Forum
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Module Name:
*
* Revision History:
*
* Date        Ver Name                    Description
* ----------  --- --------------------- -----------------------------------------
* 07-Jun-2016 0.1 Youngho Kim             Created
* ----------  --- --------------------- -----------------------------------------
*
* DESCRIPTION:
*
*  $Author:
*  $LastChangedBy:
*  $Date:
*  $Revision: 2949 $
*  $Id:
*  $HeadURL:
*******************************************************************************/
#ifndef REST_GET_H_
#define REST_GET_H_

#include "RestBase.h"
#include "ResponseBase.h"

namespace rest {

/*
 *
 */
class Get : public RestBase, public ResponseBase {
public:
	Get(cpr::Url url, cpr::Header header);
	virtual ~Get();

public:
	static cpr::Response status_callback_ref(int& status_code, const cpr::Response& res);
	virtual bool setResponse(const cpr::Response& res) throw (RestException, RestExceptionExt);
	int send() throw (RestException, RestExceptionExt);

protected:
    virtual void* run(void);
};

} /* namespace rest */ //end of rest

#endif /* REST_GET_H_ */
