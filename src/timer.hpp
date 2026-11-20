# ifndef TIMER_HPP
# define TIMER_HPP

# include <chrono>

using namespace std;
struct Timer {
    chrono :: steady_clock :: time_point inicio ;
};

void timer_iniciar ( Timer *t); /* inicia o timer */
double timer_parar ( Timer *t) ; /* retorna tempo em segundos */

# endif
