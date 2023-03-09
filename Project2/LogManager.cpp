#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <fstream>

// Engine includes
#include "LogManager.h"

namespace df {

	LogManager::LogManager() {
		setType("LogManager");

		// Initialize attributes
		m_p_f = NULL;
		m_do_flush = false;
		is_open = false;
	}

	LogManager::~LogManager() {
		if (is_open) {
			fclose(m_p_f);
		}
	}

	void LogManager::operator=(LogManager const&) {

	}

	LogManager& LogManager::getInstance() {
		static LogManager log_manager;
		return log_manager;
	}

	int LogManager::startUp() {
		Manager::startUp();

		const char* cstr = LOGFILE_NAME.c_str();

		errno_t err = fopen_s(&m_p_f, cstr, "w");

		
		if (m_p_f == NULL) {
			is_open = true;
			return 1;
		}
		else {
			return 0;
		}
	}

	void LogManager::shutDown() {
		Manager::shutDown();

		// Close logfile
		fclose(m_p_f);
		is_open = false;
	}

	void LogManager::setFlush(bool m_do_flush) {

	}

	int LogManager::writeLog(const char* fmt, ...) const {
		int chars_written;

		va_list args;
		va_start(args, fmt);
		chars_written = vfprintf(m_p_f, fmt, args);
		va_end(args);

		printf("\n", m_p_f);

		// If game programmer wants to flush after each writeLog, then flush
		if (m_do_flush == true) {
			fflush(m_p_f);
		}

		// If vfprintf failed, change return value to -1 to indicate error
		if (chars_written < 0) {
			chars_written = -1;
		}

		// Return number of bytes written to log
		return chars_written;
	}

}