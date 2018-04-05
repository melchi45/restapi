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
#include <signal.h>
//#include <errno.h>
#include <string.h>
#include <assert.h>     /* assert */
#include <stdio.h>
#include <stdlib.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <errno.h>
#include <pthread.h>

#include "Thread.h"
#include "log_utils.h"

//#define DBG_THREAD

Thread::Thread()
: m_stoprequested(false)
, m_running(false)
, title("In worker thread: Thread")
#if (!(defined(_WIN32) || defined(_WIN64)))
, m_thread(0)
#endif
{
	if (pthread_mutex_init(&m_mutex, NULL) != 0) {
		log_info("mutex init failed");
	}
}

Thread::~Thread()
{
	if(is_running()) {
		stop();
	}

	pthread_mutex_destroy(&m_mutex);

//	if(title)
//		delete title;
}

// Create the thread and start work
// Note 1
int Thread::start()
{
	assert(m_running == false);

	log_debug("start Thread::start");
	int err;
	m_running = true;

	set_pthread_attr();
	err = pthread_create(&m_thread, &m_thread_attr, &Thread::start_thread, this);
	if (err != 0) {
		log_error("can't create thread :[%s]", strerror(err));
		return -1;
	}

	pthread_attr_destroy(&m_thread_attr);

	return 0;
}

int Thread::stop() // Note 2
{
	assert(m_running == true);

	log_debug("start Thread::stop");
	int err;
	m_running = false;
	m_stoprequested = true;

	err = pthread_join(m_thread, NULL);
	if (err != 0) {
		log_error("can't create thread :[%s]", strerror(err));
		return -1;
	}
#if (!(defined(_WIN32) || defined(_WIN64)))
	display_current_attr();
#endif

	return 0;
}

bool Thread::is_running()
{
	return m_running;
}

// This is the static class function that serves as a C style function pointer
// for the pthread_create call
void* Thread::start_thread(void *obj)
{
#if (!(defined(_WIN32) || defined(_WIN64)))
	reinterpret_cast<Thread*>(obj)->display_current_attr();
#endif
	//All we do here is call the do_work() function
	reinterpret_cast<Thread*>(obj)->do_work();

	return NULL;
}

// Compute and save fibonacci numbers as fast as possible
void Thread::do_work()
{
	while (!m_stoprequested)
	{
		pthread_mutex_lock(&m_mutex);
		this->run();
		pthread_mutex_unlock(&m_mutex); // Note 6
	}
}

int Thread::set_pthread_attr()
{
	int err;

	int detach_state;
	int scope;
	int inherit_sched;
	int sched_policy;
	struct sched_param sched_param;
	size_t guard_size;
	void *stack_addr = NULL;
	size_t stack_size;

	err = pthread_attr_init(&m_thread_attr);
	if (err != 0) {
		log_error("can't pthread_attr_init :[%s]", strerror(err));
		return -1;
	}

	detach_state = PTHREAD_CREATE_JOINABLE;
	err = pthread_attr_setdetachstate(&m_thread_attr, detach_state);
	if (err != 0) {
		log_error("can't pthread_attr_setdetachstate :[%s]", strerror(err));
		return -1;
	}

	scope = PTHREAD_SCOPE_SYSTEM;
	err = pthread_attr_setscope(&m_thread_attr, scope);
	if (err != 0) {
		log_error("can't pthread_attr_setscope :[%s]", strerror(err));
		return -1;
	}

	inherit_sched = PTHREAD_INHERIT_SCHED;
	err = pthread_attr_setinheritsched(&m_thread_attr, inherit_sched);
	if (err != 0) {
		log_error("can't pthread_attr_setinheritsched :[%s]", strerror(err));
		return -1;
	}
#if (!(defined(_WIN32) || defined(_WIN64)))
	sched_policy = SCHED_RR;
	err = pthread_attr_setschedpolicy(&m_thread_attr, sched_policy);
	if (err != 0) {
		log_error("can't pthread_attr_setschedpolicy :[%s]", strerror(err));
		return -1;
	}
#endif
	sched_param.sched_priority = 10;
	err = pthread_attr_setschedparam(&m_thread_attr, &sched_param);
	if (err != 0) {
		log_error("can't pthread_attr_setschedparam :[%s]", strerror(err));
		return -1;
	}

#if (!(defined(_WIN32) || defined(_WIN64)))
	guard_size = 4096 * 4;
	err = pthread_attr_setguardsize(&m_thread_attr, guard_size);
	if (err != 0) {
		log_error("can't pthread_attr_setguardsize :[%s]", strerror(err));
		return -1;
	}

	stack_size = 1024 * 1024;
	if (sysconf(_SC_PAGESIZE) != -1)
	{
		err = posix_memalign(&stack_addr, sysconf(_SC_PAGESIZE), stack_size);
		if (err != 0) {
			log_error("can't posix_memalign :[%s]", strerror(err));
			return -1;
		}
	}

	err = pthread_attr_setstack(&m_thread_attr, stack_addr, stack_size);
	if (err != 0) {
		log_error("can't pthread_attr_setstack :[%s]", strerror(err));
		return -1;
	}
#endif
	return 0;
}

