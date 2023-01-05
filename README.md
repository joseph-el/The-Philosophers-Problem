<h1 align="center">
	42 PHILOSOPHERS 🍝⏳ 
</h1>

<p align="center">
	<b><i>  Dining Philosophers Problem </i></b><br>
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/joseph-el/The-Philosophers-Problem?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/joseph-el/The-Philosophers-Problem?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/joseph-el/The-Philosophers-Problem?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/joseph-el/The-Philosophers-Problem?color=green" />

</p>
  <p align="center">
    <a href="https://github.com/anuraghazra/github-readme-stats/actions">
      <img alt="Tests Passing" src="https://github.com/anuraghazra/github-readme-stats/workflows/Test/badge.svg" />
    </a>
    <a href="https://github.com/anuraghazra/github-readme-stats/graphs/contributors">
      <img alt="GitHub Contributors" src="https://img.shields.io/github/contributors/anuraghazra/github-readme-stats" />
    </a>
    <a href="https://codecov.io/gh/anuraghazra/github-readme-stats">
      <img src="https://codecov.io/gh/anuraghazra/github-readme-stats/branch/master/graph/badge.svg" />
    </a>
    <a href="https://github.com/anuraghazra/github-readme-stats/issues">
      <img alt="Issues" src="https://img.shields.io/github/issues/joseph-el/The-Philosophers-Problem?color=0088ff" />
    </a>
    <a href="https://github.com/anuraghazra/github-readme-stats/pulls">
      <img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/joseph-el/The-Philosophers-Problem?color=0088ff" />
    </a>
  </p>
 
<h3 align="center">

