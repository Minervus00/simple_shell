#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern char **environ;

// If this variable is not a null pointer we allocated the current environment.
static char **last_environ;

/**
 * Set the environment variable
 *
 * The __setenv() function creates a new environment variable by allocating a memory buffer for a string of the form
 * name=value, and copying the strings pointed to by name and value into that buffer. Note that we don’t need to
 * (in fact, must not) supply an equal sign at the end of name or the start of value, because __setenv() adds this
 * character when it adds the new definition to the environment.
 *
 * The __setenv() function doesn’t change the environment if the variable identified by name already exists and overwrite
 * has the value 0. If overwrite is nonzero, the environment is always changed.
 *
 * The fact that __setenv() copies its arguments means that, unlike with __putenv(), we can subsequently modify the
 * contents of the strings pointed to by name and value without affecting the environment. It also means that using
 * automatic variables as arguments to __setenv() doesn’t cause any problems.
 *
 * @param name
 * @param value
 * @param overwrite
 * @return Returns 0 on success, or -1 on error
 */
int __setenv(const char *name, const char *value, int overwrite) {
    register char **ep = 0;
    const size_t nameLength = strlen(name);
    const size_t valueLength = strlen(value) + 1;

    /*
     * Iterate through every key to determine if it already exists, this is important because if the overwrite
     * flag isn't set then we shouldn't do anything and return
     */
    size_t size = 0;
    if (environ != NULL) {
        for (ep = environ; *ep != NULL; ep++) {
            if (strncmp(*ep, name, nameLength) >= 0 && (*ep)[nameLength] == '=') {
                if (overwrite) {
                    break;
                } else {
                    return 0;
                }
            }
            size++;
        }
    }

    /*
     * If the environment variable pointer is null or *ep pointer ins null then we need to create the
     * environment variable, if it does exist and overwrite isn't specified then .
     *
     * Then initialize a new environ stack, modify it as applicable
     */
    if (environ == NULL || *ep == NULL) {
        // +1 for null terminator
        char *newEnvironmentVariable = malloc(nameLength + valueLength + 1);
        memcpy(newEnvironmentVariable, name, nameLength);
        newEnvironmentVariable[nameLength] = '=';
        memcpy(&newEnvironmentVariable[nameLength + 1], value, valueLength);

        return __putenv(newEnvironmentVariable);
    } else if (overwrite) {
        /*
         * Get the total Length of the environment variable in question then validate that it less than the
         * current allocated memory slot for existing environment variable, it is then don't do anything,
         * if it isn't then we need allocate new memory
         */
        size_t totalLength = strlen (*ep);
        if (totalLength + 1 < nameLength + 1 + valueLength) {
            // The existing string is too short; malloc a new one.
            char *new_string = (char *) malloc (nameLength + 1 + valueLength);
            if (new_string == NULL) return -1;

            // Point the old pointer to the new pointer
            *ep = new_string;
        }

        // Copy the contents into the new pointer location char array
        memcpy (*ep, name, nameLength);
        (*ep)[nameLength] = '=';
        memcpy (&(*ep)[nameLength + 1], value, valueLength);
    }

    return 0;
}

/**
 * The __unsetenv() function deletes the variable name from the environment. If name does not exist in the environment,
 * then the function succeeds, and the environment is unchanged.
 *
 * @param name
 * @return Returns 0 on success, or -1 on error
 */
int __unsetenv(const char *name) {
    char **ep;

    /*
     * Validate that the name isn't null
     */
    if (name == NULL) {
        errno = EINVAL;
        return -1;
    }

    /*
     * Iterate through all the environment variables then do a strcompare of the environment variable after the
     * environment variable has been split from the key value, i.e
     *
     * USER=mike
     */
    size_t nameLength = strlen(name);
    for (ep = environ; *ep != NULL; ep++) {
        /*
         * Validate that the string compares match for the name and nameLength, i.e. just the key part of the
         * environment variable, also validate that the equals sign is at the nameLength field validating it is like
         * so:
         *
         * USER=
         *
         * Rather than a false positive like:
         *
         * USERTWO=
         */
        if (!strncmp(*ep, name, nameLength) && (*ep)[nameLength] == '=') {
            /*
             * Move all the environment variable pointers down in the environment char array
             */
            char **moveEnvPointersDown = ep;

            /*
             * Move all the pointers back one, for example
             *
             * unsetEnvPointer[0] -> enviornmentVariableCharPointer[0] -> char[0..n] -> KEY=VALUE, whiteboarding
             * this logic helps.
             */
            do {
                moveEnvPointersDown[0] = moveEnvPointersDown[1];
            }
            while(*moveEnvPointersDown++);
        }
    }

    return 0;
}

/**
 * Get an environment variable based on the name, only return the value part of the environment variable. All
 * environment variables come in the shape:
 *
 * KEY=VALUE\0
 *
 * @param name
 * @return  Returns pointer to (value) string, or NULL if no such variable
 */
