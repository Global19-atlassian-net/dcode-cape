/* 
 * File:   error.h
 * Author: roberto
 *
 * Created on April 14, 2014, 11:52 AM
 */

#ifndef ERROR_H
#define ERROR_H

/**
 * Check if the void pointer is NULL and print out a message. If the exit_status
 * is different of zero it exit the program 
 * 
 * @param data the pointer to check
 * @param msg the message to be printed out
 * @param file the source code file (__FILE__) or NULL to not print this info
 * @param line the source code line (__LINE__) or 0
 * @param exit_status the exit status (Exit the program is this number is different of zero)
 * @return the same pointer if everything is fine
 */
extern void *checkPointerError(void *data, const char *msg, const char *file, int line, int exit_status);


#endif /* ERROR_H */

