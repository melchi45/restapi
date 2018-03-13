/*******************************************************************************
 *  Copyright (c) 2013 Samsung Techwin Co., Ltd.
 *  
 *  Licensed to the Samsung Techwin Software Foundation under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Samsung SmartCam - SmartCam Camera Proejct
 *  http://www.samsungsmartcam.com
 *  
 *  Security Solution Division / B2C Camera S/W Development Team
 *
 *  $Author$
 *  $Date$
 *  $Revision$
 *  $Id$
 *  $HeadURL$
 *
 *  History 
 *    Get.h
 *
 *  Created on: Nov 14, 2016
 *      Author: Youngho Kim
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
	virtual bool setResponse(const cpr::Response& res) throw (RestException, PixcamException);
	int send() throw (RestException, PixcamException);

protected:
    virtual void* run(void);
};

} /* namespace rest */ //end of rest

#endif /* REST_GET_H_ */
