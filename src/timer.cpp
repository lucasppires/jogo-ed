#include "timer.hpp"

using namespace std;

void timer_iniciar ( Timer *t) {
    t -> inicio = chrono :: steady_clock :: now () ;
}
double timer_parar ( Timer *t) {
    auto fim = chrono :: steady_clock :: now () ;
    return chrono :: duration < double >( fim - t -> inicio ). count () ;
}