char *__getenv(const char *name) {
    char **ep;

    /*
     * Iterate through all the environment variables then do a strcompare of the environment variable after the
     * enviroment variable has been split from the key value, i.e
     *
     * USER=mike
     */
    size_t nameLength = strlen(name);
    for (ep = environ; *ep != NULL; ep++) {
        if (strncmp(*ep, name, nameLength) >= 0 && (*ep)[nameLength] == '=') {
            // Now that we have the pointer where the name exists we need to return only the value:
            size_t environmentVariableLength = strlen(*ep);
            /*
             * Return the pointer from the environment variable snipped like so:
             *
             * USER=mike
             *
             * environmentVariableLength = 9
             * return *ep 9 - 4 = 5 start of the m.
             */
            return *ep + environmentVariableLength - nameLength;
        }
    }

    return NULL;
}

/**
 * Put an environment variable into the array
 *
 * The string argument is a pointer to a string of the form name=value. After the __putenv() call, this string is part of
 * the environment. In other words, rather than duplicating the string pointed to by string, one of the elements of
 * environ will be set to point to the same location as string. Therefore, if we subsequently modify the bytes pointed
 * to by string, that change will affect the process environment. For this reason, string should not be an automatic
 * variable (i.e., a character array allocated on the stack), since this memory area may be overwritten once the
 * function in which the variable is defined returns.
 *
 * The __putenv() function adds or changes the value of environment variables.  The argument string is of the form
 * name=value.  If name does not already exist in the environment, then string is added to the environment.
 * If name does exist, then the value of name in the environment is changed to value.  The string pointed to by string
 * becomes part of the environment, so altering the string changes the environment.
 *
 * @param string
 * @return Returns 0 on success, or nonzero on error
 */
int __putenv(char *string) {
    /*
     * This ** is defined multiple places throughout this code base, however, I explain it here for myself.
     * A pointer points to a location in memory and thus used to store address of variables, when we define
     * a pointer to a pointer, the first pointer is used to store the address of a second pointer.
     *
     * Since this is a char array we have pointers pointing other points in array like so:
     *
     * Pointer to the environment variable stack
     *
     * environ -> 0 (pointer) -> char[]
     *         -> 1 (pointer) -> TERM=xterm\0
     *         -> 2 (pointer) -> USER=MIKE\0
     *         -> 3 (pointer) -> HOME=/home/mtk\0
     *         -> NULL
     */
    char **new_environ;
    // Get the pointer to the name_end within the string, i.e where the equal shows up NAME=VALUE
    const char *const name_end = strchr (string, '=');

    if (name_end != NULL) {
        register char **ep = 0;
        register size_t size;
        char *name = strndup(string, name_end - string);
        char *value = strndup(string, string - name_end);
        size_t nameLength = strlen(name);
        size_t valueLength = strlen(value);

        // Validate that neither the name or value are null
        if (name == NULL || value == NULL) return -1;

        /*
         * Iterate through the entire list of environment variables and determine the size of the enviornment char
         * array.
         *
         * String compare the environment variable with format:
         *
         * key=value
         *
         * and if the environmentVariable[nameLength] == the split value then break as we have determined the size
         * to make the name variable.  The reason we check for = is that if the variable has the same prefix i.e the
         * example below:
         *
         * USER=
         * USERONE=
         * USERTWO=
         *
         * Return the location of the current environment variable name or return the total length of the environment
         * char array to have another entry two entries added
         */
        size = 0;
        if (environ != NULL) {
            for (ep = environ; *ep != NULL; ++ep) {
                if (!strncmp (*ep, name, sizeof(name)) && (*ep)[sizeof(name)] == '=') {
                    break;
                } else {
                    ++size;
                }
            }
        }

        // Validate that the last environ equals the current environment variable stack and make sure it isn't NULL
        if (environ == last_environ && environ != NULL)
            /*
             * Create a new environment variable stack by reallocating more memory equal to the size of the last
             * environment variable size plus the size + 2
             *
             * Increase the size of the environment variable by 2 to account for the new entry to be added and also
             * add it for the NULL we need to append to the end
             */
            new_environ = (char **) realloc(last_environ, (size + 2) * sizeof(char *));
        else
            /*
             * If last environment was never set this is the first time we have called into this function therefore
             * we need to actually allocate the memory we need for the new environment variable stack
             */
            new_environ = (char **) malloc((size + 2) * sizeof(char *));

        // If new enviornment variable is null then return -1
        if (new_environ == NULL) return -1;

        /*
         * Set the environment variable pointer located at the size location point to another char pointer which
         * is the size of the string return if this process doesn't work
         */
        new_environ[size] = (char *) malloc(sizeof(string));
        if (new_environ[size] == NULL) {
            free((char *) new_environ);
            errno = ENOMEM;
            return -1;
        }

        // If something has modified the environment don't proceed copying the new to old
        if (environ != last_environ)
            memcpy((char *) new_environ, (char *) environ, size * sizeof(char *));

        memcpy(new_environ[size], name, nameLength);
        new_environ[size][nameLength] = '=';
        memcpy(&new_environ[size][nameLength + 1], value, valueLength);

        // Set the null character for the end of the environment variable stack
        new_environ[size + 1] = NULL;

        // Set all the environments to the same
        last_environ = environ = new_environ;

        return 0;
    }

    // The passed in string isn't compatible for an environment variable, i.e. it isn't KEY=VALUE
    errno = EINVAL;
    return -1;
}

