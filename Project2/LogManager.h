# pragma once
#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

 #include <stdio.h>

 #include "Manager.h"


 namespace df {

	 const std::string LOGFILE_NAME = "dragonfly-log.txt";

#define LM df :: LogManager :: getInstance ()

class LogManager : public Manager {

private:
 LogManager(); 
 LogManager(LogManager const&); 
 void operator = (LogManager const&);
 bool m_do_flush; 
 FILE *m_p_f; 
// int log_level;
 bool is_open;
 //needed to add the above bool to remove errors

public:
	~LogManager();

	static LogManager & getInstance();

	int startUp();

	void shutDown();

	void setFlush(bool do_flush = true);

	int writeLog(const char *fmt, ...) const;

	};
	
	
} 
#endif 