void Thread::display_pthread_attr(pthread_attr_t *attr)
{
    int err;
    const char *text;

    int detach_state;
    int scope;
    int inherit_sched;
    int sched_policy;
    struct sched_param sched_param;
    size_t guard_size;
    void *stack_addr;
    size_t stack_size;

    err = pthread_attr_getdetachstate(attr, &detach_state);
	if (err != 0) {
		log_error("can't pthread_attr_getdetachstate :[%s]", strerror(err));
		return;
	}

    switch (detach_state) {
        case PTHREAD_CREATE_DETACHED:
            text = "PTHREAD_CREATE_DETACHED";
            break;

        case PTHREAD_CREATE_JOINABLE:
            text = "PTHREAD_CREATE_JOINABLE";
            break;

        default:
            text = "???";
    }
#ifdef DBG_THREAD
	log_debug("%24s = %s", "Detach state", text);
#endif

    err = pthread_attr_getscope(attr, &scope);
	if (err != 0) {
		log_error("can't pthread_attr_getscope :[%s]", strerror(err));
		return;
	}

    switch (scope) {
        case PTHREAD_SCOPE_SYSTEM:
            text = "PTHREAD_SCOPE_SYSTEM";
            break;

        case PTHREAD_SCOPE_PROCESS:
            text = "PTHREAD_SCOPE_PROCESS";
            break;

        default:
            text = "???";
    }
#ifdef DBG_THREAD
	log_debug("%24s = %s", "Scope", text);
#endif

    err = pthread_attr_getinheritsched(attr, &inherit_sched);
	if (err != 0) {
		log_error("can't pthread_attr_getinheritsched :[%s]", strerror(err));
		return;
	}
    switch (inherit_sched) {
        case PTHREAD_INHERIT_SCHED:
            text = "PTHREAD_INHERIT_SCHED";
            break;

        case PTHREAD_EXPLICIT_SCHED:
            text = "PTHREAD_EXPLICIT_SCHED";
            break;

        default:
            text = "???";
    }
#ifdef DBG_THREAD
	log_debug("%24s = %s", "Inherit scheduler", text);
#endif

    err = pthread_attr_getschedpolicy(attr, &sched_policy);
	if (err != 0) {
		log_error("can't pthread_attr_getschedpolicy :[%s]", strerror(err));
		return;
	}
    switch (sched_policy) {
        case SCHED_RR:
            text = "SCHED_RR";
            break;

        case SCHED_FIFO:
            text = "SCHED_FIFO";
            break;

        case SCHED_OTHER:
            text = "SCHED_OTHER";
            break;

        default:
            text = "???";
    }
#ifdef DBG_THREAD
	log_debug("%24s = %s", "Scheduling policy", text);
#endif

    err = pthread_attr_getschedparam(attr, &sched_param);
	if (err != 0) {
		log_error("can't pthread_attr_getschedparam :[%s]", strerror(err));
		return;
	}
#ifdef DBG_THREAD
	log_debug("%24s = %d", "Scheduling priority", sched_param.sched_priority);
#endif

#if (!(defined(_WIN32) || defined(_WIN64)))
    err = pthread_attr_getguardsize(attr, &guard_size);
	if (err != 0) {
		log_error("can't pthread_attr_getguardsize :[%s]", strerror(err));
		return;
	}

#ifdef DBG_THREAD
	log_debug("%24s = %d", "Guard size", guard_size);
#endif

    err = pthread_attr_getstack(attr, &stack_addr, &stack_size);
	if (err != 0) {
		log_error("can't pthread_attr_getstack :[%s]", strerror(err));
		return;
	}
#ifdef DBG_THREAD
	log_debug("%24s = %p", "Stack address", stack_addr);
	log_debug("%24s = %#x", "Stack size", stack_size);
#endif
#endif
}

#if (!(defined(_WIN32) || defined(_WIN64)))
void Thread::display_current_attr()
{
    int err;
    pthread_attr_t attr;

    // pthread_getattr_np() is a non-standard GNU extension that retrieves
    // the attributes of the thread specified in its first argument
    err = pthread_getattr_np(pthread_self(), &attr);
	if (err != 0) {
		log_error("can't pthread_attr_np :[%s]", strerror(err));
		return;
	}

	puts(title);
    display_pthread_attr(&attr);
    puts("");
}
#endif