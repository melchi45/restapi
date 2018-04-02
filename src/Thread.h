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
#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

class Thread
{
public:
	Thread();
	virtual ~Thread();

    // Create the thread and start work
    // Note 1
    int start();
    int stop(); // Note 2
    bool is_running();
private:
    volatile bool m_stoprequested; // Note 5
    volatile bool m_running;
    pthread_mutex_t m_mutex; // Variable declarations added 4/14/2010
    pthread_t m_thread;

    // This is the static class function that serves as a C style function pointer
    // for the pthread_create call
    static void* start_thread(void *obj);

    // Compute and save fibonacci numbers as fast as possible
    void do_work();
    void display_pthread_attr(pthread_attr_t *attr);
protected:
	pthread_attr_t m_thread_attr;
	const char *title;

protected:
    virtual void* run(void) = 0;

    // referene url
    // https://apiexamples.com/c/pthread/pthread_attr_init.html
    virtual int set_pthread_attr();
    void display_current_attr();
};

#endif /* THREAD_H_ */
