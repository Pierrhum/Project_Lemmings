#ifndef __NY_TIMER__
#define __NY_TIMER__

#include <windows.h>

#include "Element.h"

class NYTimer
{
public :
    int _MaxTime = 90;
        LARGE_INTEGER lastUpdateTime;
    LONGLONG freq;

    NYTimer()
    {
        QueryPerformanceCounter(&lastUpdateTime);
        LARGE_INTEGER li_freq;
        QueryPerformanceFrequency(&li_freq);
        freq = li_freq.QuadPart;
        freq /= 1000;
    }

    /**
     * \brief Start the timer for the first time
     */
    void start(void);
    /**
     * \brief Restart the timer, setting the new Maximum Time
     * \param MaxTime : Time in seconds allowed to complete the game
     */
    void restart(int MaxTime);

    /**
     * \brief Get the elapsed seconds since the restart
     * \return Time in seconds
     */
    float getElapsedSeconds();
    /**
     * \brief Get the elapsed milliseconds since the restart
     * \return Time in milliseconds
     */
    unsigned long getElapsedMs();
    /**
     * \brief Get the remaining time before the level ends
     * \return Time in seconds
     */
    int getRemainingTime();
    
};

#endif
