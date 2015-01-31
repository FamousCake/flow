#pragma once

 #include <time.h>

 class CStopWatch
 {

    public:

        clock_t start;
        clock_t finish;

        inline double GetDuration() { return (double)(finish - start) / CLOCKS_PER_SEC; }
        inline void Start() { this->start  = clock();    }
        inline void Stop()  { this->finish = clock(); }

}; // class CStopWatch