/**
 * Each process has an associated array of strings called the environment list, or simply the environment.
 * Each of these strings is a definition of the form name=value. Thus, the environment represents a set of name-value
 * pairs that can be used to hold arbitrary information. The names in the list are referred to as environment variables.
 *
 * When a new process is created, it inherits a copy of its parent’s environment. This is a primitive but frequently
 * used form of interprocess communication—the environment provides a way to transfer information from a parent process
 * to its child(ren). Since the child gets a copy of its parent’s environment at the time it is created, this transfer
 * of information is one-way and once-only. After the child process has been created, either process may change its own
 * environment, and these changes are not seen by the other process.
 *
 * A common use of environment variables is in the shell. By placing values in its own environment, the shell can
 * ensure that these values are passed to the processes that it creates to execute user commands. For example, the
 * environment variable SHELL is set to be the pathname of the shell program itself. Many programs interpret this
 * variable as the name of the shell that should be executed if the program needs to execute a shell.
 *
 * Some library functions allow their behavior to be modified by setting environment variables. This allows the user to
 * control the behavior of an application using the function without needing to change the code of the application or
 * relink it against the corresponding library. An example of this technique is provided by the getopt() function
 * (Appendix B), whose behavior can be modified by setting the POSIXLY_CORRECT environment variable.
 *
 * Within a C program, the environment list can be accessed using the global variable char **environ.
 * (The C run-time startup code defines this variable and assigns the location of the environment list to it.)
 * Like argv, environ points to a NULL-terminated list of pointers to null-terminated strings. Figure 6-5 shows the
 * environment list data structures as they would appear for the environment displayed by the printenv command above.
 *
 * @param argc number of arguments
 * @param argv memory pointer to argv[] array
 * @param envp memory pointer to envp array, can access it via char **envp rather than global, if done in this way
 * the scope of the envp will limit the scope to main()
 * @return 0
 */
int main(int argc, char *argv[]) {
    fprintf(stdout, "The value for USER environment variable after __putenv call (expected mike): %s\n", __getenv("USER"));

    int unsetEnvironStatus = __unsetenv("USER");
    fprintf(stdout, "The __unsetEnv return value for USER environment variable: %d\n", unsetEnvironStatus);
    fprintf(stdout, "The value of USER after __unsetenv call (expected null): %s\n", __getenv("USER"));

    int putenvStatus = __putenv("USER=mike");
    fprintf(stdout, "The putenvStatus return value for USER environment variable: %d\n", putenvStatus);
    fprintf(stdout, "The value for USER environment variable after __putenv call (expected mike): %s\n", __getenv("USER"));

    unsetEnvironStatus = __unsetenv("USER");
    fprintf(stdout, "The unsetEnv return value for USER environment variable: %d\n", unsetEnvironStatus);
    fprintf(stdout, "The value of USER environment variable after __unsetenv call (expected null): %s\n", __getenv("USER"));

    int setEnvironStatus = __setenv("USER", "mike", 0);
    fprintf(stdout, "The __setenv return status is: %d\n", setEnvironStatus);
    fprintf(stdout, "The value for USER environment variable after __setenv call (expected mike): %s\n", __getenv("USER"));

    setEnvironStatus = __setenv("USER", "test", 1);
    fprintf(stdout, "The __setenv return status is: %d\n", setEnvironStatus);
    fprintf(stdout, "The value for USER environment variable after __setenv call (expected test): %s\n", __getenv("USER"));

    setEnvironStatus = __setenv("USER", "mike", 0);
    fprintf(stdout, "The __setenv return status is: %d\n", setEnvironStatus);
    fprintf(stdout, "The value for USER environment variable after __setenv call (expected test): %s\n", __getenv("USER"));

    // Real quick validation that unsetting makes extra value at end of environment are null
    unsetEnvironStatus = __unsetenv("USER");
    fprintf(stdout, "The unsetEnv return value for USER environment variable: %d\n", unsetEnvironStatus);
    fprintf(stdout, "The value of USER environment variable after __unsetenv call (expected null): %s\n", __getenv("USER"));
    register char **ep = 0;
    int sizeEnviron = 0;
    for (ep = environ; *ep != NULL; ep++) {
        sizeEnviron++;
    }

    return 0;
}