![wallpaperflare com_wallpaper (1)](https://user-images.githubusercontent.com/80905157/210857437-2748aaaa-3623-4b99-b00d-57154fcf4206.jpg)
 
</h3>

---
### Table of Contents

* [About](#about-project)
* [Understanding Concepts](#understanding-concepts)
* [Understand Thread](#what-is-a-thread)
* [Understand Processing and Semaphore](#understand-processing-and-semaphore)
* [What is a Process?](#what-is-a-process)
* [Semaphores](#semaphores)
* [Screenshot](#screenshot)
* [Resources](#resources)

 ## About project
- This project is about the ``Dining Philosophers problem`` is a classic OS problem that’s usuallu stated in very non-OS terms:
There are N philosphers sitting around a circular table eating spaghetti and discussing philosphy. The problem is that each philosopher needs 2 forks to eat, and there are only N forks, one between each 2 philosophers. Design an algorithm that the philosophers can follow that insures that none starves as long as each philosopher eventually stops eating, and such that the maximum number of philosophers can eat at once.

## Understanding Concepts
### Understand Threads and mutexes
#### What is a Thread
- An execution thread is a logical sequence of instructions inside a process that is automatically managed by the operating system’s kernel. A regular sequential program has a single thread, but modern operating systems allow us to create several threads in our programs, all of which run in parallel.
##### > Using POSIX Threads
- The standard interface in C to manipulate threads is POSIX with its ``<pthread.h>`` library. It contains around sixty functions to create and join threads, as well as to manage their shared memory. We will only study a fraction of these in this article. In order to compile a program using this library, we can’t forget to link it with -pthread:
```Shell
gcc -pthread test.c
```
##### > Creating a Thread
- We can create a new ``thread`` from any other thread of the program with the ``pthread_create`` function. Its prototype is:
```C
int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
```
- When the ``pthread_create`` function ends, the thread variable we gave it should contain the newly created thread’s ID.
##### > Joining Threads
-In order to block the execution of a thread until another thread finishes, we can use the ``pthread_join`` function:
```C
 int pthread_join(pthread_t thread, void **retval);
```
 - Let’s note that we can only wait for the termination of a specific thread. There is no way to wait for the first terminated thread without specifying an ID, as the wait function for child processes does.
#### Detach Threads

- In some cases, it is possible and preferable to not wait for the end of certain theads at all. In that case, we can detach the thread to tell the operating system that it can reclaim its resources right away when it finishes its execution. For that, we use the pthread_detach function (usually right after that thread’s creation):

 ```C
 int pthread_detach(pthread_t thread);
 ```
 - Here, all we have to supply if the thread’s ID.
### Managing Threads’ Shared Memory
- One of the greatest qualities of threads is that they all share their process’s memory. Each thread does have its own stack, but the other threads can very easily gain access to it with a simple pointer, but this shared memory and the ease with which a thread can access another thread’s memory clearly also has its share of danger: it can cause nasty ``Race Condition`` errors.
##### > Race condition
- A race condition occurs when two or more threads can access shared data and they try to change it at the same time. Because the thread scheduling algorithm can swap between threads at any time, you don't know the order in which the threads will attempt to access the shared data. Therefore, the result of the change in data is dependent on the thread scheduling algorithm, i.e. both threads are "racing" to access/change the data. [for more informations](https://stackoverflow.com/questions/34510/what-is-a-race-condition/34550#34550)
- Indeed, if we compile the program with the -fsanitizer=thread and -g options and then run it, like this:
```Shell
gcc -fsanitize=thread -g threads.c
```
- We will get an alert: “WARNING: ThreadSanitizer: data race”.
##### So is there a way to stop a thread from reading a value while another one modifies it? Yes, thanks to mutexes!
### What is a Mutex ?
- A mutex (short for “mutual exclusion”) is a synchronization primitive. It is essentially a lock that allows us to regulate access to data and prevent shared resources being used at the same time.
#### Declaring a Mutex
- Thanks to the <pthread.h> header, we can declare a mutex type variable like this:
```C
pthread_mutex_t    mutex;
```
- Before we can use it, we first need to initialize it with the pthread_mutex_init function which has the following prototype:
```C
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
```
#### Locking and Unlocking a Mutex

- Then, in order to lock and unlock our mutex, we need two other functions. Their prototypes are as follows:
```C
int pthread_mutex_lock(pthread_mutex_t *mutex));
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```
- If the mutex is unlocked, pthread_mutex_lock locks it and the calling thread becomes its owner. In this case, the function ends immediately. However, if the mutex is already locked by another thread, pthread_mutex_lock suspends the execution of the calling thread until the mutex is unlocked.
- The pthread_mutex_unlock function unlocks a mutex. The mutex to be unlocked is assumed to be locked by the calling thread, and the function only sets it to unlocked. Let’s be careful to note that this function does not check if the mutex is in fact locked and that the calling thread is actually its owner: a mutex could therefore be unlocked by a thread that did not lock it in the first place. We will need to be careful about arranging pthread_mutex_lock and pthread_mutex_unlock in our code, otherwise, we might get “lock order violation” errors.
#### Destroying a Mutex
- When we no longer need a mutex, we should destroy it with the following pthread_mutex_destroy function:
```C
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```
- This function destroys an unlocked mutex, freeing whatever resources it might hold.
### Understand Processing and Semaphore
#### What is a Process?
- The programs we write are sets of instructions and operations meant to be executed by a computer.
#### Fork: Creating a Child Process
- The fork system call will allow our process to create a new process, which will be its exact clone and executed simultaneously. In this way, our initial process will be the parent and the new process, its child. In fact, the very name of the system call, fork, is like the fork of a family tree.
- Let’s take a look at the prototype of fork, from the <unistd.h> library:
```C
pid_t fork(void);
```
#### Distinguishing Between the Parent and Child Processes
- Since the child is a clone of the parent, it will have the same exact code. However, we probably want to give the child process different instructions than its parent. The fork system call’s return value, an integer of type pid_t, does not return the same PID to the parent and to the child. So this is what we will use in order to differentiate them. Here are the fork function’s possible return values:

- the parent receives the child’s PID,
- the child receives 0,
- and in the event of an error, fork returns -1.
```C
int main(void)
{
    pid_t   pid;

    pid = fork();
    if (! pid)
    {
        puts("HY From child"); // exit child process
        exit(EXIT_SUCCESS);
    }
    else
        puts("HY FROM parent");
    return (EXIT_SUCCESS);
}
```

- In other words, if we see 0 as the return value of fork, we know we are in the child process. Otherwise if we see a PID, we know we are in the parent.

#### ``Note:`` The Memory Duplicated but Not Shared
- As we’ve seen, a child process is an exact copy of its parent process. When a child is created, it is identical to its parent in every way. It has the same code, the same open file descriptors, the same data stored in memory, etc. But the fact that this memory is identical does not mean it is shared between the two processes. If the parent process changes the value of one of its variables after creating the child, the child process will not see any change when it reads the same variable.
### The Wait and Waitpid System Calls
- In order to suspend the parent process’ execution until the child process’ state changes, we can use the wait or waitpid system calls from the ``<sys/wait.h>`` library. Their prototypes are:
```C
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
```
- The difference between the two is especially noticeable when a process has several children. The wait call will retrieve the first terminated child, whereas waitpid holds out for the child matching the PID that we indicated and ignores all of the others. Also, waitpid allows us to specify a few options.
- The common parameter to both system calls is:

``status:`` a pointer to an integer type variable in which wait and waitpid can store the child’s exit status. We will be able to examine this number with different macros to determine if the child finished normally or was interrupted, among other things.

- The two extra parameters of ``waitpid`` are as follows:

- ``pid:`` the PID of the child process we should wait for. The parent process knows this PID because it’s the return value that fork provided when the child was created. Alternatively, we can specify -1 in order to wait for whichever child finished first, just like wait (indeed, waitpid(-1, status, 0) is exactly the same as wait(status).)
``options:`` waitpid offers several options. Among those, the sometimes very useful WNOHANG. With the WNOHANG option, waitpid returns immediately if the child process has not ended yet. Without this option, the parent process will by default remain suspended as long as the child is still executing its tasks.
- If the system call succeeds, both wait and waitpid return the terminated child’s PID.
### Analyzing a Child Process’ Exit Status
- The ``wai``t and ``waitpid functions provide us with a status that contains a lot of information about the way in which a child process finished its execution. The status is an integer that represents not only the exit code but also further details that explain why a child exited. So we can easily tell if a child really finished all of its tasks or if it was interrupted.
- We can inspect the status thanks to several macros:
```C
WIFEXITED(status);
WEXITSTATUS(status);
```
- ``WIFEXITED(status):`` returns true if the child terminated normally.
- ``WEXITSTATUS(status):`` to be used only if WIFEXITED returned true. Returns the child’s exit code.
### Kill: Terminating Child Processes
- It may be a touch sinister, but we can kill our child process if we so desire. To do so, we need to use the ``kill`` function of the ``<signal.h>`` library to send a signal to the child process that will force it to terminate immediately. The function’s prototype is:
```C
int kill(pid_t pid, int sig);
```
- The parameters we need to supply are:

- ``pid:`` the PID of the process that we want to kill.
- ``sig:`` the signal that we want to send to the process in order to kill it. There are many different possible signals for kill, each with its own nuances (see man 7 signal), but the most frequently used are perhaps SIGTERM (soft termination signal) and SIGKILL (hard kill signal).

### Semaphores
#### What is Semaphores
- A semaphore is a signalling mechanism used to regulate access to a shared resource like a railroad track. A semaphore is used to signal to the driver of a train whether he can go ahead on the track or not, for use semaphore you need to include the ``<semaphore.h>`` in your program.
#### Semaphore Calls
##### > sem_open
```C
sem_t *sem_open (const char *name, int oflag);
sem_t *sem_open (const char *name, int oflag, mode_t mode, unsigned int value);
```
- ``sem_open`` is the call to get started for a semaphore. sem_open opens an existing semaphore or creates a new semaphore and opens it for further operations.
##### > sem_post
```C
int sem_post (sem_t *sem);
```
- ``sem_post`` increments the semaphore, It returns 0 on success and -1 on error.

##### > sem_wait
```C
int sem_wait (sem_t *sem);
```
- ``sem_wait`` decrements the semaphore pointed by sem. If the semaphore value is non-zero, the decrement happens right away. If the semaphore value is zero, the call blocks till the time semaphore becomes greater than zero and the decrement is done. sem_wait returns zero on success and -1 on error

##### > sem_unlink
```C
int sem_unlink (const char *name);
```
- ``sem_unlink`` removes the semaphore associated with the name.

## Screenshot 
<h3 align="center">
<img width="1138" alt="Screen Shot 2023-01-05 at 17 07 48" src="https://user-images.githubusercontent.com/80905157/210871248-56df3ede-ee93-4a3a-9448-5a0edc28f804.png">

<img width="488" alt="Screen Shot 2023-01-05 at 17 05 07" src="https://user-images.githubusercontent.com/80905157/210871271-44b55670-5f19-4e8f-9dcb-5daca0df65ab.png">

<img width="531" alt="Screen Shot 2023-01-05 at 17 05 49" src="https://user-images.githubusercontent.com/80905157/210871287-2ad356f6-bb16-475e-ba83-9a4530c2cc03.png">

</h3>

## Resources
 
- [Semaphores](https://www.softprayog.in/programming/posix-semaphores)
- [Wikipedia, init](https://en.wikipedia.org/wiki/Init)
 
- [Geeks for Geeks, fork() in C ](https://www.geeksforgeeks.org/fork-system-call/)
 
- [Aline, Les processus zombies](https://www.it-connect.fr/les-processus-zombies/)
 
- [Tecmint, All You Need To Know About Processes in Linux](https://www.tecmint.com/linux-process-management/)

- [Wikipedia, Concurrent computing](https://en.wikipedia.org/wiki/Concurrent_computing)

- [Wikipedia, Mutual exclusion](https://en.wikipedia.org/wiki/Mutual_exclusion)

- [Data Race](https://stackoverflow.com/questions/34510/what-is-a-race-condition/34550#34550)

- [Valgrind User Manual, Helgrind: a thread error detector](https://cs.swan.ac.uk/~csoliver/ok-sat-library/internet_html/doc/doc/Valgrind/3.8.1/html/hg-manual.html)

- [Valgrind User Manual, DRD: a thread error detector](https://valgrind.org/docs/manual/drd-manual.html)

##### ``Linux Programmer’s Manual:``
 
- [fork (2)](https://linux.die.net/man/2/fork)

- [wait (2)](https://linux.die.net/man/2/wait)

- [kill (2)](https://linux.die.net/man/2/kill)

- [signal (7)](https://www.man7.org/linux/man-pages/man7/signal.7.html)

- [pthread_create(3) ](https://linux.die.net/man/3/pthread_create)
  
- [pthread_mutex_init/lock/unlock(3)](https://linux.die.net/man/3/pthread_mutex_init)
 
- [pthread_detach(3)](https://linux.die.net/man/3/pthread_detach)
 
- [pthread_join(3)](https://linux.die.net/man/3/pthread_join)
