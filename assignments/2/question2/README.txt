2. (1) Yes a thread can still exist if the thread that created has called pthread_exit( ). pthread_exit( ) will only terminate the calling thread but not the process. The other threads still running will continue their work until the function returns, or the threads call exit or pthread_exit()
    
    (2) No a detached thread cannot exist if the main thread of the process uses exit(). Sleeping the main thread in program a2_q2_2.c for 1 second allows the detached thread created to work for that time period before the main thread calls exit(1) resulting in the thread stoping it’s counting up to 1,000,000

    (3) Any thread that calls exit() terminates the process and therefore all threads associated with that process, as is demonstrated in program a2_q2_3.c

    (4) A detached thread is still part of the same process and thus calling exit(1) from within the function the detached thread is running causes the whole process to terminate as is shown in program a2_2_4.c

    (5) No. When main falls off the last statement if pthread_exit() isn’t called the main thread will terminate killing the process, and subsequently all other threads. The program a2_2_5.c demonstrates this the the main thread is dying the process is terminated and the spawned thread stops its counting. 

Yes the main thread can detach itself by calling pthread_detach(pthread_self()) which is demonstrated in the same program.
